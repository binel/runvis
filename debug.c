#include "debug.h"

void ShowMouseCoords() {
	char mouseStr[20];
	Vector2 mousePosition = GetMousePosition();
	sprintf(mouseStr, "%.2f, %.2f", mousePosition.x, mousePosition.y);
	DrawText(mouseStr, 10, 10, 16, WHITE);
}