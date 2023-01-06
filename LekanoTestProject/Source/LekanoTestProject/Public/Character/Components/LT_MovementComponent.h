// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "PersonInfo/LT_CharacterMovementInfo.h"

#include "LT_MovementComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLegMoveTypeChanged, ELegMoveType, NewLegMoveType);

/*
 * 
*/
UCLASS(BlueprintType, meta=(BlueprintSpawnableComponent))
class LEKANOTESTPROJECT_API ULT_MovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

	friend class FSavedMove_LT;
	
//constructor
public:

	ULT_MovementComponent();

//c++ public methods
public:

	virtual void UpdateFromCompressedFlags(uint8 Flags) override;
	
	virtual float GetMaxSpeed() const override;
	
	virtual float GetMaxAcceleration() const override;
	
	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;


//c++ protected methods
protected:
	
	virtual void ChangeLegMoveTypeContext(ELegMoveType NewLegMoveType);
	
	virtual void ChangeLegMoveType_Client(ELegMoveType NewLegMoveType);

//c++ private values
private:

	uint8 bWantsToSprint : 1;
	uint8 bWantsToJog : 1;
	uint8 bWantsToWalk : 1;
	
	
	ELegMoveType LegMoveType;
	
//>>>...............................................................................................................................................................................<<<//
//>>>...............................................................................................................................................................................<<<//


//Blueprint protected methods
protected:
	
	UPROPERTY(BlueprintAssignable, Category = "LegMoving")
		FOnLegMoveTypeChanged OnLegMoveTypeChangedBind;

	UFUNCTION(BlueprintCallable, Server, Unreliable, Category = "LegMoving")
		void ChangeLegMoveType_Server(ELegMoveType NewLegMoveType);
		virtual void ChangeLegMoveType_Server_Implementation(ELegMoveType NewLegMoveType);

	UFUNCTION(BlueprintCallable, NetMulticast, Unreliable, Category = "LegMoving")
		void ChangeLegMoveType_ServerToAll(ELegMoveType NewLegMoveTyp);
		virtual void ChangeLegMoveType_ServerToAll_Implementation(ELegMoveType NewLegMoveTyp);
	
//Blueprint public methods
public:


	UFUNCTION(BlueprintCallable, Category = "LegMoving")
		void ChangeLegMoveType(ELegMoveType NewLegMoveType);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LegMoving")
		ELegMoveType GetLegMoveType() const { return LegMoveType; };
	
};


class FSavedMove_LT : public FSavedMove_Character
{
	
public:

	typedef FSavedMove_Character Super;

	/* Reset all saved variables */
	virtual void Clear() override;
	/* Store input commands in the compressed flags */
	virtual uint8 GetCompressedFlags() const override;
	/* Sets up the move before sending it to server */
	virtual void SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData) override;
	/* Sets variables on character movement component before making a predictive correction */
	virtual void PrepMoveFor(ACharacter* Character) override;

private:

	uint8 SavedWantsToSprint : 1;
	uint8 SavedWantsToJog : 1;
	uint8 SavedWantsToWalk: 1;
};

class FNetworkPredictionData_Client_LT : FNetworkPredictionData_Client_Character
{

	friend class ULT_MovementComponent;
	
public:

	typedef FNetworkPredictionData_Client_Character Super;

	/* Constructor */
	FNetworkPredictionData_Client_LT(const UCharacterMovementComponent& ClientMovement);

	/* brief Allocates a new copy of our custom saved move */
	virtual FSavedMovePtr AllocateNewMove() override;
};
