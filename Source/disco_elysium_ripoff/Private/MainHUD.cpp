// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"

void UMainHUD::AddLogEntry(const FString& log_entry) {
	if (Log) {
		FText log_text = Log->GetText();
		FText new_text = FText::FromString(log_text.ToString() + "\n" + log_entry);
		Log->SetText(new_text);
		LogScroll->ScrollToEnd();
	}
}