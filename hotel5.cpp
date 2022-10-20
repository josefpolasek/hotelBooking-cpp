/**
 * @file hotel5.cpp
 * @author Josef Polasek (josef.polasek@tuni.fi)
 * @date 20-10-2022
 * @brief Version for grade 5. What was added/changed:
 *          1. clear a console
 *          2. create a database of reservations (input + print)
 *          3. reservations generated by a computer (before user's input)
 *          4. searching in reservations by 
 *              a) booking number
 *              b) name
*/

/**** LIBRARIES ****/
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <iomanip>
using namespace std;

/**** CONSTANTS ****/
int HOTEL_SIZE;
int SINGLE_ROOM_PRICE = 100; 
int DOUBLE_ROOM_PRICE = 150;

/* output widths */
int numberW = 15, 
    nameW = 25,
    invoiceW = 15,
    lineLength = 69;

/* arrays for generating random names */
const string firstNames [33] = {"Adam", "Alex", "Aaron", "Ben", "Carl", "Dan", "David", "Edward", "Fred", "Frank", "George", "Hal", "Hank", "Ike", "John", "Jack", "Joe", "Larry", "Monte", "Matthew", "Mark", "Nathan", "Otto", "Paul", "Peter", "Roger", "Roger", "Steve", "Thomas", "Tim", "Ty", "Victor", "Walter"};
const string lastNames [150] = {"Anderson", "Ashwoon", "Aikin", "Bateman", "Bongard", "Bowers", "Boyd", "Cannon", "Cast", "Deitz", "Dewalt", "Ebner", "Frick", "Hancock", "Haworth", "Hesch", "Hoffman", "Kassing", "Knutson", "Lawless", "Lawicki", "Mccord", "McCormack", "Miller", "Myers", "Nugent", "Ortiz", "Orwig", "Ory", "Paiser", "Pak", "Pettigrew", "Quinn", "Quizoz", "Ramachandran", "Resnick", "Sagar", "Schickowski", "Schiebel", "Sellon", "Severson", "Shaffer", "Solberg", "Soloman", "Sonderling", "Soukup", "Soulis", "Stahl", "Sweeney", "Tandy", "Trebil", "Trusela", "Trussel", "Turco", "Uddin", "Uflan", "Ulrich", "Upson", "Vader", "Vail", "Valente", "Van Zandt", "Vanderpoel", "Ventotla", "Vogal", "Wagle", "Wagner", "Wakefield", "Weinstein", "Weiss", "Woo", "Yang", "Yates", "Yocum", "Zeaser", "Zeller", "Ziegler", "Bauer", "Baxster", "Casal", "Cataldi", "Caswell", "Celedon", "Chambers", "Chapman", "Christensen", "Darnell", "Davidson", "Davis", "DeLorenzo", "Dinkins", "Doran", "Dugelman", "Dugan", "Duffman", "Eastman", "Ferro", "Ferry", "Fletcher", "Fietzer", "Hylan", "Hydinger", "Illingsworth", "Ingram", "Irwin", "Jagtap", "Jenson", "Johnson", "Johnsen", "Jones", "Jurgenson", "Kalleg", "Kaskel", "Keller", "Leisinger", "LePage", "Lewis", "Linde", "Lulloff", "Maki", "Martin", "McGinnis", "Mills", "Moody", "Moore", "Napier", "Nelson", "Norquist", "Nuttle", "Olson", "Ostrander", "Reamer", "Reardon", "Reyes", "Rice", "Ripka", "Roberts", "Rogers", "Root", "Sandstrom", "Sawyer", "Schlicht", "Schmitt", "Schwager", "Schutz", "Schuster", "Tapia", "Thompson", "Tiernan", "Tisler"};

/**** GLOBAL VARIABLES ****/
int resNum;
int invoice = 0;
string name = "0"; 

/**** STRUCTURES ****/

/* basic unit of the hotel */
struct room {
    int number;
    int price;
    bool free;
    bool double_room = false;
};

/* struct for keeping reservation information */
struct reservation {
    int number;
    string name;
    int invoice = 0;
    vector <room> rooms;
};

/* global vector variables */
vector <int> resNumbers;
vector <reservation> resList;
vector <room> roomsRes;

/**** FUNCTIONS ****/
/* checks whether the string is a number or not */
bool isNumber(string& str) {
    for (char const &c : str)
        if (std::isdigit(c) == 0) return false;
    return true;
}

/* clears console */
void clearConsole(int height = 60) {
    // temporary solution
    for (int i = 0; i < height; i++)
        cout << endl;
}

/* generates a random name using these arrays */
string randomName() {
    string f, l;

    f = firstNames[rand() % 33];
    l = lastNames[rand() % 150];

    return f + " " + l;
}

