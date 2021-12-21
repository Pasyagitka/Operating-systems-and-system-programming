#include <iostream>
#include <ctime>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    int i = 0;
    clock_t start= clock();
    while (true)
    {
        i++;
        clock_t end = clock();
        clock_t d = (end - start);
        if (d == 5000)  {
            cout << "5 c: " << i << endl;
        }
        if (d == 10000) {
            cout << "10 c: " << i << endl;
        }
        if (d == 15000) {
            cout << "15 c: " << i << endl; 
            break;
        }
    }
    cout << "Result: " << i << endl;
}