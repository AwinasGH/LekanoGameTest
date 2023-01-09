// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EnvironmentWD/TimerBoardWD/LT_TimerBoardWD.h"

#include "Components/TextBlock.h"
#include "GameMode/LT_GameState.h"
#include "Kismet/KismetTextLibrary.h"


ULT_TimerBoardWD::ULT_TimerBoardWD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsFocusable = false;
}

void ULT_TimerBoardWD::NativeConstruct()
{
	Super::NativeConstruct();

	check(PreparationTimeTextBlock);
	check(MatchTimeTextBlock);

	const ALT_GameState* LGameState = Cast<ALT_GameState>(GetWorld()->GetGameState());
	if( !IsValid(LGameState) ) return;

	PreparationTimeTextBlock->SetText(UKismetTextLibrary::Conv_IntToText(LGameState->GetCurrentPreparationTime()));
	
	MatchTimeTextBlock->SetText(UKismetTextLibrary::Conv_IntToText(LGameState->GetCurrentMatchTime()));
}

void ULT_TimerBoardWD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	const ALT_GameState* LGameState = Cast<ALT_GameState>(GetWorld()->GetGameState());
	if( !IsValid(LGameState) ) return;

	if( LGameState->GetInGameMatchState() == EInGameMatchState::Preparation )
	{
		const int CurrentTime = LGameState->GetCurrentPreparationTime();
		if( CurrentTime < 0 ) return;
	
		PreparationTimeTextBlock->SetText(UKismetTextLibrary::Conv_IntToText(CurrentTime));
	}
	else if( LGameState->GetInGameMatchState() == EInGameMatchState::InProgress )
	{
		const int CurrentTime = LGameState->GetCurrentMatchTime();
		if( CurrentTime < 0 ) return;
	
		MatchTimeTextBlock->SetText(UKismetTextLibrary::Conv_IntToText(CurrentTime));
	}
}

