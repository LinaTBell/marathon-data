#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

const int NUM_DAYS = 7;

struct Runner {
    std::string name;
    std::vector<int> milesPerDay;
    int totalMiles;
    double averageMiles;

    Runner(const std::string& n) : name(n), milesPerDay(NUM_DAYS, 0), totalMiles(0), averageMiles(0.0) {}
};

void readDataFromFile(const std::string& filename, std::vector<Runner>& runners) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        exit(1);
    }

    std::string name;
    while (file >> name) {
        Runner runner(name);
        for (int i = 0; i < NUM_DAYS; ++i) {
            if (!(file >> runner.milesPerDay[i])) {
                std::cerr << "Error: Invalid data format in file." << std::endl;
                exit(1);
            }
        }
        runners.push_back(runner);
    }

    file.close();
}

void calculateTotalsAndAverage(std::vector<Runner>& runners) {
    for (Runner& runner : runners) {
        int totalMiles = 0;
        for (int miles : runner.milesPerDay) {
            totalMiles += miles;
        }
        runner.totalMiles = totalMiles;
        runner.averageMiles = static_cast<double>(totalMiles) / NUM_DAYS;
    }
}

void outputResults(const std::vector<Runner>& runners) {
    std::cout << std::setw(15) << "Runner";
    for (int i = 1; i <= NUM_DAYS; ++i) {
        std::cout << std::setw(10) << "Day " << i;
    }
    std::cout << std::setw(10) << "Total" << std::setw(10) << "Average" << std::endl;

    for (const Runner& runner : runners) {
        std::cout << std::setw(15) << runner.name;
        for (int miles : runner.milesPerDay) {
            std::cout << std::setw(10) << miles;
        }
        std::cout << std::setw(10) << runner.totalMiles << std::setw(10) << std::fixed << std::setprecision(2) << runner.averageMiles << std::endl;
    }
}

int main() {
    std::vector<Runner> runners;

    readDataFromFile("runners.txt", runners);

    calculateTotalsAndAverage(runners);

    outputResults(runners);

    return 0;
}
