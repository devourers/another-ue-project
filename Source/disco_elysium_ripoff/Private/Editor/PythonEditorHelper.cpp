// Fill out your copyright notice in the Description page of Project Settings.


#include "Editor/PythonEditorHelper.h"

UPythonEditorHelper* UPythonEditorHelper::Get(){
	TArray<UClass*> PythonEditorHelpers;
	GetDerivedClasses(UPythonEditorHelper::StaticClass(), PythonEditorHelpers);
	if (PythonEditorHelpers.Num())
		return Cast<UPythonEditorHelper>(PythonEditorHelpers[0]->GetDefaultObject());
	return nullptr;
}
