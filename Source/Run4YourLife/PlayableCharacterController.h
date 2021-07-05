// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayableCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class RUN4YOURLIFE_API APlayableCharacterController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Widgets") //Selects UClass for widget
	TSubclassOf<class UUserWidget> HUDOverlayAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Widgets") //Holds widget after creating it
	UUserWidget* HUDOverlay;

protected:
	virtual void BeginPlay() override;
};
