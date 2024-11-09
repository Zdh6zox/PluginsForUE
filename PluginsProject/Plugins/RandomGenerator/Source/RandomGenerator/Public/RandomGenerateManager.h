// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Math/RandomStream.h"

enum class ERandomMethodType
{
    Normal,
    Gaussian,
    Filtered,
    Perlin
};

/**
 * 
 */
class RANDOMGENERATOR_API FRandomGenerateManager
{
public:
    static FRandomGenerateManager* GetInstance();
    void Initialize();
    void SetSeed(int32 newSeed);
    int32 GetCurrentSeed() const;

    //[min,max]
    int32 RandRange_Int(int32 min, int32 max, ERandomMethodType method = ERandomMethodType::Normal);

    //[min,max)
    float RandRange_Float(float min, float max, ERandomMethodType method = ERandomMethodType::Normal);
    bool Rand_Bool(ERandomMethodType method = ERandomMethodType::Normal);
    FVector Rand_UnitVec(ERandomMethodType method = ERandomMethodType::Normal);

private:
    static FRandomGenerateManager* m_Instace;
    FRandomStream m_RandomStream;
};
