#include "caesar.hpp"

float relative_percent_difference(float x, float y){
    return 2 * ( abs(x-y) / (abs(x)+abs(y)) );
}

char caesar_char(char c, int shift, Cipher type){
    if(!isalpha(c)) 
        return c;
    shift *= (type==Cipher::Decrypt) ? -1 : 1;
    unsigned int min = (islower(c)) ? 97 : 65;
    return (c - min + (shift % 26) + 26) % 26 + min;
}

string caesar_string(string plaintext, int shift, Cipher type){
    string ciphertext = plaintext;
    for(size_t i = 0; i<plaintext.size(); i++){
        ciphertext[i] = caesar_char(plaintext[i], shift, type);
    }
    return ciphertext;
}

void caesar_file(string in_path, string out_path, int shift, Cipher type){
    ifstream in(in_path);
    ofstream out(out_path);

    if(!in)
        return;

    if(!in.is_open() || !out.is_open())
        return;

    string line;
    while(getline(in, line)){
        out << caesar_string(line, shift, type);
    }

    in.close();
    out.close();
}

string caesar_break(string ciphertext){

    vector<pair<int, float>> shift_rpd_pairs;
    vector<float> en_freq = {6.51, 1.89, 3.06, 5.08, 17.4, 
		1.66, 3.01, 4.76, 7.55, 0.27, 
		1.21, 3.44, 2.53, 9.78, 2.51, 
		0.29, 0.02, 7.00, 7.27, 6.15, 
		4.35, 0.67, 1.89, 0.03, 0.04, 1.13};

    for(unsigned int shift = 1; shift<ALPHABET; shift++){

        string plaintext = caesar_string(ciphertext, shift, Cipher::Decrypt);
        vector<float> pt_freq(ALPHABET);

        int counter = 0;
        for(char c : plaintext){
            if(!isalpha(c)) continue;
            int alphabet_index = (islower(c)) ? c-97 : c-65;
            pt_freq[alphabet_index]+=1.0f;
            counter++;
        }
        for(float &f : pt_freq){
            f = f/counter*100.0;
        }
        
        float rpd = 0.0f;
        int valids = 0;
        for(unsigned int i = 0; i<ALPHABET; i++){
            if(pt_freq[i]==0.0f) continue;
            rpd = relative_percent_difference(en_freq[i], pt_freq[i]);
            valids++;
        }

        float rpd_average = rpd/valids;
        shift_rpd_pairs.push_back(make_pair(shift, rpd_average));

    }

    sort(shift_rpd_pairs.begin(), shift_rpd_pairs.end(), 
        [](pair<int, float> p1, pair<int, float> p2) -> bool {
            return (p1.second<p2.second);
        });

    int best_shift = shift_rpd_pairs.at(0).first;
    float best_rpd = shift_rpd_pairs.at(0).second;

    cout << setprecision(3);
    cout << "[DEBUG] Closest match at RPD: " << best_rpd << " | " << best_shift << " shifts." << endl;

    return caesar_string(ciphertext, best_shift, Cipher::Decrypt);
}