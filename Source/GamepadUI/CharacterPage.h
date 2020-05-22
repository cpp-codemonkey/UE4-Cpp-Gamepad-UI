#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include <vector>
#include "CharacterPage.generated.h"

UCLASS()
class UCharacterPage : public UUserWidget
{
	GENERATED_BODY()
public:
	void NativeConstruct() override;
	virtual void NativeTick(FGeometry const& myGeometry, float const inDeltaTime) override;
	FReply NativeOnKeyDown(FGeometry const& MyGeometry, FKeyEvent const& InKeyEvent);
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* levelNoText = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* skillStrengthValueText = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* skillArcaneValueText = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* skillStaminaValueText = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* availableSkillPointsText = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* skillStrengthButton = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* skillArcaneButton = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* skillStaminaButton = nullptr;
private:
	int level{10};
	int skillStrength{0};
	int skillArcane{0};
	int skillStamina{0};
	int availableSkillStrengthPoints{3};
	int availableSkillArcanePoints{3};
	int availableSkillStaminaPoints{3};
	int skillIndex{0};

	std::vector<UButton* UCharacterPage::*> const skillButtons
	{
		&UCharacterPage::skillStrengthButton,
		&UCharacterPage::skillArcaneButton,
		&UCharacterPage::skillStaminaButton
	};

	std::vector<int*> const availableSkillPoints
	{
		&availableSkillStrengthPoints,
		&availableSkillArcanePoints,
		&availableSkillStaminaPoints
	};

	std::vector<void (UCharacterPage::*)()> const buttonFunctions
	{
		&UCharacterPage::skillStrengthButtonClicked,
		&UCharacterPage::skillArcaneButtonClicked,
		&UCharacterPage::skillStaminaButtonClicked
	};

	void setTextBlockValue(UTextBlock* const text, int const value);

	UFUNCTION()
	void skillStrengthButtonClicked();

	UFUNCTION()
	void skillArcaneButtonClicked();

	UFUNCTION()
	void skillStaminaButtonClicked();

	void highlightCurrentSkill();
};