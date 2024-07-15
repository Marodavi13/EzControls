#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputCoreTypes.h"

#include "EzInputDataAsset.generated.h"

class UTexture2D;
/**
 * 
 */
UCLASS()
class EZCONTROLS_API UEzInputDataAsset: public UDataAsset
{
	GENERATED_BODY()

public:
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Keys")
	TMap<FKey, UTexture2D*> KeyTextures;
};
