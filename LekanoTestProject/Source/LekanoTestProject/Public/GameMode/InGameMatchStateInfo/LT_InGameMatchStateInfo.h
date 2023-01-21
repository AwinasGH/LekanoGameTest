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

USTRUCT(BlueprintType)
struct FInGameStateInfo
{
	GENERATED_USTRUCT_BODY();
	
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timer")
		float CurrentTime = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timer")
		float TimeStep = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timer")
		float TimeUpdateFrequency = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timer")
		bool IsTimerActive = true;

public:

	FTimerHandle TimerHandle;
};