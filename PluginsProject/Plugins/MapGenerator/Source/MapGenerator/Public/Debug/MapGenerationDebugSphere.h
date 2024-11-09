// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapGenerationDebugElement.h"

/**
 * 
 */
class MAPGENERATOR_API FMapGenerationDebugSphere : public IMapGenerationDebugElement
{
public:
    FMapGenerationDebugSphere(FVector sphereLoc, float sphereSize, FColor sphereColor)
        : m_SphereLocation(sphereLoc), m_SphereSize(sphereSize), m_SphereColor(sphereColor)
    {

    }

    void DebugDisplay(UWorld* world) const override;

private:
    FVector m_SphereLocation;
    float m_SphereSize;
    FColor m_SphereColor;
};
