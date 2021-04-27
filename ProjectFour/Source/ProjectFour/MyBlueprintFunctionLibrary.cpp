// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"

void UMyBlueprintFunctionLibrary::PlayerEffect(UObject* object,Boosts type)
{
	AMyBallPawn* ballPawn = Cast<AMyBallPawn>(object);
	if (ballPawn != NULL)
	{
		switch (type)
		{
		case Boosts::SPEED:
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Speed"));
			if (ballPawn->currentBallSpeed < ballPawn->boostedSpeed)
			{
				ballPawn->currentBallSpeed = ballPawn->boostedSpeed;
			}
			break;

		case Boosts::JUMP:
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Jump"));
			if (ballPawn->currentJumpForce < ballPawn->boostedJumpForce)
			{
				ballPawn->currentBallSpeed = ballPawn->boostedSpeed;
			}
			break;

		case Boosts::CONTROL:
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Control"));
			break;
		}
	}
	
}
