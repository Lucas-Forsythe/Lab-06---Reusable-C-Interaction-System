#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "InteractionDoor.generated.h"

class UStaticMeshComponent;
class USceneComponent;

UCLASS()
class LAB06_API AInteractionDoor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

public:
	AInteractionDoor();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void SetDoorOpen(bool bShouldOpen);
	
	virtual void Interact_Implementation(AActor* InteractingActor) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> DoorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Settings")
	FVector OpenOffset = FVector(0.f, 0.f, 250.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Settings",
		meta = (ClampMin = "1.0"))
	float MoveSpeed = 200.f;

	// Independent extension: delay before opening.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Settings",
		meta = (ClampMin = "0.0"))
	float ActivationDelay = 0.5f;

private:
	FVector ClosedLocation;
	bool bIsOpen = false;
	bool bPendingOpen = false;
	FTimerHandle OpenTimerHandle;

	void FinishOpening();
};
