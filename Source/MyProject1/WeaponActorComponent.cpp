// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponActorComponent.h"

// Sets default values for this component's properties
UWeaponActorComponent::UWeaponActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
		
	// ...
}


// Called when the game starts
void UWeaponActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UWeaponActorComponent::SpawnMuzzleFlash()
{
	UGameplayStatics::SpawnEmitterAttached(EmitterTemplate, ParentSceneComponent, AttachPointName,
		FVector::ZeroVector, FRotator::ZeroRotator, FVector::OneVector,
		EAttachLocation::KeepRelativeOffset, true, EPSCPoolMethod::None,
		true);
}

// Called every frame
void UWeaponActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

