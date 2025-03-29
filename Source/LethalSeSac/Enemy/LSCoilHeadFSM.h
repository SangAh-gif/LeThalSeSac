// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LSCoilHeadFSM.generated.h"

UENUM(BlueprintType)
enum class ECoilHeadState : uint8
{
	Idle,
	Patrol,
	Attack,
	Move,
	LookAtMe
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LETHALSESAC_API ULSCoilHeadFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULSCoilHeadFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	ECoilHeadState mState = ECoilHeadState::Idle;

	UPROPERTY();
	class ULSCoilHeadAnim* Anim;

	UPROPERTY();
	class ALSCharacter* target;

	UPROPERTY();
	class ALSCoilHead* me;

	UPROPERTY();
	class ALSCoilHeadController* ai;

public:
	FVector randomPos; 

	UPROPERTY(EditDefaultsOnly, Category = FSM)
	float IdleDelayTime = 2.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = FSM)
	float currentTime = 0.0f;

	UPROPERTY(EditAnywhere, Category =FSM)
	float attackDelayTime = 2.0f;

	UPROPERTY(EditAnywhere, Category = FSM)
	float damageDelayTime = 2.0f;

	UPROPERTY(EditAnywhere, Category =FSM)
	float attackRange = 150.0f;

	UPROPERTY(EditAnywhere, Category =FSM)
	float  traceRange = 500.0f;



public:
	void IdleState();

	void MoveState();

	void PatrolState();

	void AttackState();

	void LookAtMeState();

	bool GetRandomPositionInNavMesh(FVector centerLocation, float radius, FVector& dest);
};
