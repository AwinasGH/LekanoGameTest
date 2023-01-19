#pragma once

#include "CoreMinimal.h"
#include "LT_InGameMatchStateInfo.generated.h"

UENUM(BlueprintType)
enum class EInGameMatchState : uint8
{
	Preparation		UMETA(DisplayName = "Preparation"),
	InProgress		UMETA(DisplayName = "InProgress"),
	Ended			UMETA(DisplayName = "Ended")
};