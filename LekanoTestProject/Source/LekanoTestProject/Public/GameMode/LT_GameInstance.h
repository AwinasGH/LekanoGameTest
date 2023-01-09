// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "OnlineSessionSettings.h"
#include "Engine/World.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "LT_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LEKANOTESTPROJECT_API ULT_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
//constructor
public:

	ULT_GameInstance(const FObjectInitializer& ObjectInitializer);


//c++ private values
private:

	

//c++ private values
private:

//........................................Game................................................//
	
	/*
		Flag. It tells us that we are in on the playable level. Not in main menu.
	*/
	bool IsGameStarted = false;

//............................................................................................//

//....................................Current map info........................................//

	/*
		Name of the current opened level.
	*/
	FString CurrentMapName;
	
//............................................................................................//



//...................................Session............................................//


//c++ public values
public:

	
	/* Delegate called when session created */
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	/* Delegate called when session started */
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;
	
	/** Handles to registered delegates for creating/starting a session */
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;

	TSharedPtr<FOnlineSessionSettings> SessionSettings;
	

	
	/** Delegate for searching for sessions */
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;

	/** Handle to registered delegate for searching a session */
	FDelegateHandle OnFindSessionsCompleteDelegateHandle;

	TSharedPtr<FOnlineSessionSearch> SessionSearch;


	/** Delegate for joining a session */
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;

	/** Handle to registered delegate for joining a session */
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;


	/** Delegate for destroying a session */
	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;

	/** Handle to registered delegate for destroying a session */
	FDelegateHandle OnDestroySessionCompleteDelegateHandle;
	

//.......................................................................................//
	
//>>.................................................................................................................................................<<//


//Blueprint methods
public:

	UFUNCTION(BlueprintCallable, Category = "GameStartup")
		const FString& GetMainMenuMapName() const { return MainMenuMapName; };

//............................GameStartup............................................//

	UFUNCTION(BlueprintCallable, Category = "GameStartup")
		void OnMainMenuOpened(
								USoundClass* EffectsSoundClass, USoundMix* EffectsSoundMix,
								USoundClass* UISoundClass, USoundMix* UISoundMix,
								USoundClass* SpeechSoundClass, USoundMix* SpeechSoundMix,
								USoundClass* MusicSoundClass, USoundMix* MusicSoundMix,
								UMaterialParameterCollection* GlobalMatParamCollection
							 );

	
	UFUNCTION(BlueprintCallable, Category = "GameStartup")
		FORCEINLINE bool GetIsGameStarted() const { return IsGameStarted; }
	
//...................................................................................//


//...................................Session............................................//
	
	bool HostSession(const TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers);
	
	virtual void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	
	void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);
	

	void FindSessions(const TSharedPtr<const FUniqueNetId> UserId, bool bIsLAN, bool bIsPresence);

	void OnFindSessionsComplete(bool bWasSuccessful);


	bool JoinSessionByName(const TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult);

	bool DestroySession();

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);


	virtual void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

	
	const TArray<FOnlineSessionSearchResult>& GetSessionSearchResults() const { return SessionSearch->SearchResults; }
	
//......................................................................................//
	


//Blueprint values
public:

//...................................Game............................................//
	
	/*
		Name of the main menu map.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game")
		FString MainMenuMapName = "L_MainMenu";
	/*
		Name of the gameplay level
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game")
		FString GameplayLevelMapName = "L_GameMap";

//...................................................................................//

};