/* generates a random name using these arrays */
int randomResNum() {
    int num;
    bool con;
    
    do {
        num = (rand() % 89999) + 10000;
        for (int i = 0; i < resNumbers.size(); i++) {
            if(num == resNumbers[i]) {
                con = true;
                break;
            }
        }
        con = false;
    } while (con == true);

    return num;
}

/* return a list of rooms */
string getRoomList (vector <room> rooms) {    
    string roomList = "[";
    for (int i = 0; i < rooms.size(); i++) {
        if (rooms[i].number < 10) roomList += "0";
        roomList += to_string(rooms[i].number);

        if (i+1 == rooms.size()) roomList += "]";
        else roomList += ", ";
    }

    return roomList;
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

/* generates computer reservations */
void generateReservations(room hotel[]) {
    for(int i = 0; i < HOTEL_SIZE; i++) {
        if(hotel[i].free == true) continue; // ignore free rooms

        // room
        int roomPrice = hotel[i].price;
        int roomNumber = hotel[i].number;

        // reservation
        reservation res;
        res.number = randomResNum();
        res.name = randomName();
        res.invoice = roomPrice;

        // push rooms
        res.rooms.push_back(hotel[i]);

        // multiple rooms
        while (i+1 != HOTEL_SIZE && rand() % 2 == 1) {
            res.rooms.push_back(hotel[++i]);
            res.invoice += hotel[i].price;
        }

        res.invoice *= rand() % 7 + 1;

        // push this to reservations
        resList.push_back(res);
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
    clearConsole();
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

    cout << endl << endl;
}

/* prints one reservation */
void printRes(reservation res) {
    cout 
        << " "
        << left << setw(numberW) << res.number
        << left << setw(nameW) << res.name
        << left << setw(invoiceW) << res.invoice  
        << left << getRoomList(res.rooms)
        << endl; 
}

/* prints the whole list of reservations */
void printResList() {
    cout 
        << left << setw(numberW) << "RESERVATION"
        << left << setw(nameW) << "RESERVATION NAME"
        << left << setw(invoiceW) << "INVOICE"
        << left << "RESERVED ROOMS"
        << endl;
    
    for (int i=0; i<lineLength; i++) cout << "-";
        cout<< endl;

    for (int i = 0; i < resList.size(); i++) 
        printRes(resList[i]);
}

/* prints reservation(s) with a given reservation number */
void findResNum() {
    // clearConsole();

    int num;
    cout << "Please write the number: ";
    cin >> num;
    cout << endl << endl;

    for (int i = 0; i < resList.size(); i++) {
        if (resList[i].number == num) {
            cout << "We found this reservation: " << endl;
            printRes(resList[i]);
            cout << endl;
            return;
        }
    }

    cout << "We couldn't find any reservation." << endl << endl;
}

/* prints reservation(s) with a given name */
void findResName() {
    // clearConsole();

    string findName;
    cout << "Please write the name: ";
    getline(cin >> ws, findName);
    cout << endl << endl;

    bool already = false;
    for (int i = 0; i < resList.size(); i++) {
        if (!resList[i].name.find(findName)) {
            if(already == false) {
                cout << "We found this reservation: " << endl;
                already = true;
            }
            printRes(resList[i]);
            cout << endl;
            return;
        }
    }

    if(already == false) cout << "We couldn't find any reservation." << endl;

    cout << endl;
    return;
}

/* finds a reservation by number or name */
int findReservation(bool fromList) {
    if (fromList == false) clearConsole();

    cout << "FIND A RESERVATION BY:" << endl;
    cout << "1. number" << endl;
    cout << "2. name" << endl;
    cout << "0. exit" << endl;
    cout << "action: ";
    
    int action;
    cin >> action;
    cout << endl;
    if (action == 1) findResNum();
    else if (action == 2) findResName();

    // select another action
    cout << "Select action:" << endl;
    cout << "1. go back to main menu" << endl;
    cout << "2. view reservations" << endl;
    cout << "3. make a reservation" << endl << endl;
    cout << "action: ";
    cin >> action;
    cout << endl; 

    return action;
}

/* shows available rooms */
int seeAvailableRooms (room hotel[]) {
    printFreeRooms(hotel);

    int action;
    
    cout << "Select action:" << endl;
    cout << "1. go back to main menu" << endl;
    cout << "2. see a database of reservations" << endl;
    cout << "3. make a reservation" << endl << endl;
    cout << "action: ";
    cin >> action;
    cout << endl; 

    return action;
}

/* shows available rooms */
int seeInvoice () {
    clearConsole();
    cout << "The invoice is: " << invoice << " euros. | PRICING: single room = " << SINGLE_ROOM_PRICE << " euros/night | " << 
            "double room = " << DOUBLE_ROOM_PRICE << " euros/night" << endl << endl;

    int action;
    
    cout << "Select action:" << endl;
    cout << "1. go back to main menu" << endl;
    cout << "2. see a database of reservations" << endl;
    cout << "3. make a reservation" << endl;
    cout << "4. finish booking" << endl << endl;
    cout << "action: ";
    cin >> action;
    cout << endl; 

    return action;
}

/* room reservation system */
void reserveRoom(room hotel[]) {
    int room, nights, action;
    reservation res;
    
    if(name == "0") {
        clearConsole(60);
        cout << "Before we start, please tell us your name: ";
        getline(cin >> ws, name);
        resNum = randomResNum();
    }

    do {
        clearConsole();

        cout << "ROOM RESERVATION SYSTEM" << endl;
        printFreeRooms(hotel);
        cout << "Book a room: ";
        cin >> room;
        cout << endl;

        if(room < 1 || room > 50) cout << "This room doesn't exist! Please select a different number." << endl << endl;
        // else if (hotel[room-1].free == false) cout << "This room is booked. Pleaes select a different one." << endl << endl;
        else if (hotel[room-1].free == false) cout << "THIS ROOM IS BOOKED. PLEAES SELECT A DIFFERENT ONE." << endl << endl;
        else {
            hotel[room-1].free = false;
            roomsRes.push_back(hotel[room-1]);
            cout << "Select the number of nights: ";
            cin >> nights;

            invoice += hotel[room-1].price * nights;
            cout << "Your invoice is: " << invoice << " euros." << endl;
            cout << endl;
        }

        cout << "Do you want to continue?" << endl;
        cout << "1. yes" << endl;
        cout << "0. no" << endl << endl;
        cout << "action: ";
        cin >> action;
        cout << endl;

    } while (action == 1);
    
}

/* finish booking and get a discount */
int finishBooking(room hotel[]) {
    clearConsole();

    // check if reservation was done
    if (name == "0" or invoice == 0) {
        cout << "You have to make a reservation first!" << endl << endl;
    } else {

        // get a random discount
        srand(time(0));
        int discount =  (rand() % 3) * 10;
        if (discount != 0) cout << endl << "You are lucky today! We have a special discount for you! It's " << discount << " %." << endl << endl;
        
        // get values 
        // reservation res = resList.back();

        float final_price = invoice * (1-(discount/100.0));

        // output
        cout << "Reservation number: " << resNum << endl;
        cout << "Name: " << name << endl;
        cout << "Price: " << final_price << " euros." << endl;
        cout << "Rooms: " << getRoomList(roomsRes) << endl << endl;

        // push this to reservations
        reservation res;
        res.number = resNum;
        res.name = name;
        res.invoice = final_price;
        res.rooms = roomsRes;
        resList.push_back(res);

        // clear cache
        name = "0";
        invoice = 0;
    }

    // select another action
    int action;
    cout << "Select action:" << endl;
    cout << "1. go back to main menu" << endl;
    cout << "2. see a database of reservations" << endl;
    cout << "3. make a reservation" << endl << endl;
    cout << "action: ";
    cin >> action;
    cout << endl; 

    return action;
}

int viewReservations() {
    clearConsole();
    printResList();
    cout << endl << endl;

    // select another action
    int action;
    cout << "Select action:" << endl;
    cout << "1. go back to main menu" << endl;
    cout << "2. find a reservation" << endl;
    cout << "3. make a reservation" << endl << endl;
    cout << "action: ";
    cin >> action;
    cout << endl; 

    return action;
}

/**** MAIN FUNCTION ****/
int main() {
    /* initialize hotel */
    srand(time(0));
    HOTEL_SIZE = ( (rand() % 20) + 20) * 2; //generates a random number in the range 40-80
    room hotel [HOTEL_SIZE];
    generateHotel(hotel);
    generateReservations(hotel);

    string input_option;
    int option;

    do
    {   
        clearConsole();

        /* console menu */
        cout << "HOTEL RESERVATION SYSTEM" << endl;
        cout << "1. book a room" << endl;
        cout << "2. see available rooms " << endl;
        cout << "3. see invoice " << endl;
        cout << "4. finish booking " << endl;
        cout << "5. view reservations " << endl;
        cout << "6. find a reservation " << endl;
        cout << "0. exit programme" << endl << endl;
        cout << "Please select action: ";
        cin >> input_option;
        cout << endl;

        if (isNumber(input_option)) option = stoi(input_option);
        else option = -1;

        // for case 2
        int next = 0;

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
            next = seeAvailableRooms(hotel);
            break;

        case 3:
            next = seeInvoice();
            break;
        
        case 4:
            next = finishBooking(hotel);
            break;

        case 5:
            next = viewReservations();
            break;

        case 6:
            next = findReservation(false);
            break;
        
        default:
            cout << "Error: incorrect input! Please try again." << endl << endl;
            break;
        }
        do {
            if (next == 2) {
                if (option == 5) findReservation(true);
                else viewReservations();
            }
            else if(next == 3) reserveRoom(hotel);
            else if (next == 4) finishBooking(hotel);
        } while(next >= 2);

    } while (option != 0);
        
    return 0;
}
