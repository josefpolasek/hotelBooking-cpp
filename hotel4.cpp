/**
 * @file hotel4.cpp
 * @author Josef Polasek (josef.polasek@tuni.fi)
 * @date 26-09-2022
 * @brief Version for grade 4. What was added/changed:
 *        1. even number of rooms between 40-80
 *        2. half of the rooms are single rooms (for 100 euros per night) and the other half are double rooms (150 e)
 *        3. display room type
 *        4. handle all error inputs
 *        5. 0%, 10%, 20% discount on the final price (after reservation)
 *        6. Reservation menu changed:
 *               a) reservation number - random int between 10000-99999
 *               b) reservation name - user's full name (Juha Ranta-Ojala)
*/

/**** LIBRARIES ****/
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
using namespace std;

/**** CONSTANTS ****/
int HOTEL_SIZE;
int SINGLE_ROOM_PRICE = 100; 
int DOUBLE_ROOM_PRICE = 150; 

/**** GLOBAL VARIABLES ****/
int invoice = 0;
string name = "0"; 

/**** STRUCTURES ****/
struct room {
    int number;
    int price;
    bool free;
    bool double_room = false;
};

/**** FUNCTIONS ****/

/* checks whether the string is a number or not */
bool isNumber(string& str) {
    for (char const &c : str)
        if (std::isdigit(c) == 0) return false;
    return true;
}

/* generates our hotel */
void generateHotel(room hotel[]) {
    /* initialize room numbers and price */
    srand(time(0));
    int status = 0;

    for(int i = HOTEL_SIZE/2; i < HOTEL_SIZE; i++)
        hotel[i].double_room = true;

    for (int i = 0; i < HOTEL_SIZE; i++) {
        hotel[i].number = i + 1;

        // price for each type
        if(hotel[i].double_room == false) hotel[i].price = SINGLE_ROOM_PRICE;
        else hotel[i].price = DOUBLE_ROOM_PRICE;
        
        // randomly book some rooms
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
    cout << "These rooms are free: " << endl;

    // single
    cout << "SINGLE: ";
    for (int i = 0; i < HOTEL_SIZE; i++) {
        if (!hotel[i].free || hotel[i].double_room == true) continue;
        
        if (hotel[i].number < 10) cout << "0";
        cout << hotel[i].number << " ";
    }
    cout << endl;

    // double
    cout << "DOUBLE: ";
    for (int i = 0; i < HOTEL_SIZE; i++) {
        if (!hotel[i].free || hotel[i].double_room == false) continue;
        
        if (hotel[i].number < 10) cout << "0";
        cout << hotel[i].number << " ";
    }
    cout << endl;

    cout << endl << endl;
}

/* room reservation system */
void reserveRoom(room hotel[]) {
    int room, nights, action;
    
    do
    {
        if(name == "0") {
            cout << "Before we start, please tell us your name:";
            getline(cin, name);
        }

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
            invoice += hotel[room-1].price * nights;
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

/* finish booking and get a discount */
void finishBooking(room hotel[]) {
    // get a random discount
    srand(time(0));
    int discount =  (rand() % 3) * 10;

    if (discount != 0) {
        cout << endl << "You are lucky today! We have a special discount for you! It's " << discount << " %." << endl << endl;
    }
    
    // get values
    int reservationNum = (rand() % 89999) + 10000;
    float final_price = invoice * (1-(discount/100.0));

    // output
    cout << "Reservation number: " << reservationNum << endl;
    cout << "Name: " << name << endl;
    cout << "Price: " << final_price << " euros." << endl;

    // task 5

    cout << endl << endl;
}

/**** MAIN FUNCTION ****/
int main() {
    /* initialize hotel */
    srand(time(0));
    HOTEL_SIZE = ( (rand() % 20) + 20) * 2; //generates a random number in the range 40-80
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
        cout << "4. finish booking " << endl;
        cout << "0. exit programme" << endl;
        cout << "Please select action: ";
        cin >> input_option;
        cout << endl;

        if (isNumber(input_option)) option = stoi(input_option);
        else option = -1;

        /* by selected option starts a subroutine */
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
            cout << "The invoice is: " << invoice << " euros. | PRICING: single room = " << SINGLE_ROOM_PRICE << " euros/night | " << 
            "double room = " << DOUBLE_ROOM_PRICE << " euros/night" << endl << endl;
            break;
        
        case 4:
            finishBooking(hotel);
            break;
        
        default:
            cout << "Error: incorrect input! Please try again." << endl << endl;
            break;
        }
        
    } while (option != 0);
        
    return 0;
}
