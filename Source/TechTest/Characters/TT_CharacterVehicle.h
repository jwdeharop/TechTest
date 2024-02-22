#pragma once

#include "CoreMinimal.h"
#include "Characters/TT_CharacterBase.h"
#include "TT_CharacterVehicle.generated.h"

class UTT_FiringComponent;

UCLASS(Blueprintable)
class ATT_CharacterVehicle : public ATT_CharacterBase
{
	GENERATED_BODY()

public:
	ATT_CharacterVehicle();

	virtual FTransform GetProjectileSpawnPositionTransform() const override;
	virtual void Fire() override;

protected:
	UPROPERTY(EditDefaultsOnly)
		UTT_FiringComponent* FiringComponent = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		USceneComponent* ProjectileSpawnPosition = nullptr;
};