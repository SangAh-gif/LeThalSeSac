// Fill out your copyright notice in the Description page of Project Settings.


#include "LSEyelessDog.h"
#include "LSDogFSM.h"

// Sets default values
ALSEyelessDog::ALSEyelessDog()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FSM = CreateDefaultSubobject<ULSDogFSM>(TEXT("FSM"));

}

// Called when the game starts or when spawned
void ALSEyelessDog::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALSEyelessDog::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALSEyelessDog::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

