// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss/BossAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "NavigationSystem.h"
#include "BossState.h"
#include "TimerManager.h"
#include "KWFirstBoss.h"

ABossAIController::ABossAIController()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ABossAIController::BeginPlay()
{
    Super::BeginPlay();
    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void ABossAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (PlayerPawn)
    {
        MoveToActor(PlayerPawn, 5.0f);
    }
}

void ABossAIController::ChasePlayer()
{
    if (PlayerPawn)
    {
        MoveToActor(PlayerPawn, 5.0f);
    }
}