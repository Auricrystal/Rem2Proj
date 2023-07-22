#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/ActorComponent.h"
#include "ChallengeCategory.h"
#include "ChallengeComponentDelegateDelegate.h"
#include "ChallengeEventDelegateDelegate.h"
#include "PointSet.h"
#include "Templates/SubclassOf.h"
#include "ChallengeComponent.generated.h"

class UAchievementController;
class UChallenge;
class UChallengeInstance;
class UChallengeManager;
class UChallengeRank;
class UChallengeReward;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class GUNFIRERUNTIME_API UChallengeComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FChallengeEventDelegate OnChallengeUnlocked;
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FChallengeEventDelegate OnChallengeRevealed;
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FChallengeEventDelegate OnChallengeUpdated;
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FChallengeEventDelegate OnChallengeComplete;
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FChallengeEventDelegate OnChallengeRankCompleted;
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FChallengeComponentDelegate OnChallengesReset;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    UChallengeManager* ChallengeManager;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    UAchievementController* AchievementController;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TMap<FGuid, UChallengeInstance*> ChallengeInstances;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, SaveGame, meta=(AllowPrivateAccess=true))
    TMap<FGuid, int32> ObjectiveProgress;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, SaveGame, meta=(AllowPrivateAccess=true))
    TArray<FGuid> RecollectableAchievements;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TArray<FGuid> ActiveServerObjectives;
    
public:
    UChallengeComponent();
    UFUNCTION(BlueprintCallable, Reliable, Server)
    void ServerResetAllChallenges();
    
    UFUNCTION(BlueprintCallable, Reliable, Server)
    void ServerGiveRewardsForChallengeRank(UChallengeRank* ChallengeRank);
    
    UFUNCTION(BlueprintCallable, Reliable, Server)
    void RequestUpdateActiveServerObjectives(const TArray<int32>& ObjectivesToAdd, const TArray<int32>& ObjectivesToRemove);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool HasChallengeInstance(const UChallenge* Challenge) const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    TArray<UChallenge*> GetChallengesByCategory(const FChallengeCategory& Category, bool bVisibleOnly) const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    UChallengeInstance* GetChallengeInstance(const UChallenge* Challenge) const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetCategoryProgress(const FChallengeCategory& Category, FPointSet& ChallengeProgress, FPointSet& PointProgress, bool bVisibleOnly) const;
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void EventChallengeUpdated(const UChallenge* Challenge) const;
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void EventChallengeUnlocked(const UChallenge* Challenge) const;
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void EventChallengesReset() const;
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void EventChallengeRevealed(const UChallenge* Challenge) const;
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void EventChallengeRankCompleted(const UChallenge* Challenge) const;
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void EventChallengeComplete(const UChallenge* Challenge) const;
    
    UFUNCTION(BlueprintCallable, Client, Reliable)
    void ClientUnlockChallenge(FGuid ChallengeId);
    
    UFUNCTION(BlueprintCallable, Client, Unreliable)
    void ClientReceiveReward(TSubclassOf<UChallengeReward> RewardClass);
    
    UFUNCTION(BlueprintCallable, Client, Reliable)
    void ClientIncrementObjective(int32 ObjectiveId, int32 Amount);
    
};

