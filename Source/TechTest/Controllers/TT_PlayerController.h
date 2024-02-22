#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "TT_PlayerController.generated.h"

class UTT_FiringComponent;
enum class ETT_Team : uint8;
class UInputMappingContext;
class UInputAction;

UCLASS()
class ATT_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
		UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
		UInputAction* SetDestinationClickAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
		UInputAction* IAFire;

	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

private:
	UFUNCTION(Server, Reliable)
		void Server_MoveToLocation(const FVector& Location);
	UFUNCTION(Server, Reliable)
		void Server_SpawnPawnOnRandomPlayerStart();
	UFUNCTION(Server, Reliable)
		void Server_Fire();

	void OnSetDestinationTriggered(const FInputActionValue& InputActionValue);
	void Fire(const FInputActionValue& InputActionValue);
};