// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstCustomActorComponent.h"

// Sets default values for this component's properties
UFirstCustomActorComponent::UFirstCustomActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFirstCustomActorComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("On Begin called for component"));

	// ...
	
}


// Called every frame
void UFirstCustomActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

