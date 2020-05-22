#include "RPGController.h"
#include "UObject/ConstructorHelpers.h"
#include "UserWidget.h"
#include "PlayerMenu.h"

// Sets default values
ARPGController::ARPGController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> obj(TEXT("/Game/UI/PlayerMenu_UI"));
	if (obj.Succeeded())
	{
		uiBPClass = obj.Class;
	}
}

bool ARPGController::InputKey(FKey Key, EInputEvent EventType, float AmountPressed, bool bGamepad)
{
	bool ret = APlayerController::InputKey(Key, EventType, AmountPressed, bGamepad);
	key = Key;
	return ret;
}

void ARPGController::setActivePage(UUserWidget* const title)
{
	if (auto const menu = Cast<UPlayerMenu>(uiWidget))
	{
		menu->setActivePage(title);
	}
}

void ARPGController::SetupInputComponent()
{
	APlayerController::SetupInputComponent();
	InputComponent->BindAction("Menu", IE_Pressed, this, &ARPGController::openMenu);
}

void ARPGController::openMenu()
{
	// create widget and if successful display by adding to the viewport
	if (uiBPClass)
	{
		uiWidget = CreateWidget<UUserWidget>(GetWorld(), uiBPClass);
		if (uiWidget)
		{
			uiWidget->AddToViewport();

			// set input mode to UI only and set the widget to focus to
			FInputModeUIOnly mode;
			mode.SetWidgetToFocus(TSharedPtr<SWidget>(uiWidget->GetCachedWidget()));
			mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			SetInputMode(mode);
		}
	}
	if (key.IsGamepadKey())
	{
		bShowMouseCursor = false;
	}
	else
	{
		bShowMouseCursor = true;
	}
}

