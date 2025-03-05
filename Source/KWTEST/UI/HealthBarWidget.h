// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class KWTEST_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UPROPERTY(BlueprintReadWrite, Category = "Health Bar")
    float PlayerHealthPercentage;  // 보스 체력 비율

public:
 
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UProgressBar* PlayerHealthBar;

    void UpdateHealthBar();  // 체력 바 업데이트 함수

    //void UpdateBossHealthBar();

private:
    void NativeTick(const FGeometry& MyGeometry, float DeltaTime);

//public:
//    UPROPERTY(BlueprintReadWrite, Category = "Health Bar")
//    float BossHealthPercentage;  // 보스 체력 비율
//
//    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
//    UProgressBar* BossHealthBar;
};
