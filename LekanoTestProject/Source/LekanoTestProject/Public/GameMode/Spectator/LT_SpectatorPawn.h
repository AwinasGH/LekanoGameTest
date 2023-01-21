// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "LT_SpectatorPawn.generated.h"

/**
 * 
 */
UCLASS()
class LEKANOTESTPROJECT_API ALT_SpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()
	
//constructor
public:

	ALT_SpectatorPawn(const FObjectInitializer& ObjectInitializer);

//c++ protected methods
protected:

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;


	void OnPressAttackAction();
	
	void OnPressParkourAction();
	
//>>>...............................................................................................................................................................................<<<//
//>>>...............................................................................................................................................................................<<<//

	
	

};

