// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SUtagsListWidget.h"
#include "Toolkits/BaseToolkit.h"

class FUTagsEdModeToolkit : public FModeToolkit
{
public:

	FUTagsEdModeToolkit();
	
	/** FModeToolkit interface */
	virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost) override;

	/** IToolkit interface */
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual class FEdMode* GetEditorMode() const override;
	virtual TSharedPtr<class SWidget> GetInlineContent() const override { return ToolkitWidget; }

	// Reference to the SUTagsListWidget class Slate UI.
	TSharedPtr<class SUtagsListWidget> SUtagsListWidgetRef;
private:
	
	TSharedPtr<SWidget> ToolkitWidget;

};
