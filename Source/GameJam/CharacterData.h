// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"
#include "Components/ActorComponent.h"

#include "CharacterData.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAMEJAM_API UCharacterData : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCharacterData();

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetAttack() const { return CharacterStats.Attack; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetPDefence() const { return CharacterStats.PDefence; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetMDefence() const { return CharacterStats.MDefence; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetHP() const { return CharacterStats.HP; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetMP() const { return CharacterStats.MP; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE uint8 GetAP() const { return CharacterStats.AP; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE uint8 GetInitiative() const { return CharacterStats.Initiative; }

	UFUNCTION(BlueprintCallable)
	void SetAttack(float Value) { CharacterStats.Attack = Value; }

	UFUNCTION(BlueprintCallable)
	void SetPDefence(float Value) { CharacterStats.PDefence = Value; }

	UFUNCTION(BlueprintCallable)
	void SetMDefence(float Value) { CharacterStats.MDefence = Value; }

	UFUNCTION(BlueprintCallable)
	void SetHP(float Value) { CharacterStats.HP = Value; }

	UFUNCTION(BlueprintCallable)
	void SetMP(float Value) { CharacterStats.MP = Value; }

	UFUNCTION(BlueprintCallable)
	void SetAP(uint8 Value) { CharacterStats.AP = Value; }

	UFUNCTION(BlueprintCallable)
	void SetInitiative(uint8 Value) { CharacterStats.Initiative = Value; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	/** Character stats */
	UPROPERTY(BlueprintReadWrite, Category="Character")
	FGameStats CharacterStats;
};
