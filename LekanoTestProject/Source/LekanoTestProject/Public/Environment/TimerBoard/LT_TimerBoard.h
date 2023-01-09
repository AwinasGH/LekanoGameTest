// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LT_TimerBoard.generated.h"

UCLASS()
class LEKANOTESTPROJECT_API ALT_TimerBoard : public AActor
{
	GENERATED_BODY()
	
//constructor
public:

	ALT_TimerBoard(const FObjectInitializer& ObjectInitializer);
	
//>>>...............................................................................................................................................................................<<<//
//>>>...............................................................................................................................................................................<<<//


//Blueprint protected values:
protected:
	
//.................................Components.....................................................//

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TimerBoard|Components")
		class USceneComponent* SceneRootComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TimerBoard|Components")
		class UWidgetComponent* WidgetComponent = nullptr;

//................................................................................................//

};
