// Copyright Ben Tristem 2016.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "ButtonComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPushButton);
/**
 * 
 */

UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BUILDINGESCAPE_API UButtonComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	UButtonComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Called when the game starts
	virtual void BeginPlay() override;

	FPushButton ButtonPressed;

private:
	bool bCanInteractWithButton = false;

	UInputComponent* PlayerInputComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* CollisionSphere = nullptr;
	
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void PushButton();
};
