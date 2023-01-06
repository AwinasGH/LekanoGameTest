// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MenusWD/LT_MainMenuWD.h"

#include "Components/Button.h"
#include "GameMode/LT_GameHUD.h"
#include "GameMode/LT_GameInstance.h"

ULT_MainMenuWD::ULT_MainMenuWD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsFocusable = true;
}

void ULT_MainMenuWD::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstance = Cast<ULT_GameInstance>(GetGameInstance());
	
	if( IsValid(HostSessionButton) ) HostSessionButton->OnClicked.AddDynamic(this, &ULT_MainMenuWD::OnHostSessionButtonClicked);
	if( IsValid(JoinSessionButton) ) JoinSessionButton->OnClicked.AddDynamic(this, &ULT_MainMenuWD::OnJoinSessionButtonClicked);
}

void ULT_MainMenuWD::InitializeMainMenuWD_Implementation(ALT_GameHUD* InGameHUD)
{
	if( IsValid(InGameHUD) ) GameHUD = InGameHUD;
}


void ULT_MainMenuWD::OnHostSessionButtonClicked()
{
	if( IsValid(GameHUD) ) GameHUD->CreateCreateSessionWD();
}

void ULT_MainMenuWD::OnJoinSessionButtonClicked()
{
	if( IsValid(GameHUD) ) GameHUD->CreateJoinSessionWD();
}
