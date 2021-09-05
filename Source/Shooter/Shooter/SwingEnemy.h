// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "SwingEnemy.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API ASwingEnemy : public AEnemy
{
	GENERATED_BODY()
public:

	ASwingEnemy();

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void ActivateLeftWeapon();
	UFUNCTION(BlueprintCallable)
		void DeactivateLeftWeapon();
	UFUNCTION(BlueprintCallable)
		void ActivateRightWeapon();
	UFUNCTION(BlueprintCallable)
		void DeactivateRightWeapon();

	UFUNCTION()
		void OnLeftWeaponOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void OnRightWeaponOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	void SpawnBlood(AShooterCharacter* Victim, FName SocketName);

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* LeftWeaponCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* RightWeaponCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		FName LeftWeaponSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		FName RightWeaponSocket;


};
