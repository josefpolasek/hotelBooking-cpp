/**
 * @file hotel1.cpp
 * @author Josef Polasek (josef.polasek@tuni.fi)
 * @date 03-09-2022
 * @brief Simpliest version of the assignment.
 */

/**** LIBRARIES ****/
#include <iostream>
#include <string>
using namespace std;

/**** CONSTANTS ****/
int HOTEL_SIZE = 50;
int ROOM_PRICE = 100; // euros

/**** GLOBAL VARIABLES ****/
int invoice = 0;

/**** STRUCTURES ****/
struct room {
    int number;
    bool free  = true;
    int price = ROOM_PRICE;
};

/**** FUNCTIONS ****/

/* prints all information of all the rooms */
void printAllRooms (room hotel[]) {
    for (int i = 0; i < HOTEL_SIZE; i++) {

        cout << "Room number ";
        
        if (hotel[i].number < 10) cout << "0";
        cout << hotel[i].number << " " << endl;

        cout << "Status: ";
        if(hotel[i].free == true) cout << "free" << endl;
        else cout << "booked" << endl;

        cout << "Price: " << hotel[i].price << endl;
        cout << endl;
    }
}

/* prints room numbers of the free rooms */
void printFreeRooms (room hotel[]) {
    cout << "These rooms are free: ";

    for (int i = 0; i < HOTEL_SIZE; i++) {
        if (!hotel[i].free) continue;
        
        if (hotel[i].number < 10) cout << "0";
        cout << hotel[i].number << " ";
    }
    cout << endl << endl;
}

/* room reservation system */
void reserveRoom(room hotel[]) {
    int room, nights, action;

    do
    {
        cout << "ROOM RESERVATION SYSTEM" << endl;
        printFreeRooms(hotel);
        cout << "Book a room: ";
        cin >> room;
        cout << endl;

        if(room < 1 || room > 50) cout << "This room doesn't exist! Please select a different number." << endl;
        else if (hotel[room-1].free == false) cout << "This room is booked. Pleaes select a different one." << endl;
        else {
            hotel[room-1].free = false;
            cout << "Select the number of nights: ";
            cin >> nights;
            invoice += ROOM_PRICE * nights;
            cout << endl;
        }

        cout << "Do you want to continue?" << endl;
        cout << "1. yes" << endl;
        cout << "0. no" << endl;
        cout << "action: ";
        cin >> action;
        cout << endl;

    } while (action == 1);
    
}

/**** MAIN FUNCTION ****/
int main() {
    room hotel [HOTEL_SIZE];

    /* initialize room numbers */
    for (int i = 0; i < HOTEL_SIZE; i++)
        hotel[i].number = i + 1;

    int option = -1;
    do
    {
        // cout << option << endl;

        /* console menu */
        cout << "HOTEL RESERVATION SYSTEM" << endl;
        cout << "1. book a room" << endl;
        cout << "2. see available rooms " << endl;
        cout << "3. see invoice " << endl;
        cout << "0. exit programme" << endl;
        cout << "Please select action: ";
        cin >> option;
        cout << endl;

        // cout << option;

        switch (option)
        {
        case 0:
            // just break
            break;
        
        case 1:
            reserveRoom(hotel);
            break;

        case 2:
            printFreeRooms(hotel);
            break;

        case 3:
            cout << "The invoice is: " << invoice << " euros." << endl << endl;
            break;
        
        default:
            cout << "Error: incorrect input! Please try again." << endl << endl;
            break;
        }
        
    } while (option != 0);
        
    return 0;
}
