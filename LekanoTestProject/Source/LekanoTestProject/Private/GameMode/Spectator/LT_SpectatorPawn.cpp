// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/Spectator/LT_SpectatorPawn.h"

#include "Character/Player/LT_PlayerController.h"
#include "Character/Player/LT_PlayerInputActions.h"


ALT_SpectatorPawn::ALT_SpectatorPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void ALT_SpectatorPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction(FPlayerInputActionNames::AttackAction, IE_Pressed, this, &ALT_SpectatorPawn::OnPressAttackAction);
	InputComponent->BindAction(FPlayerInputActionNames::ParkourAction, IE_Pressed, this, &ALT_SpectatorPawn::OnPressParkourAction);
}

void ALT_SpectatorPawn::OnPressAttackAction()
{
	ALT_PlayerController* LPlayerController = GetController<ALT_PlayerController>();
	if( !IsValid(LPlayerController) ) return;
	
	LPlayerController->ServerViewNextPlayer();
}

void ALT_SpectatorPawn::OnPressParkourAction()
{
	ALT_PlayerController* LPlayerController = GetController<ALT_PlayerController>();
	if( !IsValid(LPlayerController) ) return;

	LPlayerController->ServerViewSelf();
}

