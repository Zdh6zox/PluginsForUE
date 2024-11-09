// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapGenerator2DSetting.h"
#include "Map2DGenerationResult.h"
/**
 * 
 */
class FMapGenerationDebugger;
class MAPGENERATOR_API FMapGeneratorFacade
{
public:
    static void Generate2DMapPOIAndLinks(const FMapGenerator2DSetting& generationSetting, FMap2DGenerationResult& generationResult, FMapGenerationDebugger* debugger);
};
