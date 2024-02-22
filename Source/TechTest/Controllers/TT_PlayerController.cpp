#include "Controllers/TT_PlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Characters/TT_CharacterBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameModes/TT_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Libraries/TT_NetLibrary.h"

void ATT_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ATT_PlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(IAFire, ETriggerEvent::Completed, this, &ATT_PlayerController::Fire);
	}
}

void ATT_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	if (IsLocalController())
	{
		// We inform the server that we want to spawn at a random player start.
		Server_SpawnPawnOnRandomPlayerStart();
	}
}

void ATT_PlayerController::Server_MoveToLocation_Implementation(const FVector& Location)
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this,Location);
}

void ATT_PlayerController::Server_SpawnPawnOnRandomPlayerStart_Implementation()
{
	ATT_GameMode* GameMode = Cast<ATT_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode)
	{
		UE_LOG(LogTemp, Error, TEXT("ATT_PlayerController::Server_SpawnPawnOnRandomPlayerStart couldn't find a valid game mode."));
		return;
	}

	GameMode->SpawnPlayerAtRandomPlayerStart(this);
}

void ATT_PlayerController::Server_Fire_Implementation()
{
	if (ATT_CharacterBase* ATTCharacter = Cast<ATT_CharacterBase>(GetPawn()))
	{
		// ATT Character would be the base class, so every character we implement could implement his own fire function.
		ATTCharacter->Fire();
	}
}

void ATT_PlayerController::OnSetDestinationTriggered(const FInputActionValue& InputActionValue)
{
	FHitResult Hit;
	const bool bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	if (bHitSuccessful)
	{
		// We inform the server that we want to move to hit location.
		Server_MoveToLocation(Hit.Location);
		if (!UTT_NetLibrary::IsServer(this))
		{
			// We predictably move to the same location if we're not servers.
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this,Hit.Location);
		}
	}
}

void ATT_PlayerController::Fire(const FInputActionValue& InputActionValue)
{
	// This function will only triggers in local clients, so we have to inform server that we want to fire the projectile.
	Server_Fire();
}
