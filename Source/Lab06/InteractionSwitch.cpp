#include "InteractionSwitch.h"
#include "Engine/Engine.h"

AInteractionSwitch::AInteractionSwitch()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AInteractionSwitch::Interact_Implementation(
	AActor* InteractingActor)
{
	UE_LOG(LogTemp, Display,
		TEXT("InteractionSwitch activated by %s"),
		InteractingActor
			? *InteractingActor->GetName()
			: TEXT("Unknown"));

	for (AActor* Target : Targets)
	{
		if (!IsValid(Target))
		{
			UE_LOG(LogTemp, Warning,
				TEXT("InteractionSwitch has an empty or invalid target."));
			continue;
		}

		if (Target == this)
		{
			continue;
		}

		if (!Target->GetClass()->ImplementsInterface(
			UInteractableInterface::StaticClass()))
		{
			UE_LOG(LogTemp, Warning,
				TEXT("%s does not implement InteractableInterface."),
				*Target->GetName());
			continue;
		}

		IInteractableInterface::Execute_Interact(
			Target, InteractingActor);

		UE_LOG(LogTemp, Display,
			TEXT("InteractionSwitch activated target: %s"),
			*Target->GetName());
	}
}