// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PT_ServerInfo.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "OnlineSubsystem.h"
#include "PTGameInstanceSubsystem.h"

bool UPT_ServerInfo::Initialize()
{
	if (!Super::Initialize()) return false;

	if (Button_Join)
	{
		Button_Join->OnClicked.AddDynamic(this, &ThisClass::BtnJoinClicked);
	}

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		PTGIS = GameInstance->GetSubsystem<UPTGameInstanceSubsystem>();
	}

	if (PTGIS)
	{
		PTGIS->MultiplayerOnJoinSessionComplete.AddUObject(this, &ThisClass::OnJoinSessions);
	}
	return true;
}

void UPT_ServerInfo::SetText(FString NameStr, int32 PlayerNum, int32 MaxPlayerNum, int32 PingStr)
{
	Name->SetText(FText::FromString(NameStr));
	Player->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), PlayerNum, MaxPlayerNum)));
	Ping->SetText(FText::FromString(FString::Printf(TEXT("%d"), PingStr)));
}

void UPT_ServerInfo::BtnJoinClicked()
{
	PTGIS->JoinSession(SearchResult);
}

void UPT_ServerInfo::OnJoinSessions(EOnJoinSessionCompleteResult::Type Result)
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();

		FString Address;
		SessionInterface->GetResolvedConnectString(NAME_GameSession, Address);

		APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
		if (PlayerController)
		{
			PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
		}
	}
}
