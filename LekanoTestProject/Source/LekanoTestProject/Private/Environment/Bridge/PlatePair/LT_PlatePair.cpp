// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/Bridge/PlatePair/LT_PlatePair.h"

#include "Engine/ActorChannel.h"
#include "Environment/Bridge/PlatePair/Plate/LT_Plate.h"
#include "Kismet/KismetMathLibrary.h"


ALT_PlatePair::ALT_PlatePair(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	
	PlatesRootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	SetRootComponent(PlatesRootComponent);

	PivotComponent = CreateDefaultSubobject<USceneComponent>("PivotComponent");
	PivotComponent->SetupAttachment(GetRootComponent());
	
	FirstPlate = CreateDefaultSubobject<UChildActorComponent>("FirstPlate");
	SecondPlate = CreateDefaultSubobject<UChildActorComponent>("SecondPlate");

	FirstPlate->SetupAttachment(GetRootComponent());
	SecondPlate->SetupAttachment(GetRootComponent());
}


void ALT_PlatePair::BeginPlay()
{
	Super::BeginPlay();

	FirstPlate->PostLoad();
	
	if( GetLocalRole() < ROLE_Authority ) return;

	ALT_Plate* LFirstPlate = Cast<ALT_Plate>(FirstPlate->GetChildActor());
	ALT_Plate* LSecondPlate = Cast<ALT_Plate>(SecondPlate->GetChildActor());
	if( !IsValid(LFirstPlate) || !IsValid(LSecondPlate) ) return;
	

	if( UKismetMathLibrary::RandomBool() )
	{
		LFirstPlate->IsFake = true;
		
		LSecondPlate->IsFake = false;
	}
	else
	{
		LSecondPlate->IsFake = true;
		
		LFirstPlate->IsFake = false;
	}
}


