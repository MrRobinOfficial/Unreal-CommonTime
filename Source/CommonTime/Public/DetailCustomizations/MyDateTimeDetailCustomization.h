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
class FMyDateTimeDetailCustomization
	: public IPropertyTypeCustomization
{
public:
public:
	/**
	 * Creates an instance of this class.
	 *
	 * @return The new instance.
	 */
	static TSharedRef<IPropertyTypeCustomization> MakeInstance()
	{
		return MakeShareable(new FMyDateTimeDetailCustomization());
	}

public:
	// IPropertyTypeCustomization interface
	void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

	void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

private:
	TOptional<int32> OnGetValue(int32 Index) const;
	/** @return the value being observed by the Numeric Entry Box as a FText */
	FText GetValueAsText(int32 Index) const;
	void OnValueCommitted(int32 NewValue, ETextCommit::Type CommitType, int32 Index);
	void OnValueChanged(int32 NewValue, int32 Index);
	void OnBeginSliderMovement();
	void OnEndSliderMovement(int32 NewValue);

private:
	/** Holds a handle to the property being edited. */
	TSharedPtr<IPropertyHandle> PropertyHandle;

	/** True if a value is being changed by dragging a slider */
	bool bIsUsingSlider;
};
