// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapGenerator2DSetting.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct MAPGENERATOR_API FMapGenerator2DSetting
{
     GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere)
        float Map2DSizeLength;

    UPROPERTY(EditAnywhere)
        float Map2DSizeWidth;

    UPROPERTY(EditAnywhere)
        int MainNodeCount;

    UPROPERTY(EditAnywhere)
        float MainNodeImpactRadius;

    UPROPERTY(EditAnywhere)
        int SubNodeCount;

    UPROPERTY(EditAnywhere)
        float SubNodeImpactRadius;

    UPROPERTY(EditAnywhere)
        int IterationCandidateNum;

    UPROPERTY(EditAnywhere)
        int VDRelaxationCycles;
};
