// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/KWRandomDropper.h"
#include "Engine/World.h"
#include "KWDropper.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AKWRandomDropper::AKWRandomDropper()
{
    PrimaryActorTick.bCanEverTick = false;

    // �⺻ ���� ����
    SpawnAreaMin = FVector(-700, -700, 950); // ���ð�
    SpawnAreaMax = FVector(700, 700, 1000);  // ���ð�

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
    // KWDropper Ŭ���� ��ü�� ����
    FActorSpawnParameters SpawnParams;
    FVector RandomLocation = FVector(
        FMath::FRandRange(SpawnAreaMin.X, SpawnAreaMax.X),
        FMath::FRandRange(SpawnAreaMin.Y, SpawnAreaMax.Y),
        FMath::FRandRange(SpawnAreaMin.Z, SpawnAreaMax.Z)
    );
    FRotator SpawnRotation = FRotator::ZeroRotator;

    AKWDropper* DroppedObject = GetWorld()->SpawnActor<AKWDropper>(RandomLocation, FRotator::ZeroRotator, SpawnParams);

    // ���� Ȱ��ȭ ���� Ȯ��
    UPrimitiveComponent* SpawnedComponent = Cast<UPrimitiveComponent>(DroppedObject->GetRootComponent());
    if (SpawnedComponent)
    {
        SpawnedComponent->SetSimulatePhysics(true);
    }

    if (DroppedObject)
    {
        // ���� �ùķ��̼� Ȱ��ȭ
        DroppedObject->EnablePhysics();
    }
}

