// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LT_PlayerState.h"
#include "InGameMatchStateInfo/LT_InGameMatchStateInfo.h"
#include "GameFramework/GameState.h"
#include "LT_GameState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInGameMatchStateChanged, const EInGameMatchState, InGameMatchState)


/**
 * 
 */
UCLASS()
class LEKANOTESTPROJECT_API ALT_GameState : public AGameState
{
	GENERATED_BODY()
	
//constructor
public:

	ALT_GameState(const FObjectInitializer& ObjectInitializer);

//public methods
public:
	
	
	bool IsEveryoneAliveHasFinished() const;

	UFUNCTION()
		void UpdateMainMatchState();
	

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

//public values
public:

	FOnInGameMatchStateChanged OnInGameMatchStateChangedBind;

//private values
private:
	
	UPROPERTY(ReplicatedUsing=OnRep_InGameMatchState)
		EInGameMatchState InGameMatchState;
	
	
	FTimerHandle PreparationTimerHandle;

	FTimerHandle MatchTimerHandle;
	

	UPROPERTY(Replicated)
		float CurrentPreparationTime = 0.0f;

	UPROPERTY(Replicated, EditDefaultsOnly, Category = "Preparation")
		float PreparationTimeStep = 1.0f;

	UPROPERTY(Replicated, EditDefaultsOnly, Category = "Preparation")
		float PreparationTimeUpdateFrequency = 1.0f;
	

	UPROPERTY(Replicated)
		float CurrentMatchTime = 0.0f;

	UPROPERTY(Replicated, EditDefaultsOnly, Category = "Match")
		float MatchTimeStep = 1.0f;

	UPROPERTY(Replicated, EditDefaultsOnly, Category = "Match")
		float MatchTimeUpdateFrequency = 1.0f;
	

	UPROPERTY(Replicated)
		bool IsPreparationTimerActive = true;

	UPROPERTY(Replicated)
		bool IsMatchTimerActive = true;

//protected methods
protected:

	virtual void BeginPlay() override;

	virtual void OnRep_MatchState() override;
	
	UFUNCTION()
		virtual void OnRep_InGameMatchState();

	UFUNCTION()
		virtual void PreparationTimerTicker(); // TODO move to GameMode

	UFUNCTION()
		virtual void MatchTimerTicker(); // TODO move to GameMode

//>>..........................................................................................................................<<//



//Blueprint methods
public:

	UFUNCTION(BlueprintCallable, Category = "Preparation")
		FORCEINLINE float GetCurrentPreparationTime() const { return CurrentPreparationTime; }

	UFUNCTION(BlueprintCallable, Category = "Match")
		FORCEINLINE float GetCurrentMatchTime() const { return CurrentMatchTime; }

	UFUNCTION(BlueprintCallable, Category = "InGameMatchState")
		FORCEINLINE EInGameMatchState GetInGameMatchState() const { return InGameMatchState; }


	UFUNCTION(BlueprintCallable, Category = "Players")
		void GetSortedFinalists(TArray<ALT_PlayerState*>& Finalists);

	UFUNCTION(BlueprintCallable, Category = "Players")
		void GetSortedLosers(TArray<ALT_PlayerState*>& Losers);
	
};
