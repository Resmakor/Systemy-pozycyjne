#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <sstream>

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

void dec_to_any (string number, int base);
int any_to_dec (string number, int base);

string any_BCD_to_dec(string BCD, int BCD_type);
string dec_to_any_BCD(int dec, int BCD_type);

string dec_to_U2(int number);
string dec_to_U1(int number);


int U2_to_dec (string U2);
int U1_to_dec(string U1);


// TODO
// string dec_to_IEEE754(int number);
// include floating numbers. f.ex 101,10 (2);

int main()
{
    //cout << dec_to_any(123.4, 2) << endl;
   // cout << any_BCD_to_dec(dec_to_any_BCD(123, 3), 3) << endl;
   // cout << dec_to_U2(-37) << endl;
    // cout << U1_to_dec("1101");
    dec_to_any("123,13131232132", 2);
} 

void dec_to_any (string number, int base)
{

    int comma_position = number.find(',');

    if (comma_position != string::npos)
    {   
        string left = number.substr(0, comma_position);
        stringstream geek1(left);
        int left_dec = 0;
        geek1 >> left_dec;


        string right = "0." + number.substr(comma_position + 1, number.size() - 1);
        stringstream geek2(right);
        float right_float = 0;
        geek2 >> right_float;
        cout << left_dec << ' ' << right_float << endl;

       
        string left_converted = "";
        bool minus = false;

         if (left_dec < 0)
        {
            minus = true;
            left_dec *= (-1);
        }

        while (left_dec != 0)
        {
            int add = left_dec % base;
            if (add > 9)
            {
                left_converted = letters[add] + left_converted;
            }

            else
            {
                left_converted = to_string(add) + left_converted;
            }
            left_dec /= base;
        }

        if (minus)
        {
            left_converted = "-" + left_converted;
        }

        cout << left_converted << endl;


        int digits_counter = 0;

        string right_converted = "";
        float current_right = base * right_float;

        while(digits_counter != 20)
        {
            string current_right_string = to_string(current_right);
            int dot_position = current_right_string.find(".");

            string left_fl;
            string right_fl;

            left_fl = current_right_string.substr(0, dot_position);

            right_fl = current_right_string.substr(dot_position + 1, current_right_string.size() - 1);


            // UWAGA NA > 9
            if (left_fl.size() > 1)
            {
                stringstream to_int(left_fl);
                int num;
                to_int >> num;
                string letter = letters[num];
                right_converted += letter;
            }

            else
            {
                right_converted += left_fl;
            }
            

            right_fl = "0." + right_fl;
            cout << right_fl << endl;
            stringstream str_to_float(right_fl);

            str_to_float >> current_right;
            current_right *= base;

            digits_counter++;

            bool only_zeros = true;
            for(int i = 0; i < right_fl.size(); i++)
            {
                if (right_fl[i] != '0' || right_fl[i] != '.')
                {
                    only_zeros = false;
                }

            }

            if (only_zeros)
            {
                break;
            }
        }
        cout << left_converted << "," <<  right_converted << endl;
         
    }

   
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

/*string any_BCD_to_dec(string BCD, int BCD_type)
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

int U2_to_dec (string U2)
{
    int dec = 0;
    int size = U2.size();
    int potega = pow(2, size - 1);
    if (U2[0] == '1')
    {
        dec += potega * (-1);
    }
    potega /= 2;

    for (int i = 1; i < size; i++)
    {
        if (U2[i] == '1')
        {
            dec += potega;
        }
        potega /= 2;
    }
    return dec;
}

int U1_to_dec(string U1)
{
    return U2_to_dec(U1) + 1;
}*/