// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawningArea.generated.h"

UCLASS()
class RUN4YOURLIFE_API ASpawningArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawningArea();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	class UBoxComponent* SpawningAreaBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<class APickUpActor> SpawningActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float TimeToNextSpawn;

	FTimerHandle SpawnTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector GetSpawnPoint();

	void SpawnPickUp();
};
