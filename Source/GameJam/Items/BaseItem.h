// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameJam/Types.h"

#include "BaseItem.generated.h"

UCLASS()
class GAMEJAM_API ABaseItem : public AActor
{
	GENERATED_BODY()

public:
	ABaseItem();

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FGameStats ItemStats;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
	class USphereComponent* Collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
	class UStaticMeshComponent* Mesh;

	/** Components */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	class URotatingMovementComponent* RotationComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	class UInterpToMovementComponent* MovementComponent;
};
