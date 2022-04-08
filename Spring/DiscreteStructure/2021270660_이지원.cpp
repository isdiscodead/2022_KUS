#include <iostream>
using namespace std;

// floor -> greatest integer less than or equal x 
int myFloor(double num) {
    // 정수 input check 
    if ( int(num) == num ) {
        return int(num);
    } else {
        return num < 0 ? int(num)-1 : int(num);
    }
}

// ceiling -> least integer greater than or equal x
int myCeiling(double num) {
        // 정수 input check 
    if ( int(num) == num ) {
        return int(num);
    } else {
        return num < 0 ? int(num) : int(num)+1;
    }
}

int main( void ) {
    // 음수 check
    cout << "floor -1.3 = " << myFloor(-1.3) << endl;
    cout << "ceiling -1.3 = " << myCeiling(-1.3) << endl;
    // 양수 check
    cout << "floor 2.8 = " << myFloor(2.8) << endl;
    cout << "ceiling 2.8 = " << myCeiling(2.8) << endl;
    // 음의 정수 check
    cout << "floor -9 = " << myFloor(-9) << endl;
    cout << "ceiling -9 = " << myCeiling(-9) << endl;
    // 양의 정수 check 
    cout << "floor 6 = " << myFloor(6) << endl;
    cout << "ceiling 6 = " << myCeiling(6) << endl;
    // 0 check 
    cout << "floor 0 = " << myFloor(0) << endl;
    cout << "ceiling 0 = " << myCeiling(0) << endl;
    return 0;
}