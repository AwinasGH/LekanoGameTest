// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LT_PlayerState.h"

#include "GameMode/LT_GameState.h"
#include "Net/UnrealNetwork.h"

ALT_PlayerState::ALT_PlayerState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void ALT_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;
	
	DOREPLIFETIME_WITH_PARAMS_FAST(ALT_PlayerState, HasFinished, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ALT_PlayerState, IsDead, SharedParams);
}


void ALT_PlayerState::SetHasFinished(const bool NewValue)
{
	if( GetLocalRole() < ROLE_Authority ) return;

	MARK_PROPERTY_DIRTY_FROM_NAME(ALT_PlayerState, HasFinished, this);
	HasFinished = NewValue;

	ALT_GameState* LGameState = Cast<ALT_GameState>(GetWorld()->GetGameState());
	if( !IsValid(LGameState) ) return;

	OnPlayerStatusChanged.Broadcast();
}

void ALT_PlayerState::SetIsDead(const bool NewValue)
{
	if( GetLocalRole() < ROLE_Authority ) return;

	MARK_PROPERTY_DIRTY_FROM_NAME(ALT_PlayerState, IsDead, this);
	IsDead = NewValue;

	ALT_GameState* LGameState = Cast<ALT_GameState>(GetWorld()->GetGameState());
	if( !IsValid(LGameState) ) return;

	OnPlayerStatusChanged.Broadcast();
}


