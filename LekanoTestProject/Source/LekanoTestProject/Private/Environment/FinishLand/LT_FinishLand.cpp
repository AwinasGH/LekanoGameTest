// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/FinishLand/LT_FinishLand.h"

#include "Character/Player/LT_PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PlayerState.h"
#include "GameMode/LT_GameModeMain.h"
#include "GameMode/LT_GameState.h"
#include "GameMode/LT_PlayerState.h"


ALT_FinishLand::ALT_FinishLand(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;

	SceneRootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	SetRootComponent(SceneRootComponent);

	BoxTrigger = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	BoxTrigger->SetupAttachment(GetRootComponent());

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("PlateMesh");
	MeshComponent->SetupAttachment(GetRootComponent());
}

void ALT_FinishLand::BeginPlay()
{
	Super::BeginPlay();

	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &ALT_FinishLand::OnTriggerBeginOverlap);
}

void ALT_FinishLand::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if( GetLocalRole() < ROLE_Authority ) return;
	
	ALT_PlayerCharacter* PlayerCharacter = Cast<ALT_PlayerCharacter>(OtherActor);
	if( !IsValid(PlayerCharacter) ) return;

	ALT_PlayerState* LPlayerState = Cast<ALT_PlayerState>(PlayerCharacter->GetPlayerState());
	ALT_GameState* LGameState = Cast<ALT_GameState>(GetWorld()->GetGameState());
	if( !IsValid(LPlayerState) || !IsValid(LGameState) ) return;
	
	ALT_GameModeMain* LGameModeMain = Cast<ALT_GameModeMain>(LGameState->AuthorityGameMode);
	if( !IsValid(LGameModeMain) ) return;

	LPlayerState->SetScore(LGameState->GetCurrentMatchTime());

	LPlayerState->SetHasFinished(true);
}
