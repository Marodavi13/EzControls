#pragma once

#include "CoreMinimal.h"
#include "EnhancedActionKeyMapping.h"
#include "EzControlEntryWidget.h"
#include "Blueprint/UserWidget.h"
#include "CommonUI/Public/CommonButtonBase.h"
#include "EzControlWidget.generated.h"

class UEzInputDataAsset;
class UVerticalBox;
/**
 * 
 */
UCLASS()
class EZCONTROLS_API UEzControlWidget: public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeOnInitialized() override;
	
protected:

	// Container for the input entries
	UPROPERTY(BlueprintReadOnly, Category="EzControls", meta=(BindWidget))
	UVerticalBox* ControlsVerticalBox = nullptr;

	// Data asset that contains the textures  
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EzControls")
	UEzInputDataAsset* InputDataAsset = nullptr;

	// Entry subclass
	UPROPERTY(EditAnywhere, Category="EzControls")
	TSubclassOf<UEzControlEntryWidget> EntryWidgetSubclass;

	UPROPERTY(BlueprintReadOnly, Category="EzControls")
	ECommonInputType CurrentInputType;

	FTimerHandle UpdateControlsHandle;

	// returns true if the key is from the same source the player is using
	bool IsValidKey(const FKey& Key) const;

	UEzControlEntryWidget* GetEntryByActionName(const FText& Text) const;
	UTexture2D* GetInputTextureByKey(const FKey& Key, const FText& Text) const;

	void UpdateControls();
	void RetryUpdateControls();

	void OnInputMethodChanged(ECommonInputType NewInput);
};
