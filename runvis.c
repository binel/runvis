#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <raylib.h>

#define BUFFER_SIZE 1024

#define MAX_COORDS 1000

typedef struct {
	double lat;
	double lon;
} Coordinates;

Coordinates* parse_gpx(char* filename);
Coordinates parse_coords_from_line(const char* line);

int main(int argc, char* argv[]) {

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return 1;
	}
	
	Coordinates* coords = parse_gpx(argv[1]);

	const int screenWidth = 800;
	const int screenHeight = 800;
	
	InitWindow(screenWidth, screenHeight, "Test");
	
	SetTargetFPS(60);
	
	while(!WindowShouldClose()) {
		BeginDrawing();
		
		ClearBackground(BLACK);
		int lastxpos = 800 - (int)round((coords[0].lat - 41.7) * 10000);
		int lastypos = 800 - (int)round(fabs(coords[0].lon + 91.6) * 10000);
		for (int i = 1; i < MAX_COORDS; i++)
		{
			if (coords[i].lat == 0 && coords[i].lon == 0)
			{
				break;
			}
			int xpos = 800 - (int)round((coords[i].lat - 41.7) * 10000);
			int ypos = 800- (int)round(fabs(coords[i].lon + 91.6) * 10000);
			

			//TraceLog(LOG_INFO, "%d,%d", xpos, ypos);
			DrawLine(lastypos, lastxpos, ypos, xpos, RED);
			lastxpos = xpos;
			lastypos = ypos;
		}
		
		EndDrawing();
	}
	
	free(coords);
	CloseWindow();
	
    return 0;
}

// extremely bad gpx parsing :) 

Coordinates* parse_gpx(char* filename) {
	Coordinates* coords = malloc(MAX_COORDS * sizeof(Coordinates));
	int coordCount = 0;
	FILE* file = fopen(filename, "r");
	
	char buffer[BUFFER_SIZE];
	while (fgets(buffer, BUFFER_SIZE, file)) {
		if (strstr(buffer, "<trkpt")) {
			coords[coordCount++] = parse_coords_from_line(buffer);
			
			if (coordCount >= MAX_COORDS) { 
				break;
			}
		}
	}
	
	fclose(file);
	return coords;
}

Coordinates parse_coords_from_line(const char* line) {
    const char* lat_start = strstr(line, "lat=\"");
    const char* lon_start = strstr(line, "lon=\"");

	Coordinates loc;

    if (lat_start != NULL && lon_start != NULL) {
        lat_start += 5;  // Move past "lat=\""
        lon_start += 5;  // Move past "lon=\""

        char latitude[20];
        char longitude[20];
        
        int i = 0;
        while (*lat_start != '\"' && i < 19) {
            latitude[i++] = *lat_start++;
        }
        latitude[i] = '\0';

        i = 0;
        while (*lon_start != '\"' && i < 19) {
            longitude[i++] = *lon_start++;
        }
        longitude[i] = '\0';
        char* endptr; 
        
        loc.lat = strtod(latitude, &endptr);
        loc.lon = strtod(longitude, &endptr);
    }
    
    return loc;
}

