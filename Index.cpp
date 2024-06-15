#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class Passenger {
public:
    string name;
    int id;

    Passenger(string name, int id) : name(name), id(id) {}
};

class Flight {
public:
    string flightNumber;
    string departure;
    string arrival;
    int totalSeats;
    int availableSeats;
    list<Passenger> passengers;

    Flight(string flightNumber, string departure, string arrival, int totalSeats)
        : flightNumber(flightNumber), departure(departure), arrival(arrival), totalSeats(totalSeats), availableSeats(totalSeats) {}
};

class FlightReservationSystem {
private:
    list<Flight> flights;
    int passengerIdCounter;

public:
    FlightReservationSystem() : passengerIdCounter(0) {}

    void addFlight(string flightNumber, string departure, string arrival, int totalSeats) {
        flights.push_back(Flight(flightNumber, departure, arrival, totalSeats));
        cout << "Flight added successfully." << endl;
    }

    void viewFlights() {
        for (const auto& flight : flights) {
            cout << "Flight Number: " << flight.flightNumber
                 << ", Departure: " << flight.departure
                 << ", Arrival: " << flight.arrival
                 << ", Available Seats: " << flight.availableSeats << endl;
        }
    }

    void bookTicket(string flightNumber, string passengerName) {
        for (auto& flight : flights) {
            if (flight.flightNumber == flightNumber && flight.availableSeats > 0) {
                flight.passengers.push_back(Passenger(passengerName, ++passengerIdCounter));
                flight.availableSeats--;
                cout << "Ticket booked successfully for " << passengerName << endl;
                return;
            }
        }
        cout << "Flight not found or no available seats." << endl;
    }

    void cancelTicket(string flightNumber, int passengerId) {
        for (auto& flight : flights) {
            if (flight.flightNumber == flightNumber) {
                for (auto it = flight.passengers.begin(); it != flight.passengers.end(); ++it) {
                    if (it->id == passengerId) {
                        flight.passengers.erase(it);
                        flight.availableSeats++;
                        cout << "Ticket cancelled successfully." << endl;
                        return;
                    }
                }
            }
        }
        cout << "Flight or passenger not found." << endl;
    }

    void searchFlights(string departure, string arrival) {
        for (const auto& flight : flights) {
            if (flight.departure == departure && flight.arrival == arrival) {
                cout << "Flight Number: " << flight.flightNumber
                     << ", Departure: " << flight.departure
                     << ", Arrival: " << flight.arrival
                     << ", Available Seats: " << flight.availableSeats << endl;
            }
        }
    }
};

int main() {
    FlightReservationSystem system; // Initialize the flight reservation system

    system.addFlight("AI101", "New York", "London", 200);
    system.addFlight("AI102", "Los Angeles", "Tokyo", 300);

    int choice;
    string flightNumber, passengerName, departure, arrival;
    int passengerId;

    while (true) {
         // Display menu options
        cout << "\n1. Add Flight\n2. View Flights\n3. Book Ticket\n4. Cancel Ticket\n5. Search Flights\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice; // Read user choice

        switch (choice) {
            case 1:  // Add Flight
                cout << "Enter Flight Number: ";
                cin >> flightNumber;
                cout << "Enter Departure: ";
                cin >> departure;
                cout << "Enter Arrival: ";
                cin >> arrival;
                cout << "Enter Total Seats: ";
                int totalSeats;
                cin >> totalSeats;
                system.addFlight(flightNumber, departure, arrival, totalSeats);// Call addFlight method
                break;
            case 2:
                system.viewFlights();
                break;
            case 3: // Book Ticket
                cout << "Enter Flight Number: ";
                cin >> flightNumber;
                cout << "Enter Passenger Name: ";
                cin >> passengerName;
                //cout << "Enter Passenger ID: ";
               // cin >> passengerId;

                system.bookTicket(flightNumber, passengerName);// Call bookTicket method
                break;
            case 4: // Cancel Ticket
                cout << "Enter Flight Number: ";
                cin >> flightNumber;
                cout << "Enter Passenger ID: ";
                cin >> passengerId;
                system.cancelTicket(flightNumber, passengerId);// Call cancelTicket method
                break;
            case 5: // Search Flights
                cout << "Enter Departure: ";
                cin >> departure;
                cout << "Enter Arrival: ";
                cin >> arrival;
                system.searchFlights(departure, arrival);  // Call searchFlights method

                break;
            case 6:// Exit
                return 0;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}
