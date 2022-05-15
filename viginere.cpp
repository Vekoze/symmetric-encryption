#include "viginere.hpp"
#include "caesar.hpp"

string viginere_string(string plaintext, string key, Cipher type){
    string ciphertext = plaintext;
    int letters = [&]() -> int {
        int counter = 0;
        for(size_t i = 0; i<plaintext.size(); i++){
            if(isalpha(plaintext[i]))
                 counter++;
        }
        return counter;
    }();
    string keystream = generate_keystream(key, letters);
    int pos = 0;
    for(size_t i = 0; i<plaintext.size(); i++){
        char k = keystream[ (isalpha(plaintext[i]) ? pos++ : pos ) ];
        int shift = (islower(k)) ? k - 97 : k - 65; 
        ciphertext[i] = caesar_char(plaintext[i], shift, type);
    }
    return ciphertext;
}

void vinigere_file(string in_path, string out_path, string key, Cipher type){
    ifstream in(in_path);
    ofstream out(out_path);

    if(!in)
        return;

    if(!in.is_open() || !out.is_open())
        return;

    string line;
    while(getline(in, line)){
        out << viginere_string(line, key, type);
    }

    in.close();
    out.close();
}