// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterData.h"
#include "GameFramework/Character.h"
#include "Types.h"

#include "BaseCharacter.generated.h"

UCLASS(Blueprintable)
class GAMEJAM_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
	FORCEINLINE ECharacterState GetState() const { return State; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetState(ECharacterState NewState) { State = NewState; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UCharacterData* GetCharacterData() const { return CharacterData; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE ECharacterFaction GetFaction() const { return Faction; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	/** Character state in world */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Character")
	ECharacterState State;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Character")
	ECharacterFaction Faction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Character")
	TObjectPtr<UCharacterData> CharacterData = nullptr;
};
