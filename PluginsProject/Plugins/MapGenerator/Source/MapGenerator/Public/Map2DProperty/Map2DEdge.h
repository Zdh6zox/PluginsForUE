// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MAPGENERATOR_API FMap2DEdge
{
public:
	FMap2DEdge(FVector2D startPos, FVector2D endPos, bool hasDirection = false)
	{
		m_StartPos = startPos;
		m_EndPos = endPos;
		m_HasDirection = hasDirection;
	}

	//FMap2DEdge& operator= (const FMap2DEdge& rhs)
 //   {
	//	m_StartPos = rhs.GetStartPos();
	//	m_EndPos = rhs.GetEndPos();
	//	return *this;
 //   }

	FVector2D GetStartPos() const { return m_StartPos; }
	FVector2D GetEndPos() const { return m_EndPos; }

	void DebugDisplayEdge(UWorld* currentWorld, FVector2D originalLoc, FColor edgeColor) const;

private:
	FVector2D m_StartPos;
	FVector2D m_EndPos;
	bool m_HasDirection = false;
};
