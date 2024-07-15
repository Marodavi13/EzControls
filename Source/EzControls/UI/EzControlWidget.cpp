#include "EzControlWidget.h"

#include "CommonInputSubsystem.h"
#include "EnhancedActionKeyMapping.h"
#include "EnhancedInputSubsystems.h"
#include "EzControlEntryWidget.h"
#include "PlayerMappableKeySettings.h"
#include "TimerManager.h"
#include "Components/VerticalBox.h"
#include "EzControls/EzControls.h"
#include "EzControls/Input/EzInputDataAsset.h"

void UEzControlWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	APlayerController* PlayerController = GetOwningPlayer();
	if (!IsValid(PlayerController))
	{
		//TODO
		ensure(false);
		return;
	}

	UCommonInputSubsystem* CommonInput = UCommonInputSubsystem::Get(GetOwningLocalPlayer());
	if (!IsValid(CommonInput))
	{
		//TODO
		ensure(false);
		return;
	}

	CommonInput->OnInputMethodChangedNative.AddUObject(this, &UEzControlWidget::OnInputMethodChanged);
	OnInputMethodChanged(CommonInput->GetCurrentInputType());
}

bool UEzControlWidget::IsValidKey(const FKey& Key) const
{
	// Using UKismetInputLibrary::Key_IsKeyboardKey as reference
	if (Key.IsGamepadKey())
	{
		if (CurrentInputType == ECommonInputType::Gamepad)
		{
			return true;
		}
	}
	else if (Key.IsBindableInBlueprints() || Key.IsMouseButton())
	{
		if (CurrentInputType == ECommonInputType::MouseAndKeyboard)
		{
			return true;
		}
	}
	
	return false;
}

UEzControlEntryWidget* UEzControlWidget::GetEntryByActionName(const FText& Text) const
{
	UEzControlEntryWidget* FoundEntry = nullptr;
	TArray<UWidget*> CurrentEntries = ControlsVerticalBox->GetAllChildren();

	for(auto Entry : CurrentEntries)
	{
		UEzControlEntryWidget* ControlEntry = Cast<UEzControlEntryWidget>(Entry);
		if (!ControlEntry)
		{
			continue;
		}
		if (!ControlEntry->GetActionText().EqualTo(Text))
		{
			continue;
		}

		FoundEntry = ControlEntry;
		break;
	}
	
	return FoundEntry;
}

UTexture2D* UEzControlWidget::GetInputTextureByKey(const FKey& Key, const FText& ActionText) const
{
	UTexture2D** ActionTexturePtr = InputDataAsset->KeyTextures.Find(Key);
	
	if (!ActionTexturePtr)
	{
		UE_LOG(LogEzControls, Warning, TEXT("Trying to find input texture, but there are not valid textures set."
											"Action: %s | Key: %s"),
											*ActionText.ToString(), *Key.ToString());
	}
	
	return ActionTexturePtr ? *ActionTexturePtr : nullptr;
}

void UEzControlWidget::RetryUpdateControls()
{
	constexpr float EmptyKeyMappingUpdateTime = 1.f;
	const FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &UEzControlWidget::UpdateControls);

	GetWorld()->GetTimerManager().SetTimer(UpdateControlsHandle, Delegate, EmptyKeyMappingUpdateTime, false);
}

void UEzControlWidget::UpdateControls()
{
	// return if there is an already queued control update
	if (UpdateControlsHandle.IsValid())
	{
	// TODO FIXME
	//	return;
	}
	
	UEnhancedInputLocalPlayerSubsystem* EnhancedInput = GetOwningLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!IsValid(EnhancedInput))
	{
		RetryUpdateControls();
		UE_LOG(LogEzControls, Warning, TEXT("Trying to update controls but EnhancedInput is not valid!"))
		return;
	}

	TArray<FEnhancedActionKeyMapping> KeyMappings = EnhancedInput->GetAllPlayerMappableActionKeyMappings();

	if (KeyMappings.IsEmpty())
	{
		RetryUpdateControls();
		UE_LOG(LogEzControls, Warning, TEXT("Trying to update controls but there are not valid inputs bound to the player."
									        "Make sure the MappableKeySettings are set!"))
		return;
	}

	//TODO reuse the Vertical box children
	//Clear all Vert.box children
	ControlsVerticalBox->ClearChildren();

	for(FEnhancedActionKeyMapping KeyMapping : KeyMappings)
	{
		if (!IsValidKey(KeyMapping.Key))
		{
			continue;
		}

		FText ActionText = KeyMapping.Action->GetPlayerMappableKeySettings()->DisplayName;
		UTexture2D* ActionTexture = GetInputTextureByKey(KeyMapping.Key, ActionText);
		
		// Search an entry with the same action name already set
		UEzControlEntryWidget* FoundEntry = GetEntryByActionName(ActionText);
		if (FoundEntry)
		{
			FoundEntry->AddNewTexture(ActionTexture);
			continue;
		}

		// if there are not entries with the same action text, create and init a new one
		FoundEntry = CreateWidget<UEzControlEntryWidget>(this, EntryWidgetSubclass);
		ControlsVerticalBox->AddChildToVerticalBox(FoundEntry);
		FoundEntry->InitAction(ActionText, ActionTexture);
	}
}

void UEzControlWidget::OnInputMethodChanged(ECommonInputType NewInput)
{
	CurrentInputType = NewInput;

	UpdateControls();
}


