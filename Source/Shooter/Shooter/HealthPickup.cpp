// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickup.h"
#include "ShooterCharacter.h"

#include "Components/SphereComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AHealthPickup::AHealthPickup() :
	HealingAmount(20.f),
	bRotate(true),
	RotationRate(45.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HealthMesh"));
	SetRootComponent(HealthMesh);

	OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	OverlapSphere->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AHealthPickup::BeginPlay()
{
	Super::BeginPlay();

	OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &AHealthPickup::ShpereOverlap);
}

void AHealthPickup::ShpereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr) return;

	AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(OtherActor);
	if (ShooterCharacter)
	{
		Healing();

		if (HealthPickupSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HealthPickupSound, GetActorLocation());
		}

		Destroy();
	}
}

// Called every frame
void AHealthPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRotate)
	{
		FRotator Rotation = GetActorRotation();
		Rotation.Yaw += DeltaTime * RotationRate;
		SetActorRotation(Rotation);
	}
}

