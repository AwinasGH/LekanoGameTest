// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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

	virtual void OnPossess(APawn* InPawn) override;

	virtual void AcknowledgePossession(APawn* InPawn) override; // Client possess

	virtual void OnUnPossess() override;
	

	virtual void BeginPlay() override;
	
	
//>>...........................................................................................................................................<<//

//Blueprint values
public:

	UPROPERTY(BlueprintReadOnly, Category = "PlayerController")
		ALT_PlayerCharacter* MyCharacter = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "PlayerController")
		ALT_GameHUD* MyGameHUD = nullptr;
	
};
