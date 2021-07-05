// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimSequence.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APlayableCharacter::APlayableCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // Rotate at this rate
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.2f;

	PlayerSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerSkeletalMesh"));
	PlayerSkeletalMesh->SetupAttachment(RootComponent);

	CameraDistance = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraDistance"));
	CameraDistance->SetupAttachment(RootComponent);
	CameraDistance->TargetArmLength = 450.0f;
	CameraDistance->bUsePawnControlRotation = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(CameraDistance, USpringArmComponent::SocketName);
	PlayerCamera->bUsePawnControlRotation = false;

	bIsDead = false;

	PlayerMaxHealth = 800.0f;
	PlayerHealth = PlayerMaxHealth;

	PlayerScore = 0;

	static ConstructorHelpers::FObjectFinder<UAnimSequence> DeathAnimation(TEXT("AnimSequence'/Game/CharacterAnimations/Falling_Back_Death.Falling_Back_Death'"));
	CharacterDeathAnim = DeathAnimation.Object;
}

// Called when the game starts or when spawned
void APlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerHealth > 0.0) 
	{
		PlayerHealth -= 60.0 * DeltaTime;
		PlayerScore += 10.0 * DeltaTime;
	}
	else {
		SetActorTickEnabled(false);
		GetMovementComponent()->SetJumpAllowed(false);
		bIsDead = true;
		PlayerSkeletalMesh->PlayAnimation(CharacterDeathAnim, false);
		GetWorldTimerManager().SetTimer(OpenLevelTimer, this, &APlayableCharacter::OpenLevel, 4.0f, false);
	}
}

void APlayableCharacter::OpenLevel()
{
	UGameplayStatics::OpenLevel(this, FName("Run4YourLifeMap"), false);
}

void APlayableCharacter::SetIsDeadTrue() 
{
	bIsDead = true;
}

void APlayableCharacter::MoveForward(float value)
{
	if ((Controller) && (value != 0.0f) && !bIsDead)
	{
		const FRotator ControllerRotation = Controller->GetControlRotation();
		const FRotator YawRotation = FRotator(0.0f, ControllerRotation.Yaw, 0.0f);

		//Find forward vector of character
		const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(ForwardVector, value);
	}
}

void APlayableCharacter::MoveRight(float value)
{
	if ((Controller) && (value != 0.0f) && !bIsDead)
	{
		const FRotator ControllerRotation = Controller->GetControlRotation();
		const FRotator YawRotation = FRotator(0.0f, ControllerRotation.Yaw, 0.0f);

		//Find forward vector of character
		const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardVector, value);
	}
}

// Called to bind functionality to input
void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Handles character rotation and look up mouse input
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	//Handles character keyboard movement input
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayableCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayableCharacter::MoveRight);

	//Handles character jumping keyboard input
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

}



