// Copyright Ben Tristem 2016.

#include "BuildingEscape.h"
#include "ProjectileLauncherBarrel.h"
#include "Projectile.h"

void UProjectileLauncherBarrel::Fire()
{
	if (!ensure(ProjectileBlueprint)) { return; }

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(
	ProjectileBlueprint,
	this->GetSocketLocation("Projectile"),
	this->GetSocketRotation("Projectile")
	);

	if (!ensure(Projectile)) { return;  }
	Projectile->LaunchProjectile(FireSpeed);

}
