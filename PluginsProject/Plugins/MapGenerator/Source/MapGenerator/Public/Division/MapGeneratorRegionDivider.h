// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapDivisionParameters.h"
#include "Map2DRegion.h"
#include "Debug/MapGenerationDebugger.h"
/**
 * 
 */
class MAPGENERATOR_API IMapGeneratorRegionDivider
{
public:
    virtual ~IMapGeneratorRegionDivider() {}
    virtual void Divide2DMap(const FMap2DDivisionParameters& divisionParams, TArray<FMap2DRegion>& generatedRegions) const = 0;
    void AttachDebugger(FMapGenerationDebugger* debugger) { m_Debugger = debugger; }

private:
    FMapGenerationDebugger* m_Debugger;
};
