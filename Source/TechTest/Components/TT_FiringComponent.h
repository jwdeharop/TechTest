#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TT_FiringComponent.generated.h"

UCLASS()
class UTT_FiringComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void Fire();

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> Projectile;
};