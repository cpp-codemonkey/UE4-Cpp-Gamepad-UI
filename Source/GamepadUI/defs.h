#pragma once
#include "Math/Color.h"

FLinearColor const unhighlightedColor{0.046875f, 0.046875f, 0.046875f, 1.0f};
FLinearColor const highlightedColor{0.103417f, 0.199653f, 0.091603f, 1.0f};

FLinearColor const questHighlightedColor{0.954166f, 0.855158f, 0.0894526f, 1.0f};
FLinearColor const questUnhighlightedColor{0.954166f, 0.855158f, 0.0894526f, 0.0f};

float const mapDimension{1024};
float const minHalfMapDimension{-mapDimension / 2.0f};
float const maxHalfMapDimension{mapDimension / 2.0f};
float const dragScale{2.0f};
float const wheelScale{-0.1f};
float const wheelMin{0.1f};
float const wheelMax{1.0f};
float const rmbDragScale{0.01};
float const rmbMinDrag{wheelMin};
float const rmbMaxDrag{wheelMax};

float const analogXScale{5.0f};
float const analogYScale{-analogXScale};
float const analogZoomMin{0.1f};
float const analogZoomMax{1.0f};
float const analogZoomScale{-0.005};