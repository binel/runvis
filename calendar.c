#include "calendar.h" 

void DrawCalendar(int xpos, int ypos, int width, int height) {

	int startingX = xpos;
	int boxSize = (width / 7) - 1;

	for (int week = 0; week < 10; week++) {
		for (int day = 0; day < 6; day++) {
			DrawRectangleLines(xpos, ypos, boxSize, boxSize, WHITE);
			xpos += boxSize + 1;
		}
		ypos += boxSize + 1;
		xpos = startingX;
	}
}