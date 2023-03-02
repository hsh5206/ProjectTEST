// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "PTGameInstanceSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnCreateSessionComplete, bool, bWasSuccessful);
DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiplayerOnFindSessionsComplete, const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);
DECLARE_MULTICAST_DELEGATE_OneParam(FMultiplayerOnJoinSessionComplete, EOnJoinSessionCompleteResult::Type Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnStartSessionComplete, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnDestroySessionComplete, bool, bWasSuccessful);

UCLASS()
class PROJECTT_API UPTGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UPTGameInstanceSubsystem();

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FMultiplayerOnCreateSessionComplete MultiplayerOnCreateSessionComplete;
	FMultiplayerOnFindSessionsComplete MultiplayerOnFindSessionsComplete;
	FMultiplayerOnJoinSessionComplete MultiplayerOnJoinSessionComplete;
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FMultiplayerOnStartSessionComplete MultiplayerOnStartSessionComplete;
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FMultiplayerOnDestroySessionComplete MultiplayerOnDestroySessionComplete;

	// Menu Handle
	void CreateSession(int32 NumPublicConnections);
	void FindSessions(int32 MAxSearchResults);
	void JoinSession(const FOnlineSessionSearchResult& SessionResults);
	void DestroySession();
	void StartSession();

protected:
	// ���� ���� ��������Ʈ �ݹ�
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccesful);
	// ���� ã�� ��������Ʈ �ݹ�
	void OnFindSessionsComplete(bool bWasSuccesful);
	// ���� ���� ��������Ʈ �ݹ�
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	// ���� ���� ��������Ʈ �ݹ�
	void OnStartSessionComplete(FName SessionName, bool bWasSuccesful);
	// ���� ���� ��������Ʈ �ݹ�
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccesful);

private:
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSettings> SessionSettings;
	TSharedPtr<FOnlineSessionSearch> SessionSearch; // ���� ã�� ���Arr

	// ���� ���� ��������Ʈ
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FDelegateHandle CreateSessionCompleteDelegateHandle;
	// ���� ã�� ��������Ʈ
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FDelegateHandle FindSessionsCompleteDelegateHandle;
	// ���� ���� ��������Ʈ
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
	FDelegateHandle JoinSessionCompleteDelegateHandle;
	// ���� ���� ��������Ʈ
	FOnStartSessionCompleteDelegate StartSessionCompleteDelegate;
	FDelegateHandle StartSessionCompleteDelegateHandle;
	// ���� ���� ��������Ʈ
	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;
	FDelegateHandle DestroySessionCompleteDelegateHandle;

};
