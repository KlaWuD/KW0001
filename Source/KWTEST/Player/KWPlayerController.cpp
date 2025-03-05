// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/KWPlayerController.h"

void AKWPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}