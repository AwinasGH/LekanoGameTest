// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LT_GameZone.generated.h"

UCLASS(Blueprintable)
class LEKANOTESTPROJECT_API ALT_GameZone : public AActor
{
	GENERATED_BODY()
	
//constructor
public:

	ALT_GameZone();


//c++ protected methods
protected:

	virtual void BeginPlay() override;

	UFUNCTION()
		void OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
//>>>...............................................................................................................................................................................<<<//
//>>>...............................................................................................................................................................................<<<//
	
	
//Blueprint values
public:
	
	/*
		Trigger for handling player entering and leaving location
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Location|Components")
		class UBoxComponent* BoxTrigger = nullptr;
};
