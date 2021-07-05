// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpActor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Sound/SoundCue.h"
#include "PlayableCharacter.h"

// Sets default values
APickUpActor::APickUpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickUpCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PickUpCollisionBox"));
	RootComponent = PickUpCollisionBox;

	PickUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickUpMesh"));
	PickUpMesh->SetupAttachment(GetRootComponent());

	IdleParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("IdleParticleSystem"));
	IdleParticleSystem->SetupAttachment(GetRootComponent());

	bRotating = true;
	RotationRate = 45.0f;
}

// Called when the game starts or when spawned
void APickUpActor::BeginPlay()
{
	Super::BeginPlay();
	
	PickUpCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APickUpActor::PickUpOverlap);
}

// Called every frame
void APickUpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRotating)
	{
		FRotator Rotation = GetActorRotation();
		Rotation.Yaw += DeltaTime * RotationRate;
		SetActorRotation(Rotation);
	}
}

void APickUpActor::PickUpOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this && OtherComp)
	{
		APlayableCharacter* Player = Cast<APlayableCharacter>(OtherActor);
		if (Player)
		{
			if (Player->PlayerHealth <= 0.0f) Player->PlayerHealth += 0.0;
			else
			{
				Player->PlayerScore += 150;
				if (Player->PlayerHealth + 70 >= Player->PlayerMaxHealth) Player->PlayerHealth = Player->PlayerMaxHealth;
				else Player->PlayerHealth += 70;

				if (OverlapParticles)
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OverlapParticles, GetActorLocation(), FRotator(0.0f), false);
				}
				if (OverlapSound)
				{
					UGameplayStatics::PlaySound2D(this, OverlapSound, 1.0f);
				}
				Destroy();
			}
		}
	}
}

