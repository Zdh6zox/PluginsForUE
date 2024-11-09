// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapGenerator2DSetting.h"
#include "Map2DGenerationResult.h"
/**
 * 
 */
class IMapGeneratorRegionDivider;
class IMapGenerationSampler;
class FMapGenerationDebugger;
class MAPGENERATOR_API FMapGenerator2D
{
public:
    FMapGenerator2D(const FMapGenerator2DSetting& generationSetting);
    ~FMapGenerator2D();

    void Construct2DMap(FMap2DGenerationResult& generationResult);
    void AttachDebugger(FMapGenerationDebugger* debugger);

private:
    FMapGenerator2D(){}

    FMapGenerator2DSetting m_GenerationSetting;
    IMapGeneratorRegionDivider* m_RegionDivider{ nullptr };
    IMapGenerationSampler* m_MainNodeSampler{ nullptr };
    IMapGenerationSampler* m_RegionNodeSampler{ nullptr };
    FMapGenerationDebugger* m_Debugger{ nullptr };
};
