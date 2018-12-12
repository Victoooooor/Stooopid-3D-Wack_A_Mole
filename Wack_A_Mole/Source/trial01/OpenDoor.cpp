// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"

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

	// ...
	Owner = GetOwner();

	
}



// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	
	if (MassOnTrigger() > MassThreshold && checkstate)
	{
		OpenRequest.Broadcast();
		checkstate = 0;
	}
	else if (MassOnTrigger() < MassThreshold && checkstate == 0)
	{
		CloseRequest.Broadcast();
		checkstate = 1;
	}
}

float UOpenDoor::MassOnTrigger()
{
	float TMass = 0.f;
	TArray<AActor*> TriggeringActors;
	if (!PressurePlate) { return 0; }
	PressurePlate->GetOverlappingActors(OUT TriggeringActors);
	for (auto* iterator : TriggeringActors)
	{
		TMass += iterator->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("Triggered: %s\n"), *iterator->GetName())

	}
	return TMass;
}

