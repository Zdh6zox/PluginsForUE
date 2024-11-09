// Fill out your copyright notice in the Description page of Project Settings.


#include "Debug/MapGenerationDebugSphere.h"
#include "DrawDebugHelpers.h"

void FMapGenerationDebugSphere::DebugDisplay(UWorld* world) const
{
    DrawDebugSphere(world, m_SphereLocation, m_SphereSize, 8, m_SphereColor, true);
}