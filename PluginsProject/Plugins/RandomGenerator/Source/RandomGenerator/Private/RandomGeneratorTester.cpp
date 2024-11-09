// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomGeneratorTester.h"
#include "RandomGenerateManager.h"

// Sets default values
ARandomGeneratorTester::ARandomGeneratorTester()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARandomGeneratorTester::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARandomGeneratorTester::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARandomGeneratorTester::TestSetSeed(int newSeed)
{
	FRandomGenerateManager::GetInstance()->SetSeed(newSeed);
}

void ARandomGeneratorTester::TestGenerateInteger(int generatingCounts, int min, int max, TArray<int32>& generatedIntegers)
{
	for (int i = 0; i < generatingCounts; ++i)
	{
		generatedIntegers.Add(FRandomGenerateManager::GetInstance()->RandRange_Int(min, max));
	}
}

void ARandomGeneratorTester::TestGenerateFloat(int generatingCounts, float min, float max, TArray<float>& generatedFloats)
{
    for (int i = 0; i < generatingCounts; ++i)
    {
		generatedFloats.Add(FRandomGenerateManager::GetInstance()->RandRange_Float(min, max));
    }
}

void ARandomGeneratorTester::TestGenerateBool(int generatingCounts, TArray<bool>& generatedBools)
{
    for (int i = 0; i < generatingCounts; ++i)
    {
		generatedBools.Add(FRandomGenerateManager::GetInstance()->Rand_Bool());
    }
}

void ARandomGeneratorTester::TestGenerateVector(int generatingCounts, TArray<FVector>& generatedVectors)
{
    for (int i = 0; i < generatingCounts; ++i)
    {
        generatedVectors.Add(FRandomGenerateManager::GetInstance()->Rand_UnitVec());
    }
}

