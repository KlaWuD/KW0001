// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HealthBarWidget.h"
#include "Character/KWCharacterPlayer.h"
#include "Boss/KWFirstBoss.h"
#include "Kismet/GameplayStatics.h"


void UHealthBarWidget::UpdateHealthBar()
{
    AActor* PlayerActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    AKWCharacterPlayer* PlayerCharacter = Cast<AKWCharacterPlayer>(PlayerActor);

    // �÷��̾� ü�� �� ������Ʈ (���� �ڵ�)
    if (PlayerCharacter)
    {
        PlayerHealthPercentage = PlayerCharacter->GetPlayerHealthPercentage();
    }

    // ü�� �� ������Ʈ
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
//        // ���� ü�� ���� ���� (���� Ŭ�������� GetBossHealthPercentage�� ȣ���� �� �ֽ��ϴ�)
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
