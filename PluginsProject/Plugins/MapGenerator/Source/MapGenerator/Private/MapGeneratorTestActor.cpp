// Fill out your copyright notice in the Description page of Project Settings.


#include "MapGeneratorTestActor.h"
#include "Map2DGenerationResult.h"
#include "DrawDebugHelpers.h"
#include "Debug/MapGenerationDebugger.h"

// Sets default values
AMapGeneratorTestActor::AMapGeneratorTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_CacheResult = new FMap2DGenerationResult();
	m_Debugger = new FMapGenerationDebugger();
	m_Debugger->SetDebugOwner(this);
}

AMapGeneratorTestActor::~AMapGeneratorTestActor()
{
	delete m_CacheResult;
	delete m_Debugger;
}

// Called when the game starts or when spawned
void AMapGeneratorTestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMapGeneratorTestActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AMapGeneratorTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapGeneratorTestActor::DebugGenerate2DMap(int& regionNum)
{
	FMap2DGenerationResult result;
	FMapGeneratorFacade::Generate2DMapPOIAndLinks(Map2DGenerationSetting, *m_CacheResult, m_Debugger);

	regionNum = m_CacheResult->GeneratedRegions.Num();
}

void AMapGeneratorTestActor::DisplayAllResult()
{
	for (int32 i = 0; i < m_CacheResult->GeneratedRegions.Num(); ++i)
	{
		m_CacheResult->GeneratedRegions[i].DebugDisplayRegion(GetWorld(), FVector2D(GetActorLocation()), SiteDisplayRadius, SiteDisplayColor, EdgeDisplayColor);
	}

	FlushDebugStrings(GetWorld());
}

void AMapGeneratorTestActor::Display2DMapGenerationResult(int regionIndex)
{
	if (regionIndex >= m_CacheResult->GeneratedRegions.Num())
	{
		return;
	}

	m_CacheResult->GeneratedRegions[regionIndex].DebugDisplayRegion(GetWorld(), FVector2D(GetActorLocation()), SiteDisplayRadius, SiteDisplayColor, EdgeDisplayColor);
}

void AMapGeneratorTestActor::Display2DMapBorder()
{
	FVector vec0 = GetActorLocation();
	FVector vec1 = GetActorLocation() + Map2DGenerationSetting.Map2DSizeLength * FVector::ForwardVector;
	FVector vec2 = vec1 + Map2DGenerationSetting.Map2DSizeWidth * FVector::RightVector;
	FVector vec3 = vec0 + Map2DGenerationSetting.Map2DSizeWidth * FVector::RightVector;
	DrawDebugLine(GetWorld(), vec0, vec1, EdgeDisplayColor, true);
	DrawDebugLine(GetWorld(), vec1, vec2, EdgeDisplayColor, true);
	DrawDebugLine(GetWorld(), vec2, vec3, EdgeDisplayColor, true);
	DrawDebugLine(GetWorld(), vec3, vec0, EdgeDisplayColor, true);
}

void AMapGeneratorTestActor::ClearDebugDisplay(bool clearStrings, bool clearLines)
{
	if (clearStrings)
	{
		FlushDebugStrings(GetWorld());
	}

	if (clearLines)
	{
		FlushPersistentDebugLines(GetWorld());
	}
}

int AMapGeneratorTestActor::GetRegionSize() const
{
	if (m_CacheResult == nullptr)
		return 0;

	return m_CacheResult->GeneratedRegions.Num();
}

int AMapGeneratorTestActor::GetDebugPeriodCount() const
{
	return m_Debugger->GetPeriodSize();
}

int AMapGeneratorTestActor::GetDebugPeriodElementCount(int periodInx) const
{
	return m_Debugger->GetPeriodElementSize(periodInx);
}

void AMapGeneratorTestActor::ClearDebugLog()
{
	m_Debugger->ClearDebugLogs();
}

void AMapGeneratorTestActor::ShowDebug(int periodInx, int elementInx) const
{
	m_Debugger->DebugDisplayElement(GetWorld(), periodInx, elementInx);
}