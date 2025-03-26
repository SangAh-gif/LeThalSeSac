// Fill out your copyright notice in the Description page of Project Settings.


#include "LSDogFSM.h"
#include "LSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "LSEyelessDog.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "AITypes.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LSEyelessDogAnim.h"
#include "LSEyelessDogAIController.h"
#include "Components\CapsuleComponent.h"

// Sets default values for this component's properties
ULSDogFSM::ULSDogFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULSDogFSM::BeginPlay()
{
	Super::BeginPlay();

	// ...

	// ���忡�� Player ã�ƿ��� 
	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ALSCharacter::StaticClass());

	target = Cast<ALSCharacter>(actor);

	// ���� ��ü
	me = Cast<ALSEyelessDog>(GetOwner());

	Anim = Cast<ULSEyelessDogAnim>(me->GetMesh()->GetAnimInstance());


	//ai = Cast<ALSEyelessDogAIController>(me->GetController());
	ai = Cast<ALSEyelessDogAIController>(me->GetController());

}


// Called every frame
void ULSDogFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	
	// ����â�� ���� �޼��� ����ϱ� 
	FString logMsg = UEnum::GetValueAsString(mState);
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, logMsg);

	switch (mState)
	{
	case EEnemyState::Idle:
	{
		IdleState();
	}
		break;
	case EEnemyState::Move:
	{
		MoveState();
	}
		break;
	case EEnemyState::MoveToSound:
	{
		MoveState();
	}
	break;
	case EEnemyState::Attack:
	{
		AttackState();
	}
		break;
	case EEnemyState::Damage:
	{
		DamageState();
	}
		break;
	case EEnemyState::Die:
	{
		DieState();
	}
		break;
	case EEnemyState::Patrol:
	{
		PatrolState();
	}
	break;
	case EEnemyState::ReturnToPatrol:
	{
		ReturnToPatrolState();
	}
	break;
	case EEnemyState::DetectSound:
	{
		DetectSoundState();
	}
	break;
	default:
		break;
	}
}

void ULSDogFSM::IdleState()
{
	currentTime += GetWorld()->DeltaTimeSeconds;

	if (currentTime >= IdleDelayTime)
	{
		mState          = EEnemyState::Patrol;
		currentTime     = 0.0f;
		Anim->AnimState = mState;
		GetRandomPositionInNavMesh(me->GetActorLocation(), 500.0f, randomPos);
	}
}

void ULSDogFSM::SetNoiseLocation(FVector NewLocation)
{
	NoiseLocation = NewLocation;
	mState = EEnemyState::DetectSound;
}

void ULSDogFSM::DetectSoundState()
{
	if (NoiseLocation.IsZero()) return;

	mState = EEnemyState::MoveToSound;
}

void ULSDogFSM::MoveState()
{

	// �ٷ� ������ ���� �� 
	
	
	// Ÿ�� �������� �ʿ��ϴ�.
	//FVector desttination = target->GetActorLocation();

	//// ����
	//FVector dir = desttination - me->GetActorLocation();

	//auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	//// ������ ��ã�� ��� ������ �˻�
	//FPathFindingQuery query;
	//FAIMoveRequest req;

	//// ���������� ������ �� �ִ� ����
	//req.SetAcceptanceRadius(3);
	//req.SetGoalLocation(desttination);

	//// �� ã�⸦ ���� ���� ����
	//ai->BuildPathfindingQuery(req, query);
	//
	//// ��ã�� ��� ��������
	//FPathFindingResult r = ns->FindPathSync(query);

	//// ���������� �� ã�� ���� ���� Ȯ��
	//if (r.Result == ENavigationQueryResult::Success)
	//{
	//	ai->MoveToLocation(desttination);
	//}
	//else
	//{
	//	auto result = ai->MoveToLocation(randomPos);

	//	if (result == EPathFollowingRequestResult::AlreadyAtGoal)
	//	{
	//		GetRandomPositionInNavMesh(me->GetActorLocation(), 500.0f, randomPos);
	//	}
	//}

	//if (dir.Size() < attackRange)
	//{
	//	// �� ã�� ��� ����
	//	ai->StopMovement();

	//	mState = EEnemyState::Attack;

	//	Anim->AnimState = mState;

	//	Anim->bAttackPlay = true;

	//	currentTime = attackDelayTime;
	//}

	

	if (!target || !me) return;
	FVector destination = target->GetActorLocation();
	FVector         dir = destination - me->GetActorLocation();


	FRotator newRotation = dir.Rotation();
	newRotation = UKismetMathLibrary::MakeRotFromXZ(dir, me->GetActorUpVector());
	newRotation = FMath::RInterpTo(me->GetActorRotation(), newRotation, GetWorld()->GetDeltaSeconds(), 1.5f);
	me->SetActorRotation(newRotation);

	auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (!ns) return;

	FPathFindingQuery query;
	FAIMoveRequest req;

	req.SetAcceptanceRadius(3);
	req.SetGoalLocation(destination);

	ai->BuildPathfindingQuery(req, query);
	FPathFindingResult r = ns->FindPathSync(query);

	if (r.Result == ENavigationQueryResult::Success)
	{
		me->GetCharacterMovement()->MaxWalkSpeed = 100.0f;
		ai->MoveToLocation(destination);

		if (dir.Size() < attackRange)
		{
			ai->StopMovement();
			mState = EEnemyState::Attack;
			Anim->AnimState = mState;
			Anim->bAttackPlay = true;
			currentTime = attackDelayTime;
		}
	}
}

