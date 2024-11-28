// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseDeviceUI.generated.h"

class ADevice;
struct FDeviceConfig;
/**
 * 
 */

UENUM()
enum EDeviceSignalType {
	EDST_CodepadCorrectCode = 0,
	EDST_CodepadIncorrectCode = 1
};

USTRUCT()
struct FDeviceUISignal {
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TEnumAsByte<EDeviceSignalType> SignalType;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeviceUISignalSentSignature, const FDeviceUISignal&, Signal);

UCLASS(Abstract)
class DISCO_ELYSIUM_RIPOFF_API UBaseDeviceUI : public UUserWidget
{
	GENERATED_BODY()

public:
	FDeviceUISignalSentSignature SignalDelegate;

public:
	UFUNCTION()
	void OnSignalSent(const FDeviceUISignal& signal);

	UFUNCTION()
	virtual void BindDevice(ADevice* device);

	virtual void SetupUIFromDeviceConfig(const FDeviceConfig& config);
	
};
