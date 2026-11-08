#include <iostream>
#include <iomanip>
#include <limits>
#include <cctype>

// AI-assisted implementation developed with OpenAI ChatGPT.

// Read and validate the journey distance
double readDistance() {
    double miles;

    while (true) {
        std::cout << "Enter journey distance in miles: ";

        if (std::cin >> miles && miles >= 0 &&
            miles <= 1000000) {
            return miles;
        }

        std::cout << "Invalid distance. Please try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Ask the user to select a valid fuel type
char selectFuel() {
    char fuel;

    while (true) {
        std::cout << "Choose fuel type (P = Petrol, D = Diesel): ";

        if (std::cin >> fuel) {
            fuel = static_cast<char>(
                std::toupper(static_cast<unsigned char>(fuel))
            );

            if (fuel == 'P' || fuel == 'D') {
                return fuel;
            }
        }

        std::cout << "Invalid fuel selection. Enter P or D.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Calculate CO2 emissions based on fuel type
double estimateEmissions(double miles, char fuel) {
    const double consumptionRate = 9.66;
    const double petrolFactor = 2.31;
    const double dieselFactor = 2.68;

    double litres = (miles / 100.0) * consumptionRate;

    if (fuel == 'P') {
        return litres * petrolFactor;
    }

    return litres * dieselFactor;
}

int main() {
    std::cout << "====================================\n";
    std::cout << "      JOURNEY CO2 CALCULATOR\n";
    std::cout << "====================================\n\n";

    double distance = readDistance();
    char fuelType = selectFuel();

    double result = estimateEmissions(distance, fuelType);

    std::cout << "\n========== JOURNEY REPORT ==========\n";
    std::cout << "Distance travelled: " << distance << " miles\n";
    std::cout << "Fuel selected: "
              << (fuelType == 'P' ? "Petrol" : "Diesel") << "\n";

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Estimated CO2 emissions: "
              << result << " kg\n";

    std::cout << "====================================\n";

    return 0;
}