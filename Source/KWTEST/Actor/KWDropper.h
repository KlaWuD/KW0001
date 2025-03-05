// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KWDropper.generated.h"

UCLASS()
class KWTEST_API AKWDropper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKWDropper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Skeletal MeshComponent
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkeletalMeshComponent;

	// 물리 시뮬레이션을 위한 컴포넌트 활성화
	void EnablePhysics();

	// 스켈레탈 메쉬를 C++ 코드에서 설정
	USkeletalMesh* FallingSkeletalMesh;
};