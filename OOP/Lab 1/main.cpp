#include "isBracketsValid.h"

using namespace std;

int main(int argc, char * argw[])
{
    string s;
    getline(cin, s);
    if(isBracketsValid(s)) {
        cout << "Brackets is valid" << endl;
    } else {
        cout << "Brackets is invalid, kek" << endl;
    }
    return 0;
}