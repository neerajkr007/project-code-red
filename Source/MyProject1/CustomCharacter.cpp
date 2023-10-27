// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCharacter.h"
#include "MyProject1.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
ACustomCharacter::ACustomCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Player Mesh"));
	//StaticMesh->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	CameraComponent->SetupAttachment(RootComponent);
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
}

void ACustomCharacter::EnhancedMove(const FInputActionInstance& Instance)
{
	FVector2D AxisValues = Instance.GetValue().Get<FVector2D>();
	AddMovementInput((GetActorRightVector() * AxisValues.X + GetActorForwardVector() * AxisValues.Y) * MovementSpeed);
}

void ACustomCharacter::EnhancedRotate(const FInputActionInstance& Instance)
{
	FVector2D AxisValues = Instance.GetValue().Get<FVector2D>();
	AddControllerYawInput(AxisValues.X * RotationSpeed);
	AddControllerPitchInput(AxisValues.Y * RotationSpeed);
}

void ACustomCharacter::EnhancedJump(const FInputActionInstance& Instance)
{

}

