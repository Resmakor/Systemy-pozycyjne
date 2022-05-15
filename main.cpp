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

string dec_to_any (int number, int base);
int any_to_dec (string number, int base);

string any_BCD_to_dec(string BCD, int BCD_type);
string dec_to_any_BCD(int dec, int BCD_type);

string dec_to_U2(int number);
string dec_to_U1(int number);



// TODO:
// int U2_to_dec (string U2);
// int U1_to_dec(string U1);


int main()
{
    cout << dec_to_any_BCD(123, 3) << endl;
    cout << any_BCD_to_dec(dec_to_any_BCD(123, 3), 3) << endl;
    cout << dec_to_U2(-37) << endl;
    cout << dec_to_U1(-113) << endl;
} 

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

string any_BCD_to_dec(string BCD, int BCD_type)
{
    string dec = "";
    int BCD_size = BCD.size();
    int power = 8;
    int sum = 0;
    for (int i = 0; i < BCD_size; i++)
    {
        if (BCD[i] == '1')
        {
            sum += power;
        }

        power /= 2;
        if ((i + 1) % 4 == 0 and i != 0)
        {
            dec += to_string(sum - BCD_type);
            sum = 0;
            power = 8; 
        }
    }
    return dec;
}

string dec_to_any_BCD(int dec, int BCD_type)
{
    string converted = "";
    while(dec > 0)
    {
        string part = "";
        part = dec_to_any((dec % 10) + BCD_type, 2);
        while(part.size() % 4 != 0)
        {
            part = '0' + part;
        }
        converted = part + converted;
        dec /= 10;
    }
    return converted;
}

string dec_to_U2(int number)
{
    if (number >= 0)
    {
        return '0' + dec_to_any(number, 2);       
    }

    string bin;
    bin = '0' + dec_to_any((-1) * number, 2);
    int LS1_index = 0;
    int counter = bin.size() - 1;

    while (bin[counter] != '1')
    {
        counter -= 1;
    }
    string U2 = "";
    LS1_index = counter;
    for (int i = 0; i < LS1_index; i++)
    {
        if (bin[i] == '0')
        {
            U2 += "1";
        }
        else
        {
            U2 += "0";
        }
    }

    for (int i = LS1_index; i < bin.size(); i++)
    {
        U2 += bin[i];
    }
    return U2;
}

string dec_to_U1(int number)
{
    if (number >= 0)
    {
        return '0' + dec_to_any(number, 2);       
    }

    string bin = '0' + dec_to_any((-1) * number, 2);
    string U1 = "";

    for (int i = 0; i < bin.size(); i++)
    {
        if (bin[i] == '0')
        {
            U1 += "1";
        }

        else
        {
            U1 += "0";
        }
    }
    return U1;
}   
