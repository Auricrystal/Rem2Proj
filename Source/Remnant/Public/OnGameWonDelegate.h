#pragma once
#include "CoreMinimal.h"
#include "EBoardUser.h"
#include "OnGameWonDelegate.generated.h"

UDELEGATE(BlueprintCallable) DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameWon, EBoardUser, User);

