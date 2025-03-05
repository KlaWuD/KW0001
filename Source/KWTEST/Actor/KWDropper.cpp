// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/KWDropper.h"

AKWDropper::AKWDropper()
{
    PrimaryActorTick.bCanEverTick = true;

    // SkeletalMeshComponent ����
    SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
    RootComponent = SkeletalMeshComponent;

    // �⺻ ���� ����
    SkeletalMeshComponent->SetSimulatePhysics(false);

    // ���̷�Ż �޽� �ε� (C++���� ����)
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonDrongo/Characters/Heroes/Drongo/Meshes/Drongo_GDC.Drongo_GDC'"));

    // �޽��� ����� �ε�� ���, ����
    if (MeshAsset.Succeeded())
    {
        FallingSkeletalMesh = MeshAsset.Object;
    }
}

void AKWDropper::BeginPlay()
{
    Super::BeginPlay();

    // �ε��� ���̷�Ż �޽��� SkeletalMeshComponent�� ����
    if (FallingSkeletalMesh)
    {
        SkeletalMeshComponent->SetSkeletalMesh(FallingSkeletalMesh);
    }

    // ���� Ȱ��ȭ
    EnablePhysics();
}

void AKWDropper::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AKWDropper::EnablePhysics()
{
    // ���� �ùķ��̼� Ȱ��ȭ
    SkeletalMeshComponent->SetSimulatePhysics(true);
}
