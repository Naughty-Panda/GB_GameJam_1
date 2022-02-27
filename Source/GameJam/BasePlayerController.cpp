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
}

void ABasePlayerController::AddPartyMember(APawn* Member)
{
	if (Member)
	{
		PartyMembers.AddUnique(Member);
	}
}

void ABasePlayerController::SelectPartyMember1()
{
	if (!PartyMembers.IsValidIndex(0))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Party member index!"));
		return;
	}

	if (SelectedPawn && SelectedPawn != PartyMembers[0])
	{
		SelectedPawn = PartyMembers[0];
		PossessPartyMember(SelectedPawn);
	}
}

void ABasePlayerController::SelectPartyMember2()
{
	if (!PartyMembers.IsValidIndex(1))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Party member index!"));
		return;
	}

	if (SelectedPawn && SelectedPawn != PartyMembers[1])
	{
		SelectedPawn = PartyMembers[1];
		PossessPartyMember(SelectedPawn);
	}
}

void ABasePlayerController::SelectPartyMember3()
{
	if (!PartyMembers.IsValidIndex(2))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Party member index!"));
		return;
	}

	if (SelectedPawn && SelectedPawn != PartyMembers[2])
	{
		SelectedPawn = PartyMembers[2];
		PossessPartyMember(SelectedPawn);
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

void ABasePlayerController::PossessPartyMember(APawn* Member)
{
	UnPossess();
	Possess(Member);
}

void ABasePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	FVector HitLocation = FVector::ZeroVector;
	FHitResult Hit;

	GetHitResultUnderCursor(ECC_Camera, true, Hit);

	if (bInputPressed)
	{
		FollowTime += DeltaTime;
		HitLocation = Hit.Location;

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

	// Set cursor
	Cast<ABaseCharacter>(Hit.GetActor()) ? SetBattleCursor() : SetDefaultCursor();
}

void ABasePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ABasePlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ABasePlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("SwitchCharacter", IE_Pressed, this, &ABasePlayerController::SwitchCharacter);
	InputComponent->BindAction("SelectPartyMember1", IE_Pressed, this, &ABasePlayerController::SelectPartyMember1);
	InputComponent->BindAction("SelectPartyMember2", IE_Pressed, this, &ABasePlayerController::SelectPartyMember2);
	InputComponent->BindAction("SelectPartyMember3", IE_Pressed, this, &ABasePlayerController::SelectPartyMember3);
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

	if (auto* CurrentPawn = GetPawn())
	{
		SelectedPawn = CurrentPawn;
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
