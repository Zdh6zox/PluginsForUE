// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Map2DSite.h"
#include "Map2DRegion.h"
/**
 * 
 */
class MAPGENERATOR_API FMap2DGenerationResult
{
public:
	TArray<FMap2DRegion> GeneratedRegions;
	TArray<FMap2DSite> GeneratedSites;
};
