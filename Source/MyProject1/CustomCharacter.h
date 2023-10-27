// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/DefaultPawn.h"
#include "InputAction.h"
#include "EnhancedInputLibrary.h"

#include "CustomCharacter.generated.h"

UCLASS()
class MYPROJECT1_API ACustomCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACustomCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	//UPROPERTY(EditAnywhere)
	//UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;
	UPROPERTY(EditAnywhere)
	float MovementSpeed;
	UPROPERTY(EditAnywhere)
	float RotationSpeed;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* IMC_Default;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* IA_Move;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* IA_Rotation;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* IA_Jump;

private:

	UFUNCTION()
	void EnhancedMove(const FInputActionInstance& Instance);
	UFUNCTION()
	void EnhancedRotate(const FInputActionInstance& Instance);
	UFUNCTION()
	void EnhancedJump(const FInputActionInstance& Instance);
};
