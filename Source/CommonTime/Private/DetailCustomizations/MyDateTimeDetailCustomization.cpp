// Copyright 2023 MrRobin. All Rights Reserved.

#include "DetailCustomizations/MyDateTimeDetailCustomization.h"

#include "Containers/Array.h"
#include "Containers/UnrealString.h"
#include "DetailWidgetRow.h"
#include "Fonts/SlateFontInfo.h"
#include "HAL/PlatformCrt.h"
#include "Internationalization/Internationalization.h"
#include "Misc/Attribute.h"
#include "Misc/DateTime.h"
#include "PropertyHandle.h"
#include "Styling/AppStyle.h"
#include "Styling/ISlateStyle.h"
#include "UObject/NameTypes.h"
#include "UObject/UnrealType.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

#include "DetailLayoutBuilder.h"

#include "Widgets/Input/SNumericEntryBox.h"
#include "Widgets/Input/SVectorInputBox.h"

#define LOCTEXT_NAMESPACE "MyDateTimeDetailCustomization"

/* IDetailCustomization interface
 *****************************************************************************/

void FMyDateTimeDetailCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	/* do nothing */
}

void FMyDateTimeDetailCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	PropertyHandle = StructPropertyHandle;

	const FSlateColor FgColor = FSlateColor(FColor::Yellow);
	const FSlateColor BgColor = FSlateColor(FColor::Blue);

	HeaderRow
		.NameContent()
		[
			StructPropertyHandle->CreatePropertyNameWidget()
		]
		.ValueContent()
		.MaxDesiredWidth(0.f)
		.MinDesiredWidth(125.0f * 3.0f)
		//.HAlign(HAlign_Fill)
		[
			SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.AutoHeight()
				.Padding(0.0f, 1.0f)
				[
					SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						.Padding(0.0f, 2.0f)
						[
							SNew(SNumericEntryBox<int32>)
								.AllowSpin(true)
								.MinValue(1)
								.MaxValue(9999)
								.MinSliderValue(1)
								.MaxSliderValue(9999)
								.Font(IDetailLayoutBuilder::GetDetailFont())
								.Value(this, &FMyDateTimeDetailCustomization::OnGetValue, 3)
								.OnValueChanged(this, &FMyDateTimeDetailCustomization::OnValueChanged, 3)
								.OnValueCommitted(this, &FMyDateTimeDetailCustomization::OnValueCommitted, 3)
								.OnBeginSliderMovement(this, &FMyDateTimeDetailCustomization::OnBeginSliderMovement)
								.OnEndSliderMovement(this, &FMyDateTimeDetailCustomization::OnEndSliderMovement)
								.ToolTipText(this, &FMyDateTimeDetailCustomization::GetValueAsText, 3)
								//.ToolTipText(MakeAttributeLambda([Value, TooltipText]
								//{
								//	if (Value.Get().IsSet())
								//	{
								//		return FText::Format(TooltipText, Value.Get().GetValue());
								//	}
								//	return NSLOCTEXT("SVectorInputBox", "MultipleValues", "Multiple Values");
								//}))
								//.UndeterminedString(NSLOCTEXT("SVectorInputBox", "MultipleValues", "Multiple Values"))
								//.ContextMenuExtender(OnContextMenuExtenderComponent)
								//.TypeInterface(InArgs._TypeInterface)
								//.MinValue(CreatePerComponentGetter(ComponentIndex, TOptional<int32>(), InArgs._MinVector))
								//.MaxValue(CreatePerComponentGetter(ComponentIndex, TOptional<int32>(), InArgs._MaxVector))
								//.MinSliderValue(CreatePerComponentGetter(ComponentIndex, TOptional<int32>(), InArgs._MinSliderVector))
								//.MaxSliderValue(CreatePerComponentGetter(ComponentIndex, TOptional<int32>(), InArgs._MaxSliderVector))
								.LinearDeltaSensitivity(1)
								/*.Delta(InArgs._SpinDelta)*/
								/*.OnBeginSliderMovement(CreatePerComponentSliderMovementEvent(InArgs._OnBeginSliderMovement, OnComponentBeginSliderMovement))*/
								/*.OnEndSliderMovement(CreatePerComponentSliderMovementEvent<FOnNumericValueChanged, NumericType>(InArgs._OnEndSliderMovement, OnComponentEndSliderMovement))*/
								/*.DisplayToggle(InArgs._DisplayToggle)
								.TogglePadding(InArgs._TogglePadding)
								.ToggleChecked(ToggleChecked)
								.OnToggleChanged(OnToggleChanged)*/
						]
						+ SHorizontalBox::Slot()
						.Padding(3.75f, 2.0f)
						[
							SNew(SNumericEntryBox<int32>)
								.AllowSpin(true)
								.MinValue(1)
								.MaxValue(12)
								.MinSliderValue(1)
								.MaxSliderValue(12)
								.Font(IDetailLayoutBuilder::GetDetailFont())
								.Value(this, &FMyDateTimeDetailCustomization::OnGetValue, 4)
								.OnValueChanged(this, &FMyDateTimeDetailCustomization::OnValueChanged, 4)
								.OnValueCommitted(this, &FMyDateTimeDetailCustomization::OnValueCommitted, 4)
								.OnBeginSliderMovement(this, &FMyDateTimeDetailCustomization::OnBeginSliderMovement)
								.OnEndSliderMovement(this, &FMyDateTimeDetailCustomization::OnEndSliderMovement)
								.ToolTipText(this, &FMyDateTimeDetailCustomization::GetValueAsText, 4)
								//.OnValueChanged(CreatePerComponentChanged(ComponentIndex, OnComponentChanged, InArgs._ConstrainVector))
								//.OnValueCommitted(CreatePerComponentCommitted(ComponentIndex, OnComponentCommitted, InArgs._ConstrainVector))
								//.ToolTipText(MakeAttributeLambda([Value, TooltipText]
								//{
								//	if (Value.Get().IsSet())
								//	{
								//		return FText::Format(TooltipText, Value.Get().GetValue());
								//	}
								//	return NSLOCTEXT("SVectorInputBox", "MultipleValues", "Multiple Values");
								//}))
								//.UndeterminedString(NSLOCTEXT("SVectorInputBox", "MultipleValues", "Multiple Values"))
								//.ContextMenuExtender(OnContextMenuExtenderComponent)
								//.TypeInterface(InArgs._TypeInterface)
								//.MinValue(CreatePerComponentGetter(ComponentIndex, TOptional<int32>(), InArgs._MinVector))
								//.MaxValue(CreatePerComponentGetter(ComponentIndex, TOptional<int32>(), InArgs._MaxVector))
								//.MinSliderValue(CreatePerComponentGetter(ComponentIndex, TOptional<int32>(), InArgs._MinSliderVector))
								//.MaxSliderValue(CreatePerComponentGetter(ComponentIndex, TOptional<int32>(), InArgs._MaxSliderVector))
								.LinearDeltaSensitivity(1)
								/*.Delta(InArgs._SpinDelta)*/
								/*.OnBeginSliderMovement(CreatePerComponentSliderMovementEvent(InArgs._OnBeginSliderMovement, OnComponentBeginSliderMovement))*/
								/*.OnEndSliderMovement(CreatePerComponentSliderMovementEvent<FOnNumericValueChanged, NumericType>(InArgs._OnEndSliderMovement, OnComponentEndSliderMovement))*/
								/*.DisplayToggle(InArgs._DisplayToggle)
								.TogglePadding(InArgs._TogglePadding)
								.ToggleChecked(ToggleChecked)
								.OnToggleChanged(OnToggleChanged)*/
						]
						+ SHorizontalBox::Slot()
						.Padding(0.0f, 2.0f)
						[
							SNew(SNumericEntryBox<int32>)
								.AllowSpin(true)
								.MinValue(1)
								.MaxValue(31)
								.MinSliderValue(1)
								.MaxSliderValue(31)
								.Font(IDetailLayoutBuilder::GetDetailFont())
								.Value(this, &FMyDateTimeDetailCustomization::OnGetValue, 5)
								.OnValueChanged(this, &FMyDateTimeDetailCustomization::OnValueChanged, 5)
								.OnValueCommitted(this, &FMyDateTimeDetailCustomization::OnValueCommitted, 5)
								.OnBeginSliderMovement(this, &FMyDateTimeDetailCustomization::OnBeginSliderMovement)
								.OnEndSliderMovement(this, &FMyDateTimeDetailCustomization::OnEndSliderMovement)
								.ToolTipText(this, &FMyDateTimeDetailCustomization::GetValueAsText, 5)
								//.OnValueChanged(CreatePerComponentChanged(ComponentIndex, OnComponentChanged, InArgs._ConstrainVector))
								//.OnValueCommitted(CreatePerComponentCommitted(ComponentIndex, OnComponentCommitted, InArgs._ConstrainVector))
								//.ToolTipText(MakeAttributeLambda([Value, TooltipText]
								//{
								//	if (Value.Get().IsSet())
								//	{
								//		return FText::Format(TooltipText, Value.Get().GetValue());
								//	}
								//	return NSLOCTEXT("SVectorInputBox", "MultipleValues", "Multiple Values");
								//}))
								//.UndeterminedString(NSLOCTEXT("SVectorInputBox", "MultipleValues", "Multiple Values"))
								//.ContextMenuExtender(OnContextMenuExtenderComponent)
								//.TypeInterface(InArgs._TypeInterface)
								//.MinValue(CreatePerComponentGetter(ComponentIndex, TOptional<int32>(), InArgs._MinVector))
								//.MaxValue(CreatePerComponentGetter(ComponentIndex, TOptional<int32>(), InArgs._MaxVector))
								//.MinSliderValue(CreatePerComponentGetter(ComponentIndex, TOptional<int32>(), InArgs._MinSliderVector))
								//.MaxSliderValue(CreatePerComponentGetter(ComponentIndex, TOptional<int32>(), InArgs._MaxSliderVector))
								.LinearDeltaSensitivity(1)
								/*.Delta(InArgs._SpinDelta)*/
								/*.OnBeginSliderMovement(CreatePerComponentSliderMovementEvent(InArgs._OnBeginSliderMovement, OnComponentBeginSliderMovement))*/
								/*.OnEndSliderMovement(CreatePerComponentSliderMovementEvent<FOnNumericValueChanged, NumericType>(InArgs._OnEndSliderMovement, OnComponentEndSliderMovement))*/
								/*.DisplayToggle(InArgs._DisplayToggle)
								.TogglePadding(InArgs._TogglePadding)
								.ToggleChecked(ToggleChecked)
								.OnToggleChanged(OnToggleChanged)*/
						]
				]
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.AutoHeight()
				.Padding(0.0f, 1.0f)
				[
					SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						.Padding(0.0f, 2.0f)
						[
							SNew(SNumericEntryBox<int32>)
								.AllowSpin(true)
								.MinValue(0)
								.MaxValue(23)
								.MinSliderValue(0)
								.MaxSliderValue(23)
								.Font(IDetailLayoutBuilder::GetDetailFont())
								.Value(this, &FMyDateTimeDetailCustomization::OnGetValue, 0)
								.OnValueChanged(this, &FMyDateTimeDetailCustomization::OnValueChanged, 0)
								.OnValueCommitted(this, &FMyDateTimeDetailCustomization::OnValueCommitted, 0)
								.OnBeginSliderMovement(this, &FMyDateTimeDetailCustomization::OnBeginSliderMovement)
								.OnEndSliderMovement(this, &FMyDateTimeDetailCustomization::OnEndSliderMovement)
								.ToolTipText(this, &FMyDateTimeDetailCustomization::GetValueAsText, 0)
								//.OnValueChanged(CreatePerComponentChanged(ComponentIndex, OnComponentChanged, InArgs._ConstrainVector))
								//.OnValueCommitted(CreatePerComponentCommitted(ComponentIndex, OnComponentCommitted, InArgs._ConstrainVector))
								//.ToolTipText(MakeAttributeLambda([Value, TooltipText]
								//{
								//	if (Value.Get().IsSet())
								//	{
								//		return FText::Format(TooltipText, Value.Get().GetValue());
								//	}
								//	return NSLOCTEXT("SVectorInputBox", "MultipleValues", "Multiple Values");
								//}))
								//.UndeterminedString(NSLOCTEXT("SVectorInputBox", "MultipleValues", "Multiple Values"))
								//.ContextMenuExtender(OnContextMenuExtenderComponent)
								//.TypeInterface(InArgs._TypeInterface)
								//.MinValue(CreatePerComponentGetter(ComponentIndex, TOptional<int32>(), InArgs._MinVector))
								//.MaxValue(CreatePerComponentGetter(ComponentIndex, TOptional<int32>(), InArgs._MaxVector))
								//.MinSliderValue(CreatePerComponentGetter(ComponentIndex, TOptional<int32>(), InArgs._MinSliderVector))
								//.MaxSliderValue(CreatePerComponentGetter(ComponentIndex, TOptional<int32>(), InArgs._MaxSliderVector))
								.LinearDeltaSensitivity(1)
								/*.Delta(InArgs._SpinDelta)*/
								/*.OnBeginSliderMovement(CreatePerComponentSliderMovementEvent(InArgs._OnBeginSliderMovement, OnComponentBeginSliderMovement))*/
								/*.OnEndSliderMovement(CreatePerComponentSliderMovementEvent<FOnNumericValueChanged, NumericType>(InArgs._OnEndSliderMovement, OnComponentEndSliderMovement))*/
								/*.DisplayToggle(InArgs._DisplayToggle)
								.TogglePadding(InArgs._TogglePadding)
								.ToggleChecked(ToggleChecked)
								.OnToggleChanged(OnToggleChanged)*/
						]
						+ SHorizontalBox::Slot()
						.Padding(3.75f, 2.0f)
						[
							SNew(SNumericEntryBox<int32>)
								.AllowSpin(true)
								.MinValue(0)
								.MaxValue(59)
								.MinSliderValue(0)
								.MaxSliderValue(59)
								.Font(IDetailLayoutBuilder::GetDetailFont())
								.Value(this, &FMyDateTimeDetailCustomization::OnGetValue, 1)
								.OnValueChanged(this, &FMyDateTimeDetailCustomization::OnValueChanged, 1)
								.OnValueCommitted(this, &FMyDateTimeDetailCustomization::OnValueCommitted, 1)
								.OnBeginSliderMovement(this, &FMyDateTimeDetailCustomization::OnBeginSliderMovement)
								.OnEndSliderMovement(this, &FMyDateTimeDetailCustomization::OnEndSliderMovement)
								.ToolTipText(this, &FMyDateTimeDetailCustomization::GetValueAsText, 1)
								//.OnValueChanged(CreatePerComponentChanged(ComponentIndex, OnComponentChanged, InArgs._ConstrainVector))
								//.OnValueCommitted(CreatePerComponentCommitted(ComponentIndex, OnComponentCommitted, InArgs._ConstrainVector))
								//.ToolTipText(MakeAttributeLambda([Value, TooltipText]
								//{
								//	if (Value.Get().IsSet())
								//	{
								//		return FText::Format(TooltipText, Value.Get().GetValue());
								//	}
								//	return NSLOCTEXT("SVectorInputBox", "MultipleValues", "Multiple Values");
								//}))
								//.UndeterminedString(NSLOCTEXT("SVectorInputBox", "MultipleValues", "Multiple Values"))
								//.ContextMenuExtender(OnContextMenuExtenderComponent)
								//.TypeInterface(InArgs._TypeInterface)
								//.MinValue(CreatePerComponentGetter(ComponentIndex, TOptional<int32>(), InArgs._MinVector))
								//.MaxValue(CreatePerComponentGetter(ComponentIndex, TOptional<int32>(), InArgs._MaxVector))
								//.MinSliderValue(CreatePerComponentGetter(ComponentIndex, TOptional<int32>(), InArgs._MinSliderVector))
								//.MaxSliderValue(CreatePerComponentGetter(ComponentIndex, TOptional<int32>(), InArgs._MaxSliderVector))
								.LinearDeltaSensitivity(1)
								/*.Delta(InArgs._SpinDelta)*/
								/*.OnBeginSliderMovement(CreatePerComponentSliderMovementEvent(InArgs._OnBeginSliderMovement, OnComponentBeginSliderMovement))*/
								/*.OnEndSliderMovement(CreatePerComponentSliderMovementEvent<FOnNumericValueChanged, NumericType>(InArgs._OnEndSliderMovement, OnComponentEndSliderMovement))*/
								/*.DisplayToggle(InArgs._DisplayToggle)
								.TogglePadding(InArgs._TogglePadding)
								.ToggleChecked(ToggleChecked)
								.OnToggleChanged(OnToggleChanged)*/
						]
						+ SHorizontalBox::Slot()
						.Padding(0.0f, 2.0f)
						[
							SNew(SNumericEntryBox<int32>)
								.AllowSpin(true)
								.MinValue(0)
								.MaxValue(59)
								.MinSliderValue(0)
								.MaxSliderValue(59)
								.Font(IDetailLayoutBuilder::GetDetailFont())
								.Value(this, &FMyDateTimeDetailCustomization::OnGetValue, 2)
								.OnValueChanged(this, &FMyDateTimeDetailCustomization::OnValueChanged, 2)
								.OnValueCommitted(this, &FMyDateTimeDetailCustomization::OnValueCommitted, 2)
								.OnBeginSliderMovement(this, &FMyDateTimeDetailCustomization::OnBeginSliderMovement)
								.OnEndSliderMovement(this, &FMyDateTimeDetailCustomization::OnEndSliderMovement)
								.ToolTipText(this, &FMyDateTimeDetailCustomization::GetValueAsText, 2)
								//.OnValueChanged(CreatePerComponentChanged(ComponentIndex, OnComponentChanged, InArgs._ConstrainVector))
								//.OnValueCommitted(CreatePerComponentCommitted(ComponentIndex, OnComponentCommitted, InArgs._ConstrainVector))
								//.ToolTipText(MakeAttributeLambda([Value, TooltipText]
								//{
								//	if (Value.Get().IsSet())
								//	{
								//		return FText::Format(TooltipText, Value.Get().GetValue());
								//	}
								//	return NSLOCTEXT("SVectorInputBox", "MultipleValues", "Multiple Values");
								//}))
								//.UndeterminedString(NSLOCTEXT("SVectorInputBox", "MultipleValues", "Multiple Values"))
								//.ContextMenuExtender(OnContextMenuExtenderComponent)
								//.TypeInterface(InArgs._TypeInterface)
								//.MinValue(CreatePerComponentGetter(ComponentIndex, TOptional<int32>(), InArgs._MinVector))
								//.MaxValue(CreatePerComponentGetter(ComponentIndex, TOptional<int32>(), InArgs._MaxVector))
								//.MinSliderValue(CreatePerComponentGetter(ComponentIndex, TOptional<int32>(), InArgs._MinSliderVector))
								//.MaxSliderValue(CreatePerComponentGetter(ComponentIndex, TOptional<int32>(), InArgs._MaxSliderVector))
								.LinearDeltaSensitivity(1)
								/*.Delta(InArgs._SpinDelta)*/
								/*.OnBeginSliderMovement(CreatePerComponentSliderMovementEvent(InArgs._OnBeginSliderMovement, OnComponentBeginSliderMovement))*/
								/*.OnEndSliderMovement(CreatePerComponentSliderMovementEvent<FOnNumericValueChanged, NumericType>(InArgs._OnEndSliderMovement, OnComponentEndSliderMovement))*/
								/*.DisplayToggle(InArgs._DisplayToggle)
								.TogglePadding(InArgs._TogglePadding)
								.ToggleChecked(ToggleChecked)
								.OnToggleChanged(OnToggleChanged)*/
						]
				]
		];
}


