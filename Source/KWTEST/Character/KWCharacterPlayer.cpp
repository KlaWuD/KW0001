// Fill out your copyright notice in the Description page of Project Settings.

#include "KWCharacterPlayer.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Boss/KWFirstBoss.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "UI/HealthBarWidget.h"
#include "EnhancedInputComponent.h"








AKWCharacterPlayer::AKWCharacterPlayer()
{
    static ConstructorHelpers::FObjectFinder<UInputAction> InputActionAttackMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ArenaBattle/Blueprint/Input/Actions/IA_Attack.IA_Attack'"));
    if (nullptr != InputActionAttackMoveRef.Object)
    {
        AttackAction = InputActionAttackMoveRef.Object;
        //UE_LOG(LogTemp, Warning, TEXT("InpurActionAttackMoveRef.Object -> IA.Attack"));
    }

    // 히트박스 생성
    AttackHitbox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AttackHitbox"));
    AttackHitbox->SetupAttachment(RootComponent);
    AttackHitbox->SetCollisionEnabled(ECollisionEnabled::NoCollision);  // 기본적으로 비활성화
    AttackHitbox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    AttackHitbox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    AttackHitbox->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);  // 적과만 충돌

    WeaponHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponHitbox"));
    WeaponHitbox->SetupAttachment(GetMesh(), TEXT("WeaponAttachPointR")); // 캐릭터의 무기 소켓에 부착
    WeaponHitbox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    WeaponHitbox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    WeaponHitbox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    WeaponHitbox->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AKWCharacterPlayer::BeginPlay()
{
    Super::BeginPlay();

    
    PlayerCurrentHealth = 100.0f;

    DefaultWalkSpeed = 500.0f;

    GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;

    APlayerController* PlayerController = Cast<APlayerController>(GetController());
    if (PlayerController)
    {
        UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
        if (InputSubsystem && DefaultMappingContext)
        {
            InputSubsystem->AddMappingContext(DefaultMappingContext, 0);
            //UE_LOG(LogTemp, Warning, TEXT("AddMappingContext -> DefaultMappingContext"));
        }
    }

    bIsAttacking = false;

    //AttackCooldown = 2.0f;

    bCanCombo = true;

    CurrentCombo = 0;

    ResetCombo();

    if (WeaponHitbox)
    {
        WeaponHitbox->OnComponentBeginOverlap.AddDynamic(this, &AKWCharacterPlayer::OnHitboxOverlap);
    }

    //if (WeaponHitbox)
    //{
    //    WeaponHitbox->OnComponentBeginOverlap.AddDynamic(this, &AKWCharacterPlayer::OnHitboxOverlap);
    //}

    if (HealthBarWidgetClass)
    {
        UHealthBarWidget* LocalHealthBarWidgetInstance = CreateWidget<UHealthBarWidget>(GetWorld(), HealthBarWidgetClass);
        if (LocalHealthBarWidgetInstance)
        {
            LocalHealthBarWidgetInstance->AddToViewport();
        }
    }
}

void AKWCharacterPlayer::SetPlayerSpeed(float Speed)
{
    
}

void AKWCharacterPlayer::SetPlayerHealth(float NewHealth)
{
	PlayerCurrentHealth = FMath::Clamp(NewHealth, 0.0f, 100.0f);  // 값 제한

}

float AKWCharacterPlayer::GetPlayerHealth() const
{
	return PlayerCurrentHealth;
}

float AKWCharacterPlayer::GetPlayerMaxHealth() const
{
    return PlayerMaxHealth;
}

void AKWCharacterPlayer::DecreasePlayerHealth(float Amount)
{
    if (!this)
    {
        UE_LOG(LogTemp, Error, TEXT("DecreasePlayerHealth: this is nullptr!"));
        return;
    }
    
    
    PlayerCurrentHealth -= Amount;

    
    UE_LOG(LogTemp, Warning, TEXT("Player HP : %f"), PlayerCurrentHealth);

    // 체력이 0 이하가 되지 않도록 체크
    if (PlayerCurrentHealth < 0)
    {
        PlayerCurrentHealth = 0;
    }

    //// 체력 감소 로그 출력
    //UE_LOG(LogTemp, Warning, TEXT("Player Health: %f"), PlayerCurrentHealth);
}

