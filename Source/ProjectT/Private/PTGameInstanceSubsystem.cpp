// Fill out your copyright notice in the Description page of Project Settings.


#include "PTGameInstanceSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

#include "PTGameInstanceSubsystem.h"

UPTGameInstanceSubsystem::UPTGameInstanceSubsystem() :
	CreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete)),
	FindSessionsCompleteDelegate(FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnFindSessionsComplete)),
	JoinSessionCompleteDelegate(FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnJoinSessionComplete)),
	StartSessionCompleteDelegate(FOnStartSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnStartSessionComplete)),
	DestroySessionCompleteDelegate(FOnDestroySessionCompleteDelegate::CreateUObject(this, &ThisClass::OnDestroySessionComplete))
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		SessionInterface = Subsystem->GetSessionInterface();
	}
}

void UPTGameInstanceSubsystem::CreateSession(int32 NumPublicConnections)
{
	if (!SessionInterface) return;

	// 扁粮 技记 昏力
	auto ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession);
	if (ExistingSession != nullptr)
	{
		SessionInterface->DestroySession(NAME_GameSession);
	}

	// 目胶乓 胆府霸捞飘 殿废
	CreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);

	// 技记 技泼 棺 技记 积己
	TSharedPtr<FOnlineSessionSettings> SessionSettings = MakeShareable(new FOnlineSessionSettings());
	SessionSettings->bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true : false;
	SessionSettings->NumPublicConnections = NumPublicConnections;
	SessionSettings->bAllowJoinInProgress = true;
	SessionSettings->bAllowJoinViaPresence = true;
	SessionSettings->bShouldAdvertise = true;
	SessionSettings->bUsesPresence = true;
	// SessionSettings->Set(FName("MatchType"), FString("FreeForAll"), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing); // Match Type
	// SessionSettings->bUseLobbiesIfAbailable = true;
	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	if (!SessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *SessionSettings))
	{
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);

		MultiplayerOnCreateSessionComplete.Broadcast(false);
	}
}

void UPTGameInstanceSubsystem::FindSessions(int32 MAxSearchResults)
{
}

void UPTGameInstanceSubsystem::JoinSession(const FOnlineSessionSearchResult& SessionResults)
{
}

void UPTGameInstanceSubsystem::DestroySession()
{
}

void UPTGameInstanceSubsystem::StartSession()
{
}

void UPTGameInstanceSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccesful)
{
	if (SessionInterface)
	{
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);
	}
	MultiplayerOnCreateSessionComplete.Broadcast(true);
}

void UPTGameInstanceSubsystem::OnFindSessionsComplete(bool bWasSuccesful)
{
}

void UPTGameInstanceSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
}

void UPTGameInstanceSubsystem::OnStartSessionComplete(FName SessionName, bool bWasSuccesful)
{
}

void UPTGameInstanceSubsystem::OnDestroySessionComplete(FName SessionName, bool bWasSuccesful)
{
}
