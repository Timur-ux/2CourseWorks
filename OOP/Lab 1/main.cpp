#include "brackets_check.h"

using namespace std;

int main(int argc, char * argw[])
{
    string s;
    getline(cin, s);
    cout << (brackets_check(s) ? "correct" : "incorrect") << endl;
    return 0;
}