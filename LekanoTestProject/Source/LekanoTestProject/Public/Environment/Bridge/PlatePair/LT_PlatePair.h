// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LT_PlatePair.generated.h"

UCLASS(Blueprintable)
class LEKANOTESTPROJECT_API ALT_PlatePair : public AActor
{
	GENERATED_BODY()
	
//constructor
public:

	ALT_PlatePair(const FObjectInitializer& ObjectInitializer);


//c++ public methods
public:

	FORCEINLINE FVector GetPivotComponentLocation() const { return PivotComponent->GetComponentLocation(); }
	
//c++ protected methods
protected:

	virtual void BeginPlay() override;
	
//>>>...............................................................................................................................................................................<<<//
//>>>...............................................................................................................................................................................<<<//


//Blueprint protected values:
protected:
	
//.................................Components.....................................................//

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlatePair|Components")
		class USceneComponent* PlatesRootComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlatePair|Components")
		class USceneComponent* PivotComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlatePair|Components")
		class UChildActorComponent* FirstPlate = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlatePair|Components")
		class UChildActorComponent* SecondPlate = nullptr;

//................................................................................................//


};
