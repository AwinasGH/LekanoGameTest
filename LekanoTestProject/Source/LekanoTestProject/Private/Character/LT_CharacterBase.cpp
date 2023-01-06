// Fill out your copyright notice in the Description page of Project Settings.


#include "LekanoTestProject/Public/Character/LT_CharacterBase.h"

#include "Camera/CameraComponent.h"
#include "Character/Components/LT_MovementComponent.h"
#include "Components/CapsuleComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "GameMode/LT_GameInstance.h"


ALT_CharacterBase::ALT_CharacterBase(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer.SetDefaultSubobjectClass<ULT_MovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = false;

	//..............................Set components.................................//

	CharacterMovementComponent = Cast<ULT_MovementComponent>(GetCharacterMovement());

	AddDefaultComponent(SpringArmComponent, USpringArmComponent, "SpringArmComponent", false)
	SpringArmComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
	SpringArmComponent->SocketOffset = FVector(0, 50, 50);
	SpringArmComponent->SetRelativeLocation(FVector(0, 0, 100));
	SpringArmComponent->bUsePawnControlRotation = true;

	AddDefaultComponent(ThirdPersonCameraComponent, UCameraComponent, "ThirdPersonCameraComponent", false)
	ThirdPersonCameraComponent->AttachToComponent(SpringArmComponent, FAttachmentTransformRules::KeepRelativeTransform, USpringArmComponent::SocketName);
	ThirdPersonCameraComponent->bUsePawnControlRotation = false;
	ThirdPersonCameraComponent->SetActive(true);
	

	//.............................................................................//
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	bCanAffectNavigationGeneration = true;
	
	GetMesh()->SetGenerateOverlapEvents(true);

	
	CharacterMovementComponent->bOrientRotationToMovement = true;
	CharacterMovementComponent->bCanWalkOffLedgesWhenCrouching = true;
	CharacterMovementComponent->bUseControllerDesiredRotation = true;

	CharacterMovementComponent->bMaintainHorizontalGroundVelocity = false;
	
	CharacterMovementComponent->MaxAcceleration = 900;
}

void ALT_CharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ALT_CharacterBase::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<ULT_GameInstance>(GetGameInstance());
}

void ALT_CharacterBase::DoJump_Implementation()
{
	if( GetMovementComponent()->IsCrouching() || GetMovementComponent()->IsFalling() || GetMovementComponent()->IsSwimming() ) return;

	DoJump_ServerToAll();
}

void ALT_CharacterBase::DoJump_ServerToAll_Implementation()
{
	Jump();

	DoJumpSound();
}



