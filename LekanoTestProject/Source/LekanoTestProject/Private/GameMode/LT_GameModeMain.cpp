// Fill out your copyright notice in the Description page of Project Settings.

#include "LekanoTestProject/Public/GameMode/LT_GameModeMain.h"

#include "GameMode/LT_GameState.h"
#include "GameMode/LT_PlayerState.h"
#include "LekanoTestProject/Public/Character/Player/LT_PlayerController.h"


ALT_GameModeMain::ALT_GameModeMain()
{
	bStartPlayersAsSpectators = true;
	bUseSeamlessTravel = false;

	PlayerControllerClass = ALT_PlayerController::StaticClass();
	GameStateClass = ALT_GameState::StaticClass();
	PlayerStateClass = ALT_PlayerState::StaticClass();
}


void ALT_GameModeMain::BeginPlay()
{
	Super::BeginPlay();

	ALT_GameState* LGameState = GetGameState<ALT_GameState>();
	if( !IsValid(LGameState) ) return;

	LGameState->OnInGameMatchStateChangedBind.AddDynamic(this, &ALT_GameModeMain::OnInGameMatchStateChanged);
}

bool ALT_GameModeMain::ReadyToStartMatch_Implementation()
{
	if ( bDelayedStart ) return false;
	
	if (GetMatchState() == MatchState::WaitingToStart)
	{
		if (NumPlayers >= MinPlayersNumToStartMatch) return true;
	}
	
	return false;
}

void ALT_GameModeMain::OnInGameMatchStateChanged_Implementation(const EInGameMatchState NewMatchState)
{
	if( NewMatchState == EInGameMatchState::Ended )
	{
		ALT_GameState* LGameState = GetGameState<ALT_GameState>();
		if( !IsValid(LGameState) ) return;

		for( const auto& Player : LGameState->PlayerArray )
		{
			if( Player->GetPawn() ) Player->GetPawn()->Destroy();
		}
	}
}

