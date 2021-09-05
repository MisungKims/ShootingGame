// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "ShooterEnemy.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AShooterEnemy : public AEnemy
{
	GENERATED_BODY()
	
public:


protected:
	
	UFUNCTION(BlueprintCallable)
	void Fire();

	void PlayFireSound();

	void SendBullet();

	void PlayFireMontage(FName Section);

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	class USoundCue* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* MuzzleFlash;
};
