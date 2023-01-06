// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"

#include "PersonInfo/LT_CharacterMovementInfo.h"

#include "LT_CharacterBase.generated.h"


#define AddDefaultComponent(ComponentObject, ComponentName, DisplayName, Replicated)\
ComponentObject = CreateDefaultSubobject<ComponentName>(TEXT(DisplayName));\
ComponentObject->SetIsReplicated(Replicated);


/*
	Base class for all characters in game.
*/
UCLASS(Abstract)
class LEKANOTESTPROJECT_API ALT_CharacterBase : public ACharacter
{
	GENERATED_BODY()

	friend class ULT_MovementComponent;

//constructor
public:

	ALT_CharacterBase(const FObjectInitializer& ObjectInitializer);

//c++ public methods
public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	

//c++ protected methods
protected:
	
	virtual void BeginPlay() override;
	
	
//>>>...............................................................................................................................................................................<<<//
//>>>...............................................................................................................................................................................<<<//


//Blueprint protected methods
protected:
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (BlueprintProtected), Category = "LegMoving")
		void OnLegMoveTypeChanged(ELegMoveType NewLegMoveTyp);
		virtual void OnLegMoveTypeChanged_Implementation(ELegMoveType NewLegMoveTyp){}
	
//Blueprint public methods
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LegMoving")
		bool CanChangeLegMoveType(ELegMoveType ToChangeMoveType);
		virtual bool CanChangeLegMoveType_Implementation(ELegMoveType ToChangeMoveType) { return true; }


//..............................................Moving......................................................//

	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BaseCharacter|Moving")
		bool GetCanMove() const;
		virtual bool GetCanMove_Implementation() const { return true; };
	

	UFUNCTION(BlueprintCallable, Server, Unreliable, Category = "BaseCharacter|Actions|Moving")
		void DoJump();
		void DoJump_Implementation();
	UFUNCTION(BlueprintCallable, NetMulticast, Unreliable, Category = "BaseCharacter|Actions|Moving")
		void DoJump_ServerToAll();
		void DoJump_ServerToAll_Implementation();
	
//...........................................................................................................//


//.................................VisualEffects/SoundEffects...............................................//
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BaseCharacter|SoundEffects")
		void DoJumpSound();
		virtual void DoJumpSound_Implementation() {}

//..........................................................................................................//
	
	

//Blueprint public values
public:
	
	UPROPERTY(BlueprintReadOnly, Category = "BaseCharacter")
		class ULT_GameInstance* GameInstance = nullptr;

	/*
		Character sprint speed
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseCharacter|Moving")
		float SprintSpeed = 900.0f;
	/*
		Character jog speed
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseCharacter|Moving")
		float JogSpeed = 600.0f;
	/*
		Character walk speed
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseCharacter|Moving")
		float WalkSpeed = 300.0f;
	/*
		Character moving acceleration
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseCharacter|Moving")
		float MovingAcceleration = 900.0f;


//Blueprint protected values:
protected:
	
//.................................Components.....................................................//

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerCharacter|Components")
		class ULT_MovementComponent* CharacterMovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerCharacter|Components")
		class UCameraComponent* ThirdPersonCameraComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerCharacter|Components")
		class USpringArmComponent* SpringArmComponent = nullptr;

//................................................................................................//

};
