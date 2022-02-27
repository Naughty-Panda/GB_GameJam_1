// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "BasePlayerController.generated.h"

class APlayerCharacter;

/**
 * 
 */
UCLASS()
class GAMEJAM_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABasePlayerController();

	void SwitchCharacter();

	UFUNCTION(BlueprintCallable)
	void SetDefaultCursor();

	UFUNCTION(BlueprintCallable)
	void SetBattleCursor();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	// End PlayerController interface

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

private:
	bool bInputPressed; // Input is bring pressed
	float FollowTime; // For how long it has been pressed

public:
	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UNiagaraSystem* FXCursor;

	/** Default cursor widget class */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TSubclassOf<UUserWidget> DefaultCursorClass;

	/** Battle cursor widget class */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TSubclassOf<UUserWidget> BattleCursorClass;

	/** Actual cursors */
	UPROPERTY()
	UUserWidget* DefaultCursor;
	UPROPERTY()
	UUserWidget* BattleCursor;

	/** Party members */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Party, meta=(AllowedClasses = "PlayerCharacter"))
	TArray<TSoftObjectPtr<APawn>> PartyMembers;
};
