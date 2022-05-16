#ifndef CAESAR_HEADER
#define CAESAR_HEADER

#include "cipher.hpp"

float relative_percent_difference(float x, float y);

char caesar_char(char c, int shift, Cipher type);
string caesar_string(string plaintext, int shift, Cipher type);
void caesar_file(string in_path, string out_path, int shift, Cipher type);
int caesar_break(string ciphertext);

#endif 