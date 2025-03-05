// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Boss/KWFirstBoss.h"
#include "BossHealthBar.generated.h"

/**
 * 
 */


UCLASS()
class KWTEST_API UBossHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, Category = "Health Bar")
    float BossHealthPercentage;  // 보스 체력 비율

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UProgressBar* BossHealthBar;

    void UpdateBossHealthBar();

};
