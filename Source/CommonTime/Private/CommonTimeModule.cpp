// Copyright 2023 MrRobin. All Rights Reserved.

#include "CommonTimeModule.h"

#include "Modules/ModuleManager.h"

#include "DetailCustomizations/MyDateTimeDetailCustomization.h"
#include "DetailCustomizations/MyTimespanDetailCustomization.h"

DEFINE_LOG_CATEGORY(LogCommonTime);

class FCommonTimeModule : public IModuleInterface
{
public:
	void StartupModule() override
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));

		PropertyModule.RegisterCustomPropertyTypeLayout(
			TEXT("Timespan"),
			FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FMyTimespanDetailCustomization::MakeInstance)
		);

		PropertyModule.RegisterCustomPropertyTypeLayout(
			TEXT("DateTime"),
			FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FMyDateTimeDetailCustomization::MakeInstance)
		);

		PropertyModule.NotifyCustomizationModuleChanged();
	}

	void ShutdownModule() override
	{
		if (FModuleManager::Get().IsModuleLoaded(TEXT("PropertyEditor")))
		{
			FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");

			PropertyModule.UnregisterCustomPropertyTypeLayout(TEXT("Timespan"));
			PropertyModule.UnregisterCustomPropertyTypeLayout(TEXT("DateTime"));

			PropertyModule.NotifyCustomizationModuleChanged();
		}
	}
};

IMPLEMENT_MODULE(FCommonTimeModule, CommonTime);