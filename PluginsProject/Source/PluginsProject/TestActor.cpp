// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"
#include <imgui.h>

// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const ImGui::FScopedContext ScopedContext;
	if (ScopedContext)
	{
		// Your ImGui code goes here!
		ImGui::ShowDemoWindow();
		// ImGui::Begin(TCHAR_TO_UTF8(*GetActorLabel()));
		// ImGui::Button("TestButton");
		// ImGui::End();
	}
}

