// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class FVoronoiDiagramGeneratedEdge
{
public:
    FVoronoiDiagramGeneratedEdge(int32 InIndex, FVector2D InLeftEndPoint, FVector2D InRightEndPoint);

    int32 Index;
    FVector2D LeftEndPoint;
    FVector2D RightEndPoint;
};
