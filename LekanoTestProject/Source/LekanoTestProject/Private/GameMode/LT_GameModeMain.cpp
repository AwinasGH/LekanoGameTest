// Fill out your copyright notice in the Description page of Project Settings.

#include "LekanoTestProject/Public/GameMode/LT_GameModeMain.h"

#include "LekanoTestProject/Public/Character/Player/LT_PlayerController.h"


ALT_GameModeMain::ALT_GameModeMain()
{
	bStartPlayersAsSpectators = false;
	bUseSeamlessTravel = false;

	PlayerControllerClass = ALT_PlayerController::StaticClass();
}
