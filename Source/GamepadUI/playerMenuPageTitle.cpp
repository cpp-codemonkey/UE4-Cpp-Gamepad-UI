#include "playerMenuPageTitle.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "RPGController.h"

void UPlayerMenuPageTitle::NativeConstruct()
{
	if (pageNameButton)
	{
		pageNameButton->OnClicked.AddDynamic(this, &UPlayerMenuPageTitle::pageNameButtonClicked);
	}
}

void UPlayerMenuPageTitle::setText(FText const& text)
{
	pageNameText->SetText(text);
}

void UPlayerMenuPageTitle::setEnabled(bool const enable)
{
	pageNameText->SetColorAndOpacity(enable ? FSlateColor(FColor::Orange) : FSlateColor(FColor::White));
}

void UPlayerMenuPageTitle::pageNameButtonClicked()
{
	auto const controller = Cast<ARPGController>(UGameplayStatics::GetPlayerController(this, 0));
	controller->setActivePage(this);
}
