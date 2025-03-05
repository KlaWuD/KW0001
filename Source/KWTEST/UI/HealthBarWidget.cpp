// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HealthBarWidget.h"
#include "Character/KWCharacterPlayer.h"
#include "Boss/KWFirstBoss.h"
#include "Kismet/GameplayStatics.h"


void UHealthBarWidget::UpdateHealthBar()
{
    AActor* PlayerActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    AKWCharacterPlayer* PlayerCharacter = Cast<AKWCharacterPlayer>(PlayerActor);

    // 플레이어 체력 바 업데이트 (기존 코드)
    if (PlayerCharacter)
    {
        PlayerHealthPercentage = PlayerCharacter->GetPlayerHealthPercentage();
    }

    // 체력 바 업데이트
    if (PlayerHealthBar)
    {
        PlayerHealthBar->SetPercent(PlayerHealthPercentage);
    }
}

//void UHealthBarWidget::UpdateBossHealthBar()
//{
//    AActor* BossActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
//    AKWFirstBoss* BossCharacter = Cast<AKWFirstBoss>(BossActor);
//
//    if (BossCharacter)
//    {
//        // 보스 체력 비율 설정 (보스 클래스에서 GetBossHealthPercentage를 호출할 수 있습니다)
//        BossHealthPercentage = BossCharacter->GetBossHealthPercentage();
//    }
//
//    if (BossHealthBar)
//    {
//        BossHealthBar->SetPercent(BossHealthPercentage);
//    }
//}

void UHealthBarWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
    Super::NativeTick(MyGeometry, DeltaTime);

    UpdateHealthBar();
    //UpdateBossHealthBar();
}
