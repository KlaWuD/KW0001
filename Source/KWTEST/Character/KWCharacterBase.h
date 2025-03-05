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
	// �⺻ ü�� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.0f;  // �ִ� ü��

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	float CurrentHealth;  // ���� ü��

public:
	// ü�� ���� �Լ���
	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void Heal(float HealAmount);

	//UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercentage() const;

private:
	// �Ÿ��� �ð� ���� ����
	UPROPERTY(EditAnywhere, Category = "Distance")
	float DistanceThreshold = 500.0f;  // ��ǥ �Ÿ� (500m ����)

	UPROPERTY(EditAnywhere, Category = "Distance")
	float TimeLimit = 3.0f;  // �� �ð� �̻� �Ÿ��� �����Ǹ� ����

	float TimeBelowThreshold = 0.0f;  // �Ÿ��� TimeThreshold ���Ϸ� ������ �ð�

	// Ÿ�̸� �ڵ�
	FTimerHandle DistanceCheckTimerHandle;

	// Ÿ�̸ӷ� ȣ��� �Լ�
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
