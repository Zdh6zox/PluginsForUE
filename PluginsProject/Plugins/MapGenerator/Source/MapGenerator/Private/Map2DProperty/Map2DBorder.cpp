// Fill out your copyright notice in the Description page of Project Settings.


#include "Map2DBorder.h"

bool FMap2DBorder::IsInsideMap(FVector2D relativePos, bool includingBorder) const
{
    if (relativePos.X > m_Length
        || relativePos.X < 0.0f
        || relativePos.Y > m_Width
        || relativePos.Y < 0.0f)
        return false;

    if (relativePos.X == m_Length
        || relativePos.X == 0.0f
        || relativePos.Y == m_Width
        || relativePos.Y == 0.0f)
        return includingBorder;

    return true;
}
