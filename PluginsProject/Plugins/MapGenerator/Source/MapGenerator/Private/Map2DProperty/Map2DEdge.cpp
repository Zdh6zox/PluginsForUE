// Fill out your copyright notice in the Description page of Project Settings.


#include "Map2DEdge.h"
#include "DrawDebugHelpers.h"

void FMap2DEdge::DebugDisplayEdge(UWorld* currentWorld, FVector2D originalLoc, FColor edgeColor) const
{
    FVector2D edgeStartLocation = originalLoc + m_StartPos;
    FVector2D edgeEndLocation = originalLoc + m_EndPos;
    DrawDebugLine(currentWorld, FVector(edgeStartLocation.X, edgeStartLocation.Y, 0.0f), FVector(edgeEndLocation.X, edgeEndLocation.Y, 0.0f), edgeColor, true);
}