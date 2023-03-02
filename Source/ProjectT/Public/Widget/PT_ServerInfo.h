// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

#include "PT_ServerInfo.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTT_API UPT_ServerInfo : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;
	
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Name;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Player;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Ping;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Join;

	FOnlineSessionSearchResult SearchResult;

	void SetText(FString NameStr, int32 PlayerNum, int32 MaxPlayerNum, int32 Ping);

private:
	// for Multi
	class UPTGameInstanceSubsystem* PTGIS;

	UFUNCTION()
	void BtnJoinClicked();
	void OnJoinSessions(EOnJoinSessionCompleteResult::Type Result);
};
