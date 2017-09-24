// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Gameframework/Actor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	//next line finds pawn
	//ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate"), *GetOwner()->GetName())
	}
}

//void UOpenDoor::OpenDoor()
//{
	//Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
	
//}

//void UOpenDoor::CloseDoor()
//{
	//Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
//}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Poll the trigger Volume every frame
	if (GetTotalMassOfActorsOnPlate() > TriggerMass) {  //TODO make into a parameter
		//OpenDoor();
		//LastDoorOpenTime = GetWorld()->GetTimeSeconds();
		OnOpen.Broadcast();
	}

// 	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
// 		OpenDoor();
// 		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
// 	}

	// Check if its time to close the door
	//if (GetWorld()->GetTimeSeconds()-LastDoorOpenTime > DoorCloseDelay) {
	else {
		OnClose.Broadcast();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() {
	float TotalMass = 0.f;

	//Find all overlapping actors
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	//Iterate through them adding up masses
	for (const auto* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass(); //UPrimitiveComponent is used to find mass of object
		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName())
	}
	
	return TotalMass;
}
