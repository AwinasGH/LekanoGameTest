// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LT_InGameMatchStateInfo.h"
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

	FORCEINLINE float GetCurrentPreparationTime() const { return CurrentPreparationTime; }
	
	FORCEINLINE float GetCurrentMatchTime() const { return CurrentMatchTime; }
	
	FORCEINLINE EInGameMatchState GetInGameMatchState() const { return InGameMatchState; }
	
	
	bool IsEveryoneAliveHasFinished() const;
	
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

	UPROPERTY(Replicated)
		float CurrentMatchTime = 0.0f;

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
	
};
