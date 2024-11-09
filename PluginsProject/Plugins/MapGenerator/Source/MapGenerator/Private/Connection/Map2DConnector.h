// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapGenerationConnector.h"

/**
 * 
 */
class FMap2DConnector : public IMapGenerationConnector
{
public:
    FMap2DConnector() {}
    ~FMap2DConnector() override {}
    void ConnectIn2DMap(const TArray<FMap2DSite>& sites, const TArray<FMap2DRegion>& regions) override;
};