/* FMyDateTimeDetailCustomization callbacks
 *****************************************************************************/

TOptional<int32> FMyDateTimeDetailCustomization::OnGetValue(int32 Index) const
{
	TArray<void*> RawData;
	PropertyHandle->AccessRawData(RawData);

	if (RawData.Num() != 1)
		return TOptional<int32>();

	if (RawData[0] == nullptr)
		return TOptional<int32>();

	auto* DateTime = ((FDateTime*)RawData[0]);

	switch (Index)
	{
		case 0:
			return TOptional<int32>(DateTime->GetHour());

		case 1:
			return TOptional<int32>(DateTime->GetMinute());

		case 2:
			return TOptional<int32>(DateTime->GetSecond());

		case 3:
			return TOptional<int32>(DateTime->GetYear());

		case 4:
			return TOptional<int32>(DateTime->GetMonth());

		case 5:
			return TOptional<int32>(DateTime->GetDay());

		default:
			return TOptional<int32>();
	}
}

FText FMyDateTimeDetailCustomization::GetValueAsText(int32 Index) const
{
	const TOptional<int32>& Value = OnGetValue(Index);

	FFormatNamedArguments Args;

	switch (Index)
	{
		case 0:
			Args.Add(TEXT("Key"), INVTEXT("Hour"));
			Args.Add(TEXT("Desc"), INVTEXT("A hour between 0-23"));
			break;

		case 1:
			Args.Add(TEXT("Key"), INVTEXT("Minute"));
			Args.Add(TEXT("Desc"), INVTEXT("A minute between 0-59"));
			break;

		case 2:
			Args.Add(TEXT("Key"), INVTEXT("Second"));
			Args.Add(TEXT("Desc"), INVTEXT("A second between 0-59"));
			break;

		case 3:
			Args.Add(TEXT("Key"), INVTEXT("Year"));
			Args.Add(TEXT("Desc"), INVTEXT("A year between 1-9999"));
			break;

		case 4:
			Args.Add(TEXT("Key"), INVTEXT("Month"));
			Args.Add(TEXT("Desc"), INVTEXT("A month between 1-12"));
			break;

		case 5:
			Args.Add(TEXT("Key"), INVTEXT("Day"));
			Args.Add(TEXT("Desc"), INVTEXT("A day between 1-31"));
			break;
	}


	if (Value.IsSet() == true)
	{
		Args.Add(TEXT("Value"), Value.GetValue());
		return FText::Format(LOCTEXT("DateTime", "{Key}: {Value} - {Desc}"), Args);
	}

	return FText::Format(LOCTEXT("DateTime", "{Key} - {Desc}"), Args);
}

