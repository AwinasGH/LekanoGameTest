// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/LT_PlayerController.h"

#include "Character/Player/LT_PlayerCharacter.h"

#include "GameMode/LT_GameHUD.h"
#include "GameMode/LT_GameState.h"


ALT_PlayerController::ALT_PlayerController()
{
	bReplicates = true;
}


void ALT_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	MyCharacter = Cast<ALT_PlayerCharacter>(InPawn);
}

void ALT_PlayerController::AcknowledgePossession(APawn* InPawn)
{
	Super::AcknowledgePossession(InPawn);

	MyCharacter = Cast<ALT_PlayerCharacter>(InPawn);
}

void ALT_PlayerController::OnUnPossess()
{
	Super::OnUnPossess();

	MyCharacter = nullptr;
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



