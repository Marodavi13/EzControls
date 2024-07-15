// Copyright The Multiplayer Group, All Rights Reserved. 2024

#include "EzControlEntryWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/Texture2D.h"
#include "EzControls/EzControls.h"

UEzControlEntryWidget::UEzControlEntryWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ControlImages.Add(ActionFirstImage);
	ControlImages.Add(ActionSecondImage);
	ControlImages.Add(ActionThirdImage);
	ControlImages.Add(ActionFourthImage);
}

void UEzControlEntryWidget::InitAction(const FText& NewActionText, UTexture2D* NewActionTexture)
{
	ControlImages.Empty(4);
	ControlImages.Add(ActionFirstImage);
	ControlImages.Add(ActionSecondImage);
	ControlImages.Add(ActionThirdImage);
	ControlImages.Add(ActionFourthImage);
	UE_CLOG(!IsValid(NewActionTexture), LogEzControls, Warning,
		TEXT("Control Entry widget with action name [%s] has a null texture!"), *NewActionText.ToString());
	
	if (ensure(ActionText))
	{
		ActionText->SetText(NewActionText);
	}	

	if (ensure(ActionFirstImage))
	{
		ActionFirstImage->SetBrushFromTexture(NewActionTexture);
	}

	LastUpdatedImage = ActionFirstImage;
	
	// Hidden on purpose to occupy the space
	ActionSecondImage->SetVisibility(ESlateVisibility::Hidden);
	ActionThirdImage->SetVisibility(ESlateVisibility::Hidden);
	ActionFourthImage->SetVisibility(ESlateVisibility::Hidden);
}

void UEzControlEntryWidget::AddNewTexture(UTexture2D* NewActionTexture)
{
	UE_CLOG(!IsValid(NewActionTexture), LogEzControls, Warning,
		TEXT("Control Entry widget with action name [%s] has a null texture!"), *ActionText->GetText().ToString());

	int32 LastUpdatedIndex = ControlImages.Find(LastUpdatedImage);

	if (!ControlImages.IsValidIndex(++LastUpdatedIndex))
	{
		ensure(false);
		return;
	}
	
	LastUpdatedImage = ControlImages[LastUpdatedIndex];
	LastUpdatedImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	LastUpdatedImage->SetBrushFromTexture(NewActionTexture);
}

FText UEzControlEntryWidget::GetActionText() const
{
	return ActionText->GetText();
}
