// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnClose;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//void OpenDoor();
	//void CloseDoor();

private: 
	//UPROPERTY(EditAnywhere)
	//float OpenAngle = -70.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	//UPROPERTY(EditAnywhere)
	//float DoorCloseDelay = 1.2f;

	float LastDoorOpenTime;
	
	UPROPERTY(EditAnywhere)
	float TriggerMass = 30.f;

	//Next line finds pawn
	//AActor* ActorThatOpens; //Pawn inherets from actor (eject from play and hit pawn)
	AActor* Owner = nullptr; //The owning door

	// Returns total mass in kg
	float GetTotalMassOfActorsOnPlate();
};
