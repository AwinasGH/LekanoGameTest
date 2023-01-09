// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LT_Plate.generated.h"

UCLASS(Blueprintable)
class LEKANOTESTPROJECT_API ALT_Plate : public AActor
{
	GENERATED_BODY()

	friend class ALT_PlatePair;

//constructors
public:	

	ALT_Plate();

//c++ private methods
private:

	UPROPERTY(Replicated)
		bool IsFake = false;
	
	bool IsBusy = false;
	
//c++ protected methods
protected:

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION()
		void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	

//>>..............................................................................................................<<//
	


//Blueprint values
public:
	
	/*
		Trigger for handling player entering and leaving plate
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Plate|Components")
		class UBoxComponent* BoxTrigger = nullptr;
	/*
		Plate's mesh component
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Plate|Components")
		class UStaticMeshComponent* PlateMesh = nullptr;

};
