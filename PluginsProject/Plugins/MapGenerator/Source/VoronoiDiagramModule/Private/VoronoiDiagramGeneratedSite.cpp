// Fill out your copyright notice in the Description page of Project Settings.


#include "VoronoiDiagramGeneratedSite.h"
#include "VoronoiDiagramGeneratedEdge.h"

FVoronoiDiagramGeneratedSite::FVoronoiDiagramGeneratedSite(int32 InIndex, FVector2D InCoordinate, FVector2D InCentroid, FColor InColor, bool InIsCorner, bool InIsEdge)
    : Index(InIndex)
    , Color(InColor)
    , Coordinate(InCoordinate)
    , Centroid(InCentroid)
    , bIsCorner(InIsCorner)
    , bIsEdge(InIsEdge)
{}