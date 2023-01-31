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

//protected methods
protected:
	
	UFUNCTION()
		virtual void UpdateMainMatchState();
	

//public values
public:

	UPROPERTY(BlueprintAssignable, Category = "InGameMatchState")
		FOnInGameMatchStateChanged OnInGameMatchStateChangedBind;

//protected values
protected:
	
	UPROPERTY(ReplicatedUsing=OnRep_InGameMatchState)
		EInGameMatchState InGameMatchState;
	
	UPROPERTY(EditDefaultsOnly, Replicated, Category = "GameInfos|Preparation")
		FInGameStateInfo PreparationInfo;

	UPROPERTY(EditDefaultsOnly, Replicated, Category = "GameInfos|Match")
		FInGameStateInfo MatchInfo;

//protected methods
protected:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	

	virtual void OnRep_MatchState() override;
	
	UFUNCTION()
		virtual void OnRep_InGameMatchState();

	UFUNCTION()
		virtual void PreparationTimerTicker();

	UFUNCTION()
		virtual void MatchTimerTicker();

//>>..........................................................................................................................<<//



//Blueprint methods
public:

	UFUNCTION(BlueprintCallable, Category = "Preparation")
		FORCEINLINE float GetCurrentPreparationTime() const { return PreparationInfo.CurrentStateTime; }

	UFUNCTION(BlueprintCallable, Category = "Match")
		FORCEINLINE float GetCurrentMatchTime() const { return MatchInfo.CurrentStateTime; }

	UFUNCTION(BlueprintCallable, Category = "InGameMatchState")
		FORCEINLINE EInGameMatchState GetInGameMatchState() const { return InGameMatchState; }

	
	UFUNCTION(BlueprintCallable)
		bool IsEveryoneAliveHasFinished() const;


	UFUNCTION(BlueprintCallable, Category = "Players")
		void GetSortedFinalists(TArray<ALT_PlayerState*>& Finalists);

	UFUNCTION(BlueprintCallable, Category = "Players")
		void GetSortedLosers(TArray<ALT_PlayerState*>& Losers);
};
