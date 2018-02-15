// Copyright Ben Tristem 2016.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileLauncher.generated.h"

class ATriggerVolume;
class UProjectileLauncherBarrel;
class UButtonComponent;

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
	void Initialize(UProjectileLauncherBarrel* BarrelToSet, UButtonComponent* ButtonToSet);

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

	UProjectileLauncherBarrel* Barrel = nullptr;

	UButtonComponent* Button = nullptr;

	// Gets mass of actors on plate in KG
	float GetTotalMassOfActorsOnPlates();

	UFUNCTION()
	void OnAttachedButtonPressed();
};
