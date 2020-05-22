#include "InventoryPage.h"
#include "UObject/ConstructorHelpers.h"
#include "GridSlot.h"
#include "InventorySlot.h"

namespace
{
	int inventoryIndex = 0;
}

UInventoryPage::UInventoryPage(FObjectInitializer const& ObjectInitializer) :
	UUserWidget(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> obj(TEXT("/Game/UI/InventorySlot_UI"));
	if (obj.Succeeded())
	{
		slotClass = obj.Class;
	}
}

void UInventoryPage::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryPage::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (slotClass)
	{
		for (int x = 0; x <= 23; ++x)
		{
			auto const slot = inventorySlotsGridPanel->AddChildToGrid(
				CreateWidget<UUserWidget>(GetWorld(), slotClass),
				x / 8,
				x % 8);
			slot->SetPadding(20);
		}
	}
}

void UInventoryPage::NativeTick(FGeometry const& myGeometry, float const inDeltaTime)
{
	if (HasKeyboardFocus())
	{
		inventorySlotsGridPanel->GetChildAt(inventoryIndex)->SetKeyboardFocus();
	}
	else
	{
		for  (int x = 0; x <= 23; ++x)
		{
			if (auto const slotWidget = Cast<UInventorySlot>(inventorySlotsGridPanel->GetChildAt(x)))
			{
				if (slotWidget->isHighlighted())
				{
					inventoryIndex = x;
					break;
				}
			}
		}
	}
}
