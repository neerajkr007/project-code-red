// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCharacter.h"
#include "MyProject1.h"
#include "EnhancedInputComponent.h" 
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Math/UnrealMathUtility.h"
#include "Net/UnrealNetwork.h"
#include "Misc/Timespan.h"
#include "Runtime/Net/Core/Public/Net/Core/PushModel/PushModel.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

// Sets default values
ACustomCharacter::ACustomCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);

	//StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Player Mesh"));
	//StaticMesh->SetupAttachment(RootComponent);
#pragma region Actors Instantiation

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	WeaponSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Skelton Mesh"));
	WeaponSkeletalMeshComponent->SetupAttachment(GetMesh(), TEXT("weapon_r"));

#pragma endregion Actors Instantiation

	WeaponSceneComponent = CreateDefaultSubobject<UWeaponSceneComponent>(TEXT("Weapon Scene Component"));
	WeaponSceneComponent->SetupAttachment(WeaponSkeletalMeshComponent);

	USceneComponent* SceneComponent = Cast<USceneComponent>(WeaponSkeletalMeshComponent);
	if (SceneComponent)
	{
		WeaponSceneComponent->SetWeaponSceneComponentForEmitter(SceneComponent);
	}
}

void ACustomCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;

	//DOREPLIFETIME_WITH_PARAMS_FAST(ACustomCharacter, testVar, SharedParams);
}

// Called when the game starts or when spawned
void ACustomCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (auto PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC_Default, 0);
		}
	}

	CurrentMovementSpeed = WalkSpeed;
	IfSprintKeyOnHold = false;
	GetCharacterMovement()->MaxWalkSpeed = 400; 
}

void ACustomCharacter::Server_ADSStateChangedOnClient_Implementation(bool isAds)
{	
	MultiCast_ADSStateChangedOnServer(isAds);
}

void ACustomCharacter::MultiCast_ADSStateChangedOnServer_Implementation(bool isAds)
{
	// Animations auto detect this var change so we just need to set the var here
	IfAds = isAds;
}

void ACustomCharacter::Server_SprintStateChangedOnClient_Implementation(bool ifSprintKeyOnHold)
{
	HandleSprintStatusOnClient(ifSprintKeyOnHold);
}

void ACustomCharacter::Server_ShotFiredOnClient_Implementation()
{
	MultiCast_ShotFiredOnServer();
}

void ACustomCharacter::MultiCast_ShotFiredOnServer_Implementation()
{
	if (HasAuthority() || IsLocallyControlled())
		return;
	WeaponSceneComponent->HandleWeaponShot();
}

// Called every frame
void ACustomCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACustomCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	Input->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ACustomCharacter::EnhancedMove);
	Input->BindAction(IA_Rotation, ETriggerEvent::Triggered, this, &ACustomCharacter::EnhancedRotate);
	Input->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	Input->BindAction(IA_Sprint, ETriggerEvent::Triggered, this, &ACustomCharacter::EnhancedSprint);
	Input->BindAction(IA_ADS, ETriggerEvent::Triggered, this, &ACustomCharacter::EnhancedAds);
	Input->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &ACustomCharacter::EnhancedFire);
}

void ACustomCharacter::EnhancedMove(const FInputActionInstance& Instance)
{
	FVector2D AxisValues = Instance.GetValue().Get<FVector2D>();

	FVector input = (GetActorRightVector() * AxisValues.X + GetActorForwardVector() * AxisValues.Y) * CurrentMovementSpeed;

	AddMovementInput(input);
	//LOG("current speed is %s", *FString::SanitizeFloat(GetVelocity().Length()));
}

void ACustomCharacter::EnhancedRotate(const FInputActionInstance& Instance)
{
	FVector2D AxisValues = Instance.GetValue().Get<FVector2D>();
	AddControllerYawInput(AxisValues.X * RotationSpeed);
	AddControllerPitchInput(AxisValues.Y * RotationSpeed);
}

void ACustomCharacter::EnhancedSprint(const FInputActionInstance& Instance)
{
	// set value locally and send RPC to server
	HandleSprintStatusOnClient(Instance.GetValue().Get<bool>());
	Server_SprintStateChangedOnClient(IfSprintKeyOnHold);
	//LOG("sprint event toggled to %s", *FString(IfSprintKeyOnHold ? "true" : "false"));
}

void ACustomCharacter::EnhancedAds(const FInputActionInstance& Instance)
{
	// set value locally and send RPC to server
	IfAds = Instance.GetValue().Get<bool>();
	Server_ADSStateChangedOnClient(IfAds);

	// handle movement depending on ads from here 
	HandleSprintStatusOnClient(IfSprintKeyOnHold);
	Server_SprintStateChangedOnClient(IfSprintKeyOnHold);
}

void ACustomCharacter::EnhancedFire(const FInputActionInstance& Instance)
{
	Server_ShotFiredOnClient();
	WeaponSceneComponent->HandleWeaponShot();
}

void ACustomCharacter::HandleSprintStatusOnClient(bool isSprintKeyOnHold)
{
	IfSprintKeyOnHold = isSprintKeyOnHold;
	if (IfAds)
	{
		CurrentMovementSpeed = WalkSpeed * 2 / 3;
		GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeedWhenWalking * 2 / 3;
	}
	else
	{
		if (IfSprintKeyOnHold)
		{
			CurrentMovementSpeed = SprintSpeed;
			GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeedWhenSprinting;
		}
		else
		{
			CurrentMovementSpeed = WalkSpeed;
			GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeedWhenWalking;
		}
	}
}

