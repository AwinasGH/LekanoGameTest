// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMode/LT_GameState.h"

#include "GameFramework/PlayerState.h"
#include "GameMode/LT_GameModeMain.h"
#include "GameMode/LT_PlayerState.h"
#include "Net/UnrealNetwork.h"



ALT_GameState::ALT_GameState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void ALT_GameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ALT_GameState, InGameMatchState);
	DOREPLIFETIME(ALT_GameState, PreparationInfo);
	DOREPLIFETIME(ALT_GameState, MatchInfo);
}


void ALT_GameState::BeginPlay()
{
	Super::BeginPlay();
}

void ALT_GameState::OnRep_MatchState()
{
	Super::OnRep_MatchState();
	
	const ALT_GameModeMain* LGameMode = Cast<ALT_GameModeMain>(GetWorld()->GetAuthGameMode());
	if( !IsValid(LGameMode) ) return;

	if ( MatchState == MatchState::InProgress )
	{
		PreparationInfo.CurrentTime = LGameMode->GetPreparationTime();
		MatchInfo.CurrentTime = LGameMode->GetMatchTime();

		for( const auto& BasePlayerState : PlayerArray )
		{
			if( ALT_PlayerState* LPlayerState = Cast<ALT_PlayerState>(BasePlayerState) )
			{
				LPlayerState->OnPlayerStatusChanged.AddDynamic(this, &ALT_GameState::UpdateMainMatchState);
			}
		}
		
		InGameMatchState = EInGameMatchState::Preparation;
		OnRep_InGameMatchState();
		
		GetWorld()->GetTimerManager().SetTimer(PreparationInfo.TimerHandle, this, &ALT_GameState::PreparationTimerTicker,
																			PreparationInfo.TimeUpdateFrequency, true);
	}
}


void ALT_GameState::OnRep_InGameMatchState()
{
	if( GetLocalRole() == ROLE_Authority && InGameMatchState == EInGameMatchState::Ended )
	{
		for( const auto& BasePlayerState : PlayerArray )
		{
			if( ALT_PlayerState* LPlayerState = Cast<ALT_PlayerState>(BasePlayerState) )
			{
				LPlayerState->OnPlayerStatusChanged.RemoveDynamic(this, &ALT_GameState::UpdateMainMatchState);

				LPlayerState->ForceNetUpdate();
			}
		}
	}
	
	OnInGameMatchStateChangedBind.Broadcast(InGameMatchState);
}


void ALT_GameState::PreparationTimerTicker()
{
	if( FMath::IsNearlyZero(PreparationInfo.CurrentTime) || PreparationInfo.CurrentTime < 0.0f )
	{
		InGameMatchState = EInGameMatchState::InProgress;
		OnRep_InGameMatchState();

		GetWorldTimerManager().ClearTimer(PreparationInfo.TimerHandle);
		
		PreparationInfo.IsTimerActive = false;

		GetWorld()->GetTimerManager().SetTimer(MatchInfo.TimerHandle, this, &ALT_GameState::MatchTimerTicker,
																		MatchInfo.TimeUpdateFrequency, true);

		return;
	}

	PreparationInfo.CurrentTime -= PreparationInfo.TimeStep;
}

void ALT_GameState::MatchTimerTicker()
{
	if( FMath::IsNearlyZero(MatchInfo.CurrentTime) || MatchInfo.CurrentTime < 0.0f )
	{
		InGameMatchState = EInGameMatchState::Ended;
		OnRep_InGameMatchState();
		
		GetWorldTimerManager().ClearTimer(MatchInfo.TimerHandle);

		MatchInfo.IsTimerActive = false;

		return;
	}

	MatchInfo.CurrentTime -= MatchInfo.TimeStep;
}

void ALT_GameState::GetSortedFinalists(TArray<ALT_PlayerState*>& Finalists)
{
	Finalists.Empty();
	
	for( const auto& BasePlayerState : PlayerArray )
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
}

void ALT_GameState::GetSortedLosers(TArray<ALT_PlayerState*>& Losers)
{
	Losers.Empty();
	
	for( const auto& BasePlayerState : PlayerArray )
	{
		if( ALT_PlayerState* LPlayerState = Cast<ALT_PlayerState>(BasePlayerState) )
		{
			if( LPlayerState->GetHasFinished() != true ) Losers.Add(LPlayerState);
		}
	}
}

bool ALT_GameState::IsEveryoneAliveHasFinished() const
{
	for( const auto& Player : PlayerArray )
	{
		if( const ALT_PlayerState* PlayerState = Cast<ALT_PlayerState>(Player) )
		{
			if( PlayerState->GetIsDead() ) continue;
				
			if( !PlayerState->GetHasFinished() ) return false;
		}
	}

	return true;
}

void ALT_GameState::UpdateMainMatchState()
{
	if( GetLocalRole() < ROLE_Authority ) return;
	
	if( InGameMatchState == EInGameMatchState::InProgress && IsEveryoneAliveHasFinished() )
	{
		InGameMatchState = EInGameMatchState::Ended;
		OnRep_InGameMatchState();

		MatchInfo.IsTimerActive = false;
	}
}




