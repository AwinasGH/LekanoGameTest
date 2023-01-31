// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/GameplayWD/ScoreBoardWD/PlayerScoreWD/LT_PlayerScoreWD.h"

#include "Components/TextBlock.h"

#include "Kismet/KismetTextLibrary.h"


ULT_PlayerScoreWD::ULT_PlayerScoreWD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsFocusable = false;
}

void ULT_PlayerScoreWD::InitializePlayerScoreWD(int32 PlayerID, float PlayerScore, const bool HasFinished)
{
	if( IsValid(PlayerIDTextBlock) ) PlayerIDTextBlock->SetText(UKismetTextLibrary::Conv_IntToText(PlayerID));
	
	if( IsValid(ScoreTextBlock) ) ScoreTextBlock->SetText(UKismetTextLibrary::Conv_DoubleToText(PlayerScore, ToZero));
	
	if( HasFinished != true ) ColorAndOpacity.A = 0.5;
}
