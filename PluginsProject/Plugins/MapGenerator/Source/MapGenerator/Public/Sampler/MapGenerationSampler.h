// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Map2DSampleSettings.h"
#include "Map2DRegion.h"
#include "Map2DSite.h"
#include "Debug/MapGenerationDebugger.h"
/**
 * 
 */
class MAPGENERATOR_API IMapGenerationSampler
{
public:
    virtual ~IMapGenerationSampler() {}
    virtual void SampleIn2DMap(const FMap2DSampleSettings& sampleSettings, TArray<FMap2DSite>& postionSamples) = 0;
    virtual void SampleInRegion(const FMap2DSampleSettings& sampleSettings, FMap2DRegion& region, TArray<FMap2DSite>& postionSamples) = 0;
    void AttachDebugger(FMapGenerationDebugger* debugger) { m_Debugger = debugger; }

protected:
    FMapGenerationDebugger* m_Debugger;
};
