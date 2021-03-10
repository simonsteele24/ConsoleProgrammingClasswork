// Fill out your copyright notice in the Description page of Project Settings.


#include "Cube.h"
#include "FPSGameModeBase.h"

void ACube::ChangeToDanger() 
{
	GetStaticMeshComponent()->SetMaterial(0, DangerMaterial);
}

void ACube::BeginPlay() 
{
	GameMode = (AFPSGameModeBase*)GetWorld()->GetAuthGameMode();
	GameMode->runningLowSignature.AddUObject(this, &ACube::ChangeToDanger);
}