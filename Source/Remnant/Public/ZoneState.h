#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EZoneStatus.h"
#include "ZoneState.generated.h"

class UWorld;

USTRUCT(BlueprintType)
struct FZoneState {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EZoneStatus Status;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector LevelOffset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSoftObjectPtr<UWorld> SkyBox;
    
    REMNANT_API FZoneState();
};

