// Copyright Ben Tristem 2016.

#include "BuildingEscape.h"
#include "DetectorVolume.h"
#include "Projectile.h"
#include "OpenDoor.h"


// Sets default values
ADetectorVolume::ADetectorVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionCube = CreateDefaultSubobject<UBoxComponent>(FName("Collision Volume"));
}

// Called when the game starts or when spawned
void ADetectorVolume::BeginPlay()
{
	Super::BeginPlay();
	CollisionCube->OnComponentBeginOverlap.AddDynamic(this, &ADetectorVolume::BeginOverlap);
}

// Called every frame
void ADetectorVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADetectorVolume::BeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->IsA(AProjectile::StaticClass()))
	{
		// Make sure there is a world actor set on the BP
		if (!ensure(ActorWithDoorToOpen)) { return; }

		// Check there is a component on the world actor, then cast to a OpenDoor component
		auto OpenDoorComponent = ActorWithDoorToOpen->FindComponentByClass(UOpenDoor::StaticClass());
		if (!ensure(OpenDoorComponent)) { return; }
		UOpenDoor* DoorToOpen = Cast<UOpenDoor>(OpenDoorComponent);

		// Ensure there is an OpenDoor component, then broadcast the OnOpen event.
		if (!ensure(DoorToOpen)) { return; }
		DoorToOpen->bOverrideOnCloseTick = true;
		DoorToOpen->OnOpen.Broadcast();
		UE_LOG(LogTemp, Warning, TEXT("GOT EM!"));
	}
}