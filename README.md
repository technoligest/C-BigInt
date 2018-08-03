# C++ Multiple Precision Integer Library Implementation (Fully Tested)
## Motivation
When using Python, we do not have to worry about representation of integers or types as Python inherintly supports multi-percision arithmetic, but that is not the case with C++. Sometimes we are forced to use integers that are larger than unsigned longs which is a challenge. Most libraries I found online had bad documentation and cumbersum implementations. This library is a way to make that a little easier.

## Representation
Each number is represented as a vector of unsigned long longs in base 18446744073709551615. Negative numbers are distinguished by having an "isPositive_" boolean in each BigInt object. 

## Usage
Include the BigInt.h and BigInt.cc files in your project and compile with -std=c++14 or above.

## bit-Shifting
Shifting positive numbers shifts the bit value of the number by shift amount provided.

Shifting negative numbers works the exact same as positive numbers. Because oru representation has the numbers in an array and the parity saved as a boolean, we are able to bit-shift regardless of the parity of the number.

Shifting by a negative value raises an assertion error.


## Future Development
Many of the algorithms used are not highly efficient, however, we are continuously working on improving the library to handle bigger numbers.

##### Things currently in development
1. Multiplication
2. Division
3. Allgorithm Improvements
