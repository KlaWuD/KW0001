// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "KWRandomDropper.generated.h"

UCLASS()
class KWTEST_API AKWRandomDropper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKWRandomDropper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
    virtual void Tick(float DeltaTime) override;

    // ��ü�� ������ ���� (X, Y, Z)
    UPROPERTY(EditAnywhere, Category = "Spawn Parameters")
    FVector SpawnAreaMin;

    UPROPERTY(EditAnywhere, Category = "Spawn Parameters")
    FVector SpawnAreaMax;

    // ��ü ���� �� ���� ��ġ���� ����߸��� �Լ�
    void SpawnRandomFallingObject();
};
