#include "CharacterPage.h"
#include "Components/Border.h"
#include "defs.h"

void UCharacterPage::NativeConstruct()
{
	Super::NativeConstruct();
	bIsFocusable = true;
	if (levelNoText)
	{
		setTextBlockValue(levelNoText, level);
	}
	if (skillStrengthValueText)
	{
		setTextBlockValue(skillStrengthValueText, skillStrength);
	}
	if (skillArcaneValueText)
	{
		setTextBlockValue(skillArcaneValueText, skillArcane);
	}
	if (skillStaminaValueText)
	{
		setTextBlockValue(skillStaminaValueText, skillStamina);
	}
	if (skillStrengthButton)
	{
		skillStrengthButton->OnClicked.AddDynamic(this, &UCharacterPage::skillStrengthButtonClicked);
	}
	if (skillArcaneButton)
	{
		skillArcaneButton->OnClicked.AddDynamic(this, &UCharacterPage::skillArcaneButtonClicked);
	}
	if (skillStaminaButton)
	{
		skillStaminaButton->OnClicked.AddDynamic(this, &UCharacterPage::skillStaminaButtonClicked);
	}
	if (availableSkillPointsText)
	{
		setTextBlockValue(availableSkillPointsText, availableSkillStrengthPoints);
	}
}

void UCharacterPage::NativeTick(FGeometry const& myGeometry, float const inDeltaTime)
{
	Super::NativeTick(myGeometry, inDeltaTime);
	if (HasKeyboardFocus())
	{
		skillStrengthButton->SetKeyboardFocus();
	}
	highlightCurrentSkill();
}

FReply UCharacterPage::NativeOnKeyDown(FGeometry const& MyGeometry, FKeyEvent const& InKeyEvent)
{
	if (InKeyEvent.GetKey().GetDisplayName().ToString() == "Gamepad Right Trigger")
	{
		(this->*buttonFunctions[skillIndex])();
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

void UCharacterPage::setTextBlockValue(UTextBlock* const text, int const value)
{
	if (text)
	{
		text->SetText(FText::FromString(FString::FromInt(value)));
	}
}

void UCharacterPage::skillStrengthButtonClicked()
{
	if (availableSkillStrengthPoints > 0)
	{
		setTextBlockValue(skillStrengthValueText, ++skillStrength);
		--availableSkillStrengthPoints;
		setTextBlockValue(availableSkillPointsText, availableSkillStrengthPoints);
	}
}

void UCharacterPage::skillArcaneButtonClicked()
{
	if (availableSkillArcanePoints > 0)
	{
		setTextBlockValue(skillArcaneValueText, ++skillArcane);
		--availableSkillArcanePoints;
		setTextBlockValue(availableSkillPointsText, availableSkillArcanePoints);
	}
}

void UCharacterPage::skillStaminaButtonClicked()
{
	if (availableSkillStaminaPoints > 0)
	{
		setTextBlockValue(skillStaminaValueText, ++skillStamina);
		--availableSkillStaminaPoints;
		setTextBlockValue(availableSkillPointsText, availableSkillStaminaPoints);
	}
}

void UCharacterPage::highlightCurrentSkill()
{
	for (size_t x = 0; x < skillButtons.size(); ++x)
	{
		if (auto const button = this->*skillButtons[x])
		{
			if (UBorder* const border = Cast<UBorder>(button->GetChildAt(0)))
			{
				border->SetBrushColor(button->HasKeyboardFocus() ? highlightedColor : unhighlightedColor);
				skillIndex = button->HasKeyboardFocus() ? x : skillIndex;
				if (button->HasKeyboardFocus())
				{
					setTextBlockValue(availableSkillPointsText, *availableSkillPoints[x]);
				}
			}
		}
	}
}
