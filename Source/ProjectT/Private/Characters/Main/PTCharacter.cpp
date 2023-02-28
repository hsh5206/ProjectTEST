// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Main/PTCharacter.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Characters/Main/PTPlayerController.h"
#include "Characters/Main/PTAnimInstance.h"

APTCharacter::APTCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraLagSpeed = 10.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void APTCharacter::BeginPlay()
{
	Super::BeginPlay();

	PTController = Cast<APTPlayerController>(GetController());
	PTController->SetShowMouseCursor(true);
	PTController->bEnableClickEvents = true;
	PTController->bEnableMouseOverEvents = true;

	PTAnimInstance = Cast<UPTAnimInstance>(GetMesh()->GetAnimInstance());
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

	PlayerInputComponent->BindAction(FName("Attack"), EInputEvent::IE_Pressed, this, &APTCharacter::Attack);
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

void APTCharacter::Attack()
{
	if (PTAnimInstance && AttackMontage)
	{
		PTAnimInstance->Montage_Play(AttackMontage);
	}
}

