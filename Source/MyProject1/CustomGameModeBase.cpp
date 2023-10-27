// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameModeBase.h"

void ACustomGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	if(DefaultPawnClass == NULL || DefaultPawnClass == ADefaultPawn::StaticClass())
		DefaultPawnClass = CustomDefaultPawn;
}
