// Fill out your copyright notice in the Description page of Project Settings.


#include "Map2DRegion.h"
#include "Map2DEdge.h"
#include "Map2DSite.h"
#include "DrawDebugHelpers.h"
#include "Math/ConvexHull2d.h"

FMap2DRegion::FMap2DRegion(FVector2D regionOrigin, const TArray<class FMap2DEdge>& edges)
{
    //ToDo: should close the region, merge with the border
    m_Origin = regionOrigin;
    m_Edges = edges;

    for (const FMap2DEdge& edge : m_Edges)
    {
        if (!CheckVertexExist(edge.GetStartPos()))
        {
            m_Vertices.Add(edge.GetStartPos());
        }

        if (!CheckVertexExist(edge.GetEndPos()))
        {
            m_Vertices.Add(edge.GetEndPos());
        }
    }

    //sort vertices use convex hull 2D
    TArray< int32 > convexHullIndices;
    ConvexHull2D::ComputeConvexHull(m_Vertices, convexHullIndices);

    TArray<FVector2D> sortedVertices;
    sortedVertices.Reserve(convexHullIndices.Num());
    for (int32 Index : convexHullIndices)
    {
        sortedVertices.Emplace(m_Vertices[Index]);
    }

    m_Vertices.Empty();
    m_Vertices.Append(sortedVertices);

    ////close region
    //if (m_Vertices.Num() >= 2 && m_Vertices.Num() >= m_Edges.Num())
    //{
    //    FMap2DEdge edge = FMap2DEdge(m_Vertices[0], m_Vertices[1], false);
    //    m_Edges.Add(edge);
    //}

    AddSite(regionOrigin);
}

//FMap2DRegion& FMap2DRegion::operator=(const FMap2DRegion& rhs)
//{
//    m_Origin = rhs.GetRegionOrigin();
//    m_Edges = rhs.GetRegionEdges();
//    m_Vertices = rhs.GetRegionVertices();
//    return *this;
//}

bool FMap2DRegion::IsInsideRegion(FVector2D testingPos, bool includingBorder, float borderThickness) const
{
    //TODO: Do we need to consider border thickness?
    //TODO: Something wrong with this check
    int32 i;
    int32 j = m_Vertices.Num() - 1;

    bool bOddNodes = false;

    for (i = 0; i < m_Vertices.Num(); ++i)
    {
        if (
            (m_Vertices[i].Y < testingPos.Y && m_Vertices[j].Y >= testingPos.Y || m_Vertices[j].Y < testingPos.Y && m_Vertices[i].Y >= testingPos.Y) &&
            (m_Vertices[i].X <= testingPos.X || m_Vertices[j].X <= testingPos.X)
            )
        {
            if (m_Vertices[i].X + (testingPos.Y - m_Vertices[i].Y) / (m_Vertices[j].Y - m_Vertices[i].Y) * (m_Vertices[j].X - m_Vertices[i].X) < testingPos.X)
            {
                bOddNodes = !bOddNodes;
            }
        }
        j = i;
    }

    return bOddNodes;
}

bool FMap2DRegion::CheckVertexExist(const FVector2D& vec) const
{
    constexpr float ErrorTolerance = 1.e-4f;
    for (const FVector2D& vector2D : m_Vertices)
    {
        if (vector2D.Equals(vec, ErrorTolerance))
        {
            return true;
        }
    }

    return false;
}

void FMap2DRegion::AddSite(FVector2D siteLocation)
{
    FMap2DSite site(siteLocation);
    m_Sites.Add(site);
}

FMap2DRegion FMap2DRegion::GetRegionFromBorder(const FMap2DBorder& border)
{
    FVector2D x_0 = FVector2D(0.0f, 0.0f);
    FVector2D x_1 = FVector2D(border.GetMapLength(), 0.0f);
    FVector2D x_y = FVector2D(border.GetMapLength(), border.GetMapWidth());
    FVector2D y_0 = FVector2D(0.0f, border.GetMapWidth());
    FMap2DEdge edge1 = FMap2DEdge(x_0, x_1, false);
    FMap2DEdge edge2 = FMap2DEdge(x_1, x_y, false);
    FMap2DEdge edge3 = FMap2DEdge(x_y, y_0, false);
    FMap2DEdge edge4 = FMap2DEdge(y_0, x_0, false);
    FVector2D mapCenter = FVector2D(border.GetMapLength() / 2.0f, border.GetMapWidth() / 2.0f);

    TArray<FMap2DEdge> regionEdges = TArray<FMap2DEdge>{ edge1, edge2, edge3, edge4 };
    FMap2DRegion region = FMap2DRegion(mapCenter, regionEdges);

    return region;
}

void FMap2DRegion::DebugDisplayRegion(UWorld* currentWorld, FVector2D originalLoc, float siteRadius, FColor siteColor, FColor borderColor) const
{
    //Draw all sites
    int index = 0;
    for (const FMap2DSite& site : m_Sites)
    {
        site.DebugDisplaySite(currentWorld, originalLoc, siteRadius, siteColor);
        FVector siteStrLoc = FVector(site.GetSiteLocation() + originalLoc, siteRadius);
        DrawDebugString(currentWorld, siteStrLoc, FString::Printf(TEXT("Site Index: %d"), index), NULL, FColor::MakeRandomColor());
        index++;
    }

    //Draw all edges
    for (const FMap2DEdge& edge : m_Edges)
    {
        edge.DebugDisplayEdge(currentWorld, originalLoc, borderColor);
    }

    //Draw all vertices
    int vertexIndex = 0;
    for (const FVector2D& vertex : m_Vertices)
    {
        FVector vertex3D = FVector(vertex + originalLoc, siteRadius);
        DrawDebugString(currentWorld, vertex3D, FString::Printf(TEXT("Vertex Index: %d"), vertexIndex), NULL, FColor::MakeRandomColor());
        vertexIndex++;
    }
}