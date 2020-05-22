#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "MapPage.generated.h"

UCLASS()
class UMapPage : public UUserWidget
{
	GENERATED_BODY()
public:
	void NativeConstruct() override;
	void NativeTick(FGeometry const& myGeometry, float const inDeltaTime) override;
	FReply NativeOnMouseButtonDown(FGeometry const& inGeometry, FPointerEvent const& inMouseEvent) override;
	FReply NativeOnMouseButtonUp(FGeometry const& inGeometry, FPointerEvent const& inMouseEvent) override;
	FReply NativeOnMouseMove(FGeometry const& inGeometry, FPointerEvent const& inMouseEvent) override;
	FReply NativeOnMouseWheel(FGeometry const& inGeometry, FPointerEvent const& inMouseEvent) override;
	FReply NativeOnAnalogValueChanged(FGeometry const& inGeometry, FAnalogInputEvent const& inAnalogEvent) override;
protected:
private:
	float mapXValue{0.0f};
	float mapYValue{0.0f};
	float mapZoomValue{0.5f};
	bool isDragging{false};
	bool isZoomingWithRMB{false};

	UPROPERTY(EditAnywhere, Category = "Material Parameters", meta = (AllowPrivateAccess = "true"))
	class UMaterialParameterCollection* parameters;
};