// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "PTGameInstanceSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnCreateSessionComplete, bool, bWasSuccessful);

UCLASS()
class PROJECTT_API UPTGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UPTGameInstanceSubsystem();

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FMultiplayerOnCreateSessionComplete MultiplayerOnCreateSessionComplete;

	// Menu Handle
	void CreateSession(int32 NumPublicConnections);
	void FindSessions(int32 MAxSearchResults);
	void JoinSession(const FOnlineSessionSearchResult& SessionResults);
	void DestroySession();
	void StartSession();

protected:
	// 세션 생성 델리게이트 콜백
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccesful);
	// 세션 찾기 델리게이트 콜백
	void OnFindSessionsComplete(bool bWasSuccesful);
	// 세션 참가 델리게이트 콜백
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	// 세션 시작 델리게이트 콜백
	void OnStartSessionComplete(FName SessionName, bool bWasSuccesful);
	// 세션 제거 델리게이트 콜백
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccesful);

private:
	IOnlineSessionPtr SessionInterface;

	// 세션 생성 델리게이트
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FDelegateHandle CreateSessionCompleteDelegateHandle;
	// 세션 찾기 델리게이트
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FDelegateHandle FindSessionsCompleteDelegateHandle;
	// 세션 참가 델리게이트
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
	FDelegateHandle JoinSessionCompleteDelegateHandle;
	// 세션 시작 델리게이트
	FOnStartSessionCompleteDelegate StartSessionCompleteDelegate;
	FDelegateHandle StartSessionCompleteDelegateHandle;
	// 세션 제거 델리게이트
	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;
	FDelegateHandle DestroySessionCompleteDelegateHandle;
};
