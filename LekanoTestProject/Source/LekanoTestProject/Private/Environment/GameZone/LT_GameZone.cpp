// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/GameZone/LT_GameZone.h"

#include "Character/Player/LT_PlayerCharacter.h"
#include "Components/BoxComponent.h"


ALT_GameZone::ALT_GameZone()
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;
	
	BoxTrigger = CreateDefaultSubobject<UBoxComponent>("BoxTrigger");
	
	if( IsValid(BoxTrigger) ) SetRootComponent(BoxTrigger);
}

void ALT_GameZone::	BeginPlay()
{
	Super::BeginPlay();

	BoxTrigger->OnComponentEndOverlap.AddDynamic(this, &ALT_GameZone::OnTriggerEndOverlap);
}

void ALT_GameZone::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if( GetLocalRole() < ROLE_Authority ) return;
	
	ALT_PlayerCharacter* PlayerCharacter = Cast<ALT_PlayerCharacter>(OtherActor);
	if( !IsValid(PlayerCharacter) ) return;

	PlayerCharacter->Destroy(true);
}


