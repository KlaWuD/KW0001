// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/KWCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimMontage.h"
#include "KWComboActionData.h"
#include "Physics/KWCollision.h"


// Sets default values
AKWCharacterBase::AKWCharacterBase()
{
	// Pawn
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Capsule
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	// Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

	// Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));

	// Health
	//CurrentHealth = MaxHealth;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMuriel/Characters/Heroes/Muriel/Meshes/Muriel_GDC.Muriel_GDC'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}
}

//void AKWCharacterBase::ProcessComboCommand()
//{
//	if (CurrentCombo == 0)
//	{
//		ComboActionBegin();
//		return;
//	}
//
//	if (!ComboTimerHandle.IsValid())
//	{
//		HasNextComboCommand = false;
//	}
//	else
//	{
//		HasNextComboCommand = true;
//	}
//}
//
//void AKWCharacterBase::ComboActionBegin()
//{
//	//Combo Status
//	CurrentCombo = 1;
//
//	//Movement Setting
//	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
//
//	//Animation Setting
//	const float AttackSpeedRate = 1.0f;
//	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
//	AnimInstance->Montage_Play(ComboActionMontage, AttackSpeedRate);
//
//	FOnMontageEnded EndDelegate;
//	EndDelegate.BindUObject(this, &AKWCharacterBase::ComboActionEnd);
//	AnimInstance->Montage_SetEndDelegate(EndDelegate, ComboActionMontage);
//
//	ComboTimerHandle.Invalidate();
//	SetComboCheckTimer();
//}
//
//void AKWCharacterBase::ComboActionEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
//{
//	ensure(CurrentCombo != 0);
//	CurrentCombo = 0;
//	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
//}
//
//void AKWCharacterBase::SetComboCheckTimer()
//{
//	int32 ComboIndex = CurrentCombo - 1;
//	ensure(ComboActionData->EffectiveFrameCount.IsValidIndex(ComboIndex));
//
//	const float AttackSpeedRate = 1.0f;
//	float ComboEffectiveTime = (ComboActionData->EffectiveFrameCount[ComboIndex] / ComboActionData->FrameRate) / AttackSpeedRate;
//	if (ComboEffectiveTime > 0.0f)
//	{
//		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &AKWCharacterBase::ComboCheck, ComboEffectiveTime, false);
//	}
//}
//
//void AKWCharacterBase::ComboCheck()
//{
//	ComboTimerHandle.Invalidate();
//	if (HasNextComboCommand)
//	{
//		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
//
//		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboActionData->MaxComboCount);
//		FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboActionData->MontageSectionNamePrefix, CurrentCombo);
//		AnimInstance->Montage_JumpToSection(NextSection, ComboActionMontage);
//		SetComboCheckTimer();
//		HasNextComboCommand = false;
//	}
//}

