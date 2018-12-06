/* ==================================================================================================================

wordBuilder.cpp
    Prompts a user for a numeric input (absolute value <= 2,147,483,647) and outputs that number in English words

================================================================================================================== */
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int number;
    int digit;
    int place;

    bool last_number_teen;
    bool negative;

    string number_in_words = "";
    string number_names[10] = {"","one","two","three","four","five","six","seven","eight","nine"};
    string tens_places[10]  = {"","ten","twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};
    string teen_names[10]   = {"","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
    string higher_places[5] = {"","thousand","million","billion"};

    while(1)
    {
        cout << "Enter a number: ";
        cin >> number;

        /* Reset variables for each new number */
        place = 0;
        number_in_words = "";
        last_number_teen = false;
        negative = false;

        /* The "negative" prefix must be added last, so save this flag for when after text is created */
        if( number < 0 )
        {
            negative = true;
            number *= -1;
        }

        while( number != 0 )
        {
            /* Grabs the right-most digit */
            digit = number % 10;

            /* Insert modifier for higher order numbers (ie- hundred, thousand, etc) */
            if( place % 3 == 0 && number % 1000 != 0 )
            {
                number_in_words = " " + higher_places[ place / 3 ] + number_in_words;
            }

            if( digit != 0 )
            {
                if( place % 3 == 0 )
                {
                    /* If the next digit it a "1", use naming convention for teen numbers (excluding "ten").
                    Otherwise, just use the name of the digit */
                    if( number % 10 == 1 )
                    {
                        number_in_words = " " + teen_names[digit] + number_in_words;
                        last_number_teen = true;
                    }
                    else
                    {
                        number_in_words = " " + number_names[digit] + number_in_words;
                        last_number_teen = false;
                    }
                }
                /* Only insert a "tens" digit if a "teen" number was not inserted (i.e.- "ten" is not used if "eleven" was added). */
                else if( place % 3 == 1 && last_number_teen == false )
                {
                    number_in_words = " " + tens_places[digit] + number_in_words;
                }
                else if( place % 3 == 2 )
                {
                    number_in_words = " " + number_names[digit] + " hundred" + number_in_words;
                }
            }

            /* Right-shift number */
            number /= 10;
            place += 1;
        }

        if( negative == true )
        {
            number_in_words = "negative" + number_in_words;
        }

        cout << number_in_words.substr(1) << "\n";
    }

    return 0;
}
