// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSBombActor.h"
#include "..\Public\FPSBombActor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Components/PrimitiveComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
AFPSBombActor::AFPSBombActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	meshComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	RootComponent = meshComp;

	explodeDelay = 2.0f;
}

void AFPSBombActor::Explode()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, explosionTemplate, GetActorLocation());

	FCollisionObjectQueryParams queryParams;
	queryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	queryParams.AddObjectTypesToQuery(ECC_PhysicsBody);

	FCollisionShape collShape;
	collShape.SetSphere(500.0f);

	TArray<FOverlapResult> outOverlaps;
	GetWorld()->OverlapMultiByObjectType(outOverlaps, GetActorLocation(), FQuat::Identity, queryParams, collShape);

	for (FOverlapResult result : outOverlaps)
	{
		UPrimitiveComponent* overlap = result.GetComponent();
		if (overlap && overlap->IsSimulatingPhysics())
		{
			UMaterialInstanceDynamic* matInst = overlap->CreateAndSetMaterialInstanceDynamic(0);
			if (matInst)
			{
				matInst->SetVectorParameterValue("Color", targetColor);
			}
		}
	}
	Destroy();
}

// Called when the game starts or when spawned
void AFPSBombActor::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle Explode_TimerHandle;
	GetWorldTimerManager().SetTimer(Explode_TimerHandle,this,&AFPSBombActor::Explode,explodeDelay);

	materialInst = meshComp->CreateAndSetMaterialInstanceDynamic(0);

	if (materialInst)
	{
		currentColor = materialInst->K2_GetVectorParameterValue("Color");
	}
	targetColor = FLinearColor::MakeRandomColor();

}

// Called every frame
void AFPSBombActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (materialInst)
	{
		float progress = (GetWorld()->TimeSeconds - CreationTime) / explodeDelay;

		FLinearColor newColor = FLinearColor::LerpUsingHSV(currentColor,targetColor,progress);

		materialInst->SetVectorParameterValue("Color", newColor);
	}
		
}

