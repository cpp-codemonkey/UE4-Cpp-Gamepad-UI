// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSlot.h"
#include "defs.h"

void UQuestSlot::NativeConstruct()
{
	UUserWidget::NativeConstruct();
	bIsFocusable = true;
	if (questButton)
	{
		questButton->OnClicked.AddDynamic(this, &UQuestSlot::questButtonClicked);
	}
}

void UQuestSlot::NativePreConstruct()
{
	UUserWidget::NativePreConstruct();
	questLevelTextBlock->SetText(questLevel);
	questTitleTextBlock->SetText(questTitle);
}

void UQuestSlot::NativeTick(FGeometry const& myGeometry, float const inDeltaTime)
{
	UUserWidget::NativeTick(myGeometry, inDeltaTime);
	if (IsHovered() || HasKeyboardFocus())
	{
		questButton->SetKeyboardFocus();
	}
}

void UQuestSlot::NativeOnAddedToFocusPath(FFocusEvent const& inFocusEvent)
{
	questButton->SetBackgroundColor(questHighlightedColor);
}

void UQuestSlot::NativeOnRemovedFromFocusPath(FFocusEvent const& inFocusEvent)
{
	questButton->SetBackgroundColor(questUnhighlightedColor);
}

FText UQuestSlot::getQuestTitle() const
{
	return questTitle;
}

FText UQuestSlot::getQuestDescription() const
{
	return questDescription;
}

bool UQuestSlot::isHighlighted() const
{
	return questButton->BackgroundColor == questHighlightedColor;
}

void UQuestSlot::questButtonClicked()
{
	OnQuestSelected.Broadcast(questTitle, questDescription);
}
