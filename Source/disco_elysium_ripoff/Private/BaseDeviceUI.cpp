// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDeviceUI.h"

void UBaseDeviceUI::OnSignalSent(const FDeviceUISignal& signal) {
	SignalDelegate.Broadcast(signal);
}

void UBaseDeviceUI::BindDevice(ADevice* device) {

}

void UBaseDeviceUI::SetupUIFromDeviceConfig(const FDeviceConfig& config) {

}