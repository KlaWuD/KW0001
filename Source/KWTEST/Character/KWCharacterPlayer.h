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
	float PlayerMaxHealth = 100.0f;  // 최대 체력

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* AttackAction;

	void SetPlayerSpeed(float Speed);

// 캐릭터 체력
public:
	void SetPlayerHealth(float NewHealth);
	float GetPlayerHealth() const;
	float GetPlayerMaxHealth() const;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	float PlayerCurrentHealth;  // 현재 체력
	void DecreasePlayerHealth(float Amount);

	
// 공격
	void PerformAttack();

	void StartAttackCooldown();

	void DeactivateHitbox();

	UFUNCTION()
	void OnHitboxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// 히트박스 활성화/비활성화 함수
	void EnableWeaponHitbox();
	void DisableWeaponHitbox();
	void DebugWeaponHitbox();

	float GetPlayerHealthPercentage();

private:
	// 공격 애니메이션 몽타주
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UAnimMontage* AttackMontage;

	// 현재 콤보 카운트
	int32 CurrentCombo = 0;

	// 최대 콤보 수 (2~3타 콤보)
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	int32 MaxCombo = 2;

	// 콤보가 이어질 수 있는 상태인지
	bool bCanCombo = false;

	// 다음 콤보를 실행할지 여부
	bool bComboInput = false;

	// 공격 실행 함수
	void HandleCombo();

	// 콤보 리셋 함수
	void ResetCombo();

	// 공격 애니메이션이 끝날 때 호출될 함수
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
	// 히트박스 컴포넌트 추가
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	class UBoxComponent* WeaponHitbox;

	// HealthBarWidget 클래스 레퍼런스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UHealthBarWidget> HealthBarWidgetClass;  // 플레이어 체력바

	// 체력바 위젯 인스턴스
	UPROPERTY()
	UHealthBarWidget* HealthBarWidgetInstance;
};
