// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BossAIController.generated.h"

/**
 * 
 */
UCLASS()
class KWTEST_API ABossAIController : public AAIController
{
    GENERATED_BODY()

public:
    ABossAIController();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    void ChasePlayer();  // 플레이어 추적 함수

private:
    APawn* PlayerPawn;
};