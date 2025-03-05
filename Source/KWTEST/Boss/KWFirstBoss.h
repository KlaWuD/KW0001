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
    float TimeLimit;  // �� �ð� �̻� �Ÿ��� �����Ǹ� ����

    float TimeBelowThreshold = 0.0f;  // �Ÿ��� TimeThreshold ���Ϸ� ������ �ð�

    // Ÿ�̸� �ڵ�
    FTimerHandle DistanceCheckTimerHandle;

    // Ÿ�̸ӷ� ȣ��� �Լ�
    void CheckDistanceAndTime();

    // Ÿ�̸� �ڵ�
    FTimerHandle DamageTimerHandle;
    FTimerHandle ApplyDamageTimerHandle;

    // Ÿ�̸ӷ� ȣ��� �Լ�
    void ApplyDamage();
    void AoEDoT();
    void RaiseTime();
    
    void DamageToPlayer1();

protected:
    // �⺻ ü�� ������
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    float KWFirstBossMaxHealth;  // �ִ� ü��

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
    float KWFirstBossCurrentHealth;  // ���� ü��

public:
    // ü�� ���� �Լ���
    UFUNCTION(BlueprintCallable, Category = "Health")
    void TakeDamage(float DamageAmount);
    /*
    UFUNCTION(BlueprintCallable, Category = "Health")
    void Heal(float HealAmount);

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealthPercentage() const;
    */

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UBossHealthBar> HealthBarWidgetClass;  // ���� ü�¹�

    // ü�¹� ���� �ν��Ͻ�
    UPROPERTY()
    UBossHealthBar* BossHealthBarWidgetInstance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> BossHealthBarWidgetClass;
};
