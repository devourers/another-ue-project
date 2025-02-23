// Fill out your copyright notice in the Description page of Project Settings.


#include "Editor/LoaderNameEnter.h"
#include "Components/TextBlock.h"

DEFINE_LOG_CATEGORY(LoaderNameEnterLog);

void ULoaderNameEnter::NativeConstruct(){
	Super::NativeConstruct();
	SetIsFocusable(true);
	if (TextBox) {
		TextBox->OnTextCommitted.AddUniqueDynamic(this, &ULoaderNameEnter::OnTextBoxTextCommited);
		TextBox->OnTextChanged.AddUniqueDynamic(this, &ULoaderNameEnter::OnTextBoxTextChanged);
	}
}

FReply ULoaderNameEnter::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent){
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);
	if (InKeyEvent.GetKey() == FKey("Enter")) {
		UE_LOGFMT(LoaderNameEnterLog, Log, "On Enter");
	}
	return FReply::Handled();
}

void ULoaderNameEnter::NameExists() {
	safe_to_create = false;
	BadNameLabel->SetText(FText::FromString(TEXT("Name already exist")));
	BadNameLabel->SetColorAndOpacity(FSlateColor(FColor::Red));
}

void ULoaderNameEnter::NameDoesNotExist() {
	safe_to_create = true;
	BadNameLabel->SetText(FText::FromString(TEXT("Avaliable")));
	BadNameLabel->SetColorAndOpacity(FSlateColor(FColor::Green));
}

void ULoaderNameEnter::OnTextBoxTextCommited(const FText& Text, ETextCommit::Type CommitMethod){
	if (CommitMethod == ETextCommit::OnEnter && safe_to_create) {
		UE_LOGFMT(LoaderNameEnterLog, Log, "Text committed");
		LoaderNameEntered.Broadcast(Text.ToString());
	}
	else {
		//animation?
	}
}

void ULoaderNameEnter::OnTextBoxTextChanged(const FText& Text) {
	UE_LOGFMT(LoaderNameEnterLog, Log, "Text changed");
	LoaderNameChanged.Broadcast(Text.ToString());
}
