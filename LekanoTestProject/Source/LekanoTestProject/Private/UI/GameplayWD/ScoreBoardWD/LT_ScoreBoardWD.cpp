// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameplayWD/ScoreBoardWD/LT_ScoreBoardWD.h"

#include "Components/ScrollBox.h"
#include "GameMode/LT_GameState.h"
#include "GameMode/LT_PlayerState.h"
#include "UI/GameplayWD/ScoreBoardWD/PlayerScoreWD/LT_PlayerScoreWD.h"

ULT_ScoreBoardWD::ULT_ScoreBoardWD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsFocusable = true;
}

void ULT_ScoreBoardWD::InitializeScoreBoardWD(ALT_GameHUD* GameHUD)
{
	MyGameHUD = GameHUD;
}

void ULT_ScoreBoardWD::NativeConstruct()
{
	Super::NativeConstruct();

	ALT_GameState* LGameState = Cast<ALT_GameState>(GetWorld()->GetGameState());
	if( !IsValid(LGameState) ) return;

	if( IsValid(PlayersScrollBox) ) PlayersScrollBox->ClearChildren();

	if( PlayerScoreWDClass.IsNull() ) return;
	

	TArray<ALT_PlayerState*> Finalists;														//TODO Make as variable in GameState
	for( const auto& BasePlayerState : LGameState->PlayerArray )
	{
		if( ALT_PlayerState* LPlayerState = Cast<ALT_PlayerState>(BasePlayerState) )
		{
			if( LPlayerState->GetHasFinished() == true ) Finalists.Add(LPlayerState);
		}
	}
	Algo::Sort(Finalists, [](const ALT_PlayerState* A, const ALT_PlayerState* B)
	{
		return A->GetScore() < B->GetScore();
	});

	for(const auto& BasePlayerState : Finalists)
	{
		if( ALT_PlayerState* LPlayerState = Cast<ALT_PlayerState>(BasePlayerState) )
		{
			ULT_PlayerScoreWD* LPlayerScoreWD = CreateWidget<ULT_PlayerScoreWD>(GetWorld(), PlayerScoreWDClass.LoadSynchronous());
			if( IsValid(LPlayerScoreWD) )
			{
				LPlayerScoreWD->InitializePlayerScoreWD(LPlayerState->GetPlayerId(), LPlayerState->GetScore(), LPlayerState->GetHasFinished());
				if( IsValid(PlayersScrollBox) ) PlayersScrollBox->AddChild(LPlayerScoreWD);
			}
		}
	}
	
	
	TArray<APlayerState*> Losers;															//TODO Make as variable in GameState
	for( const auto& BasePlayerState : LGameState->PlayerArray )
	{
		if( ALT_PlayerState* LPlayerState = Cast<ALT_PlayerState>(BasePlayerState) )
		{
			if( LPlayerState->GetHasFinished() != true ) Losers.Add(BasePlayerState.Get());
		}
	}

	for(const auto& BasePlayerState : Losers)
	{
		if( ALT_PlayerState* LPlayerState = Cast<ALT_PlayerState>(BasePlayerState) )
		{
			ULT_PlayerScoreWD* LPlayerScoreWD = CreateWidget<ULT_PlayerScoreWD>(GetWorld(), PlayerScoreWDClass.LoadSynchronous());
			if( IsValid(LPlayerScoreWD) )
			{
				LPlayerScoreWD->InitializePlayerScoreWD(LPlayerState->GetPlayerId(), LPlayerState->GetScore(), LPlayerState->GetHasFinished());
				if( IsValid(PlayersScrollBox) ) PlayersScrollBox->AddChild(LPlayerScoreWD);
			}
		}
	}
}

