// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/KWRandomDropper.h"
#include "Engine/World.h"
#include "KWDropper.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AKWRandomDropper::AKWRandomDropper()
{
    PrimaryActorTick.bCanEverTick = false;

    // 기본 범위 설정
    SpawnAreaMin = FVector(-700, -700, 950); // 예시값
    SpawnAreaMax = FVector(700, 700, 1000);  // 예시값

}

// Called when the game starts or when spawned
void AKWRandomDropper::BeginPlay()
{
	Super::BeginPlay();

    SpawnRandomFallingObject();

	
}

void AKWRandomDropper::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AKWRandomDropper::SpawnRandomFallingObject()
{
    // KWDropper 클래스 객체를 생성
    FActorSpawnParameters SpawnParams;
    FVector RandomLocation = FVector(
        FMath::FRandRange(SpawnAreaMin.X, SpawnAreaMax.X),
        FMath::FRandRange(SpawnAreaMin.Y, SpawnAreaMax.Y),
        FMath::FRandRange(SpawnAreaMin.Z, SpawnAreaMax.Z)
    );
    FRotator SpawnRotation = FRotator::ZeroRotator;

    AKWDropper* DroppedObject = GetWorld()->SpawnActor<AKWDropper>(RandomLocation, FRotator::ZeroRotator, SpawnParams);

    // 물리 활성화 여부 확인
    UPrimitiveComponent* SpawnedComponent = Cast<UPrimitiveComponent>(DroppedObject->GetRootComponent());
    if (SpawnedComponent)
    {
        SpawnedComponent->SetSimulatePhysics(true);
    }

    if (DroppedObject)
    {
        // 물리 시뮬레이션 활성화
        DroppedObject->EnablePhysics();
    }
}

