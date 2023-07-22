#pragma once
#include "CoreMinimal.h"
#include "UserSettingAppliedEventDelegate.h"
#include "UserSetting_Base.h"
#include "UserSetting.generated.h"

class UGameUserSettingsGunfire;

UCLASS(Abstract, Blueprintable, EditInlineNew)
class GUNFIRERUNTIME_API UUserSetting : public UUserSetting_Base {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName NameID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FText Label;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FText Description;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    FName Category;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FText Group;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString ConsoleVariable;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 Platforms;
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FUserSettingAppliedEvent OnApplied;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    UGameUserSettingsGunfire* Settings;
    
public:
    UUserSetting();
    UFUNCTION(BlueprintCallable)
    void ResetToDefault();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FText GetDisplayValue() const;
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Apply();
    
};

