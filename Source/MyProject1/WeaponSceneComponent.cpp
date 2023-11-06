// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSceneComponent.h"

// Sets default values for this component's properties
UWeaponSceneComponent::UWeaponSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UWeaponSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UWeaponSceneComponent::SpawnMuzzleFlash()
{
	UGameplayStatics::SpawnEmitterAttached(EmitterTemplate, WeaponSceneComponent, AttachPointName,
		FVector::ZeroVector, FRotator::ZeroRotator, FVector::OneVector,
		EAttachLocation::KeepRelativeOffset, true, EPSCPoolMethod::None,
		true);
}


void UWeaponSceneComponent::PlayWeaponFiredSound()
{
	UGameplayStatics::PlaySoundAtLocation(WeaponSceneComponent, FireSound, WeaponSceneComponent->GetComponentLocation(), FRotator::ZeroRotator, 1.F, 1.F, 0.F, nullptr, FireConcurreny, nullptr);
}

void UWeaponSceneComponent::DrawLineTracers()
{
	FHitResult CurrentHitResult(ForceInit);
	FVector StartLocation = WeaponSceneComponent->GetSocketLocation("Muzzle");
	FVector dir = WeaponSceneComponent->GetSocketRotation("Muzzle").Vector();
	FVector EndLocation = (dir * 10000) + StartLocation;
	
	this->World = GetWorld(); 
	const FName TraceTag("MyTraceTag");
	FCollisionQueryParams TraceParams(TraceTag, true, Character);
	TraceParams.bTraceComplex = true;
	GetWorld()->DebugDrawTraceTag = TraceTag;
	
	this->World->LineTraceSingleByChannel(CurrentHitResult, StartLocation, EndLocation, ECC_Visibility, TraceParams, FCollisionResponseParams::DefaultResponseParam);
	//DrawDebugLine(World, StartLocation, EndLocation, FColor::Yellow, false, 10, 0, 2.0f);
}

// Called every frame
void UWeaponSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponSceneComponent::HandleWeaponShot()
{
	SpawnMuzzleFlash();
	PlayWeaponFiredSound();
	if (Character != nullptr && Character->IsLocallyControlled())
		DrawLineTracers();
}

void UWeaponSceneComponent::SetWeaponSceneComponentForEmitter(USceneComponent* weaponSceneComponent)
{
	this->WeaponSceneComponent = weaponSceneComponent;
	Character = Cast<ACharacter>(this->WeaponSceneComponent->GetOwner());
}

