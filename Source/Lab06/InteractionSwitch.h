#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "InteractionSwitch.generated.h"

UCLASS()
class LAB06_API AInteractionSwitch
	: public AActor, public IInteractableInterface
{
	GENERATED_BODY()

public:
	AInteractionSwitch();

	virtual void Interact_Implementation(
		AActor* InteractingActor) override;

private:
	UPROPERTY(EditInstanceOnly, Category = "Interaction")
	TArray<TObjectPtr<AActor>> Targets;
};