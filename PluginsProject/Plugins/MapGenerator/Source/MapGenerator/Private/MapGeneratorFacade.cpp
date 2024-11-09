// Fill out your copyright notice in the Description page of Project Settings.


#include "MapGeneratorFacade.h"
#include "MapGenerator2D.h"
#include "Debug/MapGenerationDebugger.h"

void FMapGeneratorFacade::Generate2DMapPOIAndLinks(const FMapGenerator2DSetting& generationSetting, FMap2DGenerationResult& generationResult, FMapGenerationDebugger* debugger)
{
    FMapGenerator2D* mapGenerator2D = new FMapGenerator2D(generationSetting);
    mapGenerator2D->AttachDebugger(debugger);
    mapGenerator2D->Construct2DMap(generationResult);
    delete mapGenerator2D;
}