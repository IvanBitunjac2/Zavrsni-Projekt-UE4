// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayableCharacter.generated.h"

UCLASS()
class RUN4YOURLIFE_API APlayableCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayableCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Camera")
	class USpringArmComponent* CameraDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Camera")
	class UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Specs")
	class USkeletalMeshComponent* PlayerSkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Widgets") //Selects UClass for widget
	TSubclassOf<class UUserWidget> HUDOverlayAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Widgets") //Holds widget after creating it
	UUserWidget* HUDOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Specs")
	class UAnimSequence* CharacterDeathAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Specs")
	float PlayerMaxHealth;

	UPROPERTY(BlueprintReadWrite)
	float PlayerScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Specs")
	float PlayerHealth;

	bool bIsRunning;

	bool bIsIdle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player State")
	bool bIsDead;

	FTimerHandle OpenLevelTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void MoveForward(float value);
	void MoveRight(float value);
	
	void SetIsDeadTrue();

	void OpenLevel();
};
