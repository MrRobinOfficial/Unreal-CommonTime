// Copyright 2023 MrRobin. All Rights Reserved.

#pragma once

#include "IPropertyTypeCustomization.h"
#include "Internationalization/Text.h"
#include "Styling/SlateColor.h"
#include "Templates/SharedPointer.h"
#include "Types/SlateEnums.h"

class IPropertyHandle;
class SEditableTextBox;

/**
 * Implements a details view customization for the FTimespan structure.
 */
class FMyTimespanDetailCustomization
	: public IPropertyTypeCustomization
{
public:
	/**
	 * Creates an instance of this class.
	 *
	 * @return The new instance.
	 */
	static TSharedRef<IPropertyTypeCustomization> MakeInstance()
	{
		return MakeShareable(new FMyTimespanDetailCustomization());
	}

public:
	// IPropertyTypeCustomization interface
	void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

	void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

private:
	TOptional<double> OnGetValue(int32 Index) const;
	void OnValueCommitted(double NewValue, ETextCommit::Type CommitType, int32 Index);
	void OnValueChanged(double NewValue, int32 Index);
	void OnBeginSliderMovement();
	void OnEndSliderMovement(double NewValue);

private:
	/** Holds a handle to the property being edited. */
	TSharedPtr<IPropertyHandle> PropertyHandle;

	/** True if a value is being changed by dragging a slider */
	bool bIsUsingSlider;

	TSharedPtr<SWidget> HourEntryBox;
	TSharedPtr<SWidget> MinuteEntryBox;
	TSharedPtr<SWidget> SecondEntryBox;
};
