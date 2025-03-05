// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TimerManager.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "KWCharacterBase.h"
#include "KWCharacterPlayer.generated.h"

/**
 * 
 */
class UHealthBarWidget;
class UAnimMontage;
UCLASS()
class KWTEST_API AKWCharacterPlayer : public AKWCharacterBase
{
	GENERATED_BODY()
	
public:
	AKWCharacterPlayer();
protected:
	virtual void BeginPlay() override;
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void Move(const FInputActionValue& Value);
		
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float PlayerMaxHealth = 100.0f;  // �ִ� ü��

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* AttackAction;

	void SetPlayerSpeed(float Speed);

// ĳ���� ü��
public:
	void SetPlayerHealth(float NewHealth);
	float GetPlayerHealth() const;
	float GetPlayerMaxHealth() const;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	float PlayerCurrentHealth;  // ���� ü��
	void DecreasePlayerHealth(float Amount);

	
// ����
	void PerformAttack();

	void StartAttackCooldown();

	void DeactivateHitbox();

	UFUNCTION()
	void OnHitboxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// ��Ʈ�ڽ� Ȱ��ȭ/��Ȱ��ȭ �Լ�
	void EnableWeaponHitbox();
	void DisableWeaponHitbox();
	void DebugWeaponHitbox();

	float GetPlayerHealthPercentage();

private:
	// ���� �ִϸ��̼� ��Ÿ��
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UAnimMontage* AttackMontage;

	// ���� �޺� ī��Ʈ
	int32 CurrentCombo = 0;

	// �ִ� �޺� �� (2~3Ÿ �޺�)
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	int32 MaxCombo = 2;

	// �޺��� �̾��� �� �ִ� ��������
	bool bCanCombo = false;

	// ���� �޺��� �������� ����
	bool bComboInput = false;

	// ���� ���� �Լ�
	void HandleCombo();

	// �޺� ���� �Լ�
	void ResetCombo();

	// ���� �ִϸ��̼��� ���� �� ȣ��� �Լ�
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION(BlueprintCallable, Category = "Combo")
	void EnableCombo();

	void ReturnToDefaultWalkSpeed();

	void LockLookAxis();

	void UnlockLookAxis();

	bool bIsAttacking = false;
	
	bool bCanAttack = true;
	float AttackCooldown = 2.0f;
	FTimerHandle AttackStuckTimer;
	FTimerHandle HitboxTimerHandle;
	FTimerHandle CharacterWeaponHitBoxTimerHandle;

	float DefaultWalkSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hitbox", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* AttackHitbox;

public:
	// ��Ʈ�ڽ� ������Ʈ �߰�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	class UBoxComponent* WeaponHitbox;

	// HealthBarWidget Ŭ���� ���۷���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UHealthBarWidget> HealthBarWidgetClass;  // �÷��̾� ü�¹�

	// ü�¹� ���� �ν��Ͻ�
	UPROPERTY()
	UHealthBarWidget* HealthBarWidgetInstance;
};
