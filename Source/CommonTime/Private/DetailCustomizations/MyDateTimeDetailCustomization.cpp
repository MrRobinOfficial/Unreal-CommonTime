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
#include "Widgets/Input/NumericTypeInterface.h"
#include "Widgets/Input/NumericUnitTypeInterface.inl"
#include "Math/UnitConversion.h"

// SExpanderArrow

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

	SAssignNew(YearEntryBox, SNumericEntryBox<double>)
		.AllowSpin(true)
		.MinValue(1)
		.MaxValue(9999)
		.MinSliderValue(1)
		.MaxSliderValue(9999)
		.MinFractionalDigits(0)
		.MaxFractionalDigits(0)
		.Font(IDetailLayoutBuilder::GetDetailFont())
		.Value(this, &FMyDateTimeDetailCustomization::OnGetValue, 3)
		.OnValueChanged(this, &FMyDateTimeDetailCustomization::OnValueChanged, 3)
		.OnValueCommitted(this, &FMyDateTimeDetailCustomization::OnValueCommitted, 3)
		.OnBeginSliderMovement(this, &FMyDateTimeDetailCustomization::OnBeginSliderMovement)
		.OnEndSliderMovement(this, &FMyDateTimeDetailCustomization::OnEndSliderMovement)
		.TypeInterface(MakeShareable(new TNumericUnitTypeInterface<double>(EUnit::Years)))
		.LinearDeltaSensitivity(1);

	SAssignNew(MonthEntryBox, SNumericEntryBox<double>)
		.AllowSpin(true)
		.MinValue(1)
		.MaxValue(12)
		.MinSliderValue(1)
		.MaxSliderValue(12)
		.MinFractionalDigits(0)
		.MaxFractionalDigits(0)
		.Font(IDetailLayoutBuilder::GetDetailFont())
		.Value(this, &FMyDateTimeDetailCustomization::OnGetValue, 4)
		.OnValueChanged(this, &FMyDateTimeDetailCustomization::OnValueChanged, 4)
		.OnValueCommitted(this, &FMyDateTimeDetailCustomization::OnValueCommitted, 4)
		.OnBeginSliderMovement(this, &FMyDateTimeDetailCustomization::OnBeginSliderMovement)
		.OnEndSliderMovement(this, &FMyDateTimeDetailCustomization::OnEndSliderMovement)
		.TypeInterface(MakeShareable(new TNumericUnitTypeInterface<double>(EUnit::Months)))
		.LinearDeltaSensitivity(1);

	SAssignNew(DayEntryBox, SNumericEntryBox<double>)
		.AllowSpin(true)
		.MinValue(1)
		.MaxValue(31)
		.MinSliderValue(1)
		.MaxSliderValue(31)
		.MinFractionalDigits(0)
		.MaxFractionalDigits(0)
		.Font(IDetailLayoutBuilder::GetDetailFont())
		.Value(this, &FMyDateTimeDetailCustomization::OnGetValue, 5)
		.OnValueChanged(this, &FMyDateTimeDetailCustomization::OnValueChanged, 5)
		.OnValueCommitted(this, &FMyDateTimeDetailCustomization::OnValueCommitted, 5)
		.OnBeginSliderMovement(this, &FMyDateTimeDetailCustomization::OnBeginSliderMovement)
		.OnEndSliderMovement(this, &FMyDateTimeDetailCustomization::OnEndSliderMovement)
		.TypeInterface(MakeShareable(new TNumericUnitTypeInterface<double>(EUnit::Days)))
		.LinearDeltaSensitivity(1);

	SAssignNew(HourEntryBox, SNumericEntryBox<double>)
		.AllowSpin(true)
		.MinValue(0)
		.MaxValue(23)
		.MinSliderValue(0)
		.MaxSliderValue(23)
		.MinFractionalDigits(0)
		.MaxFractionalDigits(0)
		.Font(IDetailLayoutBuilder::GetDetailFont())
		.Value(this, &FMyDateTimeDetailCustomization::OnGetValue, 0)
		.OnValueChanged(this, &FMyDateTimeDetailCustomization::OnValueChanged, 0)
		.OnValueCommitted(this, &FMyDateTimeDetailCustomization::OnValueCommitted, 0)
		.OnBeginSliderMovement(this, &FMyDateTimeDetailCustomization::OnBeginSliderMovement)
		.OnEndSliderMovement(this, &FMyDateTimeDetailCustomization::OnEndSliderMovement)
		.TypeInterface(MakeShareable(new TNumericUnitTypeInterface<double>(EUnit::Hours)))
		.LinearDeltaSensitivity(1);

	SAssignNew(MinuteEntryBox, SNumericEntryBox<double>)
		.AllowSpin(true)
		.MinValue(0)
		.MaxValue(59)
		.MinSliderValue(0)
		.MaxSliderValue(59)
		.MinFractionalDigits(0)
		.MaxFractionalDigits(0)
		.Font(IDetailLayoutBuilder::GetDetailFont())
		.Value(this, &FMyDateTimeDetailCustomization::OnGetValue, 1)
		.OnValueChanged(this, &FMyDateTimeDetailCustomization::OnValueChanged, 1)
		.OnValueCommitted(this, &FMyDateTimeDetailCustomization::OnValueCommitted, 1)
		.OnBeginSliderMovement(this, &FMyDateTimeDetailCustomization::OnBeginSliderMovement)
		.OnEndSliderMovement(this, &FMyDateTimeDetailCustomization::OnEndSliderMovement)
		.TypeInterface(MakeShareable(new TNumericUnitTypeInterface<double>(EUnit::Minutes)))
		.LinearDeltaSensitivity(1);

	SAssignNew(SecondEntryBox, SNumericEntryBox<double>)
		.AllowSpin(true)
		.MinValue(0)
		.MaxValue(59)
		.MinSliderValue(0)
		.MaxSliderValue(59)
		.MinFractionalDigits(0)
		.MaxFractionalDigits(0)
		.Font(IDetailLayoutBuilder::GetDetailFont())
		.Value(this, &FMyDateTimeDetailCustomization::OnGetValue, 2)
		.OnValueChanged(this, &FMyDateTimeDetailCustomization::OnValueChanged, 2)
		.OnValueCommitted(this, &FMyDateTimeDetailCustomization::OnValueCommitted, 2)
		.OnBeginSliderMovement(this, &FMyDateTimeDetailCustomization::OnBeginSliderMovement)
		.OnEndSliderMovement(this, &FMyDateTimeDetailCustomization::OnEndSliderMovement)
		.TypeInterface(MakeShareable(new TNumericUnitTypeInterface<double>(EUnit::Seconds)))
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
			SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						.Padding(0.0f, 0.0f, 2.0f, 0.0f)
						[
							YearEntryBox.ToSharedRef()
						]
						+ SHorizontalBox::Slot()
						.Padding(2.0f, 0.0f)
						[
							MonthEntryBox.ToSharedRef()
						]
						+ SHorizontalBox::Slot()
						.Padding(2.0f, 0.0f, 0.0f, 0.0f)
						[
							DayEntryBox.ToSharedRef()
						]
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SSpacer)
						.Size(FVector2D(8.0f))
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						.Padding(0.0f, 0.0f, 2.0f, 0.0f)
						[
							HourEntryBox.ToSharedRef()
						]
						+ SHorizontalBox::Slot()
						.Padding(2.0f, 0.0f)
						[
							MinuteEntryBox.ToSharedRef()
						]
						+ SHorizontalBox::Slot()
						.Padding(2.0f, 0.0f, 0.0f, 0.0f)
						[
							SecondEntryBox.ToSharedRef()
						]
				]
		];
}


