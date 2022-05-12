#include <iostream>
#include <string>
#include <map>

using namespace std;

map <int, string> letters = {
    {10, "A"},
    {11, "B"},
    {12, "C"},
    {13, "D"},
    {14, "E"},
    {15, "F"}
};

map <string, int> values = {
    {"A", 10},
    {"B", 11},
    {"C", 12},
    {"D", 13},
    {"E", 14},
    {"F", 15}
};


string dec_to_any (int number, int base)
{
    string converted = "";
    while (number != 0)
    {
        int add = number % base;
        if (add > 9)
        {
            converted = letters[add] + converted;
        }
        else
        {
            converted = to_string(add) + converted;
        }
        number /= base;
    }
    return converted;
}

int any_to_dec (string number, int base)
{
    int counter = 0; int dec = 0; int power = 1; int size = number.size();
    
    while (size - counter - 1 >= 0)
    {
        if (number[size - counter - 1] >= 'A')
        {
            string letter = "";
            letter = number[size - counter - 1];
            int value = values[letter];
            dec += value * power;
        }
        
        else
        {
            dec += (int(number[size - counter - 1]) - 48)  * power;
        }
        counter++;
        power *= base; 
    }
    return dec;
}

int main()
{
    cout << dec_to_any(123, 16) << endl;
    cout << any_to_dec(dec_to_any(123, 16), 16) << endl;
}
