// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/GameplayWD/ScoreBoardWD/LT_ScoreBoardWD.h"
#include "LT_GameHUD.generated.h"


class ULT_JoinSessionWD;
class ULT_CreateSessionWD;
class ULT_MainMenuWD;
class ULT_PauseMenuWD;


UENUM()
enum class EWidgetFocusType : uint8
{
	GameOnly,
	UIOnly,
	GameAndUI
};


USTRUCT()
struct FWidgetFocusInfo
{
	GENERATED_USTRUCT_BODY()

public:

	FWidgetFocusInfo(){}
	FWidgetFocusInfo(EWidgetFocusType WidgetFocusType, UUserWidget* InWidget) : FocusType(WidgetFocusType), Widget(InWidget)
	{
		
	}

public:

	EWidgetFocusType FocusType;

	UPROPERTY()
	UUserWidget* Widget = nullptr;
};



/**
 * 
 */
UCLASS()
class LEKANOTESTPROJECT_API ALT_GameHUD : public AHUD
{
	GENERATED_BODY()
	
//constructors
public:

	ALT_GameHUD();


//c++ public methods
public:

	void SetFocusToWidget(EWidgetFocusType WidgetFocusType, UUserWidget* InWidget);
	void AddWidgetToFocusStack(EWidgetFocusType WidgetFocusType, UUserWidget* InWidget);
	void RemoveWidgetFromFocusStack(UUserWidget* InWidget);
	void FocusLastWidgetInStack();
	void ClearWidgetFocusStack();
	
//c++ protected methods
protected:

	virtual void BeginPlay() override;


//c++ private values
private:

	UPROPERTY()
		TArray<FWidgetFocusInfo> WidgetFocusStack;


//>>.................................................................................................................................................<<//
	

//Blueprint methods
public:
	
	UFUNCTION(BlueprintCallable, Category = "MainMenuWD")
		void CreateMainMenuWD();
	UFUNCTION(BlueprintCallable, Category = "MainMenuWD")
		void SetFocusToMainMenuWD();
	UFUNCTION(BlueprintCallable, Category = "MainMenuWD")
		void RemoveMainMenuWD();

	UFUNCTION(BlueprintCallable, Category = "PauseMenuWD")
		void CreatePauseMenuWD();
	UFUNCTION(BlueprintCallable, Category = "PauseMenuWD")
		void SetFocusToPauseMenuWD();
	UFUNCTION(BlueprintCallable, Category = "PauseMenuWD")
		void RemovePauseMenuWD();


	UFUNCTION(BlueprintCallable, Category = "CreateSessionWD")
		void CreateCreateSessionWD();
	UFUNCTION(BlueprintCallable, Category = "CreateSessionWD")
		void SetFocusToCreateSessionWD();
	UFUNCTION(BlueprintCallable, Category = "CreateSessionWD")
		void RemoveCreateSessionWD();


	UFUNCTION(BlueprintCallable, Category = "JoinSessionWD")
		void CreateJoinSessionWD();
	UFUNCTION(BlueprintCallable, Category = "JoinSessionWD")
		void SetFocusToJoinSessionWD();
	UFUNCTION(BlueprintCallable, Category = "JoinSessionWD")
		void RemoveJoinSessionWD();

	UFUNCTION(BlueprintCallable, Category = "ScoreBoardWD")
		void CreateScoreBoardWD();
	UFUNCTION(BlueprintCallable, Category = "ScoreBoardWD")
		void SetFocusToScoreBoardWD();
	UFUNCTION(BlueprintCallable, Category = "ScoreBoardWD")
		void RemoveScoreBoardWD();

	

	UFUNCTION(BlueprintCallable)
		void RemoveAllWD();
	UFUNCTION(BlueprintCallable)
		void RemoveAllGameplayWD();


	
//Blueprint protected values
protected:


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
		TSoftClassPtr<ULT_MainMenuWD> MainMenuWDClass;
	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
		ULT_MainMenuWD* MainMenuWD = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
		TSoftClassPtr<ULT_PauseMenuWD> PauseMenuWDClass;
	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
		ULT_PauseMenuWD* PauseMenuWD = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
		TSoftClassPtr<ULT_CreateSessionWD> CreateSessionWDClass;
	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
		ULT_CreateSessionWD* CreateSessionWD = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
		TSoftClassPtr<ULT_JoinSessionWD> JoinSessionWDClass;
	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
		ULT_JoinSessionWD* JoinSessionWD = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
		TSoftClassPtr<ULT_ScoreBoardWD> ScoreBoardWDClass;
	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
		ULT_ScoreBoardWD* ScoreBoardWD = nullptr;
	

//Blueprint public values
public:

	UPROPERTY(BlueprintReadOnly)
		class ALT_PlayerController* MyController = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
		class ULT_GameInstance* GameInstance = nullptr;
};
