#include "QuestsPage.h"
#include "Components/Widget.h"
#include "QuestSlot.h"

void UQuestsPage::NativeConstruct()
{
	Super::NativeConstruct();
	bIsFocusable = true;
	TArray<UWidget*> widgets = availableQuestsScrollBox->GetAllChildren();
	for (size_t x = 0; x < widgets.Num(); ++x)
	{
		if (UQuestSlot* const slot = Cast<UQuestSlot>(widgets[x]))
		{
			slot->OnQuestSelected.AddDynamic(this, &UQuestsPage::questClicked);
		}
	}
	if (auto const slot = Cast<UQuestSlot>(widgets[0]))
	{
		slot->SetNavigationRule(EUINavigation::Up, EUINavigationRule::Stop, FName(""));
		questClicked(slot->getQuestTitle(), slot->getQuestDescription());
	}
}

void UQuestsPage::NativeTick(FGeometry const& myGeometry, float const inDeltaTime)
{
	if (HasKeyboardFocus())
	{
		if (auto const slot = availableQuestsScrollBox->GetChildAt(0))
		{
			slot->SetKeyboardFocus();
		}
	}
}

FReply UQuestsPage::NativeOnAnalogValueChanged(FGeometry const& inGeometry, FAnalogInputEvent const& inEvent)
{
	FKey const key = inEvent.GetKey();
	if (key.GetDisplayName().ToString() == "Gamepad Right Thumbstick Y-Axis")
	{
		float const analogValue = inEvent.GetAnalogValue() * -10.0f;
		float const currentScrollOffset = questDescriptionScrollBox->GetScrollOffset();
		questDescriptionScrollBox->SetScrollOffset(currentScrollOffset + analogValue);
		return FReply::Handled();
	}
	else if (key.GetDisplayName().ToString() == "Gamepad Left Thumbstick Y-Axis")
	{
		TArray<UWidget*> widgets = availableQuestsScrollBox->GetAllChildren();
		for (size_t x = 0; x < widgets.Num(); ++x)
		{
			if (auto const slot = Cast<UQuestSlot>(widgets[x]))
			{
				if (slot->isHighlighted())
				{
					questClicked(slot->getQuestTitle(), slot->getQuestDescription());
					return FReply::Handled();
				}
			}
		}
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

void UQuestsPage::questClicked(FText const& title, FText const& description)
{
	questTitleTextBlock->SetText(title);
	questDescriptionTextBlock->SetText(description);
}
