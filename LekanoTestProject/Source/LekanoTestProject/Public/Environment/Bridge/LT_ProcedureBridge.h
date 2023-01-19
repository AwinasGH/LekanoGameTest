// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "GameMode/InGameMatchStateInfo/LT_InGameMatchStateInfo.h"

#include "LT_ProcedureBridge.generated.h"


UCLASS(Blueprintable)
class LEKANOTESTPROJECT_API ALT_ProcedureBridge : public AActor
{
	GENERATED_BODY()
	
//constructor
public:

	ALT_ProcedureBridge(const FObjectInitializer& ObjectInitializer);

	
//c++ protected methods
protected:

	virtual void BeginPlay() override;


//>>>...............................................................................................................................................................................<<<//
//>>>...............................................................................................................................................................................<<<//
	
	
//Blueprint protected values:
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ProcedureBridge|Default")
		TSoftClassPtr<class ALT_PlatePair> PlatePairClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ProcedureBridge|Default")
		TSoftClassPtr<class ALT_FinishLand> FinishLandClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ProcedureBridge|Default")
		TSoftClassPtr<class ALT_TimerBoard> TimerBoardClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ProcedureBridge|Default")
		float SpawnForwardOffset = 200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ProcedureBridge|Default")
		FName NextToFinishLandSocketName = "LandEnd";

//Blueprint protected methods:
protected:

	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "ProcedureBridge|Spawn")
		void ExecuteSpawn(const EInGameMatchState InGameMatchState);
		virtual void ExecuteSpawn_Implementation(const EInGameMatchState InGameMatchState);
};
