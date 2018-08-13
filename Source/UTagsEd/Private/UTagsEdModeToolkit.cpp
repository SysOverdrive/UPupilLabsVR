// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "UTagsEdModeToolkit.h"
#include "UTagsEdMode.h"
#include "Engine/Selection.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine.h"
#include <string>
#include "Kismet/GameplayStatics.h"
#include "EditorModeManager.h"
#include <DeclarativeSyntaxSupport.h>

#include "Editor/PropertyEditor/Private/PropertyEditorHelpers.h"

#define LOCTEXT_NAMESPACE "FUTagsEdModeToolkit"

FUTagsEdModeToolkit::FUTagsEdModeToolkit()
{
}

void FUTagsEdModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
	struct Locals
	{
		//ToDo Change to are actors selectable
		static bool IsWidgetEnabled()
		{
			return GEditor->GetSelectedActors()->Num() != 0;
		}

		static FReply OnButtonClick(FVector InOffset)
		{
			USelection* SelectedActors = GEditor->GetSelectedActors();

			// Let editor know that we're about to do something that we want to undo/redo
			GEditor->BeginTransaction(LOCTEXT("MoveActorsTransactionName", "MoveActors"));

			// For each selected actor
			for (FSelectionIterator Iter(*SelectedActors); Iter; ++Iter)
			{
				if (AActor* LevelActor = Cast<AActor>(*Iter))
				{
					// Register actor in opened transaction (undo/redo)
					LevelActor->Modify();
					// Move actor to given location
					LevelActor->TeleportTo(LevelActor->GetActorLocation() + InOffset, FRotator(0, 0, 0));
				}
			}

			// We're done moving actors so close transaction
			GEditor->EndTransaction();

			return FReply::Handled();
		}

		static TSharedRef<SWidget> MakeButton(FText InLabel, const FVector InOffset)
		{
			return SNew(SButton)
				.Text(InLabel)
				.OnClicked_Static(&Locals::OnButtonClick, InOffset);
		}


	};

	const float Factor = 256.0f;

	SAssignNew(ToolkitWidget, SBorder)
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		.IsEnabled_Static(&Locals::IsWidgetEnabled)
		
		[
			SNew(SVerticalBox)

	+ SVerticalBox::Slot()
		.AutoHeight()
		[
			Locals::MakeButton(LOCTEXT("DownButtonLabel", "Down"), FVector(0, 0, -Factor))
		]
	
	+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			
		SNew(SSplitter).ResizeMode(ESplitterResizeMode::Fill)
		+ SSplitter::Slot()
		[
			SNew(STextBlock)
			.AutoWrapText(true)
			.Text(LOCTEXT("FirstColumn", "Prima COLOANA !!!!!!!"))
		]
		+ SSplitter::Slot()
		[
			SNew(STextBlock)
			.AutoWrapText(true)
			.Text(LOCTEXT("SecondColumn", "A DOUA COLOANA !!!!!!!"))
		]

		]
	+ SVerticalBox::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.AutoHeight()
		[
			SAssignNew(SUtagsListWidgetRef, SUtagsListWidget)
		]

		];
		
	FModeToolkit::Init(InitToolkitHost);
}

FName FUTagsEdModeToolkit::GetToolkitFName() const
{
	return FName("UTagsEdMode");
}

FText FUTagsEdModeToolkit::GetBaseToolkitName() const
{
	return NSLOCTEXT("UTagsEdModeToolkit", "DisplayName", "UTagsEdMode Tool");
}

class FEdMode* FUTagsEdModeToolkit::GetEditorMode() const
{
	return GLevelEditorModeTools().GetActiveMode(FUTagsEdMode::EM_UTagsEdModeId);
}

#undef LOCTEXT_NAMESPACE
