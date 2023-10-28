// Copyright 2023 MrRobin. All Rights Reserved.

#include "DetailCustomizations/MyTimespanDetailCustomization.h"

#include "Containers/Array.h"
#include "Containers/UnrealString.h"
#include "DetailWidgetRow.h"
#include "Fonts/SlateFontInfo.h"
#include "HAL/PlatformCrt.h"
#include "Internationalization/Internationalization.h"
#include "Misc/Attribute.h"
#include "Misc/Timespan.h"
#include "PropertyHandle.h"
#include "Styling/AppStyle.h"
#include "Styling/ISlateStyle.h"
#include "UObject/NameTypes.h"
#include "UObject/UnrealType.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

#include "DetailLayoutBuilder.h"
#include "Widgets/Input/SNumericEntryBox.h"
#include "Widgets/Input/SVectorInputBox.h"
#include "Widgets/Input/NumericTypeInterface.h"
#include "Widgets/Input/NumericUnitTypeInterface.inl"
#include "Math/UnitConversion.h"

#define LOCTEXT_NAMESPACE "MyTimespanDetailCustomization"

/* IDetailCustomization interface
 *****************************************************************************/

void FMyTimespanDetailCustomization::CustomizeChildren(
	TSharedRef<IPropertyHandle> StructPropertyHandle,
	class IDetailChildrenBuilder& StructBuilder,
	IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	/* do nothing */
}

void FMyTimespanDetailCustomization::CustomizeHeader(
	TSharedRef<IPropertyHandle> StructPropertyHandle,
	class FDetailWidgetRow& HeaderRow,
	IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	PropertyHandle = StructPropertyHandle;

	SAssignNew(HourEntryBox, SNumericEntryBox<int32>)
		.AllowSpin(true)
		.MinValue(0)
		.MaxValue(23)
		.MinSliderValue(0)
		.MaxSliderValue(23)
		.Font(IDetailLayoutBuilder::GetDetailFont())
		.Value(this, &FMyTimespanDetailCustomization::OnGetValue, 0)
		.OnValueChanged(this, &FMyTimespanDetailCustomization::OnValueChanged, 0)
		.OnValueCommitted(this, &FMyTimespanDetailCustomization::OnValueCommitted, 0)
		.OnBeginSliderMovement(this, &FMyTimespanDetailCustomization::OnBeginSliderMovement)
		.OnEndSliderMovement(this, &FMyTimespanDetailCustomization::OnEndSliderMovement)
		.TypeInterface(MakeShareable(new TNumericUnitTypeInterface<int32>(EUnit::Hours)))
		.LinearDeltaSensitivity(1);

	SAssignNew(MinuteEntryBox, SNumericEntryBox<int32>)
		.AllowSpin(true)
		.MinValue(0)
		.MaxValue(59)
		.MinSliderValue(0)
		.MaxSliderValue(59)
		.Font(IDetailLayoutBuilder::GetDetailFont())
		.Value(this, &FMyTimespanDetailCustomization::OnGetValue, 1)
		.OnValueChanged(this, &FMyTimespanDetailCustomization::OnValueChanged, 1)
		.OnValueCommitted(this, &FMyTimespanDetailCustomization::OnValueCommitted, 1)
		.OnBeginSliderMovement(this, &FMyTimespanDetailCustomization::OnBeginSliderMovement)
		.OnEndSliderMovement(this, &FMyTimespanDetailCustomization::OnEndSliderMovement)
		.TypeInterface(MakeShareable(new TNumericUnitTypeInterface<int32>(EUnit::Minutes)))
		.LinearDeltaSensitivity(1);

	SAssignNew(SecondEntryBox, SNumericEntryBox<int32>)
		.AllowSpin(true)
		.MinValue(0)
		.MaxValue(59)
		.MinSliderValue(0)
		.MaxSliderValue(59)
		.Font(IDetailLayoutBuilder::GetDetailFont())
		.Value(this, &FMyTimespanDetailCustomization::OnGetValue, 2)
		.OnValueChanged(this, &FMyTimespanDetailCustomization::OnValueChanged, 2)
		.OnValueCommitted(this, &FMyTimespanDetailCustomization::OnValueCommitted, 2)
		.OnBeginSliderMovement(this, &FMyTimespanDetailCustomization::OnBeginSliderMovement)
		.OnEndSliderMovement(this, &FMyTimespanDetailCustomization::OnEndSliderMovement)
		.TypeInterface(MakeShareable(new TNumericUnitTypeInterface<int32>(EUnit::Seconds)))
		.LinearDeltaSensitivity(1);

	HeaderRow
		.NameContent()
		[
			StructPropertyHandle->CreatePropertyNameWidget()
		]
		.ValueContent()
		.MinDesiredWidth(125.0f * 3.0f)
		.MaxDesiredWidth(125.0f * 3.0f)
		[
			SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.Padding(0.0f)
				[
					HourEntryBox.ToSharedRef()
				]
				+ SHorizontalBox::Slot()
				.Padding(2.5f, 0.0f)
				[
					MinuteEntryBox.ToSharedRef()
				]
				+ SHorizontalBox::Slot()
				.Padding(0.0f)
				[
					SecondEntryBox.ToSharedRef()
				]
		];
}


