#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int secret1(int x, int y);
int secret2(int n);
int secret3(int a, int b);
int secret4(int a, int b);
int secret5(int a, int m);
int encrypt(int msg, int e, int n);
int decrypt(int cipher, int d, int n);
int secret6(int a, int b, int n);

//Less or Equal (x <= y) just to make readers hard to understand
int secret1(int x, int y) { 
 	int xsign = (x>>31) & 1;
	int ysign = (y>>31) & 1;
	
	int xor = xsign ^ ysign; //check overflow only when two signs differ

	return (xor & !ysign) | (!xor & !((y + (~x + 1))>>31));
}


// Function to check if a number is prime or not
int secret2(int n)
{
    int i = 2;
    if(secret1(n, 1)) return 0;
    while(secret1(i+1, n)){
        if(n % i++ == 0) return 0;
    }
    return 1;
}

// Function to generate a random prime number between a and b
int secret3(int a, int b)
{
    int i, p;

    while (1) {
        p = rand() % (b - a + 1) + a;

        if (secret2(p)) {
            return p;
        }
    }
}

// Function to calculate the Greatest Common Divisor (GCD) of a and b
int secret4(int a, int b)
{
    if (a == 0) {
        return b;
    }

    return secret4(b % a, a);
}

// Function to calculate the modular inverse of a mod m using the extended Euclidean algorithm
int secret5(int a, int m)
{
    int m0 = m;
    int y = 0, x = 1;

    if (m == 1) {
        return 0;
    }

    while (a > 1) {
        int q = a / m;
        int t = m;

        m = a % m;
        a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0) {
        x += m0;
    }

    return x;
}

// Function to encrypt a message using RSA
int encrypt(int msg, int e, int n)
{
    int cipher = (long long int) secret6(msg, e, n);

    return cipher;
}

// Function to decrypt a message using RSA
int decrypt(int cipher, int d, int n)
{
    int msg = (long long int) secret6(cipher, d, n);

    return msg;
}


//Function to calculate pow function with modular
int secret6(int a, int b, int n){
    int res = 1;
    for(int i = 0; i < b; i++){
        res *= a;
        res %= n;
    }

    return res;

}

int main()
{
    srand(time(NULL));

    int p, q, n, phi, e, d, msg, cipher, decrypted;

    
    // Generate two random prime numbers
    p = secret3(3, 100);
    q = secret3(3, 100);

    // Calculate n and phi(n)
    n = p * q;
    phi = (p - 1) * (q - 1);

    // Choose an integer e such that 1 < e < phi(n) and gcd(e, phi(n)) = 1
    do {
        e = rand() % phi;
    } while (secret4(e, phi) != 1);

    // Calculate d such that d is the modular inverse of e mod phi(n)
    d = secret5(e, phi);

    printf("p = %d\n", p);
    printf("q = %d\n", q);
    printf("n = %d\n", n);
    printf("phi(n) = %d\n", phi);
    printf("e = %d\n", e);
    printf("d = %d\n", d);

    // Read the message to be encrypted
    msg = 10;

    printf("msg : %d\n", msg);

    // Encrypt the message
    cipher = encrypt(msg, e, n);

    // Print
    printf("cipher : %d\n", cipher);

    decrypted = decrypt(cipher, d, n);

    printf("decrypted : %d\n", decrypted);

    return 0;
}