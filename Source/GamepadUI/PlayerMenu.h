#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "PlayerMenuPageTitle.h"
#include <vector>
#include "Components/WidgetSwitcher.h"
#include "CharacterPage.h"
#include "InventoryPage.h"
#include "QuestsPage.h"
#include "MapPage.h"
#include "PlayerMenu.generated.h"

UCLASS()
class UPlayerMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	void NativeConstruct() override;
	FReply NativeOnKeyDown(FGeometry const& MyGeometry, FKeyEvent const& InKeyEvent) override;
	void setActivePage(class UUserWidget* const title);
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UPlayerMenuPageTitle* characterPageTitle = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UPlayerMenuPageTitle* inventoryPageTitle = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UPlayerMenuPageTitle* questsPageTitle = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UPlayerMenuPageTitle* mapPageTitle = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UWidgetSwitcher* pageSwitcher = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCharacterPage* characterPage = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UInventoryPage* inventoryPage = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UQuestsPage* questsPage = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UMapPage* mapPage = nullptr;
private:
	std::vector<UPlayerMenuPageTitle*> titles;
	int currentPageIndex;
	FTimerHandle delayTimer;

	void closeMenu();
	void gotoNextPage();
	void gotoPreviousPage();
	void setActivePage(int const index);
	void setFocus();
};