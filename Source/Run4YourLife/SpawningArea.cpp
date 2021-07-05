// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawningArea.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "PickUpActor.h"


// Sets default values
ASpawningArea::ASpawningArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawningAreaBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));

}

// Called when the game starts or when spawned
void ASpawningArea::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawningArea::SpawnPickUp, TimeToNextSpawn, true);
}

// Called every frame
void ASpawningArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Get random point in box component
FVector ASpawningArea::GetSpawnPoint()
{
	FVector BoxExtent = SpawningAreaBox->GetScaledBoxExtent();
	FVector BoxOrigin = SpawningAreaBox->GetComponentLocation();

	FVector RandomSpawnPoint = UKismetMathLibrary::RandomPointInBoundingBox(BoxOrigin, BoxExtent);

	return RandomSpawnPoint;
}

//Spawn pick-up in world
void ASpawningArea::SpawnPickUp()
{
	UWorld* World = GetWorld();
	FActorSpawnParameters SpawnParams;
	FVector SpawnLocation = GetSpawnPoint();

	APickUpActor* SpawnedPickUp = World->SpawnActor<APickUpActor>(SpawningActor, SpawnLocation, FRotator(0.0f), SpawnParams);

}
