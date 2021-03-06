#include "pch.h"
#include <iostream>
#include <array>
#include <string>
using namespace std;


// Convert degrees to be between 0 and 359
float normalize_degrees(float degrees) {
	float normal = fmod(degrees, 360);
	if (normal < 0) {
		normal = 360 + normal;
	}
	return normal;
}

// Assume the API data has been neatly unpacked from the json
void calculate_direction(float yaw, float pitch, float roll) {
	string quadrants[4] = {"North", "East", "South", "West"};
	string current_quadrant;
	float normal_yaw;
	float normal_pitch = normalize_degrees(pitch);
	
	// Check to see if the object is facing forward
	if (normal_pitch <= 90 or normal_pitch > 270) {
		normal_yaw = normalize_degrees(yaw);
	}
	else { // Rotate yaw by 180 degrees if it is facing backwards
		normal_yaw = normalize_degrees(yaw + 180);
	}

	// North quadrant
	if (normal_yaw >= 315 or normal_yaw < 45) {
		current_quadrant = quadrants[0]; // North
	}
	// East quadrant
	else if (normal_yaw >= 45 and normal_yaw < 135) {
		current_quadrant = quadrants[1]; // East
	}
	// South quadrant
	else if (normal_yaw >= 135 and normal_yaw < 225) {
		current_quadrant = quadrants[2]; // South
	}
	// West quadrant
	else {
		current_quadrant = quadrants[3]; // West
	}

	cout << "You are "<<normal_yaw<<" degrees "<<current_quadrant<<".\n";
}

// Prompt the user to answer questions about the object orientation
void run_queries(string queries[], float responses[], int const query_size) {
	for (int i = 0; i < query_size; i++) {
		bool valid_input = false;
		while (!valid_input) {
			cout << queries[i];
			cin >> responses[i];
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Flush buffer.
			}
			else {
				cin.clear();
				valid_input = true;
			}
		}
	}
}

// Run the command line interface
void start_CLI() {
	bool keep_running = true;
		while (keep_running) {
		string queries[] = { "Enter yaw: ", "Enter pitch: ", "Enter roll: " };
		int const query_size = sizeof(queries) / sizeof(queries[0]);
		float responses[query_size] = {}; // This array will contain yaw, pitch, and roll.

		run_queries(queries, responses, query_size);
		calculate_direction(responses[0], responses[1], responses[2]);

		bool valid_input = false;
		string retry;
		cout << "Would you like to retry? (y/n): ";
		while (valid_input==false) {
			cin >> retry;
			if (retry == "y") {
				valid_input = true;
			}
			else if (retry == "n") {
				valid_input = true;
				keep_running = false;
			}
			else {
				cout << "Would you like to retry? (y/n): ";
			}
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore until next line.
		}
	}
}

int main()
{
	start_CLI();
	return 0;
}