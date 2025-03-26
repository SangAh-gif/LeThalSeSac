// Fill out your copyright notice in the Description page of Project Settings.


#include "LSCoilHead.h"

// Sets default values
ALSCoilHead::ALSCoilHead()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FSM = CreateDefaultSubobject<ULSCoilHeadFSM>(TEXT("FSM"));

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/SSA/Asset/CoilHead/SKM_Untitled.SKM_Untitled'"));

	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -84.0f), FRotator(0.0f, -90.0f, 0.0f));
	}

}

// Called when the game starts or when spawned
void ALSCoilHead::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALSCoilHead::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALSCoilHead::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

