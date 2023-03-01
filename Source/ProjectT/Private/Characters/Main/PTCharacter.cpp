// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Main/PTCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/Components/PTAbilitySystemComponent.h"
#include "AbilitySystem/Attribute/PTAttributeSet.h"
#include "DataAssets/PTCharacterDataAsset.h"

#include "Characters/Main/PTPlayerController.h"

APTCharacter::APTCharacter(const class FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Overlap);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraLagSpeed = 10.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	bAlwaysRelevant = true;

	/** Ability System */
	AbilitySystemComponent = CreateDefaultSubobject<UPTAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UPTAttributeSet>(TEXT("AttributeSet"));

}

void APTCharacter::BeginPlay()
{
	Super::BeginPlay();

	PTController = Cast<APTPlayerController>(GetController());
	PTController->SetShowMouseCursor(true);
	PTController->bEnableClickEvents = true;
	PTController->bEnableMouseOverEvents = true;
}

void APTCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/** Move */
	if (bIsMovePressed)
	{
		FHitResult HitResult;
		PTController->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, HitResult);
		if (HitResult.GetActor())
		{
			if (bIsFirst)
			{
				bIsFirst = false;
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(PTController, GetActorLocation());
			}

			FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), HitResult.Location);

			SetActorRotation(FMath::RInterpTo(GetActorRotation(), FRotator(GetActorRotation().Pitch, Rotation.Yaw, GetActorRotation().Roll), DeltaTime, 15.f));
			AddMovementInput(GetActorForwardVector());
			CurrentLocation = GetActorLocation();
		}
	}
}

void APTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(FName("Move"), EInputEvent::IE_Pressed, this, &APTCharacter::Move);
	PlayerInputComponent->BindAction(FName("Move"), EInputEvent::IE_Released, this, &APTCharacter::MoveEnd);
}

void APTCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (IsValid(CharacterDataAsset))
	{
		SetCharacterData(CharacterDataAsset->CharacterData);
	}
}

void APTCharacter::Move()
{
	bIsMovePressed = true;
}

void APTCharacter::MoveEnd()
{
	bIsMovePressed = false;
	FHitResult HitResult;
	PTController->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, HitResult);
	if (HitResult.GetActor())
	{
		bIsFirst = true;
		CurrentLocation = HitResult.Location;
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(PTController, CurrentLocation);
	}
}

/** 
*
* Ability System
*
*/
UAbilitySystemComponent* APTCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

bool APTCharacter::ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> Effect, FGameplayEffectContextHandle InEffectContext)
{
	if (!Effect.Get()) return false;

	// EffectSpec�ڵ鷯�� �غ� �Ϸ�� Effect�� ����
	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, 1, InEffectContext);
	if (SpecHandle.IsValid())
	{
		// ActiveEffect�ڵ鷯�� SpecHandle�� Effect����� ����
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		return ActiveGEHandle.WasSuccessfullyApplied();
	}
	return false;
}

void APTCharacter::GiveAbilities()
{
	if (HasAuthority() && AbilitySystemComponent)
	{
		for (auto DefaultAbility : CharacterData.Abilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(DefaultAbility));
		}
	}
}

void APTCharacter::ApplyStartupEffects()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		for (auto CharacterEffect : CharacterData.Effects)
		{
			ApplyGameplayEffectToSelf(CharacterEffect, EffectContext);
		}

	}
}

void APTCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	GiveAbilities();
	ApplyStartupEffects();
}

void APTCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

/**
*
* Data Assets
*
*/
FCharacterData APTCharacter::GetCharacterData() const
{
	return CharacterData;
}

void APTCharacter::SetCharacterData(const FCharacterData& InCharacterData)
{
	CharacterData = InCharacterData;
	InitFromCharacterData(CharacterData);
}

void APTCharacter::OnRep_CharacterData()
{
	InitFromCharacterData(CharacterData, true);
}

void APTCharacter::InitFromCharacterData(const FCharacterData& InCharacterData, bool bFromReplication)
{

}

void APTCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APTCharacter, CharacterData);
}