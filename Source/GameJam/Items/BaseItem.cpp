// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseItem.h"

#include "Components/InterpToMovementComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "GameJam/Interfaces/ItemInterface.h"

// Sets default values
ABaseItem::ABaseItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetupAttachment(Mesh);
	Collision->SetCollisionObjectType(ECC_PhysicsBody);
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnBeginOverlap);

	// Components
	RotationComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotation Component"));
	RotationComponent->bAutoActivate = true;

	MovementComponent = CreateDefaultSubobject<UInterpToMovementComponent>(TEXT("Movement Component"));
	MovementComponent->bAutoActivate = true;
	MovementComponent->BehaviourType = EInterpToBehaviourType::PingPong;

	// Item type and stats
	ItemType = EItemType::IT_None;
}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                               int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Yellow, TEXT("Overlaping..."));

	// Checking Actor's interface
	if (OtherActor->Implements<UItemInterface>())
	{
		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Yellow, TEXT("Got interface!"));
		if (IItemInterface* ItemUser = Cast<IItemInterface>(OtherActor))
		{
			ItemUser->UseItem(this);
			Destroy();
		}
	}
}

// Called every frame
void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
