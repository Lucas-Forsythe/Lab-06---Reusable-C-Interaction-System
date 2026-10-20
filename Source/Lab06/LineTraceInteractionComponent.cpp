
#include "LineTraceInteractionComponent.h"

#include "InteractableInterface.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "InputCoreTypes.h"

ULineTraceInteractionComponent::ULineTraceInteractionComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void ULineTraceInteractionComponent::BeginPlay()
{
    Super::BeginPlay();
}

void ULineTraceInteractionComponent::TickComponent(
    float DeltaTime,
    ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    AActor* OwnerActor = GetOwner();

    if (!OwnerActor)
    {
        return;
    }

    // Check whether the player pressed E.
    APlayerController* PlayerController =
        Cast<APlayerController>(OwnerActor->GetInstigatorController());

    if (!PlayerController)
    {
        APawn* OwnerPawn = Cast<APawn>(OwnerActor);

        if (OwnerPawn)
        {
            PlayerController =
                Cast<APlayerController>(OwnerPawn->GetController());
        }
    }

    if (PlayerController &&
        PlayerController->WasInputKeyJustPressed(EKeys::E))
    {
        TryInteract();
    }
}

void ULineTraceInteractionComponent::TryInteract()
{
    AActor* OwnerActor = GetOwner();

    if (!OwnerActor || !GetWorld())
    {
        return;
    }

    FVector TraceStart;
    FRotator ViewRotation;

    OwnerActor->GetActorEyesViewPoint(
        TraceStart,
        ViewRotation
    );

    const FVector TraceEnd =
        TraceStart + (ViewRotation.Vector() * TraceDistance);

    FHitResult Hit;

    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(OwnerActor);

    const bool bHit = GetWorld()->LineTraceSingleByChannel(
        Hit,
        TraceStart,
        TraceEnd,
        ECC_Visibility,
        QueryParams
    );

    // Draw a debug line to show where the trace goes.
    DrawDebugLine(
        GetWorld(),
        TraceStart,
        TraceEnd,
        bHit ? FColor::Green : FColor::Red,
        false,
        1.0f,
        0,
        2.0f
    );

    if (!bHit)
    {
        return;
    }

    AActor* HitActor = Hit.GetActor();

    if (!HitActor)
    {
        return;
    }

    // Only interact with actors implementing the interface.
    if (HitActor->GetClass()->ImplementsInterface(
        UInteractableInterface::StaticClass()))
    {
        IInteractableInterface::Execute_Interact(
            HitActor,
            OwnerActor
        );
    }
}
