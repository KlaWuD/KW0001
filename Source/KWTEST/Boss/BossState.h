#pragma once

#include "CoreMinimal.h"
#include "BossState.generated.h"

UENUM(BlueprintType)
enum class EBossState : uint8
{
    Idle        UMETA(DisplayName = "Idle"),         // ���
    Chase       UMETA(DisplayName = "Chase"),        // ����
    Attack      UMETA(DisplayName = "Attack"),       // ����
    Hit         UMETA(DisplayName = "Hit"),          // �ǰ�
    Staggered   UMETA(DisplayName = "Staggered"),    // �׷α�(����)
    Dead        UMETA(DisplayName = "Dead")          // ���
};