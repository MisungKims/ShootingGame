// Fill out your copyright notice in the Description page of Project Settings.


#include "SwingEnemy.h"
#include "ShooterCharacter.h"

#include "Engine/SkeletalMeshSocket.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

ASwingEnemy::ASwingEnemy() :
	LeftWeaponSocket(TEXT("FX_Trail_L_01")),
	RightWeaponSocket(TEXT("FX_Trail_R_01"))
{
	LeftWeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftWeaponCollision"));
	LeftWeaponCollision->SetupAttachment(GetMesh(), FName("LeftWeaponBone"));

	RightWeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("RightWeaponCollision"));
	RightWeaponCollision->SetupAttachment(GetMesh(), FName("RightWeaponBone"));
}

void ASwingEnemy::BeginPlay()
{
	Super::BeginPlay();

	LeftWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftWeaponCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	LeftWeaponCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	LeftWeaponCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	RightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightWeaponCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	RightWeaponCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	RightWeaponCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	LeftWeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &ASwingEnemy::OnLeftWeaponOverlap);
	RightWeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &ASwingEnemy::OnRightWeaponOverlap);


}

void ASwingEnemy::OnLeftWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap"));
	auto Character = Cast<AShooterCharacter>(OtherActor);
	if (Character)
	{
		if (GetAttacking())
		{
			DoDamage(Character);
			SpawnBlood(Character, LeftWeaponSocket);
		}
	}
}

void ASwingEnemy::OnRightWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Character = Cast<AShooterCharacter>(OtherActor);
	if (Character)
	{
		if (GetAttacking())
		{
			DoDamage(Character);
			SpawnBlood(Character, RightWeaponSocket);
		}
	}
}


void ASwingEnemy::SpawnBlood(AShooterCharacter* Victim, FName SocketName)
{
	const USkeletalMeshSocket* TipSocket{ GetMesh()->GetSocketByName(SocketName) };
	if (TipSocket)
	{
		const FTransform SocketTransform{ TipSocket->GetSocketTransform(GetMesh()) };
		if (Victim->GetBloodParticle())
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Victim->GetBloodParticle(), SocketTransform);
		}
	}
}


void ASwingEnemy::ActivateLeftWeapon()
{
	LeftWeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ASwingEnemy::DeactivateLeftWeapon()
{
	LeftWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASwingEnemy::ActivateRightWeapon()
{
	RightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ASwingEnemy::DeactivateRightWeapon()
{
	RightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}