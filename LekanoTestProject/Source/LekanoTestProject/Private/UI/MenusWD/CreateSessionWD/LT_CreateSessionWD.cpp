// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MenusWD/CreateSessionWD/LT_CreateSessionWD.h"

#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/EditableTextBox.h"

#include "GameMode/LT_GameHUD.h"
#include "GameMode/LT_GameInstance.h"


ULT_CreateSessionWD::ULT_CreateSessionWD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsFocusable = true;
}

void ULT_CreateSessionWD::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstance = Cast<ULT_GameInstance>(GetGameInstance());

	if( IsValid(CreateSessionButton) ) CreateSessionButton->OnClicked.AddDynamic(this, &ULT_CreateSessionWD::OnCreateSessionButtonClicked);
}



void ULT_CreateSessionWD::InitializeCreateSessionWD_Implementation(ALT_GameHUD* InGameHUD)
{
	if( IsValid(InGameHUD) ) GameHUD = InGameHUD;
}

void ULT_CreateSessionWD::OnCreateSessionButtonClicked()
{
	if( IsValid(GameInstance) )
	{
		const ULocalPlayer* LPlayer = GameInstance->GetFirstGamePlayer();
		if( !IsValid(LPlayer) ) return;
		
		GameInstance->HostSession(
			LPlayer->GetUniqueNetIdForPlatformUser().GetUniqueNetId(),
			NAME_GameSession,
			IsLANCheckBox->IsChecked(),
			false,
			FCString::Atoi(*MaxPlayersEditableText->GetText().ToString()));
	}
}

