#include <bits/stdc++.h>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace std::chrono;

class Vehicle {
public:
    string number;
    string type;   // Car/Bike
    system_clock::time_point entryTime;

    Vehicle(string num, string t) {
        number = num;
        if (t == "C" || t == "car" || t == "Car") type = "Car";
        else if (t == "B" || t == "bike" || t == "Bike") type = "Bike";
        entryTime = system_clock::now();
    }

    string getEntryTime() {
        time_t et = system_clock::to_time_t(entryTime);
        string s = ctime(&et);
        s.pop_back(); // remove newline
        return s;
    }
};

class ParkingLot {
    int capacity;
    vector<Vehicle*> slots;

public:
    ParkingLot(int cap) {
        capacity = cap;
        slots.resize(capacity, nullptr);
    }

    void parkVehicle(string num, string type) {
        // Validate vehicle type
        if (!(type == "C" || type == "car" || type == "Car" ||
              type == "B" || type == "bike" || type == "Bike")) {
            cout << "Invalid Vehicle Type! Enter only 'Car/C' or 'Bike/B'.\n";
            return;
        }

        for (int i = 0; i < capacity; i++) {
            if (slots[i] == nullptr) {
                slots[i] = new Vehicle(num, type);
                cout << "Vehicle " << num << " (" << slots[i]->type
                     << ") parked at slot " << i + 1 << endl;
                cout << "Entry Time: " << slots[i]->getEntryTime() << endl;
                return;
            }
        }
        cout << "Parking Full! No slot available.\n";
    }

    void exitVehicle(string num) {
        for (int i = 0; i < capacity; i++) {
            if (slots[i] != nullptr && slots[i]->number == num) {
                auto exitTime = system_clock::now();
                time_t exitt = system_clock::to_time_t(exitTime);

                // Duration in hours (with decimals)
                duration<double> diff = exitTime - slots[i]->entryTime;
                double hours = diff.count() / 3600.0;
                if (hours < 1) hours = 1; // Minimum 1 hour charge

                double rate = (slots[i]->type == "Car") ? 30 : 15;
                double bill = hours * rate;

                cout << "Vehicle " << num << " (" << slots[i]->type
                     << ") exited from slot " << i + 1 << endl;
                cout << "Entry Time: " << slots[i]->getEntryTime() << endl;
                cout << "Exit Time: " << ctime(&exitt);
                cout << fixed << setprecision(2);
                cout << "Duration: " << hours << " hour(s)\n";
                cout << "Bill Amount: Rs." << bill << endl;

                delete slots[i];
                slots[i] = nullptr;
                return;
            }
        }
        cout << "Vehicle not found!\n";
    }

    void displayStatus() {
        cout << "\n Parking Lot Status:\n";
        for (int i = 0; i < capacity; i++) {
            if (slots[i] != nullptr) {
                cout << "Slot " << i + 1 << ": " << slots[i]->number
                     << " (" << slots[i]->type << "), "
                     << "Entry: " << slots[i]->getEntryTime() << endl;
            } else {
                cout << "Slot " << i + 1 << ": [Empty]\n";
            }
        }
    }
};

int main() {
    int n;
    cout << "Enter total parking slots: ";
    cin >> n;

    ParkingLot p(n);
    int choice;
    string num, type;

    do {
        cout << "\n===== SMART PARKING SYSTEM =====\n";
        cout << "1. Park Vehicle\n2. Exit Vehicle\n3. Display Status\n4. Exit Program\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Vehicle Number: ";
            cin >> num;
            cout << "Enter Vehicle Type (Car/C or Bike/B): ";
            cin >> type;
            p.parkVehicle(num, type);
            break;

        case 2:
            cout << "Enter Vehicle Number: ";
            cin >> num;
            p.exitVehicle(num);
            break;

        case 3:
            p.displayStatus();
            break;

        case 4:
            cout << "Exiting Program... Goodbye!\n";
            break;

        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
