// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LT_ScoreBoardWD.generated.h"

/*
 *  Widget for displaying score
*/
UCLASS(Abstract)
class LEKANOTESTPROJECT_API ULT_ScoreBoardWD : public UUserWidget
{
	GENERATED_BODY()

//constructors
public:

	ULT_ScoreBoardWD(const FObjectInitializer& ObjectInitializer);
	

//c++ public methods
public:

	virtual void InitializeScoreBoardWD(class ALT_GameHUD* GameHUD);

	virtual void NativeConstruct() override;

//>>..........................................................................................................................<<//



//Blueprint methods
public:

	UPROPERTY(BlueprintReadOnly)
		ALT_GameHUD* MyGameHUD = nullptr;

//Blueprint values
public:

	/*
		*
	*/
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "ScoreBoardWD|Widgets")
		class UTextBlock* PlayersNumTextBlock = nullptr;
	/*
		*
	*/
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "ScoreBoardWD|Widgets")
		class UScrollBox* PlayersScrollBox = nullptr;
	/*
		Player score widget class
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ScoreBoardWD|Classes")
		TSoftClassPtr<class ULT_PlayerScoreWD> PlayerScoreWDClass;
};
