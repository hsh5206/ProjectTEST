// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PT_MultiplayMenu.h"
#include "Components/Button.h"

#include "Widget/PT_ServerInfo.h"
#include "PTGameInstanceSubsystem.h"

bool UPT_MultiplayMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	if (Button_Refresh)
	{
		Button_Refresh->OnClicked.AddDynamic(this, &ThisClass::BtnRefreshClicked);
	}
	if (Button_Host)
	{
		Button_Host->OnClicked.AddDynamic(this, &ThisClass::BtnHostClicked);
	}
	if (Button_Back)
	{
		Button_Back->OnClicked.AddDynamic(this, &ThisClass::BtnBackClicked);
	}

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		PTGIS = GameInstance->GetSubsystem<UPTGameInstanceSubsystem>();
	}

	if (PTGIS)
	{
		PTGIS->MultiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
	}

	return true;
}

void UPT_MultiplayMenu::NativeConstruct()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController && ServerInfoClass)
	{
		ServerInfo = CreateWidget<UPT_ServerInfo>(GetWorld(), ServerInfoClass);
	}
}

void UPT_MultiplayMenu::BtnRefreshClicked()
{

}

void UPT_MultiplayMenu::BtnHostClicked()
{
	if (PTGIS)
	{
		PTGIS->CreateSession(NumPublicConnections);
	}
}

void UPT_MultiplayMenu::BtnBackClicked()
{
	RemoveFromParent();

	OnBtnBackClickedDelegation.Broadcast();
}

void UPT_MultiplayMenu::OnCreateSession(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel("/Game/Map/MainLevel?listen");
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Green,
				FString::Printf(TEXT("Failed to Create Session Call"))
			);
		}
	}
}