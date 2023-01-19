// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "LT_PlayerState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerStatusChanged)

/**
 * 
 */
UCLASS()
class LEKANOTESTPROJECT_API ALT_PlayerState : public APlayerState
{
	GENERATED_BODY()
	
//constructor
public:

	ALT_PlayerState(const FObjectInitializer& ObjectInitializer);

//private values
public:

	UPROPERTY(BlueprintAssignable)
		FOnPlayerStatusChanged OnPlayerStatusChanged;
	
//private values
public:
	
	void SetHasFinished(const bool NewValue);
	
	void SetIsDead(const bool NewValue);

//protected methods
public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

//private values
private:

	UPROPERTY(Replicated)
		bool HasFinished = false;

	UPROPERTY(Replicated)
		bool IsDead = false;


//>>>...............................................................................................................................................................................<<<//
//>>>...............................................................................................................................................................................<<<//
	
	
//Blueprint public values:
public:

	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool GetHasFinished() const { return HasFinished; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool GetIsDead() const { return IsDead; }
};
