//Simple example of a finite state machine. Garage door will open or close based on the series of commands.

#include <iostream>
#include <vector>
#include <string>
#include <fstream>


struct garageDoor {
	garageDoor() {};
	bool Open = false;
	bool Closed = false;
	bool Opening = false;
	bool Closing = false;
	std::string Status = "CLOSED";
	std::string State(garageDoor& gd) { return "Door: " + gd.Status + "\n"; }
	void Clicked(garageDoor& gd);
	void Complete(garageDoor& gd);
};

void garageDoor::Clicked(garageDoor& gd) {
	if (gd.Status == "OPEN" || gd.Status == "OPENING") {
		gd.Open = false;
		gd.Closed = false;
		gd.Opening = false;
		gd.Closing = true;
		gd.Status = "CLOSING";
	}
	else {
		gd.Open = false;
		gd.Closed = false;
		gd.Opening = true;
		gd.Closing = false;
		gd.Status = "OPENING";
	}
}

void garageDoor::Complete(garageDoor& gd) {
	if (gd.Status == "OPENING") {
		gd.Open = true;
		gd.Closed = false;
		gd.Opening = false;
		gd.Closing = false;
		gd.Status = "OPEN";
	}
	else if (gd.Status == "CLOSING") {
		gd.Open = false;
		gd.Closed = true;
		gd.Opening = false;
		gd.Closing = false;
		gd.Status = "CLOSED";
	}
	else {
		if (gd.Status == "OPEN")
			std::cout << "Error: Door is already open." << std::endl;
		if (gd.Status == "CLOSED")
			std::cout << "Error: Door is already closed." << std::endl;
	}
}

int main() {
	garageDoor Door = garageDoor();
	std::ifstream instructions;
	std::string line;

	instructions.open("Instructions.txt");
	if (instructions.is_open()) {
		while (std::getline(instructions, line)) {
			std::cout << Door.State(Door);
			if (line == "button_clicked") {
				Door.Clicked(Door);
				std::cout << "< Button clicked.\n";
			}
			else if (line == "cycle_complete") {
				Door.Complete(Door);
				std::cout << "< Cycle complete.\n";
			}
			else {
				std::cout << "Error: Unknown Command." << std::endl;
			}
		}
	}
	else {
		std::cout << "Error: File could not be opened.";
	}

	std::cout << Door.State(Door);
	std::cin.get();
	return 0;
}