void FMyDateTimeDetailCustomization::OnBeginSliderMovement()
{
	bIsUsingSlider = true;

	GEditor->BeginTransaction(
		FText::Format(
			NSLOCTEXT("MyDateTimeDetailCustomization", "SetDateTimeProperty", "Edit {0}"),
			PropertyHandle->GetPropertyDisplayName())
	);
}

void FMyDateTimeDetailCustomization::OnEndSliderMovement(int32 NewValue)
{
	bIsUsingSlider = false;

	GEditor->EndTransaction();
}

void FMyDateTimeDetailCustomization::OnValueCommitted(int32 NewValue, ETextCommit::Type CommitType, int32 Index)
{
	TArray<void*> RawData;

	PropertyHandle->AccessRawData(RawData);
	PropertyHandle->NotifyPreChange();

	for (auto RawDataInstance : RawData)
	{
		auto* DateTime = (FDateTime*)RawDataInstance;

		int32 Year = DateTime->GetYear();
		int32 Month = DateTime->GetMonth();
		int32 Day = DateTime->GetDay();

		int32 Hour = DateTime->GetHour();
		int32 Minute = DateTime->GetMinute();
		int32 Second = DateTime->GetSecond();

		int32 MaxDays = FDateTime::DaysInMonth(Year, Month);

		switch (Index)
		{
			case 0:
				*DateTime = FDateTime(Year, Month, Day > MaxDays ? MaxDays : Day, NewValue, Minute, Second);
				break;

			case 1:
				*DateTime = FDateTime(Year, Month, Day > MaxDays ? MaxDays : Day, Hour, NewValue, Second);
				break;

			case 2:
				*DateTime = FDateTime(Year, Month, Day > MaxDays ? MaxDays : Day, Hour, Minute, NewValue);
				break;

			case 3:
			{
				MaxDays = FDateTime::DaysInMonth(NewValue, Month);
				*DateTime = FDateTime(NewValue, Month, Day > MaxDays ? MaxDays : Day, Hour, Minute, Second);
			}
				break;

			case 4:
			{
				MaxDays = FDateTime::DaysInMonth(Year, NewValue);
				*DateTime = FDateTime(Year, NewValue, Day > MaxDays ? MaxDays : Day, Hour, Minute, Second);
			}
				break;

			case 5:
				*DateTime = FDateTime(Year, Month, NewValue > MaxDays ? MaxDays : NewValue, Hour, Minute, Second);
				break;

			default:
				break;
		}
	}

	PropertyHandle->NotifyPostChange(EPropertyChangeType::ValueSet);
	PropertyHandle->NotifyFinishedChangingProperties();
}

