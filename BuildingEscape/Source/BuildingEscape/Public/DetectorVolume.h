// Copyright Ben Tristem 2016.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DetectorVolume.generated.h"

UCLASS()
class BUILDINGESCAPE_API ADetectorVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADetectorVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UBoxComponent* CollisionCube = nullptr;
	
	UPROPERTY(EditAnywhere)
	AActor* ActorWithDoorToOpen = nullptr;
	
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
};
