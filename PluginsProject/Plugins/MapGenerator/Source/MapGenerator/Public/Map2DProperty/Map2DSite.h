// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class FMap2DEdge;
class MAPGENERATOR_API FMap2DSite
{
public:
    FMap2DSite()
    {
        m_SiteLocation = FVector2D::ZeroVector;
    }

    FMap2DSite(FVector2D siteLocation)
    {
        m_SiteLocation = siteLocation;
    }

    void AddLinkFrom(FVector2D startLocation);
    void AddLinkTo(FVector2D endLocation);

    void DebugDisplaySite(UWorld* currentWorld, FVector2D originalLoc, float centerRadius, FColor centerColor) const;
    FVector2D GetSiteLocation() const { return m_SiteLocation; }

private:
    FVector2D m_SiteLocation;
    TArray<class FMap2DEdge> m_LinkedEdge;
};
