// Fill out your copyright notice in the Description page of Project Settings.


#include "junk.h"

Ajunk::Ajunk()
{
	minVal = 10;
	maxVal = 100;
	curVal = FMath::RandRange(minVal, maxVal);
}

void Ajunk::BeginPlay()
{
	Super::BeginPlay();
	
}
