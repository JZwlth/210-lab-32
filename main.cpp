#include <iostream>
#include <deque>
#include <cstdlib>
#include <ctime>
#include "Car.h"

using namespace std;

const int INITIAL_MIN_SIZE = 1;
const int INITIAL_MAX_SIZE = 3;
const int NUM_LANES = 4;
const int SIMULATION_TIME = 20;

const int PROB_PAID = 46;
const int PROB_JOINED = 39;
const int PROB_SWITCH = 15;

struct Operation {
    string type;
    Car car;
};

int main() {
    srand(static_cast<unsigned>(time(0)));

    deque<Car> lanes[NUM_LANES];

    // Initialize lanes with 1-3 cars
    for (int i = 0; i < NUM_LANES; i++) {
        int num_cars = rand() % (INITIAL_MAX_SIZE - INITIAL_MIN_SIZE + 1) + INITIAL_MIN_SIZE;
        for (int j = 0; j < num_cars; j++) {
            lanes[i].push_back(Car());
        }
    }

    // Display initial queue
    cout << "Initial queue:\n";
    for (int i = 0; i < NUM_LANES; i++) {
        cout << "Lane " << i + 1 << ":\n";
        if (lanes[i].empty()) {
            cout << "    empty\n";
        } else {
            for (auto &car : lanes[i]) {
                cout << "    ";
                car.print();
            }
        }
    }
    cout << endl;

    for (int time = 1; time <= SIMULATION_TIME; time++) {
        Operation operations[NUM_LANES];
        // Initialize operations
        for (int i = 0; i < NUM_LANES; i++) {
            operations[i].type = "";
        }

        // Process each lane
        for (int i = 0; i < NUM_LANES; i++) {
            if (lanes[i].empty()) {
                int operation = rand() % 100 + 1;
                if (operation <= 50) {
                    // New car joins
                    Car newCar;
                    lanes[i].push_back(newCar);
                    operations[i].type = "Joined";
                    operations[i].car = newCar;
                } else {
                    operations[i].type = "No action";
                }
            } else {
                int operation = rand() % 100 + 1;
                if (operation <= PROB_PAID) {
                    Car paidCar = lanes[i].front();
                    lanes[i].pop_front();
                    operations[i].type = "Paid";
                    operations[i].car = paidCar;
                } else if (operation <= PROB_PAID + PROB_JOINED) {
                    Car newCar;
                    lanes[i].push_back(newCar);
                    operations[i].type = "Joined";
                    operations[i].car = newCar;
                } else {
                    Car switchCar = lanes[i].back();
                    lanes[i].pop_back();

                    // Choose a random lane that's not the original lane
                    int newLane;
                    do {
                        newLane = rand() % NUM_LANES;
                    } while (newLane == i);

                    lanes[newLane].push_back(switchCar);

                    operations[i].type = "Switched";
                    operations[i].car = switchCar;
                }
            }
        }

        // Display operations
        cout << "Time: " << time << endl;
        for (int i = 0; i < NUM_LANES; i++) {
            if (operations[i].type == "Paid" || operations[i].type == "Joined" || operations[i].type == "Switched") {
                cout << "Lane: " << i + 1 << " " << operations[i].type << ": ";
                operations[i].car.print();
            }
        }

        // Display queues
        for (int i = 0; i < NUM_LANES; i++) {
            cout << "Lane " << i + 1 << " Queue:\n";
            if (lanes[i].empty()) {
                cout << "    empty\n";
            } else {
                for (auto &car : lanes[i]) {
                    cout << "    ";
                    car.print();
                }
            }
        }
        cout << endl;
    }

    return 0;
}
