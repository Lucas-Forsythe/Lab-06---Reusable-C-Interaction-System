
#include "InteractionDoor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "TimerManager.h"

AInteractionDoor::AInteractionDoor()
{
    PrimaryActorTick.bCanEverTick = true;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(
        TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(
        TEXT("DoorMesh"));
    DoorMesh->SetupAttachment(SceneRoot);
}

void AInteractionDoor::BeginPlay()
{
    Super::BeginPlay();

    ClosedLocation = GetActorLocation();

    if (!DoorMesh || !DoorMesh->GetStaticMesh())
    {
        UE_LOG(LogTemp, Warning,
            TEXT("%s has no door mesh assigned."), *GetName());
    }
}

void AInteractionDoor::SetDoorOpen(bool bShouldOpen)
{
    GetWorldTimerManager().ClearTimer(OpenTimerHandle);
    bPendingOpen = false;

    if (bShouldOpen)
    {
        if (bIsOpen)
        {
            return;
        }

        if (ActivationDelay > 0.f)
        {
            bPendingOpen = true;

            GetWorldTimerManager().SetTimer(
                OpenTimerHandle,
                this,
                &AInteractionDoor::FinishOpening,
                ActivationDelay,
                false);

            UE_LOG(LogTemp, Log,
                TEXT("%s: Door opening delayed."), *GetName());
        }
        else
        {
            FinishOpening();
        }
    }
    else
    {
        bIsOpen = false;

        UE_LOG(LogTemp, Log,
            TEXT("%s: Door closing."), *GetName());
    }
}

void AInteractionDoor::FinishOpening()
{
    bPendingOpen = false;
    bIsOpen = true;

    UE_LOG(LogTemp, Log,
        TEXT("%s: Door opening."), *GetName());
}

void AInteractionDoor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    const FVector TargetLocation = bIsOpen
        ? ClosedLocation + OpenOffset
        : ClosedLocation;

    const FVector NewLocation = FMath::VInterpConstantTo(
        GetActorLocation(),
        TargetLocation,
        DeltaTime,
        MoveSpeed);

    SetActorLocation(NewLocation);
}

void AInteractionDoor::Interact_Implementation(
    AActor* InteractingActor)
{
    UE_LOG(LogTemp, Display,
        TEXT("Door received an interaction event."));

    // Toggle the door open or closed.
    SetDoorOpen(!bIsOpen);
}

