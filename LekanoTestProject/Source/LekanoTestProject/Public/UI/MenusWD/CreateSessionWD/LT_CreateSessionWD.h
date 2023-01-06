// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LT_CreateSessionWD.generated.h"


class ALT_GameHUD;
class ULT_GameInstance;
class UEditableTextBox;
class UCheckBox;
class UButton;
class APO_GameHUD;



/*
 *  Widget for creating session
*/
UCLASS(Abstract)
class LEKANOTESTPROJECT_API ULT_CreateSessionWD : public UUserWidget
{
	GENERATED_BODY()

	
//constructors
public:

	ULT_CreateSessionWD(const FObjectInitializer& ObjectInitializer);

//c++ protected methods
protected:

	virtual void NativeConstruct() override;


	UFUNCTION()
		void OnCreateSessionButtonClicked();

//>>..........................................................................................................................<<//



//Blueprint methods
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CreateSessionWD")
		void InitializeCreateSessionWD(ALT_GameHUD* InGameHUD);
		virtual void InitializeCreateSessionWD_Implementation(ALT_GameHUD* InGameHUD);


//Blueprint values
public:

	/*
		Button for create new game
	*/
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "CreateSessionWD|Widgets")
		UButton* CreateSessionButton = nullptr;
	/*
		IP address text 
	*/
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "CreateSessionWD|Widgets")
		UEditableTextBox* MaxPlayersEditableText = nullptr;
	/*
		Need to host LAN session check box 
	*/
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "CreateSessionWD|Widgets")
		UCheckBox* IsLANCheckBox = nullptr;
	/*
		
	*/
	UPROPERTY(BlueprintReadOnly)
		ALT_GameHUD* GameHUD = nullptr;
	/*
		
	*/
	UPROPERTY(BlueprintReadOnly)
		ULT_GameInstance* GameInstance = nullptr;
};
