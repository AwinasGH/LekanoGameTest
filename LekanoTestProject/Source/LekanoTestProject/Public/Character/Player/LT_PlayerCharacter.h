// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LT_CharacterBase.h"
#include "LT_PlayerCharacter.generated.h"



/*
	
*/
UCLASS()
class LEKANOTESTPROJECT_API ALT_PlayerCharacter : public ALT_CharacterBase
{
	GENERATED_BODY()

//constructor
public:

	ALT_PlayerCharacter(const FObjectInitializer& ObjectInitializer);

//c++ public methods
public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	
//..........................................Methods to bind with Input Actions.................................................................//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//..........Moving..............//

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	void LookRight(float AxisValue);
	void LookUp(float AxisValue);

	void OnPressWalk();
	void OnReleaseWalk();

	void OnPressSprint();
	void OnReleaseSprint();

	//..............................//


	//.....Gameplay Actions.........//

	void OnPressParkourAction();
	
	void OnPressOpenMenu();

	//..............................//


	



//c++ protected methods
protected:

	virtual void BeginPlay() override;

//>>>...............................................................................................................................................................................<<<//
//>>>...............................................................................................................................................................................<<<//
	
	

};
