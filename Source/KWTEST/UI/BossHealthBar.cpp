// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BossHealthBar.h"
#include "Boss/KWFirstBoss.h"
#include "Kismet/GameplayStatics.h"

void UBossHealthBar::UpdateBossHealthBar()
{
    AActor* BossActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    AKWFirstBoss* BossCharacter = Cast<AKWFirstBoss>(BossActor);

    if (BossCharacter)
    {
        // 보스 체력 비율 설정 (보스 클래스에서 GetBossHealthPercentage를 호출할 수 있습니다)
        BossHealthPercentage = BossCharacter->GetBossHealthPercentage();
    }

    if (BossHealthBar)
    {
        BossHealthBar->SetPercent(BossHealthPercentage);
    }
}