void FMyDateTimeDetailCustomization::OnValueChanged(int32 NewValue, int32 Index)
{
	if (!bIsUsingSlider)
		return;

	TArray<void*> RawData;

	PropertyHandle->AccessRawData(RawData);
	PropertyHandle->NotifyPreChange();

	for (auto RawDataInstance : RawData)
	{
		auto* DateTime = (FDateTime*)RawDataInstance;

		int32 Year = DateTime->GetYear();
		int32 Month = DateTime->GetMonth();
		int32 Day = DateTime->GetDay();

		int32 Hour = DateTime->GetHour();
		int32 Minute = DateTime->GetMinute();
		int32 Second = DateTime->GetSecond();

		int32 MaxDays = FDateTime::DaysInMonth(Year, Month);

		switch (Index)
		{
			case 0:
				*DateTime = FDateTime(Year, Month, Day > MaxDays ? MaxDays : Day, NewValue, Minute, Second);
				break;

			case 1:
				*DateTime = FDateTime(Year, Month, Day > MaxDays ? MaxDays : Day, Hour, NewValue, Second);
				break;

			case 2:
				*DateTime = FDateTime(Year, Month, Day > MaxDays ? MaxDays : Day, Hour, Minute, NewValue);
				break;

			case 3:
			{
				MaxDays = FDateTime::DaysInMonth(NewValue, Month);
				*DateTime = FDateTime(NewValue, Month, Day > MaxDays ? MaxDays : Day, Hour, Minute, Second);
			}
				break;

			case 4:
			{
				MaxDays = FDateTime::DaysInMonth(Year, NewValue);
				*DateTime = FDateTime(Year, NewValue, Day > MaxDays ? MaxDays : Day, Hour, Minute, Second);
			}
				break;

			case 5:
				*DateTime = FDateTime(Year, Month, NewValue > MaxDays ? MaxDays : NewValue, Hour, Minute, Second);
				break;

			default:
				break;
		}
	}

	PropertyHandle->NotifyPostChange(EPropertyChangeType::ValueSet);
	PropertyHandle->NotifyFinishedChangingProperties();

	//EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::InteractiveChange;
	//PropertyHandle->SetValue(NewValue, Flags);
}

#undef LOCTEXT_NAMESPACE
