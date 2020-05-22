// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "QuestSlot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FQuestSelectedDelegate, FText const&, questLevel, FText const&, questDescription);

UCLASS()
class GAMEPADUI_API UQuestSlot : public UUserWidget
{
	GENERATED_BODY()
public:
	void NativeConstruct() override;
	void NativePreConstruct() override;
	void NativeTick(FGeometry const& myGeometry, float const inDeltaTime) override;
	void NativeOnAddedToFocusPath(FFocusEvent const& inFocusEvent) override;
	void NativeOnRemovedFromFocusPath(FFocusEvent const& inFocusEvent) override;
	FQuestSelectedDelegate OnQuestSelected;
	FText getQuestTitle() const;
	FText getQuestDescription() const;
	bool isHighlighted() const;
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* questButton = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* questLevelTextBlock = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* questTitleTextBlock = nullptr;
private:
	UPROPERTY(EditAnywhere, Category = "Text", meta = (AllowPrivateAccess = "true"))
	FText questLevel{FText::FromString("1")};

	UPROPERTY(EditAnywhere, Category = "Text", meta = (AllowPrivateAccess = "true"))
	FText questTitle{FText::FromString("Title")};

	UPROPERTY(EditAnywhere, Category = "Text", meta = (AllowPrivateAccess = "true"))
	FText questDescription{FText::FromString("Description")};

	UFUNCTION()
	void questButtonClicked();
};
