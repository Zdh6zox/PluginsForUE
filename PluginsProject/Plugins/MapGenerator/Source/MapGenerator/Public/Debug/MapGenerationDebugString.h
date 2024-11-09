// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapGenerationDebugElement.h"

/**
 * 
 */
class MAPGENERATOR_API FMapGenerationDebugString : public IMapGenerationDebugElement
{
public:
    FMapGenerationDebugString(FString debugStr)
        : m_Str(debugStr)
    {

    }
    void DebugDisplay(UWorld* world) const override;

private:
    FString m_Str;
};
