// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/Bridge/PlatePair/Plate/LT_Plate.h"

#include "Character/Player/LT_PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"


ALT_Plate::ALT_Plate()
{
	PrimaryActorTick.bCanEverTick = true;
	
	bReplicates = true;
	
	BoxTrigger = CreateDefaultSubobject<UBoxComponent>("Trigger");
	SetRootComponent(BoxTrigger);

	PlateMesh = CreateDefaultSubobject<UStaticMeshComponent>("PlateMesh");
	PlateMesh->SetupAttachment(GetRootComponent());
}


void ALT_Plate::BeginPlay()
{
	Super::BeginPlay();

	if( GetLocalRole() < ROLE_Authority ) return;
	
	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &ALT_Plate::OnTriggerBeginOverlap);
	BoxTrigger->OnComponentEndOverlap.AddDynamic(this, &ALT_Plate::OnTriggerEndOverlap);
}

void ALT_Plate::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, IsFake);
}


void ALT_Plate::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if( OtherActor->IsA(ALT_PlayerCharacter::StaticClass()) && IsFake == true )
	{
		Destroy(true);
	}
	else
	{
		IsBusy = true;
	}
}

void ALT_Plate::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	TArray<AActor*> OutOverlappingActor;
	BoxTrigger->GetOverlappingActors(OutOverlappingActor);

	if( OutOverlappingActor.IsEmpty() )
	{
		IsBusy = false;

		return;
	}

	for( const auto& OverlappingActor : OutOverlappingActor )
	{
		if( OtherActor->IsA(ALT_PlayerCharacter::StaticClass()) ) return;
	}

	IsBusy = false;
}


