#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <raylib.h>

#define BUFFER_SIZE 1024

typedef struct {
	double lat;
	double lon;
	struct Coordinates* next;
} Coordinates;

typedef struct {
	double maxLat;
	double minLat; 
	double maxLon;
	double minLon;
} RunBounds;

Coordinates* parse_gpx(char* filename);
Coordinates* parse_coords_from_line(const char* line);
RunBounds get_bounding_box(Coordinates* coords);

int main(int argc, char* argv[]) {

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return 1;
	}
	
	Coordinates* curCoord = parse_gpx(argv[1]);
	Coordinates* firstCoord = curCoord;
	
	RunBounds box = get_bounding_box(firstCoord);
	const int screenWidth = 800;
	const int screenHeight = 800;
	const int padding = 25;
	double latRange = box.maxLat - box.minLat;
	double lonRange = box.maxLon - box.minLon;
	
	double degreePerPixel;
	
	if (latRange > lonRange){
		degreePerPixel = latRange / (screenWidth - (padding * 2));
	}
	else {
		degreePerPixel = lonRange / (screenHeight - (padding * 2));
	}
	
	
	//double lonPerPixel = 
	
	//printf("latRange: %f, lonRange: %f",latRange, lonRange);
	
	InitWindow(screenWidth, screenHeight, "Test");
	
	SetTargetFPS(60);
	
	while(!WindowShouldClose()) {
		BeginDrawing();
		
		ClearBackground(BLACK);
		int lastxpos = (screenWidth - padding) - (int)round((box.maxLat - curCoord->lat) / degreePerPixel);
		int lastypos = (screenHeight - padding) - (int)round((box.maxLon - curCoord->lon) / degreePerPixel);
		while(curCoord->next != NULL)
		{
			if (curCoord->lat == 0 && curCoord->lon == 0)
			{
				break;
			}
			int xpos = (screenWidth - padding) - (int)round((box.maxLat - curCoord->lat) / degreePerPixel);
			int ypos = (screenWidth - padding) - (int)round((box.maxLon - curCoord->lon) / degreePerPixel);
			
			DrawLine(lastypos, lastxpos, ypos, xpos, RED);
			lastxpos = xpos;
			lastypos = ypos;
			curCoord = curCoord->next;
		}
		curCoord = firstCoord;
		EndDrawing();
	}
	
	//free(coords);
	CloseWindow();
	
    return 0;
}

// extremely bad gpx parsing :) 

Coordinates* parse_gpx(char* filename) {
	Coordinates* curCord; 
	Coordinates* firstCord;
	FILE* file = fopen(filename, "r");
	
	char buffer[BUFFER_SIZE];
	while (fgets(buffer, BUFFER_SIZE, file)) {
		if (strstr(buffer, "<trkpt")) {
			if (curCord == NULL)
			{
				curCord = parse_coords_from_line(buffer);
				firstCord = curCord;
			}
			else 
			{
				curCord->next = parse_coords_from_line(buffer);
				curCord = curCord->next;
			}
		}
	}
	
	fclose(file);
	return firstCord;
}

Coordinates* parse_coords_from_line(const char* line) {
    const char* lat_start = strstr(line, "lat=\"");
    const char* lon_start = strstr(line, "lon=\"");

	Coordinates* loc = malloc(sizeof(Coordinates));
	
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
        
        loc->lat = strtod(latitude, &endptr);
        loc->lon = strtod(longitude, &endptr);
    }
    
    return loc;
}

RunBounds get_bounding_box(Coordinates* coords) {
	RunBounds box;
	
	box.maxLat = coords->lat;
	box.minLat = coords->lat;
	box.maxLon = coords->lon;
	box.minLon = coords->lon;
	
	coords = coords->next;
	
	while(coords->next != NULL) {
		if (coords->lat > box.maxLat)
		{
			box.maxLat = coords->lat;
		}
		
		if (coords->lat < box.minLat)
		{
			box.minLat = coords->lat;
		}
		
		if (coords->lon > box.maxLon)
		{
			box.maxLon = coords->lon;
		}
		
		if (coords->lon < box.minLon)
		{
			box.minLon = coords->lon;
		}
		
		coords = coords->next;
	}
	
	return box;
}