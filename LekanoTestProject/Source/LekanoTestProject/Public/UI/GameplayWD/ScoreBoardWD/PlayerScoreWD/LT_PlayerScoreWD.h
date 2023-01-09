// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LT_PlayerScoreWD.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class LEKANOTESTPROJECT_API ULT_PlayerScoreWD : public UUserWidget
{
	GENERATED_BODY()
	
//constructors
public:

	ULT_PlayerScoreWD(const FObjectInitializer& ObjectInitializer);
	

//c++ public methods
public:

	virtual void InitializePlayerScoreWD(int32 PlayerID, float PlayerScore, const bool HasFinished);
	

//>>..........................................................................................................................<<//



//Blueprint methods
public:

	/*
		*
	*/
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "ScoreBoardWD|Widgets")
		class UTextBlock* PlayerIDTextBlock = nullptr;
	/*
		*
	*/
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "ScoreBoardWD|Widgets")
		class UTextBlock* ScoreTextBlock = nullptr;

};
