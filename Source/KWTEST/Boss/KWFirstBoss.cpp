// Fill out your copyright notice in the Description page of Project Settings.


#include "KWFirstBoss.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "BossAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/KWCharacterPlayer.h"
#include "UI/BossHealthBar.h"
#include "Kismet/GameplayStatics.h"


AKWFirstBoss::AKWFirstBoss()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AKWFirstBoss::BeginPlay()
{
    Super::BeginPlay();
    SetBossState(EBossState::Idle);


    KWFirstBossMaxHealth = 100.0f;
    KWFirstBossCurrentHealth = 100.0f;
    TimeLimit = 3.0f;
    TimeBelowThreshold = 0.0f;

    //UE_LOG(LogTemp, Log, TEXT("HP : %f "), KWFirstBossCurrentHealth);
    //UE_LOG(LogTemp, Log, TEXT("TimeLimit : %f "), TimeLimit);
    //UE_LOG(LogTemp, Log, TEXT("TimeBelowThreshold : %f "), TimeBelowThreshold);

    if (HealthBarWidgetClass)
    {
        UBossHealthBar* LocalBossHealthBarWidgetInstance = CreateWidget<UBossHealthBar>(GetWorld(), HealthBarWidgetClass);
        if (LocalBossHealthBarWidgetInstance)
        {
            LocalBossHealthBarWidgetInstance->AddToViewport();
        }
    }
}

void AKWFirstBoss::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    switch (CurrentState)
    {
    case EBossState::Idle:
        HandleIdleState();
        break;
    case EBossState::Chase:
        HandleChaseState();
        break;
    case EBossState::Attack:
        HandleAttackState();
        break;
    case EBossState::Hit:
        HandleHitState();
        break;
    case EBossState::Staggered:
        HandleStaggeredState();
        break;
    case EBossState::Dead:
        HandleDeadState();
        break;
    default:
        break;
    }
}

void AKWFirstBoss::SetBossState(EBossState NewState)
{
    CurrentState = NewState;
}

EBossState AKWFirstBoss::GetBossState() const
{
    return EBossState();
}

void AKWFirstBoss::DecreaseBossHealth(float Amount)
{
    KWFirstBossCurrentHealth -= Amount;

    UE_LOG(LogTemp, Warning, TEXT("Boss HP : %f"), KWFirstBossCurrentHealth);
    // 체력이 0 이하가 되지 않도록 체크
    if (KWFirstBossCurrentHealth < 0)
    {
        KWFirstBossCurrentHealth = 0;
    }
}

float AKWFirstBoss::GetBossHealthPercentage()
{
    if (KWFirstBossMaxHealth <= 0.0f)
    {
        return 0.0f;
    }

    return KWFirstBossCurrentHealth / KWFirstBossMaxHealth;
}

void AKWFirstBoss::SetBossSpeed(float Speed)
{
    GetCharacterMovement()->MaxWalkSpeed = Speed;
}

void AKWFirstBoss::DistanceToPlayer()
{

}

void AKWFirstBoss::CheckDistanceAndTime()
{
}

void AKWFirstBoss::ApplyDamage()
{
    /*float DamageAmount = 1.0f;
    KWFirstBossCurrentHealth -= DamageAmount;

    // 체력이 0 이하일 때 사망 처리
    if (KWFirstBossCurrentHealth <= 0.0f)
    {
        KWFirstBossCurrentHealth = 0.0f; // 체력이 음수가 되지 않도록 설정
        UE_LOG(LogTemp, Log, TEXT("Died!"));
        // 사망 처리 (예시: 타이머 멈춤)
        GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
    }

    UE_LOG(LogTemp, Log, TEXT("Boss Current Health: %f"), KWFirstBossCurrentHealth);
    */


    //UE_LOG(LogTemp, Log, TEXT("TimeBelowThreshold : %f "), TimeBelowThreshold);

    if (TimeBelowThreshold >= TimeLimit)
    {
        KWFirstBossCurrentHealth -= 1.0f;
        //UE_LOG(LogTemp, Log, TEXT("Boss HP : %f "), KWFirstBossCurrentHealth);
    }
}

void AKWFirstBoss::AoEDoT()
{
    AActor* PlayerActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    AKWCharacterPlayer* PlayerCharacter = Cast<AKWCharacterPlayer>(PlayerActor);
    if (PlayerCharacter)
    {
        //  체력 감소 실행 (예: 5 데미지)
        PlayerCharacter->DecreasePlayerHealth(5.0f);
    }

   /* if (CurrentState == EBossState::Attack)
    {
        KWFirstBossCurrentHealth -= 1.0f;
        UE_LOG(LogTemp, Log, TEXT("Boss HP : %f "), KWFirstBossCurrentHealth);

        AActor* PlayerActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
        AKWCharacterPlayer* PlayerCharacter = Cast<AKWCharacterPlayer>(PlayerActor);

        if (PlayerCharacter)
        {
            // 3. 현재 체력 가져오기
            float PlayerCurrentHealth = PlayerCharacter->GetPlayerHealth();

            // 4. 데미지를 적용한 새 체력 계산
            float NewHealth = PlayerCurrentHealth - 1.0f;  // 보스가 20 데미지 줌

            // 5. 플레이어 체력 업데이트
            PlayerCharacter->SetPlayerHealth(NewHealth);

            UE_LOG(LogTemp, Warning, TEXT("Player HP: %f"), NewHealth);
        }
    }
    */
}

