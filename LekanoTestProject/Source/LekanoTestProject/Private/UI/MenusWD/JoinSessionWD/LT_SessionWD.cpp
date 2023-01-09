// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MenusWD/JoinSessionWD/LT_SessionWD.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "GameMode/LT_GameInstance.h"


ULT_SessionWD::ULT_SessionWD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void ULT_SessionWD::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstance = Cast<ULT_GameInstance>(GetGameInstance());
	
	if( IsValid(JoinSessionButton) ) JoinSessionButton->OnClicked.AddDynamic(this, &ULT_SessionWD::OnJoinSessionButtonClicked);
}


void ULT_SessionWD::InitializeSessionWD(FOnlineSessionSearchResult InSearchResult)
{
	SearchResult = InSearchResult;
	SessionName = FName(InSearchResult.GetSessionIdStr());

	ServerNameText->SetText(FText::FromString(InSearchResult.GetSessionIdStr()));
	AmountOfPlayersText->SetText(FText::FromString(
		FString::FromInt(InSearchResult.Session.SessionSettings.NumPublicConnections - InSearchResult.Session.NumOpenPublicConnections) + "/"
		+ FString::FromInt(InSearchResult.Session.NumOpenPublicConnections + 1)));
		PingText->SetText(FText::FromString(FString::FromInt(InSearchResult.PingInMs) + "ms"));
}


void ULT_SessionWD::OnJoinSessionButtonClicked()
{
	if( IsValid(GameInstance) )
	{
		const ULocalPlayer* LPlayer = GameInstance->GetFirstGamePlayer();
		if( !IsValid(LPlayer) ) return;
		
		GameInstance->JoinSessionByName(LPlayer->GetPreferredUniqueNetId().GetUniqueNetId(), NAME_GameSession, SearchResult);
	} 
}
