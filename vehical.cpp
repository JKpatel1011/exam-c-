#include <iostream>
#include <string>
using namespace std;

class Vehicle {
protected:
    string vehicleID;
    string manufacturer;
    string model;
    int year;
    static int totalVehicles;

public:
    Vehicle() : vehicleID(""), manufacturer(""), model(""), year(0) {
        totalVehicles++;
    }

    Vehicle(string id, string manuf, string mod, int yr) : vehicleID(id), manufacturer(manuf), model(mod), year(yr) {
        totalVehicles++;
    }

    ~Vehicle() {
        totalVehicles--;
    }

    static int getTotalVehicles() {
        return totalVehicles;
    }

    string getVehicleID() const { return vehicleID; }
    string getManufacturer() const { return manufacturer; }
    string getModel() const { return model; }
    int getYear() const { return year; }

    void setVehicleID(const string& id) { vehicleID = id; }
    void setManufacturer(const string& manuf) { manufacturer = manuf; }
    void setModel(const string& mod) { model = mod; }
    void setYear(int yr) { year = yr; }
};

int Vehicle::totalVehicles = 0;

class Car : public Vehicle {
protected:
    string fuelType;

public:
    Car() : Vehicle(), fuelType("") {}

    Car(string id, string manuf, string mod, int yr, string fuel)
        : Vehicle(id, manuf, mod, yr), fuelType(fuel) {}

    string getFuelType() const { return fuelType; }
    void setFuelType(const string& fuel) { fuelType = fuel; }
};

class ElectricCar : public Car {
protected:
    int batteryCapacity;

public:
    ElectricCar() : Car(), batteryCapacity(0) {}

    ElectricCar(string id, string manuf, string mod, int yr, string fuel, int battery)
        : Car(id, manuf, mod, yr, fuel), batteryCapacity(battery) {}

    int getBatteryCapacity() const { return batteryCapacity; }
    void setBatteryCapacity(int capacity) { batteryCapacity = capacity; }
};

class Aircraft {
protected:
    int flightRange;

public:
    Aircraft() : flightRange(0) {}

    Aircraft(int range) : flightRange(range) {}

    int getFlightRange() const { return flightRange; }
    void setFlightRange(int range) { flightRange = range; }
};

class FlyingCar : public Car, public Aircraft {
public:
    FlyingCar() : Car(), Aircraft() {}

    FlyingCar(string id, string manuf, string mod, int yr, string fuel, int range)
        : Car(id, manuf, mod, yr, fuel), Aircraft(range) {}

    void displayFlyingCarDetails() {
        cout << "Flying Car Details: " << getVehicleID() << ", " << getManufacturer() 
             << ", " << getModel() << ", Year: " << getYear() 
             << ", Fuel: " << getFuelType() << ", Flight Range: " << getFlightRange() << " km" << endl;
    }
};

class SportsCar : public ElectricCar {
protected:
    int topSpeed;

public:
    SportsCar() : ElectricCar(), topSpeed(0) {}

    SportsCar(string id, string manuf, string mod, int yr, string fuel, int battery, int speed)
        : ElectricCar(id, manuf, mod, yr, fuel, battery), topSpeed(speed) {}

    int getTopSpeed() const { return topSpeed; }
    void setTopSpeed(int speed) { topSpeed = speed; }
};

class Sedan : public Car {
public:
    Sedan(string id, string manuf, string mod, int yr, string fuel) : Car(id, manuf, mod, yr, fuel) {}
};

class SUV : public Car {
public:
    SUV(string id, string manuf, string mod, int yr, string fuel) : Car(id, manuf, mod, yr, fuel) {}
};

class VehicleRegistry {
private:
    Vehicle* vehicles[100];
    int count;

public:
    VehicleRegistry() : count(0) {}

    void addVehicle(Vehicle* v) {
        vehicles[count++] = v;
    }

    void displayVehicles() {
        for (int i = 0; i < count; i++) {
            cout << "Vehicle ID: " << vehicles[i]->getVehicleID() << ", Manufacturer: " 
                 << vehicles[i]->getManufacturer() << ", Model: " 
                 << vehicles[i]->getModel() << ", Year: " << vehicles[i]->getYear() << endl;
        }
    }

    Vehicle* searchById(string id) {
        for (int i = 0; i < count; i++) {
            if (vehicles[i]->getVehicleID() == id)
                return vehicles[i];
        }
        return NULL;
    }
};

int main() {
    VehicleRegistry registry;
    int choice;
    do {
        cout << "1. Add a vehicle\n2. View all vehicles\n3. Search by ID\n4. Exit\n";
        cin >> choice;

        if (choice == 1) {
            string id, manufacturer, model;
            int year;
            cout << "Enter Vehicle ID: ";
            cin >> id;
            cout << "Enter Manufacturer: ";
            cin >> manufacturer;
            cout << "Enter Model: ";
            cin >> model;
            cout << "Enter Year: ";
            cin >> year;

            Vehicle* v = new Vehicle(id, manufacturer, model, year);
            registry.addVehicle(v);
        } else if (choice == 2) {
            registry.displayVehicles();
        } else if (choice == 3) {
            string searchId;
            cout << "Enter Vehicle ID to search: ";
            cin >> searchId;
            Vehicle* v = registry.searchById(searchId);
            if (v != NULL) {
                cout << "Vehicle Found: " << v->getVehicleID() << ", Manufacturer: " 
                     << v->getManufacturer() << ", Model: " << v->getModel() 
                     << ", Year: " << v->getYear() << endl;
            } else {
                cout << "Vehicle not found!" << endl;
            }
        }
    } while (choice != 4);

    return 0;
}

