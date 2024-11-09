// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapGeneratorRegionDivider.h"
#include "Map2DBorder.h"
#include "VoronoiDiagramGeneratedSite.h"
#include "VoronoiDiagramGeneratedEdge.h"

/**
 * 
 */
class FMap2DRegionDivider_VD : public IMapGeneratorRegionDivider
{
public:
    FMap2DRegionDivider_VD(){}
    ~FMap2DRegionDivider_VD() override {}

    void Divide2DMap(const FMap2DDivisionParameters& divisionParams, TArray<FMap2DRegion>& generatedRegions) const override;

public:
    FMap2DRegion ConvertGeneratedSite(const FVoronoiDiagramGeneratedSite& site) const;
};
