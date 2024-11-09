// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Map2DBorder.h"
#include "Map2DEdge.h"
#include "Map2DSite.h"
/**
 * 
 */
class MAPGENERATOR_API FMap2DRegion
{
public:
    FMap2DRegion()
    {
        m_Origin = FVector2D::ZeroVector;
    }

    FMap2DRegion(FVector2D regionOrigin, const TArray<class FMap2DEdge>& edges);
    //FMap2DRegion& operator= (const FMap2DRegion& rhs);

    bool IsInsideRegion(FVector2D testingPos, bool includingBorder = false, float borderThickness = 0.0f) const;
    FVector2D GetRegionOrigin() const { return m_Origin; }
    TArray<FVector2D> GetRegionVertices() const { return m_Vertices; }
    TArray<FMap2DEdge> GetRegionEdges() const { return m_Edges; }
    static FMap2DRegion GetRegionFromBorder(const FMap2DBorder& border);
    void AddSite(FVector2D siteLocation);

    void DebugDisplayRegion(UWorld* currentWorld, FVector2D originalLoc, float siteRadius, FColor siteColor, FColor borderColor) const;

private:
    bool CheckVertexExist(const FVector2D& vec) const;
    FVector2D m_Origin;
    TArray<FMap2DEdge> m_Edges;
    TArray<FMap2DSite> m_Sites;
    TArray<FVector2D> m_Vertices;
};
