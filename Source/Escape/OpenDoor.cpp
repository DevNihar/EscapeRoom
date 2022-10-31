// Copyright Nihar Raut


#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"


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
	initialYaw = GetOwner()->GetActorRotation().Yaw;
	targetYaw = initialYaw + 90.0f;
	currentYaw = initialYaw;

	if(!PressurePlate){
		UE_LOG(LogTemp, Error, TEXT("No PressurePlate Attached to Actor %s"), *GetOwner()->GetName());
	}

	ActorThatOpensDoor = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpensDoor)){
		OpenDoor(DeltaTime);
	}else{
		CloseDoor(DeltaTime);
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
// UE_LOG(LogTemp, Warning, TEXT("Rotation: %s , Yaw: %f"), *GetOwner()->GetActorRotation().ToString(), GetOwner()->GetActorRotation().Yaw);
	currentYaw = FMath::Lerp(currentYaw, targetYaw, DeltaTime * 1);
	UE_LOG(LogTemp, Warning, TEXT("%f"), currentYaw);
	currentRotation.Yaw = currentYaw;
	GetOwner()->SetActorRotation(currentRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{	
	currentYaw = FMath::Lerp(currentYaw, initialYaw, DeltaTime * 1);
	currentRotation.Yaw = currentYaw;
	GetOwner()->SetActorRotation(currentRotation);
}

