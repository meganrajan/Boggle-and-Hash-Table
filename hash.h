#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }

    HASH_INDEX_T operator()(const std::string& k) const {
            HASH_INDEX_T w[5] = {0};
            int segment_length = 6;

            // Start processing from the end of the string
            int n = k.length();
            int segments = (n + segment_length - 1) / segment_length; // Compute number of segments

            for (int i = 0; i < segments; ++i) {
                HASH_INDEX_T power_of_36 = 1;
                int segment_end = n - i * segment_length;
                int segment_start = std::max(0, segment_end - segment_length);

                for (int pos = segment_end - 1; pos >= segment_start; --pos) {
                    char c = std::tolower(k[pos]);
                    HASH_INDEX_T value = letterDigitToNumber(c);
                    int index = 4 - i; // Correct index calculation
                    w[index] += value * power_of_36;
                    power_of_36 *= 36;
                }
            }

            // Calculate the final hash value using the r values
            HASH_INDEX_T hash_value = 0;
            for (int i = 0; i < 5; ++i) {
                hash_value += rValues[i] * w[i];
            }

            return hash_value;
    }


    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        // int HASH_INDEX_T result = letter - '0' + 1;
        // return result;

        letter = std::tolower(letter);

        if(std::isalpha(letter)) {
            return letter - 'a';
        }
        else if(std::isdigit(letter)) {
            return letter - '0' + 26;
        }
        else {
            return 0;
        }
        
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
