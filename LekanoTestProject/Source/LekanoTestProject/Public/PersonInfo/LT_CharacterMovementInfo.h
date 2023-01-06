#pragma once

#include "CoreMinimal.h"
#include "LT_CharacterMovementInfo.generated.h"


UENUM(BlueprintType)
enum class ELegMoveType : uint8
{
	Walk		UMETA(DisplayName = "Walk"),
	Jog			UMETA(DisplayName = "Jog"),
	Sprint		UMETA(DisplayName = "Sprint")
};