/* FMyDateTimeDetailCustomization callbacks
 *****************************************************************************/

TOptional<double> FMyDateTimeDetailCustomization::OnGetValue(int32 Index) const
{
	TArray<void*> RawData;
	PropertyHandle->AccessRawData(RawData);

	if (RawData.Num() != 1)
		return TOptional<double>();

	if (RawData[0] == nullptr)
		return TOptional<double>();

	auto* DateTime = ((FDateTime*)RawData[0]);

	switch (Index)
	{
		case 0:
			return TOptional<double>(DateTime->GetHour());

		case 1:
			return TOptional<double>(DateTime->GetMinute());

		case 2:
			return TOptional<double>(DateTime->GetSecond());

		case 3:
			return TOptional<double>(DateTime->GetYear());

		case 4:
			return TOptional<double>(DateTime->GetMonth());

		case 5:
			return TOptional<double>(DateTime->GetDay());

		default:
			return TOptional<double>();
	}
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

void FMyDateTimeDetailCustomization::OnEndSliderMovement(double NewValue)
{
	bIsUsingSlider = false;

	GEditor->EndTransaction();
}

void FMyDateTimeDetailCustomization::OnValueCommitted(double NewValue, ETextCommit::Type CommitType, int32 Index)
{
	NewValue = FMath::CeilToDouble(NewValue);

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

void FMyDateTimeDetailCustomization::OnValueChanged(double NewValue, int32 Index)
{
	if (!bIsUsingSlider)
		return;

	NewValue = FMath::CeilToDouble(NewValue);

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

#undef LOCTEXT_NAMESPACE
