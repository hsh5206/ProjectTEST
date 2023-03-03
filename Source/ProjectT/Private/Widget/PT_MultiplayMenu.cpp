// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PT_MultiplayMenu.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"

#include "OnlineSessionSettings.h"
#include "Components/ScrollBox.h"
#include "OnlineSubsystem.h"

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
	if (Slider_PlayerNum)
	{
		Slider_PlayerNum->OnValueChanged.AddDynamic(this, &ThisClass::SliderChanged);
	}

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		PTGIS = GameInstance->GetSubsystem<UPTGameInstanceSubsystem>();
	}

	if (PTGIS)
	{
		PTGIS->MultiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
		PTGIS->MultiplayerOnFindSessionsComplete.AddUObject(this, &ThisClass::OnFindSessions);
	}

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController && ServerInfoClass)
	{
		ServerInfo = CreateWidget<UPT_ServerInfo>(GetWorld(), ServerInfoClass);
	}

	return true;
}

void UPT_MultiplayMenu::BtnRefreshClicked()
{
	if (PTGIS)
	{
		PTGIS->FindSessions(1000);
	}
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

void UPT_MultiplayMenu::SliderChanged(float value)
{
	NumPublicConnections = int32(value);
	FString Str = FString::Printf(TEXT("%d명"), int32(value));
	PlayerNum->SetText(FText::FromString(Str));
}

void UPT_MultiplayMenu::OnCreateSession(bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("OnCreateSessionCalled"));
	if (bWasSuccessful)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel("/Game/Map/MainLevel?listen");
		}

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::
				Green,
				FString::Printf(TEXT("Success to Create Session"))
			);
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString::Printf(TEXT("Failed to Create Session : MultiMenu"))
			);
		}
	}
}

void UPT_MultiplayMenu::OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Green,
			FString::Printf(TEXT("FindSession Successed"))
		);
		for (auto Result : SessionResults)
		{
			FString UserName = Result.Session.OwningUserName;
			int32 PlayerCurNum = Result.Session.NumOpenPublicConnections;
			int32 MaxPlayerNum = Result.Session.SessionSettings.NumPublicConnections;
			int32 Ping = Result.PingInMs;

			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(
					-1,
					15.f,
					FColor::Green,
					FString::Printf(TEXT("%s, %d / %d, %d"), *UserName, PlayerCurNum, MaxPlayerNum, Ping)
				);
			}
			
			UPT_ServerInfo* Info = CreateWidget<UPT_ServerInfo>(GetWorld(), ServerInfoClass);
			Info->SetText(UserName, PlayerCurNum, MaxPlayerNum, Ping);
			Info->SearchResult = Result;
			ServerScroll->AddChild(Info);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Red,
			FString::Printf(TEXT("FindSession Failed"))
		);
	}
}

void UPT_MultiplayMenu::OnStartSession(bool bWasSuccessful)
{

}

void UPT_MultiplayMenu::OnDestroySession(bool bWasSuccessful)
{

}