void AKWFirstBoss::RaiseTime()
{
    TimeBelowThreshold += 1.0f;
    //UE_LOG(LogTemp, Log, TEXT("TimeBelowThreshold : %f"), TimeBelowThreshold);
}

void AKWFirstBoss::DamageToPlayer1()
{
    // 1. 플레이어 캐릭터 찾기
    AActor* PlayerActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

    // 2. AKWCharacterBase로 캐스팅
    if (TimeBelowThreshold >= TimeLimit)
    {
        if (PlayerActor)
        {
            AKWCharacterPlayer* PlayerCharacter = Cast<AKWCharacterPlayer>(PlayerActor);

            if (PlayerCharacter)
            {
                // 3. 현재 체력 가져오기
                float PlayerCurrentHealth = PlayerCharacter->GetPlayerHealth();

                // 4. 데미지를 적용한 새 체력 계산
                float NewHealth = PlayerCurrentHealth - 1.0f;  // 보스가 20 데미지 줌

                // 5. 플레이어 체력 업데이트
                PlayerCharacter->SetPlayerHealth(NewHealth);

                //UE_LOG(LogTemp, Warning, TEXT("Player Health: %f"), NewHealth);
            }
        }
    }
}

void AKWFirstBoss::TakeDamage(float DamageAmount)
{
   
}

void AKWFirstBoss::HandleIdleState()
{
    ABossAIController* AIController = Cast<ABossAIController>(GetController());
    if (AIController)
    {
        AIController->ChasePlayer();
        SetBossState(EBossState::Chase);
        //UE_LOG(LogTemp, Log, TEXT("Change To Chase State!"));
    }
}

void AKWFirstBoss::HandleChaseState()
{
    SetBossSpeed(100.0f); // 보스 속도 설정
    TimeBelowThreshold = 0.0f;

    GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
    GetWorld()->GetTimerManager().ClearTimer(ApplyDamageTimerHandle);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn)
    {
        float Distance = FVector::Dist(GetActorLocation(), PlayerPawn->GetActorLocation());

        if (Distance < 200.0f)
        {
            SetBossState(EBossState::Attack);
            //UE_LOG(LogTemp, Log, TEXT("Change To Attack State!"));
        }
    }
}

void AKWFirstBoss::HandleAttackState()
{
    SetBossSpeed(0.0f); // 보스 제자리 고정

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn)
    {
        // Timer A가 이미 활성화되지 않았다면 타이머를 설정
        if (!GetWorld()->GetTimerManager().IsTimerActive(DamageTimerHandle))
        {
            GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle, this, &AKWFirstBoss::RaiseTime, 1.0f, true);
            //UE_LOG(LogTemp, Log, TEXT("Timer A set."));
        }
        else
        {
            //UE_LOG(LogTemp, Log, TEXT("Timer A is already active."));
        }

        // 3초가 지난 후 ApplyDamage 타이머 설정
        if (TimeBelowThreshold >= TimeLimit)
        {
            // Timer B가 이미 활성화되지 않았다면 타이머를 설정
            if (!GetWorld()->GetTimerManager().IsTimerActive(ApplyDamageTimerHandle))
            {
                GetWorld()->GetTimerManager().SetTimer(ApplyDamageTimerHandle, this, &AKWFirstBoss::AoEDoT, 1.0f, true);
                //UE_LOG(LogTemp, Log, TEXT("Timer B set."));
            }
            else
            {
                //UE_LOG(LogTemp, Log, TEXT("Timer B is already active."));
            }
        }

        // 거리 체크 및 상태 변경
        float Distance = FVector::Dist(GetActorLocation(), PlayerPawn->GetActorLocation());
        if (Distance > 250.0f)
        {
            SetBossState(EBossState::Chase);
            UE_LOG(LogTemp, Log, TEXT("Change To Chase State!"));
        }

        if (KWFirstBossCurrentHealth <= 0)
        {
            SetBossState(EBossState::Dead);
            UE_LOG(LogTemp, Log, TEXT("Change To Dead State!"));
        }
    }


}

void AKWFirstBoss::HandleHitState()
{
    // 피격 상태 로직 추가
}

void AKWFirstBoss::HandleStaggeredState()
{
    // 그로기 상태 로직 추가
}

void AKWFirstBoss::HandleDeadState()
{
    // 사망 상태 로직 추가
}