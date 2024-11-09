// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class FVoronoiDiagramGeneratedSite
{
public:
    FVoronoiDiagramGeneratedSite(int32 InIndex, FVector2D InCoordinate, FVector2D InCentroid, FColor InColor, bool InIsCorner, bool InIsEdge);

    int32 Index;
    FColor Color;
    FVector2D Coordinate;
    FVector2D Centroid;
    TArray<class FVoronoiDiagramGeneratedEdge> Edges;
    TArray<FVector2D> Vertices;
    TArray<int32> NeighborSites;

    bool bIsCorner;
    bool bIsEdge;
};
