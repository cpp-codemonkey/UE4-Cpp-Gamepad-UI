// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/Border.h"
#include "InventorySlot.generated.h"

UCLASS()
class GAMEPADUI_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()
public:
	void NativeConstruct() override;
	void NativeOnAddedToFocusPath(FFocusEvent const& InFocusEvent) override;
	void NativeOnRemovedFromFocusPath(FFocusEvent const& InFocusEvent) override;
	bool isHighlighted() const;
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* slotButton = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UBorder* slotBorder = nullptr;
private:
	UFUNCTION()
	void onHovered();
};
