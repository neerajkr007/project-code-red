// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"

#include "Sound/SoundConcurrency.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"

#include "WeaponSceneComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT1_API UWeaponSceneComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponSceneComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void HandleWeaponShot();
	void SetWeaponSceneComponentForEmitter(USceneComponent* weaponSceneComponent);
		
private:

#pragma region Muzzle flash vars
	
	UPROPERTY(EditAnywhere)
	UParticleSystem* EmitterTemplate;
	UPROPERTY(EditAnywhere)
	FName AttachPointName;
	UPROPERTY(EditAnywhere)
	USceneComponent* WeaponSceneComponent;

#pragma endregion Muzzle flash vars

#pragma region Sounds Region
	
	UPROPERTY(EditAnywhere)
	USoundBase* FireSound;
	UPROPERTY(EditAnywhere)
	USoundConcurrency* FireConcurreny;

#pragma endregion Sounds Region

#pragma region Tracers
	
	ACharacter* Character;
	UWorld* World;

#pragma endregion Tracers

private:

	UFUNCTION()
	void SpawnMuzzleFlash();
	UFUNCTION()
	void PlayWeaponFiredSound();
	// for debugging
	UFUNCTION()
	void DrawLineTracers();
};
