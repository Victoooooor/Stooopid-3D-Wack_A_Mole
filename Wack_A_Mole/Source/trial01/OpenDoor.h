// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoor);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRIAL01_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
		FDoor OpenRequest;

	UPROPERTY(BlueprintAssignable)
		FDoor CloseRequest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerMusicSkill)
		int checkstate = 1;
private:

	UPROPERTY(EditAnywhere)
	float MassThreshold = 60.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume *PressurePlate = nullptr;

	AActor *Owner = nullptr;

	float MassOnTrigger();

	
};
