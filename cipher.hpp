#ifndef CIPHER_HEADER
#define CIPHER_HEADER

#include <iostream>
#include <string>
#include <ctype.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

#define ALPHABET 26
#define print_vector(v) for_each(v.begin(),v.end(),[](const auto &e) { cout << e << " ";}); cout << endl;

enum Cipher {
    Encrypt,
    Decrypt
};

string generate_keystream(string key, int len);

#endif