// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePlayerController.h"
#include "PlayerCharacter.h"
#include "NiagaraFunctionLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PawnMovementComponent.h"

ABasePlayerController::ABasePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ABasePlayerController::SwitchCharacter()
{
	PartyMembers.AddUnique(GetPawn());

	if (PartyMembers.Num() > 1)
	{
		if (auto* NewCharacter = PartyMembers[0].LoadSynchronous())
		{
			UnPossess();
			Possess(NewCharacter);
		}
	}
}

void ABasePlayerController::SetDefaultCursor()
{
	if (IsValid(DefaultCursor))
	{
		SetMouseCursorWidget(EMouseCursor::Default, DefaultCursor);
	}
}

void ABasePlayerController::SetBattleCursor()
{
	if (IsValid(BattleCursor))
	{
		SetMouseCursorWidget(EMouseCursor::Default, BattleCursor);
	}
}

void ABasePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bInputPressed)
	{
		FollowTime += DeltaTime;

		// Look for the touch location
		FVector HitLocation = FVector::ZeroVector;
		FHitResult Hit;

		GetHitResultUnderCursor(ECC_Visibility, true, Hit);
		HitLocation = Hit.Location;

		if (APawn* HitPawn = Cast<APawn>(Hit.GetActor()))
		{
			GEngine->AddOnScreenDebugMessage(1, DeltaTime, FColor::Red, TEXT("Hit Actor!"));
			GEngine->AddOnScreenDebugMessage(1, DeltaTime, FColor::Red, Hit.GetActor()->GetName());

			SetBattleCursor();
		}
		else
		{
			SetDefaultCursor();
		}

		// Direct the Pawn towards that location
		if (APawn* const MyPawn = GetPawn())
		{
			const FVector WorldDirection = (HitLocation - MyPawn->GetActorLocation()).GetSafeNormal();
			MyPawn->AddMovementInput(WorldDirection, 1.f, false);
		}
	}
	else
	{
		FollowTime = 0.f;
	}
}

void ABasePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ABasePlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ABasePlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("SwitchCharacter", IE_Pressed, this, &ABasePlayerController::SwitchCharacter);
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Creating cursors
	if (*DefaultCursorClass)
	{
		DefaultCursor = CreateWidget(this, DefaultCursorClass, FName("DefaultCursor"));
	}

	if (*DefaultCursorClass)
	{
		BattleCursor = CreateWidget(this, BattleCursorClass, FName("BattleCursor"));
	}
}

void ABasePlayerController::OnSetDestinationPressed()
{
	// We flag that the input is being pressed
	bInputPressed = true;
	// Just in case the character was moving because of a previous short press we stop it
	StopMovement();
}

void ABasePlayerController::OnSetDestinationReleased()
{
	// Player is no longer pressing the input
	bInputPressed = false;

	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We look for the location in the world where the player has pressed the input
		FVector HitLocation = FVector::ZeroVector;
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, true, Hit);
		HitLocation = Hit.Location;

		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, HitLocation);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, HitLocation, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true,
		                                               ENCPoolMethod::None, true);
	}
}
