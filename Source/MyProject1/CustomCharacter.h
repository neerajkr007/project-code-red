// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/DefaultPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputAction.h"
#include "EnhancedInputLibrary.h"
#include "WeaponSceneComponent.h"

#include "CustomCharacter.generated.h"

UCLASS()
class MYPROJECT1_API ACustomCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACustomCharacter();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_ADSStateChangedOnClient(bool isAds);
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void MultiCast_ADSStateChangedOnServer(bool isAds);

	
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_SprintStateChangedOnClient(bool ifSprintKeyOnHold);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_ShotFiredOnClient();
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void MultiCast_ShotFiredOnServer();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	bool IfSprintKeyOnHold;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	bool IfAds;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
public:

private:

#pragma region Actors
	
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* WeaponSkeletalMeshComponent;

#pragma endregion Actors

#pragma region Actor Components

	UPROPERTY(EditAnywhere)
	UWeaponSceneComponent* WeaponSceneComponent;

#pragma endregion Actor Components

#pragma region Movement Vars
	
	UPROPERTY(EditAnywhere)
	float WalkSpeed;
	UPROPERTY(EditAnywhere)
	float SprintSpeed;
	UPROPERTY(EditAnywhere)
	float RotationSpeed;
	UPROPERTY(EditAnywhere)
	float MaxWalkSpeedWhenWalking;
	UPROPERTY(EditAnywhere)
	float MaxWalkSpeedWhenSprinting;

#pragma endregion Movement Vars

#pragma region Input Actions

	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* IMC_Default;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* IA_Move;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* IA_Rotation;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* IA_Jump;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* IA_Sprint;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* IA_ADS;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* IA_Fire;

#pragma endregion Input Actions

	float CurrentMovementSpeed;


private:

	UFUNCTION()
	void EnhancedMove(const FInputActionInstance& Instance);
	UFUNCTION()
	void EnhancedRotate(const FInputActionInstance& Instance);
	UFUNCTION()
	void EnhancedSprint(const FInputActionInstance& Instance);
	UFUNCTION()
	void EnhancedAds(const FInputActionInstance& Instance);
	UFUNCTION()
	void EnhancedFire(const FInputActionInstance& Instance);

	UFUNCTION()
	void HandleSprintStatusOnClient(bool isSprintKeyOnHold);
};
