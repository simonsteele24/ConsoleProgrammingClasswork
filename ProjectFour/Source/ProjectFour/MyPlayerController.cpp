// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

// Sets default values
AMyPlayerController::AMyPlayerController()
{
}

void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
		
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMyPlayerController::Jump);
	InputComponent->BindAxis("MoveForward", this, &AMyPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyPlayerController::MoveRight);
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
	ballPawn->speedBoosted = true;
}

void AMyPlayerController::ActivateJumpBoost()
{
	UMyBlueprintFunctionLibrary::PlayerEffect(ballPawn, Boosts::JUMP);
	ballPawn->jumpBoosted = true;
}

void AMyPlayerController::MoveForward(float input) 
{
	if (ballActor != nullptr && ballPawn != nullptr) 
	{
		ballMeshComponent->AddForce(ballPawn->currentBallSpeed * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * input * FVector(ballPawn->GetCameraForwardVector().X, ballPawn->GetCameraForwardVector().Y, 0));
	}
}

void AMyPlayerController::MoveRight(float input) 
{
	if (ballActor != nullptr && ballPawn != nullptr)
	{
		ballMeshComponent->AddForce(ballPawn->currentBallSpeed * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * input * FVector(ballPawn->GetCameraRightVector().X, ballPawn->GetCameraRightVector().Y, 0));
	}
}