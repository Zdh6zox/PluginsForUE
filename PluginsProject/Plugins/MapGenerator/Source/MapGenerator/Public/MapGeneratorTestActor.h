// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapGeneratorIncludes.h"
#include "MapGeneratorTestActor.generated.h"


class FMap2DGenerationResult;
class FMapGenerationDebugger;
UCLASS()
class MAPGENERATOR_API AMapGeneratorTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapGeneratorTestActor();
	~AMapGeneratorTestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable)
		void DebugGenerate2DMap(int& regionNum);

public:
	UPROPERTY(EditAnywhere)
		FMapGenerator2DSetting Map2DGenerationSetting;

	UPROPERTY(EditAnywhere)
		float SiteDisplayRadius;

    UPROPERTY(EditAnywhere)
        FColor SiteDisplayColor;

    UPROPERTY(EditAnywhere)
		FColor EdgeDisplayColor;

	UFUNCTION(BlueprintCallable)
		void Display2DMapGenerationResult(int regionIndex);

    UFUNCTION(BlueprintCallable)
        void DisplayAllResult();

	UFUNCTION(BlueprintCallable)
		void Display2DMapBorder();

	UFUNCTION(BlueprintCallable)
		void ClearDebugDisplay(bool clearStrings, bool clearLines);

	UFUNCTION(BlueprintCallable)
		int GetRegionSize() const;

    UFUNCTION(BlueprintCallable)
        int GetDebugPeriodCount() const;

    UFUNCTION(BlueprintCallable)
        int GetDebugPeriodElementCount(int periodInx) const;

    UFUNCTION(BlueprintCallable)
        void ClearDebugLog();

	UFUNCTION(BlueprintCallable)
		void ShowDebug(int periodInx, int elementInx) const;

private:
	FMap2DGenerationResult* m_CacheResult = nullptr;
	FMapGenerationDebugger* m_Debugger{ nullptr };
};
