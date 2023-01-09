// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LT_FinishLand.generated.h"

UCLASS()
class LEKANOTESTPROJECT_API ALT_FinishLand : public AActor
{
	GENERATED_BODY()
	

//constructor
public:

	ALT_FinishLand(const FObjectInitializer& ObjectInitializer);

	
//c+ public methods
public:

	FORCEINLINE UStaticMeshComponent* GetMesh() const { return MeshComponent; }
	
//c++ protected methods
protected:

	virtual void BeginPlay() override;

	UFUNCTION()
		void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
//>>>...............................................................................................................................................................................<<<//
//>>>...............................................................................................................................................................................<<<//
	
	
//Blueprint values
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlatePair|Components")
		class USceneComponent* SceneRootComponent = nullptr;

	/*
		Trigger for handling player entering and leaving finish
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Plate|Components")
		class UBoxComponent* BoxTrigger = nullptr;
	

	/*
		Mesh component
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Plate|Components")
		class UStaticMeshComponent* MeshComponent = nullptr;
};
