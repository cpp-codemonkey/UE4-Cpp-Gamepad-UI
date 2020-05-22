#include "PlayerMenu.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void UPlayerMenu::NativeConstruct()
{
	characterPageTitle->setText(FText::FromString("Character"));
	inventoryPageTitle->setText(FText::FromString("Inventory"));
	questsPageTitle->setText(FText::FromString("Quests"));
	mapPageTitle->setText(FText::FromString("Map"));
	titles = {characterPageTitle, inventoryPageTitle, questsPageTitle, mapPageTitle};
	currentPageIndex = 0;
	setActivePage(currentPageIndex);
	GetWorld()->GetTimerManager().SetTimer(delayTimer, this, &UPlayerMenu::setFocus, 0.2f);
}

FReply UPlayerMenu::NativeOnKeyDown(FGeometry const& MyGeometry, FKeyEvent const& InKeyEvent)
{
	if (InKeyEvent.GetKey().GetDisplayName().ToString() == "Gamepad Special Right")
	{
		closeMenu();
		return FReply::Handled();
	}
	else if (InKeyEvent.GetKey().GetDisplayName().ToString() == "Tab")
	{
		closeMenu();
	}
	else if (InKeyEvent.GetKey().GetDisplayName().ToString() == "Gamepad Right Shoulder")
	{
		gotoNextPage();
	}
	else if (InKeyEvent.GetKey().GetDisplayName().ToString() == "Gamepad Left Shoulder")
	{
		gotoPreviousPage();
	}
	return FReply::Unhandled();
}

void UPlayerMenu::setActivePage(UUserWidget* const title)
{
	for (auto x = 0; x < titles.size(); ++x)
	{
		if (titles[x] == title)
		{
			setActivePage(x);
			break;
		}
	}
}

void UPlayerMenu::closeMenu()
{
	RemoveFromParent();
	auto const controller = UGameplayStatics::GetPlayerController(this, 0);
	FInputModeGameOnly mode;
	controller->SetInputMode(mode);
	controller->bShowMouseCursor = false;
}

void UPlayerMenu::gotoNextPage()
{
	currentPageIndex = ++currentPageIndex % 4;
	setActivePage(currentPageIndex);
}

void UPlayerMenu::gotoPreviousPage()
{
	currentPageIndex = currentPageIndex <= 0 ? 3 : --currentPageIndex;
	setActivePage(currentPageIndex);
}

void UPlayerMenu::setActivePage(int const index)
{
	currentPageIndex = index;
	pageSwitcher->SetActiveWidgetIndex(currentPageIndex);
	for (auto x = 0; x < titles.size(); ++x)
	{
		titles[x]->setEnabled(x == currentPageIndex);
	}
	setFocus();
}

void UPlayerMenu::setFocus()
{
	pageSwitcher->GetChildAt(currentPageIndex)->SetKeyboardFocus();
}
