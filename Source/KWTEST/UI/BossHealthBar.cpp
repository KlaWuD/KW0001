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
        // ���� ü�� ���� ���� (���� Ŭ�������� GetBossHealthPercentage�� ȣ���� �� �ֽ��ϴ�)
        BossHealthPercentage = BossCharacter->GetBossHealthPercentage();
    }

    if (BossHealthBar)
    {
        BossHealthBar->SetPercent(BossHealthPercentage);
    }
}
