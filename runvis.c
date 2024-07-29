#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <raylib.h>

#include "debug.h"
#include "calendar.h"

int main(int argc, char* argv[]) {	
	const int screenWidth = 800;
	const int screenHeight = 800;
	
	InitWindow(screenWidth, screenHeight, "runvis");
	
	SetTargetFPS(60);
	
	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		
		ShowMouseCoords();
		DrawFPS(0, 0);
		
		//Vector2 pos = GetMousePosition();
		
		DrawCalendar(100, 100, screenWidth - 100, screenHeight - 100);

		EndDrawing();
	}
	
	CloseWindow();
	
    return 0;
}