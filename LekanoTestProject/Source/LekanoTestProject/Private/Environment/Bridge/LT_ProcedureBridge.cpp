// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/Bridge/LT_ProcedureBridge.h"

#include "Environment/Bridge/PlatePair/LT_PlatePair.h"
#include "Environment/FinishLand/LT_FinishLand.h"
#include "Environment/TimerBoard/LT_TimerBoard.h"
#include "GameMode/LT_GameModeMain.h"
#include "GameMode/LT_GameState.h"


ALT_ProcedureBridge::ALT_ProcedureBridge(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALT_ProcedureBridge::BeginPlay()
{
	Super::BeginPlay();

	ALT_GameState* LGameState = Cast<ALT_GameState>(GetWorld()->GetGameState());
	if( !IsValid(LGameState) ) return;

	LGameState->OnInGameMatchStateChangedBind.AddDynamic(this, &ALT_ProcedureBridge::ExecuteSpawn);
}


void ALT_ProcedureBridge::ExecuteSpawn_Implementation(const EInGameMatchState InGameMatchState)
{
	if( InGameMatchState != EInGameMatchState::Preparation ) return;
		
	UWorld* LWorld = Cast<UWorld>(GetWorld());
	if( !IsValid(LWorld) ) return;
	
	ALT_GameModeMain* LGameMode = Cast<ALT_GameModeMain>(LWorld->GetAuthGameMode());
	if( !IsValid(LGameMode) ) return;

	FActorSpawnParameters ActorSpawnParameters;

	FVector LastSpawnedLocation = FVector::ZeroVector;

	FVector LFirstSpawnLocation = GetActorLocation();
	FRotator LFirstSpawnRotation = FRotator::ZeroRotator;
	
	ALT_PlatePair* LLastSpawnedPlate = Cast<ALT_PlatePair>(LWorld->SpawnActor(PlatePairClass.LoadSynchronous(),
																&LFirstSpawnLocation, &LFirstSpawnRotation, ActorSpawnParameters));

	for( int i = 0; i < LGameMode->GetNumPlayers() - 1; ++i )
	{
		FVector SpawnLocation = LLastSpawnedPlate->GetPivotComponentLocation();
		SpawnLocation.X += SpawnForwardOffset;
		
		FRotator SpawnRotation = FRotator::ZeroRotator;
	
		LLastSpawnedPlate = Cast<ALT_PlatePair>(LWorld->SpawnActor(PlatePairClass.LoadSynchronous(),
												&SpawnLocation, &SpawnRotation, ActorSpawnParameters));
	}

	if( !IsValid(LLastSpawnedPlate) ) return;

	
	FVector LFinishLandSpawnLocation = LLastSpawnedPlate->GetPivotComponentLocation();
	LFinishLandSpawnLocation.X += SpawnForwardOffset;
		
	FRotator LFinishLandSpawnRotation = FRotator::ZeroRotator;
	
	ALT_FinishLand* LLastSpawnedFinishLand = Cast<ALT_FinishLand>(LWorld->SpawnActor(FinishLandClass.LoadSynchronous(), &LFinishLandSpawnLocation, &LFinishLandSpawnRotation, ActorSpawnParameters));

	
	FVector TimerBoardSpawnLocation = FVector::ZeroVector;
	FRotator TimerBoardSpawnRotation = FRotator::ZeroRotator;
	LLastSpawnedFinishLand->GetMesh()->GetSocketWorldLocationAndRotation(NextToFinishLandSocketName, TimerBoardSpawnLocation, TimerBoardSpawnRotation);
	
	TimerBoardSpawnLocation.X += SpawnForwardOffset;
	
	ALT_TimerBoard* LLastSpawnedTimerBoard = Cast<ALT_TimerBoard>(LWorld->SpawnActor(TimerBoardClass.LoadSynchronous(), &TimerBoardSpawnLocation, &TimerBoardSpawnRotation, ActorSpawnParameters));
}



