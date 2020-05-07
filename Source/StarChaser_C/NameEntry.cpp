// Fill out your copyright notice in the Description page of Project Settings.


#include "NameEntry.h"

bool UNameEntry::Initialize()
{
	if (!Super::Initialize()) return false;
	if (!NameEntry) return false;
	//NameEntry->OnTextCommitted.AddDynamic(this, &UNameEntry::SaveName);
	return true;
}
