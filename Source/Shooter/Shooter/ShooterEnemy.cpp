// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterEnemy.h"
#include "ShooterCharacter.h"

#include "Engine/SkeletalMeshSocket.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


void AShooterEnemy::Fire()
{
	PlayAttackMontage(GetAttackSectionName());

	PlayFireSound();

	SendBullet();
}

void AShooterEnemy::PlayFireSound()
{
	if (FireSound)
	{
		UGameplayStatics::PlaySound2D(this, FireSound);
	}
}

void AShooterEnemy::SendBullet()
{
	const USkeletalMeshSocket* BarrelSocket = GetMesh()->GetSocketByName("FX_Gun_Barrel");
	if (BarrelSocket)
	{
		const FTransform SocketTransform = BarrelSocket->GetSocketTransform(GetMesh());

		if (MuzzleFlash)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, SocketTransform);
		}

		FHitResult FireHit;
		const FVector Start{ SocketTransform.GetLocation() };
		const FQuat Rotation{ SocketTransform.GetRotation() };
		const FVector RotationAxis{ Rotation.GetAxisX() };
		const FVector End{ Target->GetActorLocation() };

		FVector BeamEndPoint{ End };
		BeamEndPoint = FireHit.Location;

		GetWorld()->LineTraceSingleByChannel(FireHit, Start, End, ECollisionChannel::ECC_Visibility);
		if (FireHit.bBlockingHit)
		{
			if (Target)
			{
				DoDamage(Target);
				if (Target->GetBloodParticle())
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Target->GetBloodParticle(), Target->GetActorLocation());
				}
			}
		}
	}
}
