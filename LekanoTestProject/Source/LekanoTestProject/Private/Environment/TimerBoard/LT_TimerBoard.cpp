// Fill out your copyright notice in the Description page of Project Settings.

#include "Environment/TimerBoard/LT_TimerBoard.h"

#include "Components/WidgetComponent.h"


ALT_TimerBoard::ALT_TimerBoard(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;

	SceneRootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	SetRootComponent(SceneRootComponent);
	
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	WidgetComponent->SetupAttachment(SceneRootComponent);
}


