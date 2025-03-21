// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LSDogFSM.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8 
{
	Idle,
	Move,
	Attack,
	Damage,
	Die,
	Patrol
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LETHALSESAC_API ULSDogFSM : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULSDogFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditDefaultsOnly, Category = FSM)
	float IdleDelayTime = 2.0f;

	// ��ã�� ����� ������ġ 
	FVector randomPos;
	
	UPROPERTY(EditDefaultsOnly, Category = FSM)
	float currentTime = 0.0f;

	UPROPERTY(EditAnywhere, Category =FSM)
	float attackRange = 150.0f;

	UPROPERTY(EditAnywhere, Category =FSM)
	float attackDelayTime = 2.0f;

	int32 MaxHP = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FSM)
	int32 hp = MaxHP;

	UPROPERTY(EditAnywhere, Category = FSM)
	float damageDelayTime = 2.0f;



public:
	void IdleState();

	void MoveState();

	void Attack();

	void DamageState();

	void DieState();

	void PatrolState();

	// ���� ��ġ ��������
	bool GetRandomPositionInNavMesh(FVector centerLocation, float radius, FVector& dest);

	void OnDamageProcess(int damage);


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	EEnemyState mState = EEnemyState::Idle;

	UPROPERTY()
	class ULSEyelessDogAnim* Anim;
	
	UPROPERTY(VisibleAnywhere, Category = FSM)
	class ALSCharacter* target;

	UPROPERTY()
	class ALSEyelessDog* me;

	UPROPERTY()
	class AAIController* ai;

	

};
