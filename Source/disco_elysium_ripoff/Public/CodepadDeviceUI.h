// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseDeviceUI.h"
#include "CodepadDeviceUI.generated.h"

/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API UCodepadDeviceUI : public UBaseDeviceUI
{
	GENERATED_BODY()
	
	UPROPERTY()
	class UButton* CloseButton;
};
