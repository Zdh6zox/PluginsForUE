// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomGenerateManager.h"

FRandomGenerateManager* FRandomGenerateManager::m_Instace = NULL;

FRandomGenerateManager* FRandomGenerateManager::GetInstance()
{
    if (m_Instace == NULL)
    {
        m_Instace = new FRandomGenerateManager();
    }

    return m_Instace;
}

void FRandomGenerateManager::Initialize()
{
    m_RandomStream.GenerateNewSeed();
}

void FRandomGenerateManager::SetSeed(int32 newSeed)
{
    m_RandomStream.Initialize(newSeed);
}

int32 FRandomGenerateManager::GetCurrentSeed() const
{
    return m_RandomStream.GetCurrentSeed();
}

int32 FRandomGenerateManager::RandRange_Int(int32 min, int32 max, ERandomMethodType method /* = ERandomMethodType::Normal */)
{
    return m_RandomStream.RandRange(min, max);
}

float FRandomGenerateManager::RandRange_Float(float min, float max, ERandomMethodType method /* = ERandomMethodType::Normal */)
{
    return min + (max - min) * m_RandomStream.GetFraction();
}

bool FRandomGenerateManager::Rand_Bool(ERandomMethodType method /* = ERandomMethodType::Normal */)
{
    return (m_RandomStream.RandRange(0, 1) == 1) ? true : false;
}

FVector FRandomGenerateManager::Rand_UnitVec(ERandomMethodType method /* = ERandomMethodType::Normal */)
{
    return m_RandomStream.VRand();
}