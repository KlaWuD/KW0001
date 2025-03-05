#pragma once

#include "CoreMinimal.h"
#include "BossState.generated.h"

UENUM(BlueprintType)
enum class EBossState : uint8
{
    Idle        UMETA(DisplayName = "Idle"),         // 대기
    Chase       UMETA(DisplayName = "Chase"),        // 추적
    Attack      UMETA(DisplayName = "Attack"),       // 공격
    Hit         UMETA(DisplayName = "Hit"),          // 피격
    Staggered   UMETA(DisplayName = "Staggered"),    // 그로기(경직)
    Dead        UMETA(DisplayName = "Dead")          // 사망
};