#ifndef VIGINERE_HEADER
#define VIGINERE_HEADER

#include "cipher.hpp"

string viginere_string(string plaintext, string key, Cipher type);
void viginere_file(string in_path, string out_path, string key, Cipher type);

#endif