
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LineTraceInteractionComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LAB06_API ULineTraceInteractionComponent
	: public UActorComponent
{
	GENERATED_BODY()

public:
	ULineTraceInteractionComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction
	) override;

private:
	UPROPERTY(EditAnywhere, Category = "Interaction")
	float TraceDistance = 500.0f;

	UPROPERTY(EditInstanceOnly, Category = "Interaction")
	TArray<TObjectPtr<AActor>> InteractionTargets;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	FName SourceTag = TEXT("InteractionSource");

	void TryInteract();
};
