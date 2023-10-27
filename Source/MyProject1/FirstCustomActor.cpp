// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstCustomActor.h"

// Sets default values
AFirstCustomActor::AFirstCustomActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	CustomActorComponent = CreateDefaultSubobject<UFirstCustomActorComponent>(TEXT("First Custom Component"));
}

// Called when the game starts or when spawned
void AFirstCustomActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("On Begin called for Actor"));
}

// Called every frame
void AFirstCustomActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

