#define MAX_STRLEN 32
#define DEBUG false
#include<iostream>
#include<string>
#include<vector>

using namespace std;

const string letters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

inline int
AsciiToBase(char letter) {
    for(int i = 0; i < letters.size(); ++i) {
        if(letters[i] == letter) return i;
    }
    return -1;
}

inline int
power(int base, int power) {

    for(int i = 0; i < power; ++i) {
        base *= base;
    }

    return base;
}

int
main(void) {

    //Pre-configuration
    //std::ios_base::sync_with_stdio(false);

    //Variables
    string raw_string;
    int    target_base;
    int    source_base;
    long int    temp_factor = 1;
    long int    temp_sum    = 0;
    int    temp_convert_result;
    string output;


    //Prompt for input
    printf("Enter your raw number: ");
    cin>>raw_string;
    printf("Please enter the source base:");
    cin>>source_base;
    printf("Enter the target base: (Max support: %d): ", letters.size());
    cin>>target_base;

    //Parsing phase 1
    for(int i = raw_string.size()-1; i >= 0; --i ) {

        temp_convert_result = AsciiToBase(raw_string[i]);

        if(temp_convert_result != -1) {
#if DEBUG
            printf("%d\n",temp_convert_result);
#endif
            temp_sum += (temp_convert_result * temp_factor);
            temp_factor *= source_base;
        }
        else {
            printf("Convert failed at letter %d, please double-check your input and try again.\n", i);
            return 0;
        }

    }

    //Start making the output
    for(int i = 0; i < MAX_STRLEN; ++i) {

        //Skip calculation for improving time complexity even though this is already O(n)
        if(temp_sum <= target_base) {
            output += '1';
            break;
        }
        else {
            output += letters[temp_sum % target_base];
            temp_sum /= target_base;
        }
    }

    //Reversing the output
    for(int i = 0; i < (output.size()/ 2); ++i) {
        swap(output[i], output[output.size()-1-i]);
    }

    printf("Input: %s\n"
           "Target base: %d\n"
           "Output: %s\n",raw_string.c_str(),target_base,output.c_str());
    return 0;

};