void AKWCharacterPlayer::PerformAttack()
{
    UE_LOG(LogTemp, Warning, TEXT("PerformAttack is On"));
    if (bIsAttacking || !bCanCombo)
    {
        return;
        //UE_LOG(LogTemp, Warning, TEXT("bIsAttacking is true or bCanCombo is false"));
    }

    EnableWeaponHitbox();

    GetWorldTimerManager().SetTimer(CharacterWeaponHitBoxTimerHandle, this, &AKWCharacterPlayer::DisableWeaponHitbox, 0.5f, false);

    DebugWeaponHitbox();

    // 현재 콤보가 가능할 때만 실행
    if (bCanCombo)
    {
        //UE_LOG(LogTemp, Warning, TEXT("bCanCombo is true"));
        //UE_LOG(LogTemp, Warning, TEXT("CurrentCombo is %s"), CurrentCombo);

        if (CurrentCombo == 0)
        {
            HandleCombo();
            //UE_LOG(LogTemp, Warning, TEXT("bCanCombo is false from PerformAttack"));
            //UE_LOG(LogTemp, Warning, TEXT("HandleCombo from PerformAttack"));
            //UE_LOG(LogTemp, Warning, TEXT("CurrentCombo is %s"),CurrentCombo);
        }
        else
        {
            bComboInput = true; // 다음 콤보 입력 저장
            HandleCombo();
            //UE_LOG(LogTemp, Warning, TEXT("bCanCombo is true from PerformAttack"));
            //UE_LOG(LogTemp, Warning, TEXT("CurrentCombo is %s"), CurrentCombo);
        }
    }

}

void AKWCharacterPlayer::StartAttackCooldown()
{
    //bCanAttack = false;
    //GetWorldTimerManager().SetTimer(AttackCooldownTimer, this, &AKWCharacterPlayer::EnableCombo, AttackCooldown, false);
}

void AKWCharacterPlayer::DeactivateHitbox()
{
    AttackHitbox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AKWCharacterPlayer::OnHitboxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Log, TEXT("OnHitboxOverlap is On"));
    
    if (OtherActor && OtherActor != this && OtherComp && OtherActor->IsA(AKWFirstBoss::StaticClass()))
    {
        AKWFirstBoss* Boss = Cast<AKWFirstBoss>(OtherActor);
        if (Boss)
        {
            Boss->DecreaseBossHealth(1.0f); // 1 데미지 적용
            UE_LOG(LogTemp, Warning, TEXT("Hit boss!"));
        }
    }
}

void AKWCharacterPlayer::EnableWeaponHitbox()
{
    WeaponHitbox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    UE_LOG(LogTemp, Warning, TEXT("Weapon hitbox enabled!"));
}

void AKWCharacterPlayer::DisableWeaponHitbox()
{
    if (!this || !GetWorld())
    {
        UE_LOG(LogTemp, Error, TEXT("Timer Set Failed: Invalid World or this pointer!"));
        return;
    }

    if (WeaponHitbox)
    {
        UE_LOG(LogTemp, Warning, TEXT("Weapon Hitbox is valid"));
        WeaponHitbox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        UE_LOG(LogTemp, Warning, TEXT("Weapon hitbox disabled!"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("WeaponHitbox is NULL!"));
    }
}

void AKWCharacterPlayer::DebugWeaponHitbox()
{
    if (WeaponHitbox)
    {
        FVector Location = WeaponHitbox->GetComponentLocation();
        FQuat Rotation = WeaponHitbox->GetComponentQuat();
        FVector Extent = WeaponHitbox->GetScaledBoxExtent();

        DrawDebugBox(GetWorld(), Location, Extent, Rotation, FColor::Red, false, 1.0f);
    }
}

float AKWCharacterPlayer::GetPlayerHealthPercentage()
{
    if (PlayerCurrentHealth <= 0.0f)
    {
        return 0.0f;
    }

    return (PlayerCurrentHealth / PlayerMaxHealth);
}

void AKWCharacterPlayer::HandleCombo()
{
    GetCharacterMovement()->MaxWalkSpeed = 0.0f;
    if (!AttackMontage) return;
    UE_LOG(LogTemp, Warning, TEXT("HandleCombo is On"));



    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    if (AnimInstance)
    {
        if (CurrentCombo < MaxCombo)
        {
            bIsAttacking = true;

            CurrentCombo++;
            //UE_LOG(LogTemp, Warning, TEXT("CurrentCombo is %d from HandleCombo"),CurrentCombo);

            //LockLookAxis();

            AnimInstance->Montage_Play(AttackMontage);
            AnimInstance->Montage_JumpToSection(FName(*FString::Printf(TEXT("Attack%d"), CurrentCombo)), AttackMontage);

            // 공격 히트박스를 활성화
            AttackHitbox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
           

            GetWorld()->GetTimerManager().SetTimer(HitboxTimerHandle, this, &AKWCharacterPlayer::DeactivateHitbox, 0.2f, false); // 예시: 0.5초 후 비활성화

            // 애니메이션 종료 이벤트 바인딩
            FOnMontageEnded EndDelegate;
            EndDelegate.BindUObject(this, &AKWCharacterPlayer::OnAttackMontageEnded);
            AnimInstance->Montage_SetEndDelegate(EndDelegate, AttackMontage);
        }
    }

    GetWorld()->GetTimerManager().SetTimer(AttackStuckTimer, this, &AKWCharacterPlayer::ReturnToDefaultWalkSpeed, 0.5f, false);

}

void AKWCharacterPlayer::ResetCombo()
{
    CurrentCombo = 0;
    bCanCombo = false;
    bComboInput = false;

    //UE_LOG(LogTemp, Warning, TEXT("bCanCombo is false from ResetCombo"));

    EnableCombo();
}

void AKWCharacterPlayer::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
    if (Montage == AttackMontage)
    {
        bIsAttacking = false;

        if (bComboInput && CurrentCombo < MaxCombo)
        {
            bComboInput = false;
            HandleCombo();/*
            UE_LOG(LogTemp, Warning, TEXT("bCanCombo is true from OnAttackMontageEnded"));

            UE_LOG(LogTemp, Warning, TEXT("HandleCombo from OnAttackMontageEnded"));*/

            GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
        }
        else if (CurrentCombo == MaxCombo)
        {
            //UE_LOG(LogTemp, Warning, TEXT("CurrentCombo is %d from OnAttackMontageEnded's else before ResetCombo"), CurrentCombo);
            ResetCombo();
            bIsAttacking = false;
            //UE_LOG(LogTemp, Warning, TEXT("CurrentCombo is %d from OnAttackMontageEnded's else after ResetCombo"), CurrentCombo);

            GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
        }
    }
}

