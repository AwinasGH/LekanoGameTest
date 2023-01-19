// Fill out your copyright notice in the Description page of Project Settings.


#include "LekanoTestProject/Public/Character/LT_CharacterBase.h"

#include "Character/Components/LT_MovementComponent.h"
#include "Components/CapsuleComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "GameMode/LT_GameInstance.h"

#include "GameFramework/PlayerState.h"
#include "GameMode/LT_GameState.h"
#include "GameMode/LT_PlayerState.h"
#include "Net/UnrealNetwork.h"


ALT_CharacterBase::ALT_CharacterBase(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer.SetDefaultSubobjectClass<ULT_MovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = false;

	//..............................Set components.................................//

	CharacterMovementComponent = Cast<ULT_MovementComponent>(GetCharacterMovement());

	//.............................................................................//\
	
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

	DOREPLIFETIME(ALT_CharacterBase, CanMove);
	DOREPLIFETIME(ALT_CharacterBase, WalkSpeed);
	DOREPLIFETIME(ALT_CharacterBase, JogSpeed);
	DOREPLIFETIME(ALT_CharacterBase, SprintSpeed);
	DOREPLIFETIME(ALT_CharacterBase, MovingAcceleration);
}

void ALT_CharacterBase::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<ULT_GameInstance>(GetGameInstance());

	ALT_GameState* LGameState = Cast<ALT_GameState>(GetWorld()->GetGameState());
	if( !IsValid(LGameState) ) return;

	ALT_PlayerState* LPlayerState = Cast<ALT_PlayerState>(GetPlayerState());
	if( IsValid(LPlayerState) ) LPlayerState->SetIsDead(false);

	LGameState->OnInGameMatchStateChangedBind.AddDynamic(this, &ALT_CharacterBase::OnInGameMatchStateChanged);
}


void ALT_CharacterBase::Destroyed()
{
	if( GetLocalRole() < ROLE_Authority ) return;
	
	if( APlayerController* LPlayerController = Cast<APlayerController>(Controller) )
	{
		LPlayerController->ChangeState(NAME_Spectating);
		LPlayerController->ClientGotoState(NAME_Spectating);

		ALT_PlayerState* LPlayerState = Cast<ALT_PlayerState>(LPlayerController->PlayerState);
		if( IsValid(LPlayerState) )
		{
			LPlayerState->SetIsDead(true);
		}
	}

	Super::Destroyed();
}


void ALT_CharacterBase::OnInGameMatchStateChanged_Implementation(const EInGameMatchState NewMatchState)
{
	if( NewMatchState == EInGameMatchState::Preparation )
	{
		this->SetCanMove(false);
	}
	else if( NewMatchState == EInGameMatchState::InProgress )
	{
		this->SetCanMove(true);
	}
}


void ALT_CharacterBase::DoJump_Implementation()
{
	if( GetMovementComponent()->IsCrouching() || GetMovementComponent()->IsFalling() || GetMovementComponent()->IsSwimming() ) return;

	DoJump_ServerToAll();
}

void ALT_CharacterBase::DoJump_ServerToAll_Implementation()
{
	Jump();
}



