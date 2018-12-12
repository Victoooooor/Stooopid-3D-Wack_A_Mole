// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"

#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	FindPhysicsHandleComponent();
	SetupInputCom();
	
}

void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsH = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsH == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PhysicsHandler not found, Object: %s\n"), *GetOwner()->GetName())
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	

	//UE_LOG(LogTemp, Warning, TEXT("test: Position: %s\tRotation: %s\n"), *PlayerVPL.ToString(), *PlayerVPR.ToString())
	if (!PhysicsH) { return; }
	if (PhysicsH->GrabbedComponent)
	{
		PhysicsH->SetTargetLocation(GetReachEnd());
	}
	
	

}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab activated"))

		
	auto HitResult = GetFirstPhysics();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();
	if (!PhysicsH) { return; }
	if (ActorHit)
	{
		
		PhysicsH->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
	}
}


void UGrabber::Release() 
{
	UE_LOG(LogTemp, Warning, TEXT("Grab deactivated"))
		if (!PhysicsH) { return; }
		PhysicsH->ReleaseComponent();
}

void UGrabber::SetupInputCom()
{
	InputMonitor = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputMonitor)
	{
		InputMonitor->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputMonitor->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Input Component not Found\n"))
	}
}

const FHitResult UGrabber::GetFirstPhysics()
{
	
	FCollisionQueryParams TracePara(FName(TEXT("")), false, GetOwner());

	FHitResult LineHit;

	GetWorld()->LineTraceSingleByObjectType(OUT LineHit, GetReachStart(), GetReachEnd(), FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TracePara);

	AActor *ActorHit = LineHit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line Hit: %s\n"), *(ActorHit->GetName()))
	}
	
	return LineHit;
}


FVector UGrabber::GetReachEnd()
{
	FVector PlayerVPL;
	FRotator PlayerVPR;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerVPL, OUT PlayerVPR);
	return PlayerVPL + PlayerVPR.Vector() * reach;
}


FVector UGrabber::GetReachStart()
{
	FVector PlayerVPL;
	FRotator PlayerVPR;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerVPL, OUT PlayerVPR);
	return PlayerVPL;
}