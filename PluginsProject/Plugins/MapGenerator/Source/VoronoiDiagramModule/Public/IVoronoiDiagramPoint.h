// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
//interface class for all coordinated in VoronoiDiagram
class IVoronoiDiagramPoint
{
public:
    virtual FVector2D GetCoordinate() const = 0;
};
