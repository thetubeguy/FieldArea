// FieldArea.cpp
// Author:  Adrian Hallas
// Date:    11th March 2024

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

class Field {

    public:
        virtual void set_side(int, int) = 0;
        virtual string calculate_area(void) = 0;
        virtual int get_num_sides(void) = 0;
        int get_one_side(int);
};

int Field:: get_one_side(int side)
{
    bool non_digit_detected;
    string side_length_str;
    int side_length;

    do
    {
        non_digit_detected = false;
        cout << "Please enter length of side " << side + 1 << " in metres: ";

        // Read value as a string, sanitise, and then convert to integer

        getline(cin, side_length_str);

        for (int char_count = 0; (char_count < side_length_str.length()) && ((non_digit_detected == false)); char_count++)
        {
            if (!isdigit(side_length_str[char_count]))
            {
                non_digit_detected = true;
                cout << "Please only enter integers \n";
            }

        }

        // Check that side length is >= 0
        stringstream(side_length_str) >> side_length;
        if (!(side_length >= 1) && !(non_digit_detected))
        {
            cout << "Side lengths must be greater than 0 \n";
            non_digit_detected = true;
        }

    } while (non_digit_detected == true);

    return side_length;
}

class Triangular_Field : public Field {
    
    static const int num_sides = 3;
    int my_sides[num_sides];
    
    public:
        int get_num_sides(void);
        void set_side(int, int);
        string calculate_area(void);
};

int Triangular_Field::get_num_sides()
{
    return num_sides;
}

void Triangular_Field::set_side(int side_number, int length)
{
    my_sides[side_number] = length;
}

string Triangular_Field::calculate_area(void)
{
    float s = 0;
    float terms_total = 1;
    int area = 0;
    stringstream area_stream;
    string area_string;

    // The sum of 2 sides must be larger than the third

    sort(my_sides, my_sides + num_sides);
    if (my_sides[2] >= (my_sides[0] + my_sides[1]))
    {
        return "The sum of 2 sides must be larger than the third \n";
    }

    // The semi-perimeter of triangle ABC = s = (a + b + c)/2 

    for (int side = 0; side < num_sides; side++)
        s += my_sides[side]; 

    s /= 2;

    // Then, the area of triangle ABC = √[s × (s – a) × (s – b) × (s – c)].

    for (int term_num = 0; term_num < num_sides; term_num++)
        terms_total *= (s - my_sides[term_num]);
      
    terms_total *= s;

    area_stream << round(sqrt(terms_total));
    area_stream >> area_string;

    return "The area of the field is: " + area_string  + " square metres \n";
}

int main()
{
    do
    {
        Triangular_Field fieldA;
        int side_length = 0;

        for (int side = 0; side < fieldA.get_num_sides(); side++)
        {
            side_length = fieldA.get_one_side(side);
            fieldA.set_side(side, side_length);
        }

        cout << "\n" << fieldA.calculate_area() << "\n";
        cout << "Enter to continue.  'q' then Enter to quit.\n";
    } while(getchar() != 0x71);
   
    return 0;
}

