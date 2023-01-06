// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MenusWD/PauseMenuWD/LT_PauseMenuWD.h"

#include "Components/Button.h"
#include "GameMode/LT_GameHUD.h"
#include "GameMode/LT_GameInstance.h"
#include "Kismet/GameplayStatics.h"

ULT_PauseMenuWD::ULT_PauseMenuWD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsFocusable = true;
}

void ULT_PauseMenuWD::NativeConstruct()
{
	Super::NativeConstruct();

	//AGameModeBase::StartPlay()
	BackToMenuButton->OnClicked.AddDynamic(this, &ULT_PauseMenuWD::OnBackToMenuButtonClicked);
}


void ULT_PauseMenuWD::InitializePauseMenuWD_Implementation(ALT_GameHUD* InGameHUD)
{
	GameHUD = InGameHUD;

	SetKeyboardFocus();
}


FReply ULT_PauseMenuWD::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if( EKeys::Escape == InKeyEvent.GetKey() )
	{
		GameHUD->RemovePauseMenuWD();

		return FReply::Handled();
	}
	
	return FReply::Unhandled();
}


void ULT_PauseMenuWD::OnBackToMenuButtonClicked()
{
	ULT_GameInstance* LGameInstance = Cast<ULT_GameInstance>(GetGameInstance());
	if( !IsValid(LGameInstance) ) return;
	
	UGameplayStatics::OpenLevel(GetWorld(), FName(LGameInstance->GetMainMenuMapName()), true);

	LGameInstance->DestroySession();
}

