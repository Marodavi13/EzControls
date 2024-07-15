// Copyright The Multiplayer Group, All Rights Reserved. 2024

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EzControlEntryWidget.generated.h"

class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS(Abstract)
class EZCONTROLS_API UEzControlEntryWidget: public UUserWidget
{
	GENERATED_BODY()

public:

	UEzControlEntryWidget(const FObjectInitializer& ObjectInitializer);
	
	UFUNCTION(BlueprintCallable, Category="EzControls")
	void InitAction(const FText& NewActionText, UTexture2D* NewActionTexture);

	UFUNCTION(BlueprintCallable, Category="EzControls")
	void AddNewTexture(UTexture2D* NewActionTexture);

	FText GetActionText() const;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EzControls", meta=(BindWidget))
	UTextBlock* ActionText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EzControls", meta=(BindWidget))
	UImage* ActionFirstImage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EzControls", meta=(BindWidget))
	UImage* ActionSecondImage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EzControls", meta=(BindWidget))
	UImage* ActionThirdImage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EzControls", meta=(BindWidget))
	UImage* ActionFourthImage = nullptr;


	UPROPERTY(Transient)
	UImage* LastUpdatedImage = nullptr;

	TArray<UImage*> ControlImages;
};
