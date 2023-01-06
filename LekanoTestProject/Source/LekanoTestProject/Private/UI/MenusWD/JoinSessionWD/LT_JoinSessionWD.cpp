// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MenusWD/JoinSessionWD/LT_JoinSessionWD.h"

#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/ScrollBox.h"


#include "UI/MenusWD/JoinSessionWD/LT_SessionWD.h"


#include "GameMode/LT_GameInstance.h"
#include "GameMode/LT_GameHUD.h"

#include "OnlineSubsystem.h"




ULT_JoinSessionWD::ULT_JoinSessionWD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsFocusable = true;
}

void ULT_JoinSessionWD::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstance = Cast<ULT_GameInstance>(GetGameInstance());

	if( IsValid(FindSessionsButton) ) FindSessionsButton->OnClicked.AddDynamic(this, &ULT_JoinSessionWD::OnFindSessionButtonClicked);

	if( IsValid(GameInstance) ) GameInstance->OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &ULT_JoinSessionWD::OnFindSessionsComplete);
}


void ULT_JoinSessionWD::InitializeJoinSessionWD_Implementation(ALT_GameHUD* InGameHUD)
{
	if( IsValid(InGameHUD) ) GameHUD = InGameHUD;
}

void ULT_JoinSessionWD::OnFindSessionButtonClicked()
{
	if( IsValid(GameInstance) )
	{
		const ULocalPlayer* LPlayer = GameInstance->GetFirstGamePlayer();
		if( !IsValid(LPlayer) ) return;
		
		GameInstance->FindSessions(LPlayer->GetPreferredUniqueNetId().GetUniqueNetId(), DoSearchLANCheckBox->IsChecked(), false);
	} 
}

void ULT_JoinSessionWD::OnFindSessionsComplete(bool bWasSuccessful)
{
	if( SessionWDClass.IsNull() || !IsValid(GameInstance) ) return;

	if ( const IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get() )
	{
		const IOnlineSessionPtr SessionInterface = OnlineSub->GetSessionInterface();
		if ( SessionInterface.IsValid() )
		{
			SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(GameInstance->OnFindSessionsCompleteDelegateHandle);
		}

		if( IsValid(SessionsScrollBox) ) SessionsScrollBox->ClearChildren();

		for(const auto& SearchResult : GameInstance->GetSessionSearchResults())
		{
			ULT_SessionWD* SessionWD = CreateWidget<ULT_SessionWD>(GetWorld(), SessionWDClass.LoadSynchronous());
			if( IsValid(SessionWD) )
			{
				SessionWD->InitializeSessionWD(SearchResult);
				if( IsValid(SessionsScrollBox) ) SessionsScrollBox->AddChild(SessionWD);
			}
		}
	}
}