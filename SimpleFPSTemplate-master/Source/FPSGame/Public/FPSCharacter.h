// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class AFPSProjectile;
class USoundBase;
class UAnimSequence;
class AFPSBombActor;


UCLASS()
class AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	/** Pawn mesh: 1st person view  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh")
	USkeletalMeshComponent* Mesh1PComponent;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* GunMeshComponent;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	TArray<class AActor*> ActorsToDestroy;

public:
	AFPSCharacter();

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	TSubclassOf<AFPSProjectile> ProjectileClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AFPSProjectile> SpecialProjectileClass;

	/** Bomb class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = "Bombs")
	TSubclassOf<AFPSBombActor> BombClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	UAnimSequence* FireAnimation;

	/* Particle System to represent the explosion effect */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	class UParticleSystem* ExplosionEffect;

	UPROPERTY(EditAnywhere)
	float FireCooldown = 2.0f;

	void PlayExplosionEffect(float _Scale, const FVector& Location);

protected:
	
	// When I press right button
	UFUNCTION() void BeginDestructionSequence();

	// Iterate over array and explode them at different sizes
	UFUNCTION() void ActivateDestructionSequence();

	/** Fires a projectile. */
	void Fire();

	/** Drops a bomb. */
	void SpawnBomb();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	void SpawnSpecial();

	/** Handles strafing movement, left and right */
	void MoveRight(float Val);

	void StopCooldown();

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	FTimerHandle MemberTimerHandle;
	bool bCanFireSpecial = true;

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1PComponent; }

	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return CameraComponent; }

};

