// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "UTagsEdMode.h"
#include "UTagsEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"

const FEditorModeID FUTagsEdMode::EM_UTagsEdModeId = TEXT("EM_UTagsEdMode");

FUTagsEdMode::FUTagsEdMode()
{

}

FUTagsEdMode::~FUTagsEdMode()
{

}

void FUTagsEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FUTagsEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FUTagsEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

bool FUTagsEdMode::UsesToolkits() const
{
	return true;
}

//
//TArray<TWeakObjectPtr<AActor>> GetWeakActors()
//{
//	TArray<TWeakObjectPtr<AActor>> ActorArray;
//	for (const auto* ActorItem : Actors)
//	{
//		if (ActorItem->Actor.IsValid())
//		{
//			ActorArray.Add(ActorItem->Actor);
//		}
//	}
//	return ActorArray;
//}



