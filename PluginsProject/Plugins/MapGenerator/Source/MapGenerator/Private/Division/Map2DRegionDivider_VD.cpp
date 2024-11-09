// Fill out your copyright notice in the Description page of Project Settings.


#include "Division/Map2DRegionDivider_VD.h"
#include "VoronoiDiagram.h"
#include "Map2DEdge.h"

void FMap2DRegionDivider_VD::Divide2DMap(const FMap2DDivisionParameters& divisionParams, TArray<FMap2DRegion>& generatedRegions) const
{
    FBox2D inBounds;
    inBounds.Min = FVector2D(0.0f, 0.0f);
    inBounds.Max = FVector2D(divisionParams.GetMap2DBorder().GetMapLength(), divisionParams.GetMap2DBorder().GetMapWidth());
    FVoronoiDiagram* voronoDiagram = new FVoronoiDiagram(inBounds);

    voronoDiagram->AddPoints(divisionParams.GetRegionOrigins());
    voronoDiagram->GenerateSites(divisionParams.GetRelaxationCycles());

    for (auto it(voronoDiagram->GeneratedSites.CreateConstIterator()); it; ++it)
    {
        generatedRegions.Add(ConvertGeneratedSite(it->Value));
    }
}

FMap2DRegion FMap2DRegionDivider_VD::ConvertGeneratedSite(const FVoronoiDiagramGeneratedSite& site) const
{
    TArray<FMap2DEdge> edges;
    for (const FVoronoiDiagramGeneratedEdge& generatedEdge : site.Edges)
    {
        edges.Add(FMap2DEdge(generatedEdge.LeftEndPoint, generatedEdge.RightEndPoint));
    }

    return FMap2DRegion(site.Coordinate, edges);
}