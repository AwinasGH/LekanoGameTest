// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "LT_PlayerState.generated.h"

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

	FORCEINLINE bool GetHasFinished() const { return HasFinished; }
	
	void SetHasFinished(const bool NewValue);

	FORCEINLINE bool GetIsDead() const { return IsDead; }
	
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
};
