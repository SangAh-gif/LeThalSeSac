// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LSCharacter.generated.h"

UCLASS()
class LETHALSESAC_API ALSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 카메라
	UPROPERTY(EditAnywhere)
	class UCameraComponent* VRCamera;


public: // 이동 및 회전
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* IMC_LS;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Move;
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Turn;
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Run;
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Duck;
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Jump;
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Interact;

	void Move(const struct FInputActionValue& val);
	void Turn(const struct FInputActionValue& val);
	void RunStart();
	void RunEnd();
	void DuckStart();
	void DuckEnd();
	void Interact();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RunSpeed = 1000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WalkSpeed = 600;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InteractDist = 5000;

	void drawInteractLine();
};
