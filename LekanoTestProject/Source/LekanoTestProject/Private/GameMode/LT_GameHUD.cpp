// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LT_GameHUD.h"

#include "Blueprint/UserWidget.h"
#include "Character/Player/LT_PlayerController.h"
#include "GameMode/LT_GameInstance.h"
#include "UI/MenusWD/LT_MainMenuWD.h"
#include "UI/MenusWD/CreateSessionWD/LT_CreateSessionWD.h"
#include "UI/MenusWD/JoinSessionWD/LT_JoinSessionWD.h"
#include "UI/MenusWD/PauseMenuWD/LT_PauseMenuWD.h"


ALT_GameHUD::ALT_GameHUD()
{
	
}

void ALT_GameHUD::SetFocusToWidget(EWidgetFocusType WidgetFocusType, UUserWidget* InWidget)
{
	if( !IsValid(InWidget) ) return;


	switch( WidgetFocusType )
	{
	case EWidgetFocusType::GameOnly:
		{
			MyController->SetInputMode(FInputModeGameOnly());
			
			break;
		}
		
	case EWidgetFocusType::UIOnly:
		{
			MyController->SetInputMode(FInputModeUIOnly());
			
			break;
		}
	case EWidgetFocusType::GameAndUI:
		{
			MyController->SetInputMode(FInputModeGameAndUI());
			
			break;
		}
	default: MyController->SetInputMode(FInputModeGameOnly());
	}

	if( InWidget->bIsFocusable ) InWidget->SetKeyboardFocus();
}

void ALT_GameHUD::AddWidgetToFocusStack(EWidgetFocusType WidgetFocusType, UUserWidget* InWidget)
{
	if( !IsValid(InWidget) ) return;


	if( WidgetFocusStack.Num() == 0 || WidgetFocusStack[WidgetFocusStack.Num() - 1].Widget != InWidget )
	{
		WidgetFocusStack.Add(FWidgetFocusInfo(WidgetFocusType, InWidget));
	}
}

void ALT_GameHUD::RemoveWidgetFromFocusStack(UUserWidget* InWidget)
{
	WidgetFocusStack.RemoveAll([InWidget](const FWidgetFocusInfo& LInfo){ return InWidget == LInfo.Widget || !IsValid(LInfo.Widget); });
}

void ALT_GameHUD::FocusLastWidgetInStack()
{
	if( WidgetFocusStack.Num() > 0 )
	{
		const FWidgetFocusInfo WidgetFocusInfo = WidgetFocusStack[WidgetFocusStack.Num() - 1];
		SetFocusToWidget(WidgetFocusInfo.FocusType, WidgetFocusInfo.Widget);
	}
}

void ALT_GameHUD::ClearWidgetFocusStack()
{
	WidgetFocusStack.Empty();
}

void ALT_GameHUD::BeginPlay()
{
	Super::BeginPlay();

	MyController = Cast<ALT_PlayerController>(GetOwningPlayerController());
	GameInstance = Cast<ULT_GameInstance>(GetGameInstance());
}






void ALT_GameHUD::CreateMainMenuWD()
{
	RemoveAllWD();

	if( !MainMenuWDClass.IsNull() && !MainMenuWD )
	{
		MainMenuWD = CreateWidget<ULT_MainMenuWD>(GetWorld(), MainMenuWDClass.LoadSynchronous());
		if( IsValid(MainMenuWD) )
		{
			MainMenuWD->InitializeMainMenuWD(this);
			MainMenuWD->AddToViewport();
		}

		SetFocusToMainMenuWD();
	}
}

void ALT_GameHUD::SetFocusToMainMenuWD()
{
	if( IsValid(MainMenuWD) )
	{
		MyController->SetShowMouseCursor(true);

		AddWidgetToFocusStack(EWidgetFocusType::UIOnly, MainMenuWD);
		SetFocusToWidget(EWidgetFocusType::UIOnly, MainMenuWD);
	}
}

void ALT_GameHUD::RemoveMainMenuWD()
{
	if( IsValid(MainMenuWD) )
	{
		RemoveWidgetFromFocusStack(MainMenuWD);
		FocusLastWidgetInStack();

		MainMenuWD->RemoveFromParent();
		MainMenuWD = nullptr;

		MyController->SetShowMouseCursor(false);
		MyController->SetInputMode(FInputModeGameOnly());
	}
}

