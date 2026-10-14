// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Lab06GameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class ALab06GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	/** Constructor */
	ALab06GameMode();
};



