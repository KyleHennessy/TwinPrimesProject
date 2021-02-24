#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <time.h>
#include <chrono>
#include <omp.h>

using namespace std;

static const int numOfThreads = 4;

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

int main()
{
    int primeCount = 0;
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
                if (isPrime(i) && isPrime(i+2))
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