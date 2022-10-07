/**
 * @file hotel3.cpp
 * @author Josef Polasek (josef.polasek@tuni.fi)
 * @date 05-09-2022
 * @brief Version for grade 3. What was added:
 *        1. random number of rooms in a hotel (between 30 and 70)
 *        2. random price for each room (80 to 100)
 *        3. random availability of the room
 *        4. non-numbers input check
 */

/**** LIBRARIES ****/
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
using namespace std;

/**** CONSTANTS ****/
int HOTEL_SIZE;
int ROOM_PRICE; // euros

/**** GLOBAL VARIABLES ****/
int invoice = 0;

/**** STRUCTURES ****/
struct room {
    int number;
    int price;
    bool free;
};

/**** FUNCTIONS ****/

/* checks whether the string is a number or not */
bool isNumber(string& str) {
    for (char const &c : str)
        if (std::isdigit(c) == 0) return false;
    return true;
}

void generateHotel(room hotel[]) {
    /* initialize room numbers and price */
    srand(time(0));
    int status = 0;

    for (int i = 0; i < HOTEL_SIZE; i++) {
        hotel[i].number = i + 1;
        hotel[i].price = ROOM_PRICE;
        
        status = (rand() % 2);

        if (status == 1) hotel[i].free = false;
        else hotel[i].free = true;
    }
}

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

        if(room < 1 || room > 50) cout << "This room doesn't exist! Please select a different number." << endl << endl;
        else if (hotel[room-1].free == false) cout << "This room is booked. Pleaes select a different one." << endl << endl;
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
    /* initialize hotel */
    srand(time(0));
    HOTEL_SIZE = 30 + (rand() % 40);
    ROOM_PRICE = 80 + (rand() % 20);
    room hotel [HOTEL_SIZE];
    generateHotel(hotel);

    string input_option;
    int option;

    do
    {
        /* console menu */
        cout << "HOTEL RESERVATION SYSTEM" << endl;
        cout << "1. book a room" << endl;
        cout << "2. see available rooms " << endl;
        cout << "3. see invoice " << endl;
        cout << "0. exit programme" << endl;
        cout << "Please select action: ";
        cin >> input_option;
        cout << endl;

        if (isNumber(input_option)) option = stoi(input_option);
        else option = -1;

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
            cout << "The invoice is: " << invoice << " euros. | Price for one room is: " << ROOM_PRICE << " euros." << endl << endl;
            break;
        
        default:
            cout << "Error: incorrect input! Please try again." << endl << endl;
            break;
        }
        
    } while (option != 0);
        
    return 0;
}
