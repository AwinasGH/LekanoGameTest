// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LT_JoinSessionWD.generated.h"

class ULT_GameInstance;
class UCheckBox;
class UScrollBox;
class UButton;
class ULT_SessionWD;
class ALT_GameHUD;


/*
 *  Widget for searching and joining sessions
*/
UCLASS(Abstract)

class LEKANOTESTPROJECT_API ULT_JoinSessionWD : public UUserWidget
{
	GENERATED_BODY()
	
//constructors
public:

	ULT_JoinSessionWD(const FObjectInitializer& ObjectInitializer);

//c++ protected methods
protected:

	virtual void NativeConstruct() override;


	UFUNCTION()
		void OnFindSessionButtonClicked();

	UFUNCTION()
		void OnFindSessionsComplete(bool bWasSuccessful);

//>>..........................................................................................................................<<//



//Blueprint methods
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "JoinSessionWD")
		void InitializeJoinSessionWD(ALT_GameHUD* InGameHUD);
		virtual void InitializeJoinSessionWD_Implementation(ALT_GameHUD* InGameHUD);


//Blueprint values
public:

	/*
		Button for create new game
	*/
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "JoinSessionWD|Widgets")
		UButton* FindSessionsButton = nullptr;
	/*
		Need to search LAN sessions check box 
	*/
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "JoinSessionWD|Widgets")
		UCheckBox* DoSearchLANCheckBox = nullptr;
	/*
		Button for create new game
	*/
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "JoinSessionWD|Widgets")
		UScrollBox* SessionsScrollBox = nullptr;
	/*
		Session widget class
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "JoinSessionWD|Classes")
		TSoftClassPtr<ULT_SessionWD> SessionWDClass;
	/*
		
	*/
	UPROPERTY(BlueprintReadOnly)
		ALT_GameHUD* GameHUD = nullptr;
	/*
		
	*/
	UPROPERTY(BlueprintReadOnly)
		ULT_GameInstance* GameInstance = nullptr;
};
