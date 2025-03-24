// Fill out your copyright notice in the Description page of Project Settings.


#include "LSCharacter.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ItemBase.h"
#include "Components/BoxComponent.h"

// Sets default values
ALSCharacter::ALSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	VRCamera->SetupAttachment(RootComponent);

	scene = CreateDefaultSubobject<USceneComponent>(TEXT("scene"));
	scene->SetupAttachment(RootComponent);

	// Crouch 설정켜기
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

	ConstructorHelpers::FObjectFinder<UInputMappingContext> TempIMC (TEXT("/Script/EnhancedInput.InputMappingContext'/Game/KHH/Input/IMC_LS.IMC_LS'"));
	if (TempIMC.Succeeded())
	{
		IMC_LS = TempIMC.Object;
	}
	ConstructorHelpers::FObjectFinder<UInputAction> TempIA_Move(TEXT("/Script/EnhancedInput.InputAction'/Game/KHH/Input/IA_LSMove.IA_LSMove'"));
	if (TempIA_Move.Succeeded())
	{
		IA_Move = TempIA_Move.Object;
	}
	ConstructorHelpers::FObjectFinder<UInputAction> TempIA_Turn(TEXT("/Script/EnhancedInput.InputAction'/Game/KHH/Input/IA_LSTurn.IA_LSTurn'"));
	if (TempIA_Turn.Succeeded())
	{
		IA_Turn = TempIA_Turn.Object;
	}
	ConstructorHelpers::FObjectFinder<UInputAction> TempIA_Run(TEXT("/Script/EnhancedInput.InputAction'/Game/KHH/Input/IA_LSRun.IA_LSRun'"));
	if (TempIA_Run.Succeeded())
	{
		IA_Run = TempIA_Run.Object;
	}
	ConstructorHelpers::FObjectFinder<UInputAction> TempIA_Duck(TEXT("/Script/EnhancedInput.InputAction'/Game/KHH/Input/IA_LSDuck.IA_LSDuck'"));
	if (TempIA_Duck.Succeeded())
	{
		IA_Duck = TempIA_Duck.Object;
	}
	ConstructorHelpers::FObjectFinder<UInputAction> TempIA_Interact(TEXT("/Script/EnhancedInput.InputAction'/Game/KHH/Input/IA_LSInteract.IA_LSInteract'"));
	if (TempIA_Interact.Succeeded())
	{
		IA_Interact = TempIA_Interact.Object;
	}
	ConstructorHelpers::FObjectFinder<UInputAction> TempIA_Jump(TEXT("/Script/EnhancedInput.InputAction'/Game/KHH/Input/IA_LSJump.IA_LSJump'"));
	if (TempIA_Jump.Succeeded())
	{
		IA_Jump = TempIA_Jump.Object;
	}
}

// Called when the game starts or when spawned
void ALSCharacter::BeginPlay()
{
	Super::BeginPlay();
	ItemArray.SetNum(4);
}

// Called every frame
void ALSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void ALSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PC = Cast<APlayerController>(Controller);
	if (PC)
	{
		if(UEnhancedInputLocalPlayerSubsystem* ss = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			ss->AddMappingContext(IMC_LS, 1);
		}
	}

	UEnhancedInputComponent* InputSys = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (InputSys)
	{
		InputSys->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ALSCharacter::Move);
		InputSys->BindAction(IA_Turn, ETriggerEvent::Triggered, this, &ALSCharacter::Turn);
		InputSys->BindAction(IA_Run, ETriggerEvent::Started, this, &ALSCharacter::RunStart);
		InputSys->BindAction(IA_Run, ETriggerEvent::Completed, this, &ALSCharacter::RunEnd);
		InputSys->BindAction(IA_Duck, ETriggerEvent::Started, this, &ALSCharacter::DuckStart);
		InputSys->BindAction(IA_Duck, ETriggerEvent::Completed, this, &ALSCharacter::DuckEnd);
		InputSys->BindAction(IA_Jump, ETriggerEvent::Started, this, &ALSCharacter::Jump);
		InputSys->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ALSCharacter::StopJumping);
		InputSys->BindAction(IA_Interact, ETriggerEvent::Triggered, this, &ALSCharacter::Interact);
		InputSys->BindAction(IA_Throw, ETriggerEvent::Started, this, &ALSCharacter::Throw);
		InputSys->BindAction(IA_ChangeItem, ETriggerEvent::Triggered, this, &ALSCharacter::ChangeItem);
	}
}

void ALSCharacter::Move(const struct FInputActionValue& val)
{
	FVector2D scale = val.Get<FVector2D>();
	FVector Dir = VRCamera->GetForwardVector() * scale.X + VRCamera->GetRightVector() * scale.Y;
	AddMovementInput(Dir);
}

void ALSCharacter::Turn(const struct FInputActionValue& val)
{
	FVector2D scale = val.Get<FVector2D>();
	AddControllerPitchInput(scale.Y);
	AddControllerYawInput(scale.X);
}

void ALSCharacter::RunStart()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void ALSCharacter::RunEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ALSCharacter::DuckStart()
{
	ALSCharacter::Crouch();
}

void ALSCharacter::DuckEnd()
{
	ALSCharacter::UnCrouch();
}

void ALSCharacter::Interact()
{
	TArray<FHitResult> HitInfos;
	bool bHit = drawInteractLine(HitInfos);
	if (bHit)
	{
		for (FHitResult HitInfo : HitInfos)
		{
			AItemBase* item = Cast<AItemBase>(HitInfo.GetActor());
			if (item)
			{
				if (!ItemArray[SelectedIndex])
				{
					ItemArray[SelectedIndex] = item;
					item->BoxComp->SetSimulatePhysics(false);
					item->BoxComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
					item->AttachToComponent(scene, FAttachmentTransformRules::SnapToTargetIncludingScale);
				}
				break;
			}
		}
			
	}
}

void ALSCharacter::Throw()
{
	if(!ItemArray[SelectedIndex]) return;
	ItemArray[SelectedIndex]->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	ItemArray[SelectedIndex]->BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ItemArray[SelectedIndex]->BoxComp->SetSimulatePhysics(true);
	ItemArray[SelectedIndex] = nullptr;
	MakeNoise(2, this, GetActorLocation());
}

void ALSCharacter::ChangeItem(const struct FInputActionValue& val)
{
	int32 preIndex = SelectedIndex;
	SelectedIndex += (int32)val.Get<float>();
	SelectedIndex = SelectedIndex < 0 ? 3 : SelectedIndex;
	SelectedIndex %= 4;
	UE_LOG(LogTemp, Warning, TEXT("%d"), SelectedIndex);
	SelectItem(SelectedIndex, preIndex);
}

void ALSCharacter::SelectItem(int32 index, int32 preIndex)
{
	if (ItemArray[preIndex])
	{
		//ItemArray[preIndex]->BoxComp->SetVisibility(false);
		ItemArray[preIndex]->SetActorHiddenInGame(true);
	}
	if(ItemArray[index])
	{
		//ItemArray[index]->BoxComp->SetVisibility(true);
		ItemArray[index]->SetActorHiddenInGame(false);
	}
}

bool ALSCharacter::drawInteractLine(TArray<FHitResult>& HitInfos)
{
	FVector StartPos = VRCamera->GetComponentLocation();
	FVector EndPos = StartPos + VRCamera->GetForwardVector() * InteractDist;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	bool bHit = GetWorld()->SweepMultiByChannel(HitInfos, StartPos, EndPos, FQuat::Identity, ECollisionChannel::ECC_Visibility, FCollisionShape::MakeSphere(50), params);

	return bHit;
}

