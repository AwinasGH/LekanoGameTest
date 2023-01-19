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

	DOREPLIFETIME(ALT_GameState, CurrentPreparationTime);
	DOREPLIFETIME(ALT_GameState, InGameMatchState);
	DOREPLIFETIME(ALT_GameState, IsPreparationTimerActive);
	DOREPLIFETIME(ALT_GameState, CurrentMatchTime);
	DOREPLIFETIME(ALT_GameState, IsMatchTimerActive);
	DOREPLIFETIME(ALT_GameState, PreparationTimeStep);
	DOREPLIFETIME(ALT_GameState, PreparationTimeUpdateFrequency);
	DOREPLIFETIME(ALT_GameState, MatchTimeStep);
	DOREPLIFETIME(ALT_GameState, MatchTimeUpdateFrequency);
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
		CurrentPreparationTime = LGameMode->GetPreparationTime();
		CurrentMatchTime = LGameMode->GetMatchTime();

		if( GetLocalRole() == ROLE_Authority )
		{
			for( const auto& BasePlayerState : PlayerArray )
			{
				if( ALT_PlayerState* LPlayerState = Cast<ALT_PlayerState>(BasePlayerState) )
				{
					LPlayerState->OnPlayerStatusChanged.AddDynamic(this, &ALT_GameState::UpdateMainMatchState);
				}
			}
		}
		
		InGameMatchState = EInGameMatchState::Preparation;
		OnRep_InGameMatchState();
		
		GetWorld()->GetTimerManager().SetTimer(PreparationTimerHandle, this, &ALT_GameState::PreparationTimerTicker,
																			PreparationTimeUpdateFrequency, true);
	}
}


void ALT_GameState::OnRep_InGameMatchState()
{
	if( InGameMatchState == EInGameMatchState::Ended && GetLocalRole() == ROLE_Authority )
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
	if( FMath::IsNearlyZero(CurrentPreparationTime) || CurrentPreparationTime < 0.0f )
	{
		InGameMatchState = EInGameMatchState::InProgress;
		OnRep_InGameMatchState();

		GetWorldTimerManager().ClearTimer(PreparationTimerHandle);
		
		IsPreparationTimerActive = false;

		GetWorld()->GetTimerManager().SetTimer(MatchTimerHandle, this, &ALT_GameState::MatchTimerTicker,
																		MatchTimeUpdateFrequency, true);

		return;
	}

	CurrentPreparationTime -= PreparationTimeStep;
}

void ALT_GameState::MatchTimerTicker()
{
	if( FMath::IsNearlyZero(CurrentMatchTime) || CurrentMatchTime < 0.0f )
	{
		InGameMatchState = EInGameMatchState::Ended;
		OnRep_InGameMatchState();

		IsMatchTimerActive = false;

		GetWorldTimerManager().ClearTimer(MatchTimerHandle);

		return;
	}

	CurrentMatchTime -= MatchTimeStep;
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

		IsMatchTimerActive = false;
	}
}




