// Copyright Ben Tristem 2016.

#include "BuildingEscape.h"
#include "ProjectileLauncher.h"
#include "ProjectileLauncherBarrel.h"
#include "ButtonComponent.h"

#define OUT

// Sets default values
AProjectileLauncher::AProjectileLauncher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Base Mesh"));
	SetRootComponent(BaseMesh);

}

// Called when the game starts or when spawned
void AProjectileLauncher::BeginPlay()
{
	Super::BeginPlay();

	if (!AddWeightTrigger || !SubtractWeightTrigger)
	{
		UE_LOG(LogTemp, Warning, TEXT("One of the triggers is not set!"));
	}
	
}

// Called every frame
void AProjectileLauncher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GetTotalMassOfActorsOnPlates();
}

void AProjectileLauncher::Initialize(UProjectileLauncherBarrel* BarrelToSet, UButtonComponent* ButtonToSet)
{
	Barrel = BarrelToSet;
	Button = ButtonToSet;

	if (!ensure(Button)) { return; }
	Button->ButtonPressed.AddUniqueDynamic(this, &AProjectileLauncher::OnAttachedButtonPressed);
}

float AProjectileLauncher::GetTotalMassOfActorsOnPlates()
{
	float TotalMass = 0.f;
	TArray<AActor*> ActorsOnAddPlate;
	TArray<AActor*> ActorsOnSubtractPlate;

	if (!AddWeightTrigger || !SubtractWeightTrigger) { return TotalMass; }

	AddWeightTrigger->GetOverlappingActors(OUT ActorsOnAddPlate);
	SubtractWeightTrigger->GetOverlappingActors(OUT ActorsOnSubtractPlate);

	for (const auto& Actor : ActorsOnAddPlate)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	for (const auto& Actor : ActorsOnSubtractPlate)
	{
		TotalMass -= Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	WeightOnScales = TotalMass;
	return TotalMass;
} 

void AProjectileLauncher::OnAttachedButtonPressed()
{
	if (!ensure(Barrel)) { return; }
	Barrel->Fire(GetTotalMassOfActorsOnPlates());
}
