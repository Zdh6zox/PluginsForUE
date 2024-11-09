// Fill out your copyright notice in the Description page of Project Settings.


#include "Map2DProperty/Map2DSite.h"
#include "Map2DEdge.h"
#include "DrawDebugHelpers.h"

void FMap2DSite::AddLinkFrom(FVector2D startLocation)
{
    FMap2DEdge fromEdge(startLocation, m_SiteLocation, true);

    m_LinkedEdge.Add(fromEdge);
}

void FMap2DSite::AddLinkTo(FVector2D endLocation)
{
    FMap2DEdge endEdge(m_SiteLocation, endLocation, true);

    m_LinkedEdge.Add(endEdge);
}

void FMap2DSite::DebugDisplaySite(UWorld* currentWorld, FVector2D originalLoc, float centerRadius, FColor centerColor) const
{
    FVector2D siteLocaion = originalLoc + m_SiteLocation;
    DrawDebugSphere(currentWorld, FVector(siteLocaion.X, siteLocaion.Y, 0.0f), centerRadius, 8, centerColor, true);
}