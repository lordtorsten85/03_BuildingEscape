// Copyright Ben Tristem 2016.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "ProjectileLauncherBarrel.generated.h"

class AProjectile;
/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BUILDINGESCAPE_API UProjectileLauncherBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;
	
	void Fire(float MassOnScales);

private:
	UPROPERTY(EditAnywhere, Category = "Firing")
	float FireSpeedMultiplier = 100;

	
};
