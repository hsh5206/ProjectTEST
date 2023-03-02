// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PTMainMenu.h"
#include "Components/Button.h"

#include "PTGameInstanceSubsystem.h"
#include "Widget/PT_MultiplayMenu.h"

void UPTMainMenu::MenuSetup()
{
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		PTGIS = GameInstance->GetSubsystem<UPTGameInstanceSubsystem>();
	}
}

bool UPTMainMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	if (Button_PlayMulti)
	{
		Button_PlayMulti->OnClicked.AddDynamic(this, &ThisClass::BtnMultiClicked);
	}
	if (Button_PlaySingle)
	{
		Button_PlaySingle->OnClicked.AddDynamic(this, &ThisClass::BtnSingleClicked);
	}
	if (Button_Load)
	{
		Button_Load->OnClicked.AddDynamic(this, &ThisClass::BtnLoadClicked);
	}
	if (Button_Settings)
	{
		Button_Settings->OnClicked.AddDynamic(this, &ThisClass::BtnSettingsClicked);
	}
	if (Button_Exit)
	{
		Button_Exit->OnClicked.AddDynamic(this, &ThisClass::BtnExitClicked);
	}

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController && MultiplayMenuClass)
	{
		MultiplayMenu = CreateWidget<UPT_MultiplayMenu>(GetWorld(), MultiplayMenuClass);
		MultiplayMenu->OnBtnBackClickedDelegation.AddDynamic(this, &ThisClass::MultiMenuBackCliced);
	}

	return true;
}

void UPTMainMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);

	MenuTearDown();
}

void UPTMainMenu::BtnMultiClicked()
{
	SetVisibility(ESlateVisibility::Hidden);

	if (MultiplayMenu)
	{
		MultiplayMenu->AddToViewport();
	}
}

void UPTMainMenu::BtnSingleClicked()
{

}

void UPTMainMenu::BtnLoadClicked()
{

}

void UPTMainMenu::BtnSettingsClicked()
{
	/** 환경설정 추후 */
}

void UPTMainMenu::BtnExitClicked()
{
	// 블루프린트
}

void UPTMainMenu::MultiMenuBackCliced()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UPTMainMenu::MenuTearDown()
{
	RemoveFromParent();
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeGameOnly InputModeData;
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(false);
		}
	}
}
