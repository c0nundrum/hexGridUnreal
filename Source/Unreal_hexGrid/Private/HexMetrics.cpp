#include "HexMetrics.h"

float HexMetrics::outerRadius = 100.0f;
float HexMetrics::innerRadius = outerRadius * 0.866025404;

FVector HexMetrics::corners[] = {
				FVector(0.0, outerRadius, 0.0),
				FVector(innerRadius, 0.5 * outerRadius, 0.0),
				FVector(innerRadius, -0.5 * outerRadius,  0.0),
				FVector(0.0, -outerRadius, 0.0),
				FVector(-innerRadius, -0.5 * outerRadius, 0.0),
				FVector(-innerRadius, 0.5 * outerRadius, 0.0),
				FVector(0.0, outerRadius, 0.0)
		};	