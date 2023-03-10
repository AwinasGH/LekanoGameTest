// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameMode/InGameMatchStateInfo/LT_InGameMatchStateInfo.h"
#include "LT_PlayerController.generated.h"

class ALT_GameHUD;
class ALT_PlayerCharacter;

/**
 * 
 */
UCLASS()
class LEKANOTESTPROJECT_API ALT_PlayerController : public APlayerController
{
	GENERATED_BODY()


//constructor
public:
	
	ALT_PlayerController();

//c++ protected methods
protected:
	
	virtual void OnRep_Pawn() override;


	virtual APlayerState* GetNextViewablePlayer(int32 dir) override;

	
	virtual void BeginPlay() override;
	

//>>>...............................................................................................................................................................................<<<//
//>>>...............................................................................................................................................................................<<<//


//Blueprint protected values:
protected:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (BlueprintProtected))
		void OnInGameMatchStateChanged(const EInGameMatchState NewMatchState);
		virtual void OnInGameMatchStateChanged_Implementation(const EInGameMatchState NewMatchState);
	
//Blueprint values
public:

	UPROPERTY(BlueprintReadOnly, Category = "PlayerController")
		ALT_PlayerCharacter* MyCharacter = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "PlayerController")
		ALT_GameHUD* MyGameHUD = nullptr;
	
};
