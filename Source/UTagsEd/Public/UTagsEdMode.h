// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "EdMode.h"


class FUTagsEdMode : public FEdMode
{
public:
	const static FEditorModeID EM_UTagsEdModeId;
public:
	FUTagsEdMode();
	virtual ~FUTagsEdMode();

	// FEdMode interface
	virtual void Enter() override;
	virtual void Exit() override;
	bool UsesToolkits() const override;

public:
};