void ULSDogFSM::MoveToSoundState()
{
	if (!ai || !me) return;

	ai->MoveToLocation(NoiseLocation);

	// ���� ��ǥ ������ �����ߴٸ� ���� ���·� ��ȯ
	float Distance = FVector::Dist(me->GetActorLocation(), NoiseLocation);
	if (Distance < 100.0f) // 100 ���� �̳��� �����ϸ� ���� ����
	{
		mState = EEnemyState::Attack;
	}
}

void ULSDogFSM::AttackState()
{
	/*me->GetCharacterMovement()->MaxWalkSpeed = 0.0f;

	FVector destination = target->GetActorLocation();
	FVector dir = destination - me->GetActorLocation();

	FRotator newRotation = dir.Rotation();
	newRotation = UKismetMathLibrary::MakeRotFromXZ(dir, me->GetActorUpVector());
	newRotation = FMath::RInterpTo(me->GetActorRotation(), newRotation, GetWorld()->GetDeltaSeconds(), 0.2f);
	me->SetActorRotation(newRotation);*/

	//currentTime += GetWorld()->GetDeltaSeconds();

	//if (currentTime >= attackDelayTime)
	//{
	//	currentTime = 0.0f;
	//	Anim->bAttackPlay = true;
	//	//target->Die();
	//}

	//else
	//{
	//	float distance = FVector::Distance(target->GetActorLocation(), me->GetActorLocation());

	//	if (distance > attackRange)
	//	{
	//		mState = EEnemyState::Move;

	//		Anim->AnimState = mState;

	//		GetRandomPositionInNavMesh(me->GetActorLocation(), 500.0f, randomPos);
	//	}
	//}

	if (!ai || !me) return;

	// ���� �ִϸ��̼� ����
	Anim->bAttackPlay = true;

	GetWorld()->GetTimerManager().SetTimer(
		AttackTimerHandle,
		[this]()
		{
			mState = EEnemyState::ReturnToPatrol;
		},
		2.0f, false); // ���� �� 3�� �� ������ ����
}


void ULSDogFSM::DamageState()
{
	currentTime += GetWorld()->DeltaTimeSeconds;

	if (currentTime >= damageDelayTime)
	{
		mState = EEnemyState::Idle;
		currentTime = 0.0f;

		Anim->AnimState = mState;
	}
}

void ULSDogFSM::DieState()
{
	ai->isDead = true;

	me->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision); 
	
}

void ULSDogFSM::PatrolState()
{
	me->GetCharacterMovement()->MaxWalkSpeed = 100.0f;
	auto result = ai->MoveToLocation(randomPos);
	if (result == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		GetRandomPositionInNavMesh(me->GetActorLocation(), 500.0f, randomPos);
	}

	//if (!me || !ai) return;

	//if (!ai->IsMoving()) // �̵��� �����ٸ� ���ο� ���� �������� �̵�
	//{
	//	FVector RandomPoint = GetRandomPatrolPoint();
	//	ai->MoveToLocation(RandomPoint);
	//}
}

bool ULSDogFSM::GetRandomPositionInNavMesh(FVector centerLocation, float radius, FVector& dest)
{
	auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	
	FNavLocation loc;
	bool result = ns->GetRandomReachablePointInRadius(centerLocation, radius, loc);
	
	dest = loc.Location;

	return result; 
}

void ULSDogFSM::OnDamageProcess(int damage)
{
	hp -= damage;
	if (hp > 0)
	{
		mState = EEnemyState::Damage;
		int32 randValue = FMath::RandRange(0, 1);
		FString sectionName = FString::Printf(TEXT("Damage%d"), randValue);
		me->PlayAnimMontage(Anim->EnemyMongtage, 1.0f, FName(*sectionName));
	}
	else
	{
		mState = EEnemyState::Die;
		me->PlayAnimMontage(Anim->EnemyMongtage, 1.0f, TEXT("Die"));
	}
}

void ULSDogFSM::ReturnToPatrolState()
{
	mState = EEnemyState::Patrol;
}



