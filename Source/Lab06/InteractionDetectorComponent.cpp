
#include "InteractionDetectorComponent.h"
#include "InteractionDoor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

UInteractionDetectorComponent::UInteractionDetectorComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UInteractionDetectorComponent::BeginPlay()
{
    Super::BeginPlay();

    AActor* OwnerActor = GetOwner();

    if (!OwnerActor)
    {
        UE_LOG(LogTemp, Error,
            TEXT("Interaction detector has no owner."));
        return;
    }

    TriggerBox = OwnerActor->FindComponentByClass<UBoxComponent>();

    if (!TriggerBox)
    {
        UE_LOG(LogTemp, Error,
            TEXT("%s needs a Box Collision component."),
            *OwnerActor->GetName());
        return;
    }

    if (!TargetDoor)
    {
        UE_LOG(LogTemp, Warning,
            TEXT("%s has no target door assigned."),
            *OwnerActor->GetName());
    }

    TriggerBox->OnComponentBeginOverlap.AddDynamic(
        this,
        &UInteractionDetectorComponent::HandleBeginOverlap);

    TriggerBox->OnComponentEndOverlap.AddDynamic(
        this,
        &UInteractionDetectorComponent::HandleEndOverlap);
}

void UInteractionDetectorComponent::HandleBeginOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComponent,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (!OtherActor || !OtherActor->IsA<ACharacter>())
    {
        return;
    }

    if (!TargetDoor)
    {
        UE_LOG(LogTemp, Warning,
            TEXT("Interaction detected, but no door is assigned."));
        return;
    }

    UE_LOG(LogTemp, Log,
        TEXT("%s activated by %s."),
        *GetOwner()->GetName(),
        *OtherActor->GetName());

    TargetDoor->SetDoorOpen(true);
}

void UInteractionDetectorComponent::HandleEndOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComponent,
    int32 OtherBodyIndex)
{
    if (!OtherActor || !OtherActor->IsA<ACharacter>())
    {
        return;
    }

    if (TargetDoor)
    {
        TargetDoor->SetDoorOpen(false);

        UE_LOG(LogTemp, Log,
            TEXT("%s deactivated."),
            *GetOwner()->GetName());
    }
}
