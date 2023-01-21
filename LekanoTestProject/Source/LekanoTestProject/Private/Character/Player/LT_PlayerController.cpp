// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/LT_PlayerController.h"

#include "Character/Player/LT_PlayerCharacter.h"
#include "GameFramework/SpectatorPawn.h"

#include "GameMode/LT_GameHUD.h"
#include "GameMode/LT_GameState.h"


ALT_PlayerController::ALT_PlayerController()
{
	bReplicates = true;
}


void ALT_PlayerController::OnRep_Pawn()
{
	Super::OnRep_Pawn();
	
	if (GetStateName() == NAME_Spectating)
	{
		AutoManageActiveCameraTarget(GetSpectatorPawn());
	}
}

APlayerState* ALT_PlayerController::GetNextViewablePlayer(int32 dir)
{
	APlayerState* LPlayerState = Super::GetNextViewablePlayer(dir);
	if( !IsValid(LPlayerState) ) return nullptr;

	return LPlayerState->IsSpectator() ? nullptr : LPlayerState;
}


void ALT_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	MyGameHUD = Cast<ALT_GameHUD>(GetHUD());

	SetInputMode(FInputModeGameOnly());

	ALT_GameState* LGameState = Cast<ALT_GameState>(GetWorld()->GetGameState());
	if( !IsValid(LGameState) ) return;

	LGameState->OnInGameMatchStateChangedBind.AddDynamic(this, &ALT_PlayerController::OnInGameMatchStateChanged);
}

void ALT_PlayerController::OnInGameMatchStateChanged_Implementation(const EInGameMatchState NewMatchState)
{
	if( NewMatchState == EInGameMatchState::Ended )
	{
		if( IsValid(MyGameHUD) ) MyGameHUD->CreateScoreBoardWD();
	}
}



