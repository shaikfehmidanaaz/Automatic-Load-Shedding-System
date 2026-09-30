#include <iostream>
#include <vector>
using namespace std;

class LoadSheddingSystem {
private:
    double availablePower;
    vector<double> loadPower;
    vector<bool> loadStatus;

public:
    LoadSheddingSystem(double power, vector<double> loads) {
        availablePower = power;
        loadPower = loads;
        loadStatus.resize(loads.size(), true);
    }

    void checkAndShedLoads() {
        double totalLoad = 0;

        for (double load : loadPower) {
            totalLoad += load;
        }

        cout << "Available Power: " << availablePower << " kW" << endl;
        cout << "Total Load: " << totalLoad << " kW" << endl;

        // If load is within available power
        if (totalLoad <= availablePower) {
            cout << "\nSystem Status: NORMAL" << endl;
            cout << "No load shedding required." << endl;
            return;
        }

        cout << "\nSystem Status: OVERLOAD" << endl;
        cout << "Automatic load shedding started..." << endl;

        // Shed loads from the last load first
        for (int i = loadPower.size() - 1; i >= 0; i--) {

            if (totalLoad <= availablePower)
                break;

            loadStatus[i] = false;
            totalLoad -= loadPower[i];

            cout << "Load " << i + 1
                 << " (" << loadPower[i] << " kW) disconnected."
                 << endl;
        }

        cout << "\nRemaining Load: " << totalLoad << " kW" << endl;

        if (totalLoad <= availablePower)
            cout << "System stabilized successfully." << endl;
        else
            cout << "Critical overload! More action required." << endl;
    }

    void displayStatus() {
        cout << "\n----- LOAD STATUS -----" << endl;

        for (int i = 0; i < loadPower.size(); i++) {
            cout << "Load " << i + 1 << " : "
                 << loadPower[i] << " kW - ";

            if (loadStatus[i])
                cout << "CONNECTED";
            else
                cout << "DISCONNECTED";

            cout << endl;
        }
    }
};

int main() {

    double availablePower;
    int numberOfLoads;

    cout << "===== AUTOMATIC LOAD SHEDDING SYSTEM =====" << endl;

    cout << "Enter available power (kW): ";
    cin >> availablePower;

    cout << "Enter number of loads: ";
    cin >> numberOfLoads;

    vector<double> loads(numberOfLoads);

    for (int i = 0; i < numberOfLoads; i++) {
        cout << "Enter power of Load " << i + 1 << " (kW): ";
        cin >> loads[i];
    }

    LoadSheddingSystem system(availablePower, loads);

    cout << endl;

    system.checkAndShedLoads();
    system.displayStatus();

    return 0;
}
