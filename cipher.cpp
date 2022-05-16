#include "caesar.hpp"
#include "viginere.hpp"

using namespace std;

string generate_keystream(string key, int len){
    string keystream = "";
    size_t size = key.size();
    for(int i = 0; i<len; i++){
        keystream.push_back(key[i%size]);
    }
    return keystream;
}

int main(){

    string plaintext = "Des dissidentes athletiques se rapprochent irrespectueusement pour s'associer a une splendide torsade.";
    string ciphertext = caesar_string(plaintext, 19, Cipher::Encrypt);
    cout << "Caesar ciphertext: " << ciphertext << endl;

    int guessed_shift = caesar_break(ciphertext);
    cout << "Caesar plaintext: " << caesar_string(ciphertext, guessed_shift, Cipher::Decrypt) << endl;

    return 0;
}