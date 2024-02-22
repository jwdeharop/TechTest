#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TT_NetLibrary.generated.h"

UCLASS()
class UTT_NetLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject"))
		static bool IsServer(const UObject* WorldContextObject);
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
		static bool IsDedicatedServer(const UObject* WorldContextObject);
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
		static bool IsClient(const UObject* WorldContextObject);
};