void ALT_GameHUD::CreatePauseMenuWD()
{
	RemoveAllWD();

	if( !PauseMenuWDClass.IsNull() && !PauseMenuWD )
	{
		PauseMenuWD = CreateWidget<ULT_PauseMenuWD>(GetWorld(), PauseMenuWDClass.LoadSynchronous());
		if( IsValid(PauseMenuWD) )
		{
			PauseMenuWD->InitializePauseMenuWD(this);
			PauseMenuWD->AddToViewport();
		}

		SetFocusToPauseMenuWD();
	}
}

void ALT_GameHUD::SetFocusToPauseMenuWD()
{
	if( IsValid(PauseMenuWD) )
	{
		MyController->SetShowMouseCursor(true);

		AddWidgetToFocusStack(EWidgetFocusType::UIOnly, PauseMenuWD);
		SetFocusToWidget(EWidgetFocusType::UIOnly, PauseMenuWD);
	}
}

void ALT_GameHUD::RemovePauseMenuWD()
{
	if( IsValid(PauseMenuWD) )
	{
		RemoveWidgetFromFocusStack(PauseMenuWD);
		FocusLastWidgetInStack();

		PauseMenuWD->RemoveFromParent();
		PauseMenuWD = nullptr;

		MyController->SetShowMouseCursor(false);
		MyController->SetInputMode(FInputModeGameOnly());
	}
}


void ALT_GameHUD::CreateCreateSessionWD()
{
	RemoveAllWD();
	
	if( !CreateSessionWDClass.IsNull() && !CreateSessionWD )
	{
		CreateSessionWD = CreateWidget<ULT_CreateSessionWD>(GetWorld(), CreateSessionWDClass.LoadSynchronous());
		if( IsValid(CreateSessionWD) )
		{
			CreateSessionWD->InitializeCreateSessionWD(this);
			CreateSessionWD->AddToViewport();
		}

		SetFocusToCreateSessionWD();
	}
}

void ALT_GameHUD::SetFocusToCreateSessionWD()
{
	if( IsValid(CreateSessionWD) )
	{
		MyController->SetShowMouseCursor(true);
		
		AddWidgetToFocusStack(EWidgetFocusType::UIOnly, CreateSessionWD);
		SetFocusToWidget(EWidgetFocusType::UIOnly, CreateSessionWD);
	}
}

void ALT_GameHUD::RemoveCreateSessionWD()
{
	if( IsValid(CreateSessionWD) )
	{
		RemoveWidgetFromFocusStack(CreateSessionWD);
		FocusLastWidgetInStack();

		CreateSessionWD->RemoveFromParent();
		CreateSessionWD = nullptr;

		MyController->SetShowMouseCursor(false);
		MyController->SetInputMode(FInputModeGameOnly());
	}
}



void ALT_GameHUD::CreateJoinSessionWD()
{
	RemoveAllWD();
	
	if( !JoinSessionWDClass.IsNull() && !JoinSessionWD )
	{
		JoinSessionWD = CreateWidget<ULT_JoinSessionWD>(GetWorld(), JoinSessionWDClass.LoadSynchronous());
		if( IsValid(JoinSessionWD) )
		{
			JoinSessionWD->InitializeJoinSessionWD(this);
			JoinSessionWD->AddToViewport();
		}

		SetFocusToJoinSessionWD();
	}
}

void ALT_GameHUD::SetFocusToJoinSessionWD()
{
	if( IsValid(JoinSessionWD) )
	{
		MyController->SetShowMouseCursor(true);
		
		AddWidgetToFocusStack(EWidgetFocusType::UIOnly, JoinSessionWD);
		SetFocusToWidget(EWidgetFocusType::UIOnly, JoinSessionWD);
	}
}

void ALT_GameHUD::RemoveJoinSessionWD()
{
	if( IsValid(JoinSessionWD) )
	{
		RemoveWidgetFromFocusStack(JoinSessionWD);
		FocusLastWidgetInStack();

		JoinSessionWD->RemoveFromParent();
		JoinSessionWD = nullptr;

		MyController->SetShowMouseCursor(false);
		MyController->SetInputMode(FInputModeGameOnly());
	}
}




void ALT_GameHUD::RemoveAllWD()
{
	RemoveMainMenuWD();
	RemoveCreateSessionWD();
	RemoveJoinSessionWD();
}

void ALT_GameHUD::RemoveAllGameplayWD()
{
	
}
