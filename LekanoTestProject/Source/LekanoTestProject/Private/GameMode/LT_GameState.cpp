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

	if (MatchState == MatchState::InProgress)
	{
		CurrentPreparationTime = LGameMode->GetPreparationTime();
		CurrentMatchTime = LGameMode->GetMatchTime();
		
		InGameMatchState = EInGameMatchState::Preparation;
		OnRep_InGameMatchState();
		
		GetWorld()->GetTimerManager().SetTimer(PreparationTimerHandle, this, &ALT_GameState::PreparationTimerTicker, 1.0f, true);
	}
}


void ALT_GameState::OnRep_InGameMatchState()
{
	OnInGameMatchStateChangedBind.Broadcast(InGameMatchState);
}


void ALT_GameState::PreparationTimerTicker()
{
	if( FMath::IsNearlyZero(CurrentPreparationTime) )
	{
		InGameMatchState = EInGameMatchState::InProgress;
		OnRep_InGameMatchState();

		GetWorldTimerManager().ClearTimer(PreparationTimerHandle);
		
		IsPreparationTimerActive = false;

		GetWorld()->GetTimerManager().SetTimer(MatchTimerHandle, this, &ALT_GameState::MatchTimerTicker, 1.0f, true);

		return;
	}

	--CurrentPreparationTime;
}

void ALT_GameState::MatchTimerTicker()
{
	if( FMath::IsNearlyZero(CurrentMatchTime) )
	{
		InGameMatchState = EInGameMatchState::Ended;
		OnRep_InGameMatchState();

		IsMatchTimerActive = false;

		GetWorldTimerManager().ClearTimer(MatchTimerHandle);

		return;
	}

	--CurrentMatchTime;
}

bool ALT_GameState::IsEveryoneAliveHasFinished() const
{
	for( const auto& Player : PlayerArray )
	{
		if( const ALT_PlayerState* PlayerState = Cast<ALT_PlayerState>(Player) )
		{
			if( PlayerState->GetIsDead() ) continue;
				
			if( !PlayerState->GetHasFinished() )
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "false");
				return false;
			}
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




