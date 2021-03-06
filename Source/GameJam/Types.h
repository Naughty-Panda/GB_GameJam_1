#pragma once

#include "Types.generated.h"

// Character states in world
UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	CS_FreeRoam,
	CS_Encounter
};

// Character states in world
UENUM(BlueprintType)
enum class ECharacterFaction : uint8
{
	CF_Ally,
	CF_Enemy
};

// Character states in world
UENUM(BlueprintType)
enum class EItemType : uint8
{
	IT_None,
	IT_Weapon,
	IT_Armor,
	IT_Consumable
};

// Game stats
USTRUCT(BlueprintType)
struct FGameStats
{
	GENERATED_BODY()

public:
	float Attack = 0.f;
	float PDefence = 0.f;
	float MDefence = 0.f;
	float HP = 0.f;
	float MP = 0.f;
	uint8 AP = 0;
	uint8 Initiative = 0;
};
