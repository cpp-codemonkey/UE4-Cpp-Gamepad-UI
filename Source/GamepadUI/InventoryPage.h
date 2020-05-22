#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/GridPanel.h"
#include "InventoryPage.generated.h"

UCLASS()
class UInventoryPage : public UUserWidget
{
	GENERATED_BODY()
public:
	UInventoryPage(FObjectInitializer const& ObjectInitializer);
	void NativeConstruct() override;
	void NativePreConstruct() override;
	void NativeTick(FGeometry const& myGeometry, float const inDeltaTime) override;
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UGridPanel* inventorySlotsGridPanel = nullptr;
private:
	TSubclassOf<class UUserWidget> slotClass;
};