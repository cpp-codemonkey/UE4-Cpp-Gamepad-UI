#include "MapPage.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Materials/MaterialParameterCollection.h"
#include "Kismet/KismetMathLibrary.h"
#include "defs.h"

void UMapPage::NativeConstruct()
{
	UUserWidget::NativeConstruct();
	bIsFocusable = true;
}

void UMapPage::NativeTick(FGeometry const& myGeometry, float const inDeltaTime)
{
	UUserWidget::NativeTick(myGeometry, inDeltaTime);
	if (UMaterialParameterCollectionInstance* instance = GetWorld()->GetParameterCollectionInstance(parameters))
	{
		instance->SetScalarParameterValue("Zoom", mapZoomValue);
		instance->SetScalarParameterValue("X", mapXValue);
		instance->SetScalarParameterValue("Y", mapYValue);
	}
}

FReply UMapPage::NativeOnMouseButtonDown(FGeometry const& inGeometry, FPointerEvent const& inMouseEvent)
{
	isDragging = inMouseEvent.IsMouseButtonDown(FKey("LeftMouseButton"));
	isZoomingWithRMB = inMouseEvent.IsMouseButtonDown(FKey("RightMouseButton"));
	return FReply::Handled();
}

FReply UMapPage::NativeOnMouseButtonUp(FGeometry const& inGeometry, FPointerEvent const& inMouseEvent)
{
	isDragging = inMouseEvent.IsMouseButtonDown(FKey("LeftMouseButton"));
	isZoomingWithRMB = inMouseEvent.IsMouseButtonDown(FKey("RightMouseButton"));
	return FReply::Handled();
}

FReply UMapPage::NativeOnMouseMove(FGeometry const& inGeometry, FPointerEvent const& inMouseEvent)
{
	if (isDragging)
	{
		auto const delta = inMouseEvent.GetCursorDelta();
		mapXValue = UKismetMathLibrary::FClamp(mapXValue + delta.X * dragScale, minHalfMapDimension, maxHalfMapDimension);
		mapYValue = UKismetMathLibrary::FClamp(mapYValue + delta.Y * dragScale, minHalfMapDimension, maxHalfMapDimension);
	}
	else if (isZoomingWithRMB)
	{
		auto const delta = inMouseEvent.GetCursorDelta();
		mapZoomValue = UKismetMathLibrary::FClamp(mapZoomValue + delta.Y * rmbDragScale, rmbMinDrag, rmbMaxDrag);
	}
	return FReply::Handled();
}

FReply UMapPage::NativeOnMouseWheel(FGeometry const& inGeometry, FPointerEvent const& inMouseEvent)
{
	float const delta = inMouseEvent.GetWheelDelta();
	mapZoomValue = UKismetMathLibrary::FClamp(mapZoomValue + delta * wheelScale, wheelMin, wheelMax);
	return FReply::Handled();
}

FReply UMapPage::NativeOnAnalogValueChanged(FGeometry const& inGeometry, FAnalogInputEvent const& inAnalogEvent)
{
	auto const axisName = inAnalogEvent.GetKey().GetDisplayName().ToString();
	float const valueX = inAnalogEvent.GetAnalogValue() * analogXScale;
	float const valueY = inAnalogEvent.GetAnalogValue() * analogYScale;
	if (axisName == "Gamepad Left Thumbstick X-Axis" && !FMath::IsNearlyEqual(valueX, 0.0f, 0.1f))
	{
		mapXValue = UKismetMathLibrary::FClamp(mapXValue + valueX, minHalfMapDimension, maxHalfMapDimension);
		return FReply::Handled();
	}
	else if (axisName == "Gamepad Left Thumbstick Y-Axis" && !FMath::IsNearlyEqual(valueY, 0.0f, 0.1f))
	{
		mapYValue = UKismetMathLibrary::FClamp(mapYValue + valueY, minHalfMapDimension, maxHalfMapDimension);
		return FReply::Handled();
	}
	else if (axisName == "Gamepad Right Thumbstick Y-Axis")
	{
		float const value = inAnalogEvent.GetAnalogValue() * analogZoomScale;
		mapZoomValue = UKismetMathLibrary::FClamp(mapZoomValue + value, analogZoomMin, analogZoomMax);
		return FReply::Handled();
	}

	return FReply::Unhandled();
}
