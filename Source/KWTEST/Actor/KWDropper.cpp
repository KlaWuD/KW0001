// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/KWDropper.h"

AKWDropper::AKWDropper()
{
    PrimaryActorTick.bCanEverTick = true;

    // SkeletalMeshComponent 생성
    SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
    RootComponent = SkeletalMeshComponent;

    // 기본 물리 설정
    SkeletalMeshComponent->SetSimulatePhysics(false);

    // 스켈레탈 메쉬 로드 (C++에서 지정)
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonDrongo/Characters/Heroes/Drongo/Meshes/Drongo_GDC.Drongo_GDC'"));

    // 메쉬가 제대로 로드된 경우, 설정
    if (MeshAsset.Succeeded())
    {
        FallingSkeletalMesh = MeshAsset.Object;
    }
}

void AKWDropper::BeginPlay()
{
    Super::BeginPlay();

    // 로드한 스켈레탈 메쉬를 SkeletalMeshComponent에 적용
    if (FallingSkeletalMesh)
    {
        SkeletalMeshComponent->SetSkeletalMesh(FallingSkeletalMesh);
    }

    // 물리 활성화
    EnablePhysics();
}

void AKWDropper::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AKWDropper::EnablePhysics()
{
    // 물리 시뮬레이션 활성화
    SkeletalMeshComponent->SetSimulatePhysics(true);
}
