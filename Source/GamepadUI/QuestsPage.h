#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/ScrollBox.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "QuestsPage.generated.h"

UCLASS()
class UQuestsPage : public UUserWidget
{
	GENERATED_BODY()
public:
	void NativeConstruct() override;
	void NativeTick(FGeometry const& myGeometry, float const inDeltaTime ) override;
	FReply NativeOnAnalogValueChanged(FGeometry const& inGeometry, FAnalogInputEvent const& inEvent) override;
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* questDescriptionTextBlock = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* questTitleTextBlock = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UScrollBox* availableQuestsScrollBox = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UScrollBox* questDescriptionScrollBox = nullptr;
private:
	UFUNCTION()
	void questClicked(FText const& title, FText const& description);
};