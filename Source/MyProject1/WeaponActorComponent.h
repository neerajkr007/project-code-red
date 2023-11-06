// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"

#include "Kismet/GameplayStatics.h"

#include "WeaponActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT1_API UWeaponActorComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SpawnMuzzleFlash();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	
	UPROPERTY(EditAnywhere)
	USceneComponent* ParentSceneComponent;
		
private:

	UPROPERTY(EditAnywhere)
	UParticleSystem* EmitterTemplate;
	UPROPERTY(EditAnywhere)
	FName AttachPointName;

};
