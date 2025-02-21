// Fill out your copyright notice in the Description page of Project Settings.


#include "Editor/LoaderNameEnter.h"

void ULoaderNameEnter::NativeConstruct(){
	Super::NativeConstruct();
}

FReply ULoaderNameEnter::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent){
	TextBox->OnTextCommitted.Broadcast(FText(), ETextCommit::OnEnter);
	return FReply::Handled();
}


