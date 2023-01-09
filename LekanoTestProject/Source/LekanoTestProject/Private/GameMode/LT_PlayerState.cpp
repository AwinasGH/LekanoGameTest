// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LT_PlayerState.h"

#include "GameMode/LT_GameState.h"
#include "Net/UnrealNetwork.h"

ALT_PlayerState::ALT_PlayerState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void ALT_PlayerState::SetHasFinished(const bool NewValue)
{
	if( GetLocalRole() < ROLE_Authority ) return;
	
	HasFinished = NewValue;

	ALT_GameState* LGameState = Cast<ALT_GameState>(GetWorld()->GetGameState());
	if( !IsValid(LGameState) ) return;

	LGameState->UpdateMainMatchState();
}

void ALT_PlayerState::SetIsDead(const bool NewValue)
{
	if( GetLocalRole() < ROLE_Authority ) return;
	
	HasFinished = NewValue;

	ALT_GameState* LGameState = Cast<ALT_GameState>(GetWorld()->GetGameState());
	if( !IsValid(LGameState) ) return;

	LGameState->UpdateMainMatchState();
}

void ALT_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALT_PlayerState, HasFinished);
	DOREPLIFETIME(ALT_PlayerState, IsDead);
}

