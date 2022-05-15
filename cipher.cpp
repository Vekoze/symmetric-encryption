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

    cout << caesar_break("jvbjvb j'lza sl alza.") << endl;

    return 0;
}