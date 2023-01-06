// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "Blueprint/UserWidget.h"
#include "LT_SessionWD.generated.h"

class UTextBlock;
class ULT_GameInstance;
class UButton;
class ALT_GameHUD;


/*
 *  Widget which contains session information and spawns in runtime
*/
UCLASS(Abstract)
class LEKANOTESTPROJECT_API ULT_SessionWD : public UUserWidget
{
	GENERATED_BODY()
	
//constructors
public:

	ULT_SessionWD(const FObjectInitializer& ObjectInitializer);
	

//c++ public methods
public:

	virtual void InitializeSessionWD(FOnlineSessionSearchResult InSearchResult);

//c++ protected methods
protected:

	virtual void NativeConstruct() override;


	UFUNCTION()
		void OnJoinSessionButtonClicked();


//c++ protected values
private:

	FOnlineSessionSearchResult SearchResult;

	FName SessionName; 

//>>..........................................................................................................................<<//
	


//Blueprint values
public:

	/*
		Button for create new game
	*/
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "SessionWD|Widgets")
		UButton* JoinSessionButton = nullptr;
	/*
		
	*/
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "SessionWD|Widgets")
		UTextBlock* ServerNameText = nullptr;
	/*
		
	*/
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "SessionWD|Widgets")
		UTextBlock* AmountOfPlayersText = nullptr;
	/*
		
	*/
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "SessionWD|Widgets")
		UTextBlock* PingText = nullptr;
	/*
		
	*/
	UPROPERTY(BlueprintReadOnly)
		ALT_GameHUD* GameHUD = nullptr;
	/*
		
	*/
	UPROPERTY(BlueprintReadOnly)
		ULT_GameInstance* GameInstance = nullptr;
};

