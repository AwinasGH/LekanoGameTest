// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LT_TimerBoardWD.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class LEKANOTESTPROJECT_API ULT_TimerBoardWD : public UUserWidget
{
	GENERATED_BODY()

	friend class ALT_TimerBoard;
	
//constructor
public:

	ULT_TimerBoardWD(const FObjectInitializer& ObjectInitializer);
	
//c++ protected methods
protected:
	
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


//>>..........................................................................................................................<<//

//Blueprint values
public:

	/*
		Preparation time text.
	*/
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "TimerBoard|Widgets")
		UTextBlock* PreparationTimeTextBlock = nullptr;
	/*
		Match time text.
	*/
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "TimerBoard|Widgets")
		UTextBlock* MatchTimeTextBlock = nullptr;
};