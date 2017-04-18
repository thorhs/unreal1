// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject2.h"
#include "OpenDoor.h"


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
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

	CloseAngle = Owner->GetActorRotation().Yaw;
}

void UOpenDoor::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
	IsOpen = true;
}

void UOpenDoor::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.0f, CloseAngle, 0.0f));
	IsOpen = false;
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the trigger volume every frame
	// If the ActorThatOpens is in the volume, then we open the door
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();

	}

	if (IsOpen && GetWorld()->GetTimeSeconds() > LastDoorOpenTime + DoorCloseDelay) {
		CloseDoor();
		UE_LOG(LogTemp, Warning, TEXT("Closing door: %f, %f, %f"), LastDoorOpenTime, DoorCloseDelay, GetWorld()->GetTimeSeconds());
	}

}

