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
						.Value(this, &FMyTimespanDetailCustomization::OnGetValue, 0)
						.OnValueChanged(this, &FMyTimespanDetailCustomization::OnValueChanged, 0)
						.OnValueCommitted(this, &FMyTimespanDetailCustomization::OnValueCommitted, 0)
						.OnBeginSliderMovement(this, &FMyTimespanDetailCustomization::OnBeginSliderMovement)
						.OnEndSliderMovement(this, &FMyTimespanDetailCustomization::OnEndSliderMovement)
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

					//SNew(SNumericEntryBox<int32>)
					//	.AllowSpin(true)
					//	.Font(IDetailLayoutBuilder::GetDetailFont())
					//	.Value(this, &FMyTimespanDetailCustomization::OnGetValue, 0)
					//	.MinValue(0)
					//	.MaxValue(23)
					//	.MinSliderValue(0)
					//	.MaxSliderValue(23)
					//	.LabelPadding(FMargin(3.f))
					//	.LabelLocation(SNumericEntryBox<int32>::ELabelLocation::Inside)
					//	.UndeterminedString(NSLOCTEXT("PropertyEditor", "MultipleValues", "Multiple Values"))
					//	.OnValueCommitted(const_cast<FMyTimespanDetailCustomization*>(this),&FMyTimespanDetailCustomization::OnValueCommitted, 0)
					//	.OnValueChanged(const_cast<FMyTimespanDetailCustomization*>(this),&FMyTimespanDetailCustomization::OnValueChanged, 0)
					//	.OnBeginSliderMovement(const_cast<FMyTimespanDetailCustomization*>(this), &FMyTimespanDetailCustomization::OnBeginSliderMovement)
					//	.OnEndSliderMovement(const_cast<FMyTimespanDetailCustomization*>(this),  &FMyTimespanDetailCustomization::OnEndSliderMovement)
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
						.Value(this, &FMyTimespanDetailCustomization::OnGetValue, 1)
						.OnValueChanged(this, &FMyTimespanDetailCustomization::OnValueChanged, 1)
						.OnValueCommitted(this, &FMyTimespanDetailCustomization::OnValueCommitted, 1)
						.OnBeginSliderMovement(this, &FMyTimespanDetailCustomization::OnBeginSliderMovement)
						.OnEndSliderMovement(this, &FMyTimespanDetailCustomization::OnEndSliderMovement)
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
						.Value(this, &FMyTimespanDetailCustomization::OnGetValue, 2)
						.OnValueChanged(this, &FMyTimespanDetailCustomization::OnValueChanged, 2)
						.OnValueCommitted(this, &FMyTimespanDetailCustomization::OnValueCommitted, 2)
						.OnBeginSliderMovement(this, &FMyTimespanDetailCustomization::OnBeginSliderMovement)
						.OnEndSliderMovement(this, &FMyTimespanDetailCustomization::OnEndSliderMovement)
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
