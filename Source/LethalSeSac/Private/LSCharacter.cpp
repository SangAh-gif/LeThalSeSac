// Fill out your copyright notice in the Description page of Project Settings.


#include "LSCharacter.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ALSCharacter::ALSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	VRCamera->SetupAttachment(RootComponent);

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
}

// Called when the game starts or when spawned
void ALSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
		InputSys->BindAction(IA_Interact, ETriggerEvent::Triggered, this, &ALSCharacter::Interact);
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

}

