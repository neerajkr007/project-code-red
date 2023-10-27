// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CustomCharacter.h"
#include "CustomGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT1_API ACustomGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<ACustomCharacter> CustomDefaultPawn;

};
