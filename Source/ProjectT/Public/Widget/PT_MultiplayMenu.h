// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PT_MultiplayMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBtnBackClickedDelegation);
/**
 * 
 */
UCLASS()
class PROJECTT_API UPT_MultiplayMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FOnBtnBackClickedDelegation OnBtnBackClickedDelegation;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> ServerInfoClass;
	UPROPERTY(VisibleAnywhere, Category = "Widget")
	class UPT_ServerInfo* ServerInfo;

protected:
	virtual bool Initialize() override;
	void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UScrollBox* ServerScroll;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Refresh;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Host;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Back;
	
	UFUNCTION()
	void BtnRefreshClicked();
	UFUNCTION()
	void BtnHostClicked();
	UFUNCTION()
	void BtnBackClicked();

	// for Multi
	class UPTGameInstanceSubsystem* PTGIS;

	/** Host Infos */
	int32 NumPublicConnections = 4;

	/** Callbacks custom delegate from multiplyaer */
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);
};