void AKWCharacterPlayer::EnableCombo()
{
    if (!bIsAttacking)
    {
        bCanCombo = true;
        //UE_LOG(LogTemp, Log, TEXT("Combo Enabled! Next attack can be chained."));
        //UE_LOG(LogTemp, Warning, TEXT("bCanCombo is true from EnableCombo"));

        bCanAttack = true;
    }
}

void AKWCharacterPlayer::ReturnToDefaultWalkSpeed()
{
    GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
}

void AKWCharacterPlayer::LockLookAxis()
{
    //bUseControllerRotationYaw = false;
    //GetCharacterMovement()->bOrientRotationToMovement = false;

    //GetWorldTimerManager().SetTimer(CharacterWeaponHitBoxTimerHandle, this, &AKWCharacterPlayer::UnlockLookAxis, 0.5f, false);
   
    UE_LOG(LogTemp, Warning, TEXT("LockLookAxis"));

    bUseControllerRotationYaw = true;
    //GetCharacterMovement()->bOrientRotationToMovement = true;

    // 0.5초 후에 UnlockLookAxis() 실행
    GetWorldTimerManager().SetTimer(CharacterWeaponHitBoxTimerHandle, this, &AKWCharacterPlayer::UnlockLookAxis, 0.5f, false);
}

void AKWCharacterPlayer::UnlockLookAxis()
{
    UE_LOG(LogTemp, Warning, TEXT("UnlockLookAxis!"));

    bUseControllerRotationYaw = false;
    //GetCharacterMovement()->bOrientRotationToMovement = false;
}

void AKWCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    if (EnhancedInputComponent)
    {
        //UE_LOG(LogTemp, Log, TEXT("SetupPlayerInputComponent OK!"));

        // 이동 입력 바인딩
        if (MoveAction)
        {
            EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AKWCharacterPlayer::Move);
        }

        // 점프 입력 바인딩
        if (JumpAction)
        {
            EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AKWCharacterPlayer::Jump);
            EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AKWCharacterPlayer::StopJumping);
        }

        //공격 입력 바인딩
        if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent))
        {
            EnhancedInputComp->BindAction(AttackAction, ETriggerEvent::Started, this, &AKWCharacterPlayer::PerformAttack);

            //UE_LOG(LogTemp, Warning, TEXT("HandleCombo from SetupPlayerInputComponent"));
        }

        //UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
        //if (EnhancedInputComp)
        //{
        //    // Attack InputAction과 HandleCombo 바인딩
        //    EnhancedInputComp->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AKWCharacterPlayer::HandleCombo);
        //}

    }
}

void AKWCharacterPlayer::Move(const FInputActionValue& Value)
{
    if (bIsAttacking) return;

    FVector2D MovementVector = Value.Get<FVector2D>();


    if (Controller && (MovementVector.X != 0.0f || MovementVector.Y != 0.0f))
    {
        // 카메라의 방향을 기준으로 이동 벡터 계산
        FRotator Rotation = Controller->GetControlRotation();
        FRotator YawRotation(0, Rotation.Yaw, 0);

        FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        // 이동 적용
        AddMovementInput(ForwardDirection, MovementVector.Y);
        AddMovementInput(RightDirection, MovementVector.X);


    }
}