/* FMyTimespanDetailCustomization callbacks
 *****************************************************************************/

TOptional<int32> FMyTimespanDetailCustomization::OnGetValue(int32 Index) const
{
	TArray<void*> RawData;
	PropertyHandle->AccessRawData(RawData);

	if (RawData.Num() != 1)
		return TOptional<int32>();

	if (RawData[0] == nullptr)
		return TOptional<int32>();

	auto* Timespan = ((FTimespan*)RawData[0]);

	switch (Index)
	{
		case 0:
			return TOptional<int32>(Timespan->GetHours());

		case 1:
			return TOptional<int32>(Timespan->GetMinutes());

		case 2:
			return TOptional<int32>(Timespan->GetSeconds());

		default:
			return TOptional<int32>();
	}
}

void FMyTimespanDetailCustomization::OnBeginSliderMovement()
{
	bIsUsingSlider = true;

	GEditor->BeginTransaction(FText::Format(NSLOCTEXT("MyTimespanDetailCustomization", "SetTimespanProperty", "Edit {0}"), PropertyHandle->GetPropertyDisplayName()));
}

void FMyTimespanDetailCustomization::OnEndSliderMovement(int32 NewValue)
{
	bIsUsingSlider = false;

	GEditor->EndTransaction();
}

void FMyTimespanDetailCustomization::OnValueCommitted(int32 NewValue, ETextCommit::Type CommitType, int32 Index)
{
	TArray<void*> RawData;

	PropertyHandle->AccessRawData(RawData);
	PropertyHandle->NotifyPreChange();

	for (auto RawDataInstance : RawData)
	{
		auto* Timespan = (FTimespan*)RawDataInstance;

		int32 Hours = Timespan->GetHours();
		int32 Minutes = Timespan->GetMinutes();
		int32 Seconds = Timespan->GetSeconds();

		switch (Index)
		{
			case 0:
				*Timespan = FTimespan(NewValue, Minutes, Seconds);
				break;

			case 1:
				*Timespan = FTimespan(Hours, NewValue, Seconds);
				break;

			case 2:
				*Timespan = FTimespan(Hours, Minutes, NewValue);
				break;

			default:
				break;
		}
	}

	PropertyHandle->NotifyPostChange(EPropertyChangeType::ValueSet);
	PropertyHandle->NotifyFinishedChangingProperties();
}

void FMyTimespanDetailCustomization::OnValueChanged(int32 NewValue, int32 Index)
{
	if (!bIsUsingSlider)
		return;

	//EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::InteractiveChange;
	//PropertyHandle->SetValue(NewValue, Flags);

	TArray<void*> RawData;

	PropertyHandle->AccessRawData(RawData);
	PropertyHandle->NotifyPreChange();

	for (auto RawDataInstance : RawData)
	{
		auto* Timespan = (FTimespan*)RawDataInstance;

		int32 Hours = Timespan->GetHours();
		int32 Minutes = Timespan->GetMinutes();
		int32 Seconds = Timespan->GetSeconds();

		switch (Index)
		{
			case 0:
				*Timespan = FTimespan(NewValue, Minutes, Seconds);
				break;

			case 1:
				*Timespan = FTimespan(Hours, NewValue, Seconds);
				break;

			case 2:
				*Timespan = FTimespan(Hours, Minutes, NewValue);
				break;

			default:
				break;
		}
	}

	PropertyHandle->NotifyPostChange(EPropertyChangeType::ValueSet);
	PropertyHandle->NotifyFinishedChangingProperties();
}

#undef LOCTEXT_NAMESPACE
