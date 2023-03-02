// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PTMainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTT_API UPTMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Blueprintcallable)
	void MenuSetup();

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> MultiplayMenuClass;
	UPROPERTY(VisibleAnywhere, Category = "Widget")
	class UPT_MultiplayMenu* MultiplayMenu;

protected:
	virtual bool Initialize() override;
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_PlayMulti;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_PlaySingle;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Load;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Settings;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Exit;

	UFUNCTION()
	void BtnMultiClicked();
	UFUNCTION()
	void BtnSingleClicked();
	UFUNCTION()
	void BtnLoadClicked();
	UFUNCTION()
	void BtnSettingsClicked();
	UFUNCTION()
	void BtnExitClicked();

	// for Multi
	class UPTGameInstanceSubsystem* PTGIS;

	UFUNCTION()
	void MultiMenuBackCliced();

	UFUNCTION()
	void MenuTearDown();

};
