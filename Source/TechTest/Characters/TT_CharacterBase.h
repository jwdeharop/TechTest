#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TT_CharacterBase.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS(Blueprintable)
class ATT_CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ATT_CharacterBase();

	UCameraComponent* GetTopDownCameraComponent() const;
	USpringArmComponent* GetCameraBoom() const;

	virtual FTransform GetProjectileSpawnPositionTransform() const;
	virtual void Fire();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* TopDownCameraComponent = nullptr;;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* CameraBoom = nullptr;;
};