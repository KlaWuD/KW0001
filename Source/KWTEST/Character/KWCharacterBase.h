// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KWCharacterBase.generated.h"

UCLASS()
class KWTEST_API AKWCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKWCharacterBase();


/*
protected:
	// 기본 체력 변수들
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.0f;  // 최대 체력

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	float CurrentHealth;  // 현재 체력

public:
	// 체력 관련 함수들
	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void Heal(float HealAmount);

	//UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercentage() const;

private:
	// 거리와 시간 관련 변수
	UPROPERTY(EditAnywhere, Category = "Distance")
	float DistanceThreshold = 500.0f;  // 목표 거리 (500m 이하)

	UPROPERTY(EditAnywhere, Category = "Distance")
	float TimeLimit = 3.0f;  // 이 시간 이상 거리가 유지되면 동작

	float TimeBelowThreshold = 0.0f;  // 거리가 TimeThreshold 이하로 유지된 시간

	// 타이머 핸들
	FTimerHandle DistanceCheckTimerHandle;

	// 타이머로 호출될 함수
	void CheckDistanceAndTime();
	*/

//	//Combo Attack Section
//protected:
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
//	TObjectPtr<class UAnimMontage> ComboActionMontage;
//
//	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
//	TObjectPtr<class UKWComboActionData> ComboActionData;
//
//	void ProcessComboCommand();
//
//	void ComboActionBegin();
//	void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);
//	void SetComboCheckTimer();
//	void ComboCheck();
//
//	int32 CurrentCombo = 0;
//	FTimerHandle ComboTimerHandle;
//	bool HasNextComboCommand = false;

};
