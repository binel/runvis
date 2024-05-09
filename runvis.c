#include <stdio.h>
#include <raylib.h>


int main() {
	const int screenWidth = 800;
	const int screenHeight = 800;
	
	InitWindow(screenWidth, screenHeight, "Test");
	
	SetTargetFPS(60);
	
	while(!WindowShouldClose()) {
		BeginDrawing();
		
		ClearBackground(RAYWHITE);
		DrawText("Hello World", 200, 200, 20, LIGHTGRAY);
		
		EndDrawing();
	}
	
	CloseWindow();

    return 0;
}
