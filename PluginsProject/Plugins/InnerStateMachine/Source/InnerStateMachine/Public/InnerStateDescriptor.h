// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class INNERSTATEMACHINE_API InnerStateDescriptor
{
public:
	InnerStateDescriptor();
	~InnerStateDescriptor();

public:
	static constexpr int INVALID_STATE_ID = -1;
	static constexpr int INVALID_STATE_DEPTH = -1;

private:
    int m_Id{ INVALID_STATE_ID }; // also the index in StateMachine Descriptor
    int m_Depth{ INVALID_STATE_DEPTH }; // depth from root state
    int m_ForkId{ INVALID_STATE_ID }; // also the index of the fork
    int m_RelativeDepth{ INVALID_STATE_DEPTH }; // depth from state fork
    bool m_IsFork{ false };

    InnerStateDescriptor* m_Parent{ nullptr };
    InnerStateDescriptor* m_Children{ nullptr };
    InnerStateDescriptor* m_Sibling{ nullptr };
    InnerStateDescriptor* m_ForkChildern{ nullptr };
    InnerStateDescriptor* m_ForkSibling{ nullptr };
};
