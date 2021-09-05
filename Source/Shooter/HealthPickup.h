// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthPickup.generated.h"

UCLASS()
class SHOOTER_API AHealthPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthPickup();

	UFUNCTION()
	void ShpereOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Healing, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* HealthMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Healing, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* OverlapSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Healing, meta = (AllowPrivateAccess = "true"))
	float HealingAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Healing, meta = (AllowPrivateAccess = "true"))
	class USoundCue* HealthPickupSound;

	UFUNCTION(BlueprintImplementableEvent)
	void Healing();

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	bool bRotate;

	float RotationRate;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
