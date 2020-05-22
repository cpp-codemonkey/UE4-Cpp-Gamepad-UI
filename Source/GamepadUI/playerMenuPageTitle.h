#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Components/TextBlock.h"
#include "playerMenuPageTitle.generated.h"

UCLASS()
class UPlayerMenuPageTitle : public UUserWidget
{
	GENERATED_BODY()
public:
	void NativeConstruct() override;
	void setText(FText const& text);
	void setEnabled(bool const enable);
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* pageNameButton = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* pageNameText = nullptr;

private:
	UFUNCTION()
	void pageNameButtonClicked();
};