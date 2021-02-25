#include <iostream>
#include <vector>
#include <set>
#include <chrono> ///< To time the execution
#include <omp.h> ///< Header for OpenMP

using namespace std;
/**
 * A parallel program that uses multi-threading to divide computations among threads
 * This is achieved using the OpenMP library. OpenMP is a library for parallel programming that shares memory and data between threads
 * It makes it much easier and simpler to create multi-threaded software, which can be achieved by using a pragma.
 * A pragma is a compiler directive, which allows you to send additional instructions to the compiler on run time.
 */

static const int numOfThreads = 10; 
/*! Determines if the int number is a prime or not */
/*!
    Function used to determine if a given number is a prime
    If a number is less than 2 it returns false as there is no prime numbers below 2
    Any number above 2, it is looped over from 2 to number - 1 to see if it divides evenly into any number
    by doing number mod(i). If for every int i it does not divide into the number evenly,
    then it is a prime.
*/

bool isPrime(int number)
{
    if (number < 2)
    {
        return false;
    }
    for (int i = 2; i < number; i++)
    {
        if (number % i == 0)
        {
            return false;
        }
    }
    return true;
}
/*! main driver of the program */
/*! 
    Where the majority of the program occurs. A vector of prime numbers and a set of twin primes
    are initilized to store the prime numbers, and a chrono high resolution clock is used to calculate
    the time it takes to execute the code. Before execution of the for loop, a pragma is used to signal to the compiler
    that openMP will be used and the memory will be shared among the number of threads declared earlier.
    Then inside the for loop, once the number is a for loop, a thread enters the critical section where a number is added to the vector
    of prime numbers. Then, if the number i+2 is a prime also, then i and i+2 is added to the set of twin primes.
    Once this has finished executing, the timer will stop and the duration will be recorded. The time is calculated by
    subtracting the start time from the end time. Finally, the contents of the vector and the set are printed on to the screen.
*/
int main()
{

    int maxNumber;
    vector<int> primeNumbers; 
    set<int>twinPrimes;

    cout << "Enter maximum number: ";
    cin >> maxNumber;
    auto startTime = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for num_threads(numOfThreads)
    for (int i = 0; i < maxNumber; i++)
    {
        if (isPrime(i))
        {   
            #pragma omp critical
            {
                primeNumbers.push_back(i);
                if (isPrime(i+2))
                {   
                    twinPrimes.insert(i);
                    twinPrimes.insert(i+2);
                }
            }
        }        
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( startTime - endTime ).count();
    cout << "Number of Primes: " << primeNumbers.size();
    cout <<"\nTwin Primes: ";
    for(auto iterator = twinPrimes.begin(); iterator != twinPrimes.end(); ++iterator)
    {
        cout << " " << *iterator;
    }

    cout << "\nTime taken: " << duration << " microseconds" << endl;
    cout << fixed << "Number of threads: " << numOfThreads << endl;

    return 0;
}