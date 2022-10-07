#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    // cout
    cout << "cout" << endl;
    // cin
    cout << "请输入两个整数:";
    int num_01;
    int num_02;
    cin >> num_01 >> num_02;
    cout << "num_01: " << num_01 << "; num_02: " << num_02 << endl;
    // cerr
    cerr << "cerr" << endl;
    // clog
    clog << "clog" << endl;
    return 0;
}
