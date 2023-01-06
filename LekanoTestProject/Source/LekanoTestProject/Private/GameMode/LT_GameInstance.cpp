// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LT_GameInstance.h"

#include "OnlineSubsystem.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Character/Player/LT_PlayerController.h"
#include "GameMode/LT_GameHUD.h"
#include "Kismet/GameplayStatics.h"


ULT_GameInstance::ULT_GameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &ULT_GameInstance::OnCreateSessionComplete);
	OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(this, &ULT_GameInstance::OnStartOnlineGameComplete);
	
	OnJoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(this, &ULT_GameInstance::OnJoinSessionComplete);
	
	OnDestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(this, &ULT_GameInstance::OnDestroySessionComplete);
}


//............................GameStartup............................................//

void ULT_GameInstance::OnMainMenuOpened(USoundClass* EffectsSoundClass, USoundMix* EffectsSoundMix,
																		USoundClass* UISoundClass,
																		USoundMix* UISoundMix,
																		USoundClass* SpeechSoundClass,
																		USoundMix* SpeechSoundMix,
																		USoundClass* MusicSoundClass,
																		USoundMix* MusicSoundMix,
																		UMaterialParameterCollection* GlobalMatParamCollection)
{
	IsGameStarted = false;
	
	CurrentMapName = MainMenuMapName;

	UWidgetBlueprintLibrary::SetFocusToGameViewport();
	if( const ALT_PlayerController* LPlayerController = Cast<ALT_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)) )
	{
		LPlayerController->MyGameHUD->CreateMainMenuWD();
	}
}








bool ULT_GameInstance::HostSession(const TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers)
{
	if ( const IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get() )
	{
		const IOnlineSessionPtr SessionInterface = OnlineSub->GetSessionInterface();
		
		if ( SessionInterface.IsValid() && UserId.IsValid() )
		{
			SessionSettings = MakeShareable(new FOnlineSessionSettings());

			SessionSettings->bIsLANMatch = bIsLAN;
			SessionSettings->bUsesPresence = bIsPresence;
			SessionSettings->NumPublicConnections = MaxNumPlayers;
			SessionSettings->NumPrivateConnections = 0;
			SessionSettings->bAllowInvites = true;
			SessionSettings->bAllowJoinInProgress = true;
			SessionSettings->bShouldAdvertise = true;
			SessionSettings->bAllowJoinViaPresence = true;
			SessionSettings->bAllowJoinViaPresenceFriendsOnly = false;

			SessionSettings->Set(SETTING_MAPNAME, FString(GameplayLevelMapName), EOnlineDataAdvertisementType::ViaOnlineService);

			OnCreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);
			
			return SessionInterface->CreateSession(*UserId, SessionName, *SessionSettings);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "No OnlineSubsystem found!");
	}

	return false;
}

void ULT_GameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if ( const IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get() )
	{
		const IOnlineSessionPtr SessionInterface = OnlineSub->GetSessionInterface();
		
		if ( SessionInterface.IsValid() )
		{
			SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
			if ( bWasSuccessful == true )
			{
				OnStartSessionCompleteDelegateHandle = SessionInterface->AddOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegate);

				SessionInterface->StartSession(SessionName);
			}
		}
	}
}

void ULT_GameInstance::OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful)
{
	if ( const IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get() )
	{
		const IOnlineSessionPtr SessionInterface = OnlineSub->GetSessionInterface();
		if ( SessionInterface.IsValid() )
		{
			SessionInterface->ClearOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegateHandle);
		}
	}
	
	if ( bWasSuccessful == true )
	{
		IsGameStarted = true;
		
		UGameplayStatics::OpenLevel(GetWorld(), FName(GameplayLevelMapName), true, "listen");
	}
}




void ULT_GameInstance::FindSessions(const TSharedPtr<const FUniqueNetId> UserId, bool bIsLAN, bool bIsPresence)
{
	if ( const IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get() )
	{
		const IOnlineSessionPtr SessionInterface = OnlineSub->GetSessionInterface();

		if ( SessionInterface.IsValid() && UserId.IsValid() )
		{
			SessionSearch = MakeShareable(new FOnlineSessionSearch());

			SessionSearch->bIsLanQuery = bIsLAN;
			SessionSearch->MaxSearchResults = 20;
			SessionSearch->PingBucketSize = 50;
			SessionSearch->PingBucketSize = 50;
			
			if ( bIsPresence == true )
			{
				SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, bIsPresence, EOnlineComparisonOp::Equals);
			}

			const TSharedRef<FOnlineSessionSearch> SearchSettingsRef = SessionSearch.ToSharedRef();
			
			OnFindSessionsCompleteDelegateHandle = SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);
			
			SessionInterface->FindSessions(*UserId, SearchSettingsRef);
		}
	}
	else
	{
		OnFindSessionsComplete(false);
	}
}

void ULT_GameInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
	if ( const IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get() )
	{
		const IOnlineSessionPtr SessionInterface = OnlineSub->GetSessionInterface();
		if ( SessionInterface.IsValid() )
		{
			SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegateHandle);

			if ( SessionSearch->SearchResults.Num() > 0 )
			{
				for (int32 SearchIdx = 0; SearchIdx < SessionSearch->SearchResults.Num(); SearchIdx++)
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Session Number: %d | Sessionname: %s "), SearchIdx+1, *(SessionSearch->SearchResults[SearchIdx].Session.OwningUserName)));
				}
			}
		}
	}
}





bool ULT_GameInstance::JoinSession(const TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult)
{
	bool bSuccessful = false;

	if ( const IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get() )
	{
		const IOnlineSessionPtr SessionInterface = OnlineSub->GetSessionInterface();

		if ( SessionInterface.IsValid() && UserId.IsValid() )
		{
			OnJoinSessionCompleteDelegateHandle = SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);
			
			bSuccessful = SessionInterface->JoinSession(*UserId, SessionName, SearchResult);
		}
	}
		
	return bSuccessful;
}

bool ULT_GameInstance::DestroySession()
{
	const IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if( OnlineSub == nullptr ) return false;

	const IOnlineSessionPtr SessionInterface = OnlineSub->GetSessionInterface();
	if( !SessionInterface.IsValid() ) return false;
	
	OnDestroySessionCompleteDelegateHandle = SessionInterface->AddOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegate);

	if ( !SessionInterface->DestroySession(NAME_GameSession) )
	{
		SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegateHandle);
	}

	return true;
}


void ULT_GameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if ( const IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get() )
	{
		const IOnlineSessionPtr SessionInterface = OnlineSub->GetSessionInterface();

		if ( SessionInterface.IsValid() )
		{
			SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);
			
			APlayerController* PlayerController = GetFirstLocalPlayerController();
			
			FString TravelURL;

			if ( IsValid(PlayerController) && SessionInterface->GetResolvedConnectString(SessionName, TravelURL))
			{
				IsGameStarted = true;
				
				PlayerController->ClientTravel(TravelURL, ETravelType::TRAVEL_Absolute, true);
			}
		}
	}
}




void ULT_GameInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	if ( const IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get() )
	{
		const IOnlineSessionPtr SessionInterface = OnlineSub->GetSessionInterface();

		if (SessionInterface.IsValid())
		{
			SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegateHandle);
			
			if ( bWasSuccessful == true )
			{
				UGameplayStatics::OpenLevel(GetWorld(), FName(MainMenuMapName), true);
			}
		}
	}
}