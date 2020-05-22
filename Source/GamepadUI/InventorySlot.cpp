// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlot.h"
#include "defs.h"

void UInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();
	if (slotButton)
	{
		slotButton->OnHovered.AddDynamic(this, &UInventorySlot::onHovered);
	}
}

void UInventorySlot::NativeOnAddedToFocusPath(FFocusEvent const& InFocusEvent)
{
	Super::NativeOnAddedToFocusPath(InFocusEvent);
	slotBorder->SetBrushColor(highlightedColor);
}

void UInventorySlot::NativeOnRemovedFromFocusPath(FFocusEvent const& InFocusEvent)
{
	Super::NativeOnRemovedFromFocusPath(InFocusEvent);
	slotBorder->SetBrushColor(unhighlightedColor);
}

bool UInventorySlot::isHighlighted() const
{
	return slotBorder->BrushColor == highlightedColor;
}

void UInventorySlot::onHovered()
{
	SetKeyboardFocus();
}
