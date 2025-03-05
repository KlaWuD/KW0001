// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BossState.h"
#include "KWFirstBoss.generated.h"


class UBossHealthBar;

UCLASS()
class KWTEST_API AKWFirstBoss : public ACharacter
{
    GENERATED_BODY()

public:
    AKWFirstBoss();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    EBossState CurrentState;

    void HandleIdleState();
    void HandleChaseState();
    void HandleAttackState();
    void HandleHitState();
    void HandleStaggeredState();
    void HandleDeadState();

    void SetBossState(EBossState NewState);

public:
    EBossState GetBossState() const;
    
    void DecreaseBossHealth(float Amount);

    float GetBossHealthPercentage();

private:
    void SetBossSpeed(float Speed);
    void DistanceToPlayer();

private:
    UPROPERTY(EditAnywhere, Category = "Distance")
    float TimeLimit;  // 이 시간 이상 거리가 유지되면 동작

    float TimeBelowThreshold = 0.0f;  // 거리가 TimeThreshold 이하로 유지된 시간

    // 타이머 핸들
    FTimerHandle DistanceCheckTimerHandle;

    // 타이머로 호출될 함수
    void CheckDistanceAndTime();

    // 타이머 핸들
    FTimerHandle DamageTimerHandle;
    FTimerHandle ApplyDamageTimerHandle;

    // 타이머로 호출될 함수
    void ApplyDamage();
    void AoEDoT();
    void RaiseTime();
    
    void DamageToPlayer1();

protected:
    // 기본 체력 변수들
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    float KWFirstBossMaxHealth;  // 최대 체력

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
    float KWFirstBossCurrentHealth;  // 현재 체력

public:
    // 체력 관련 함수들
    UFUNCTION(BlueprintCallable, Category = "Health")
    void TakeDamage(float DamageAmount);
    /*
    UFUNCTION(BlueprintCallable, Category = "Health")
    void Heal(float HealAmount);

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealthPercentage() const;
    */

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UBossHealthBar> HealthBarWidgetClass;  // 보스 체력바

    // 체력바 위젯 인스턴스
    UPROPERTY()
    UBossHealthBar* BossHealthBarWidgetInstance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> BossHealthBarWidgetClass;
};
