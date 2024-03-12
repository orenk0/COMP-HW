/*
Use the Sieve to find all the prime numbers that are less than or equal to a given number N or to find out whether a number is a prime number.
The basic idea: at each iteration one prime number is picked up and all its multiples are eliminated.
After the elimination process is complete, all the unmarked numbers that remain are prime. 
Time complexity : 𝑂(𝑛⋅log⁡(log⁡(𝑛)))
*/

void sieve(int N)
{
    bool isPrime[N + 1];
    for (int i = 0; i <= N; ++i) {
        isPrime[i] = true;
    }
    
    isPrime[0] = false;
    isPrime[1] = false;
    
    for (int i = 2; i * i <= N; ++i) {
        
        // Mark all the multiples of i as composite numbers
        if (isPrime[i] == true) {
            for (int j = i * i; j <= N; j += i)
                isPrime[j] = false;
        }
    }
} 
