#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RPGController.generated.h"

UCLASS()
class ARPGController : public APlayerController
{
	GENERATED_BODY()
public:
	ARPGController();
	bool InputKey(FKey Key, EInputEvent EventType, float AmountPressed, bool bGamepad) override;
	void setActivePage(class UUserWidget* const title);
protected:
	void SetupInputComponent() override;
private:
	FKey key;
	TSubclassOf<class UUserWidget> uiBPClass;
	UUserWidget* uiWidget;

	void openMenu();
};
