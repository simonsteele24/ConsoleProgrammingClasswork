// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

// Sets default values
AMyPlayerController::AMyPlayerController()
{
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
		
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMyPlayerController::Jump);
	InputComponent->BindAction("SpeedBoost", IE_Pressed, this, &AMyPlayerController::ActivateSpeedBoost);
}

void AMyPlayerController::SetPlayerDataToController(AMyBallActor* myActor, AMyBallPawn* myPawn)
{

	ballPawn = myPawn;

	ballActor = myActor;
	TArray<UStaticMeshComponent*> Components;
	ballActor->GetComponents<UStaticMeshComponent>(Components);
	ballMeshComponent = Components[0];
}

// Called when the game starts or when spawned
void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPlayerController::Jump()
{
	GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Red, TEXT("JUMP"));
	if(ballPawn != nullptr)
		ballMeshComponent->AddForce(FVector(0, 0, ballPawn->currentJumpForce));
	
}
void AMyPlayerController::ActivateSpeedBoost()
{
	//Player
	UMyBlueprintFunctionLibrary::PlayerEffect(ballPawn, Boosts::SPEED);
}

void AMyPlayerController::ActivateJumpBoost()
{
}
