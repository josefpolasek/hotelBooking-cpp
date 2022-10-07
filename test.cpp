#include <iostream>
using namespace std;

struct room {
    int number;
    int price;
    bool free;
    bool double_room = false;
};

//////////////////////////////

#include <vector>

struct reservation {
    int resNumber;
    string name;
    int invoice;
    vector <room> rooms;
};

int main(void) {
    vector <reservation> reservation;

    return 0;
}
