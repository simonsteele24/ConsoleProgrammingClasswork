// Fill out your copyright notice in the Description page of Project Settings.


#include "Cube.h"
#include "FPSGameModeBase.h"
#include "GameManagerActor.h"
#include "Kismet/GameplayStatics.h"


// Changes the cube to the running low material
void ACube::ChangeToDanger() 
{
	GetStaticMeshComponent()->SetMaterial(0, DangerMaterial);
}

void ACube::BeginPlay() 
{
	
}