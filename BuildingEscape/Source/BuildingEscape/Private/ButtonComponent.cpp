// Copyright Ben Tristem 2016.

#include "BuildingEscape.h"
#include "ButtonComponent.h"

// Sets default values for this component's properties
UButtonComponent::UButtonComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(FName("Pawn Detection Radius"));
	CollisionSphere->SetupAttachment(this);

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &UButtonComponent::BeginOverlap);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &UButtonComponent::EndOverlap);
	
}

void UButtonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime,TickType, ThisTickFunction);

}

void UButtonComponent::BeginPlay()
{
	Super::BeginPlay();

	auto PC = GetWorld()->GetFirstPlayerController();
	if (!PC) { return; }
	PC->InputComponent->BindAction("USE", IE_Pressed, this, &UButtonComponent::PushButton);
	
}

void UButtonComponent::BeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == UGameplayStatics::GetPlayerPawn(this, 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("You are in the collsiion sphere!"));
		bCanInteractWithButton = true;
	}
}

void UButtonComponent::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == UGameplayStatics::GetPlayerPawn(this, 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("You left the collsiion sphere!"));
		bCanInteractWithButton = false;
	}
}

void UButtonComponent::PushButton()
{
	if (bCanInteractWithButton)
	{
		UE_LOG(LogTemp, Warning, TEXT("You pressed the button!"));
	}
}