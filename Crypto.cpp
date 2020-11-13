#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <string>
using namespace std;

//This function calculates checks if a number is prime of not.
//The function take arguments of unsigned long long type integer. Since, the number is minimum 1 million.

bool isPrime(unsigned long long int n)
{

    bool isPrime = true;
    //Necessery conditions for the validity of a prime number.
    for (unsigned long long int i = 2; i <= n / 2; ++i)
    {
        if (n % i == 0)
        {
            isPrime = false;
            break;
        }
    }

    // return true if a prime number else return false. 
    if (isPrime)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//This function generates a random number of range from 1 million to 1.2 million.
//The function return a randomly generated number.
unsigned long long int Generate_random()
{
    unsigned long long int result = (rand() % 1200000 + 1000000);
    return result;
}

//This function generates a randomly generated prime number.
//Each time a random number generates in a loop and if it is a prime it is 
  //then store and kept otherwise new number is generated & again check if it is prime or not.
//Since, we needed 2 prime number i.e. P & Q thats why we have mentained a counter in the loop.
  //The counter checks if a randomly generated prime number is found. It helps to exit the loop.

unsigned long long int Generate_IsPrime()
{
    int count = 0;

    while (true)
    {
        if (count < 1)
        {
            unsigned long long int value = Generate_random();
            bool val = isPrime(value);
            if (val == true)
            {
                return value;
                count++;
            }
        }
        else
        {
            break;
        }
    }
}

//This function helps to calculate & return the value by taking 2 prime numbers & multiplying them with each other.
//In simple words, the function returns n = pxq

unsigned long long int Calculate_n(unsigned long long int value_p, unsigned long long int value_q)
{
    unsigned long long int value_n = value_p * value_q;
    return value_n;
}

//This function finds Phi(n) = (p-1) X (q-1)

unsigned long long int Calculate_Phi_n(unsigned long long valu_p, unsigned long long value_q)
{
    unsigned long long value_phi_n = (valu_p - 1) * (valu_p - 1);
    return value_phi_n;
}

//This function finds the Multiplicative inverse of d = e mod phi(n)
//This function uses Euclid's algorithm to find the Multiplicative inverse.

unsigned long long int Calculate_modInverse(unsigned long long int value_e, unsigned long long int phi)
{
    unsigned long long int value_y = 0, value_x = 1, m0 = phi;

    if (phi == 1)
    {
        return 0;
    }

    while (value_e > 1)
    {
        // q is quotient 
        unsigned long long int value_q = value_e / phi;
        unsigned long long int value_t = phi;

        // m is remainder now, process same as 
        // Euclid's algo 
        phi = value_e % phi, value_e = value_t;
        value_t = value_y;

        // Update y and x 
        value_y = value_x - value_q * value_y;
        value_x = value_t;
    }

    // Make x positive 
    if (value_x < 0)
    {
        value_x += m0;
    }
    return value_x;
}

//This function is a helping function to find the value of e.
//The function recursively helps to find the GCD.

unsigned long long int Calculate_GCD(unsigned long long int num1, unsigned long long int num2)
{
    if (num2 != 0)
    {
        return Calculate_GCD(num2, num1 % num2);
    }
    else
    {
        return num1;
    }
}

//Following the condition 1<e<Phi(n) && GCD(e, Phi(n) == 1 we found the value of e.
//The helping function GCD was used to find the GCD. The function is written above.

unsigned long long int Calculate_e(unsigned long long int phi)
{
    for (unsigned long long int i = 3; i < phi; i += 2)
    {
        if (Calculate_GCD(i, phi) == 1)
        {
            return i;
        }
    }
}

//This function helps to concatnate the 2 integers.

unsigned long long int concat(unsigned long long int integer1, int integer2)
{

    // Convert both the integers to string 
    string str1 = to_string(integer1);
    string str2 = to_string(integer2);

    // Concatenate both strings 
    string str = str1 + str2;

    // Convert the concatenated string to integer 
    unsigned long long int result = stoll(str);

    // return the formed integer 
    return result;
}

//In this function, we passed the String message & we are converting each character of string into ASCII Integer.
//Why we converted it into ACII? Because, we want to calculate M^e where M is a string & it exponent is integer.
//This function takes the each character from the string, store into an array of integer type after converting 
  //into string by using above method & then the above function named Concat() to concatenate the integers available in the array.

unsigned long long int Encrypt_Message(string msg)
{
    int arr[10] = {0};
    int length = sizeof(arr) / sizeof(int);
    unsigned long long int val=0;
    int count = 0;
    for (char i : msg)
    {
        arr[count] = (int)i;
        cout << arr[count] << endl;
        count++;
    }

    for (int c = 0; c<length; c++)
    {
        if (arr[c] != 0)
        {
            val = concat(val, arr[c]);
            cout << "Value: " << val << endl;
        }
    }
    //cout <<"Value: " << val << endl;
    return val;
}

//This function takes a power of a number.
//The function would be helping us to take power in O(logn) time complexity.
//This function will be used to calculate M^e.

unsigned long long int power(unsigned long long int base, unsigned long long int expo)
{
    unsigned long long int temp_var;
    if (expo == 0)
    {
        return 1;
    }

    temp_var = power(base, expo / 2);

    if (expo % 2 == 0)
    {
        return temp_var * temp_var;
    }
    else
    {
        return base * temp_var * temp_var;
    }
}

int main()
{
    //This function generate different random number on each run.
    srand(time(NULL));

    //Generating prime number p & storing it into variable p.
    unsigned long long int p = Generate_IsPrime();
    //Generating prime number q & storing it into variable q.
    unsigned long long int q = Generate_IsPrime();
    //Generating n = p X q & storing into variable n.
    unsigned long long int n = Calculate_n(p, q);
    //Calculating Phi(n) = (p-1) X (q-1) & storing it into Phi_n variable.
    unsigned long long int Phi_n = Calculate_Phi_n(p, q);
    //Calculating e by keeping the condition 1<e<Phi(n) && GCD(e, Phi(n)) ==1.
    //Where e is short Odd number. 
    unsigned long long int e = Calculate_e(Phi_n);
    //Calculating d which is a multiplicative inverse of e mod phi(n).
    unsigned long long int d = Calculate_modInverse(e, Phi_n);

    cout << "Value of p: " << p << endl;
    cout << "Value of q: " << q << endl;
    cout << "Value of n: " << n << endl;
    cout << "Value of Phi(n): " << Phi_n << endl;
    cout << "Value of e: " << e << endl;
    cout << "Value of d: " << d << endl;

    //Encrypted code after solving the equation (M^e mod n).
    unsigned long long int EncrptedCode = Encrypt_Message("Jahan");
    unsigned long long int EncryptMe = power(EncrptedCode, e);
    EncryptMe = power(EncrptedCode, e) % n;

    //Final result of the Encrpted message.
    cout << "\nEncrypting ... \n" << endl;
    cout << EncryptMe << endl;
    return 0;
}
