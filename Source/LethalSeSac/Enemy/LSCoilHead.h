// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LSCoilHead.generated.h"

UCLASS()
class LETHALSESAC_API ALSCoilHead : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALSCoilHead();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class ULSCoilHeadFSM* FSM;


};
