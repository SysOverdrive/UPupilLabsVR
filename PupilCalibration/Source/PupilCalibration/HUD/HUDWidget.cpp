// Fill out your copyright notice in the Description page of Project Settings.

#include "HUDWidget.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"

#define TEX_WIDTH 200
#define TEX_HEIGHT 200
#define TEX_PIXEL_FORMAT EPixelFormat::PF_R8G8B8A8_UINT
#define TEX_PIXEL_SIZE_IN_BYTES 4

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetEyeCameraEnabled(0, false);
	SetEyeCameraEnabled(1, false);


	// https://answers.unrealengine.com/questions/463625/c-updating-texture-data.html
	LeftEyeTexture = UTexture2D::CreateTransient(TEX_WIDTH, TEX_HEIGHT, TEX_PIXEL_FORMAT);
	LeftEyeTexture->UpdateResource();

	LeftEyeTexture->AddressX = TextureAddress::TA_Clamp;
	LeftEyeTexture->AddressY = TextureAddress::TA_Clamp;
	LeftEyeTexture->Filter = TextureFilter::TF_Default;
	LeftEyeTexture->RefreshSamplerStates();

	RightEyeTexture = UTexture2D::CreateTransient(TEX_WIDTH, TEX_HEIGHT, TEX_PIXEL_FORMAT);
	RightEyeTexture->UpdateResource();

	RightEyeTexture->AddressX = TextureAddress::TA_Clamp;
	RightEyeTexture->AddressY = TextureAddress::TA_Clamp;
	RightEyeTexture->Filter = TextureFilter::TF_Default;
	RightEyeTexture->RefreshSamplerStates();
}

void UHUDWidget::SetMessageEnabled(bool bEnabled)
{
	MessageBox->SetVisibility(bEnabled ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden);
}

void UHUDWidget::SetMessage(const FText& Message)
{
	MessageBox->SetText(Message);
	SetMessageEnabled(Message.ToString().Len() > 0);
}

void UHUDWidget::UpdateEyeImage(uint8 EyeIndex, const uint8*& Data)
{
	UTexture2D* TextureToUpdate = nullptr;
	switch (EyeIndex)
	{
	case 0:
		TextureToUpdate = LeftEyeTexture;
		break;
	case 1:
		TextureToUpdate = RightEyeTexture;
		break;
	}

	const uint8* pData = Data;

	ENQUEUE_UNIQUE_RENDER_COMMAND_TWOPARAMETER(
		UpdateDynamicTextureCode,
		UTexture2D*, pTexture, TextureToUpdate,
		const uint8*, pData, pData,
		{
			FUpdateTextureRegion2D region;
			region.SrcX = 0;
			region.SrcY = 0;
			region.DestX = 0;
			region.DestY = 0;
			region.Width = TEX_WIDTH;
			region.Height = TEX_HEIGHT;

			FTexture2DResource* resource = (FTexture2DResource*)pTexture->Resource;
			RHIUpdateTexture2D(resource->GetTexture2DRHI(), 0, region, region.Width * TEX_PIXEL_SIZE_IN_BYTES, pData);
			delete[] pData;
		});
}

void UHUDWidget::SetEyeCameraEnabled(uint8 EyeIndex, bool bEnabled)
{
	switch (EyeIndex)
	{
	case 0:
		LeftEyeCamera->SetVisibility(bEnabled ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden);
		break;
	case 1:
		RightEyeCamera->SetVisibility(bEnabled ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden);
		break;
	}
}
