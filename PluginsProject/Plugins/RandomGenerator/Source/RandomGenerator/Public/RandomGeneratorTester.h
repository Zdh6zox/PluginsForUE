// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomGeneratorTester.generated.h"

UCLASS()
class RANDOMGENERATOR_API ARandomGeneratorTester : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARandomGeneratorTester();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void TestSetSeed(int newSeed);

	UFUNCTION(BlueprintCallable)
		void TestGenerateInteger(int generatingCounts, int min, int max, TArray<int32>& generatedIntegers);

	UFUNCTION(BlueprintCallable)
		void TestGenerateFloat(int generatingCounts, float min, float max, TArray<float>& generatedFloats);

    UFUNCTION(BlueprintCallable)
        void TestGenerateBool(int generatingCounts, TArray<bool>& generatedBools);

    UFUNCTION(BlueprintCallable)
        void TestGenerateVector(int generatingCounts, TArray<FVector>& generatedVectors);
};
