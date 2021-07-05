// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpActor.generated.h"

UCLASS()
class RUN4YOURLIFE_API APickUpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp Specs")
	class UBoxComponent* PickUpCollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp Specs")
	class UStaticMeshComponent* PickUpMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp Specs")
	class UParticleSystemComponent* IdleParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp Specs")
	class UParticleSystem* OverlapParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp Specs")
	class USoundCue* OverlapSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp Specs")
	bool bRotating;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp Specs")
	float RotationRate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void PickUpOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
