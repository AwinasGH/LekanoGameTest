// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LT_MainMenuWD.generated.h"


class ULT_GameInstance;
class UButton;
class ALT_GameHUD;

/*
 *  Widget for MainMenu
*/
UCLASS(Abstract)
class LEKANOTESTPROJECT_API ULT_MainMenuWD : public UUserWidget
{
	GENERATED_BODY()
	
//constructors
public:

	ULT_MainMenuWD(const FObjectInitializer& ObjectInitializer);

//c++ protected methods
protected:

	virtual void NativeConstruct() override;


	UFUNCTION()
		void OnHostSessionButtonClicked();

	UFUNCTION()
		void OnJoinSessionButtonClicked();

//>>..........................................................................................................................<<//



//Blueprint methods
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MainMenuWD")
		void InitializeMainMenuWD(ALT_GameHUD* InGameHUD);
		virtual void InitializeMainMenuWD_Implementation(ALT_GameHUD* InGameHUD);


//Blueprint values
public:

	/*
		Button for create new game
	*/
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "MainMenuWD|Widgets")
		UButton* HostSessionButton = nullptr;
	/*
		Button for join game
	*/
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "MainMenuWD|Widgets")
		UButton* JoinSessionButton = nullptr;
	/*
		*
	*/
	UPROPERTY(BlueprintReadOnly)
		ALT_GameHUD* GameHUD = nullptr;
	/*
		*
	*/
	UPROPERTY(BlueprintReadOnly)
		ULT_GameInstance* GameInstance = nullptr;
};
