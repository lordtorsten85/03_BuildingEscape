// Copyright Ben Tristem 2016.

#include "BuildingEscape.h"
#include "ProjectileLauncherBarrel.h"
#include "Projectile.h"

void UProjectileLauncherBarrel::Fire(float MassOnScales)
{
	if (!ensure(ProjectileBlueprint)) { return; }

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(
	ProjectileBlueprint,
	GetSocketLocation(FName("Projectile")),
	GetSocketRotation(FName("Projectile"))
	);

	if (!ensure(Projectile)) { return;  }
	Projectile->LaunchProjectile(FireSpeedMultiplier * MassOnScales);
	auto ProjectileLocation = Projectile->GetActorLocation();
}
