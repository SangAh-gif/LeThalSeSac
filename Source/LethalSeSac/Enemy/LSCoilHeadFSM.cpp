// Fill out your copyright notice in the Description page of Project Settings.


#include "LSCoilHeadFSM.h"
#include "LSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "LSCoilHeadAnim.h"
#include "LSCoilHead.h"

// Sets default values for this component's properties
ULSCoilHeadFSM::ULSCoilHeadFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULSCoilHeadFSM::BeginPlay()
{
	Super::BeginPlay();

	// ...

	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ALSCharacter::StaticClass());
	
	target = Cast<ALSCharacter>(actor);

	me = Cast<ALSCoilHead>(GetOwner());

	Anim = Cast <ULSCoilHeadAnim>(me->GetMesh()->GetAnimInstance());

	ai = Cast<ALSCoilHeadController>(me->GetController());
}


// Called every frame
void ULSCoilHeadFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULSCoilHeadFSM::IdleState()
{
}

void ULSCoilHeadFSM::MoveState()
{
}

void ULSCoilHeadFSM::PatrolState()
{
}

bool ULSCoilHeadFSM::GetRandomPositionInNavMesh(FVector centerLocation, float radius, FVector& dest)
{
	return false;
}

