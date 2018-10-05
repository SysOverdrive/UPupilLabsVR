// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */

class UImage;
class UTexture2D;

UCLASS(Abstract)
class PUPILCALIBRATION_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* MessageBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UImage* LeftEyeCamera;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UImage* RightEyeCamera;

	UPROPERTY()
		UTexture2D* LeftEyeTexture;
	UPROPERTY()
		UTexture2D* RightEyeTexture;

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
		void SetMessageEnabled(bool bEnabled = true);

	UFUNCTION()
		void SetMessage(const FText& Message);

	void UpdateEyeImage(uint8 EyeIndex, const uint8*& Data);

	void SetEyeCameraEnabled(uint8 EyeIndex, bool bEnabled = true);
	
};
