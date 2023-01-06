// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LT_PauseMenuWD.generated.h"


class UButton;
class ALT_GameHUD;

/*
 *  Widget for in-game pause menu
*/
UCLASS(Abstract)
class LEKANOTESTPROJECT_API ULT_PauseMenuWD : public UUserWidget
{
	GENERATED_BODY()

//constructors
public:

	ULT_PauseMenuWD(const FObjectInitializer& ObjectInitializer);

//c++ protected methods
protected:

	virtual void NativeConstruct() override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	UFUNCTION()
		void OnBackToMenuButtonClicked();

//>>..........................................................................................................................<<//



//Blueprint methods
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PauseMenuWD")
		void InitializePauseMenuWD(ALT_GameHUD* InGameHUD);
		virtual void InitializePauseMenuWD_Implementation(ALT_GameHUD* InGameHUD);


//Blueprint values
public:

	/*
		Back to menu button
	*/
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "PauseMenuWD|Widgets")
		UButton* BackToMenuButton = nullptr;
	/*
		
	*/
	UPROPERTY(BlueprintReadOnly)
		ALT_GameHUD* GameHUD = nullptr;
};
