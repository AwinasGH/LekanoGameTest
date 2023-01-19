// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InGameMatchStateInfo/LT_InGameMatchStateInfo.h"
#include "GameFramework/GameMode.h"
#include "LT_GameModeMain.generated.h"

/**
 * 
 */
UCLASS()
class LEKANOTESTPROJECT_API ALT_GameModeMain : public AGameMode
{
	GENERATED_BODY()
	
//constructor
public:

	ALT_GameModeMain();


//public methods
public:

	FORCEINLINE float GetPreparationTime() const { return PreparationTime; }
	
	FORCEINLINE float GetMatchTime() const { return MatchTime; }

//protected methods
protected:

	virtual void BeginPlay() override;

	virtual bool ReadyToStartMatch_Implementation() override;

//>>>...............................................................................................................................................................................<<<//
//>>>...............................................................................................................................................................................<<<//


//Blueprint protected values:
protected:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (BlueprintProtected))
		void OnInGameMatchStateChanged(const EInGameMatchState NewMatchState);
		virtual void OnInGameMatchStateChanged_Implementation(const EInGameMatchState NewMatchState);;

//Blueprint protected values:
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
		float PreparationTime = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
		float MatchTime = 30.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
		int32 MinPlayersNumToStartMatch = 2;
};
