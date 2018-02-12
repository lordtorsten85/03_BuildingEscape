// Copyright Ben Tristem 2016.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileLauncher.generated.h"

class ATriggerVolume;
class UProjectileLauncherBarrel;

UCLASS()
class BUILDINGESCAPE_API AProjectileLauncher : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileLauncher();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UProjectileLauncherBarrel* BarrelToSet);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	ATriggerVolume* AddWeightTrigger = nullptr;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* SubtractWeightTrigger = nullptr;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	UProjectileLauncherBarrel* Barrel = nullptr;

	// Gets mass of actors on plate in KG
	float GetTotalMassOfActorsOnPlates();
};
