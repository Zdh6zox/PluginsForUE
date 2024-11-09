// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Map2DRegion.h"
#include "Map2DSite.h"
#include "Debug/MapGenerationDebugger.h"

/**
 * 
 */
class MAPGENERATOR_API IMapGenerationConnector
{
public:
    virtual ~IMapGenerationConnector() {}
    virtual void ConnectIn2DMap(const TArray<FMap2DSite>& sites, const TArray<FMap2DRegion>& regions) = 0;
    void AttachDebugger(FMapGenerationDebugger* debugger) { m_Debugger = debugger; }

protected:
    FMapGenerationDebugger* m_Debugger;
};
