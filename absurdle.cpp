// Absurdle-Abs.cpp
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Word.h"

int main()
{
    std::vector<Word> word_list_A;
    std::vector<Word> word_list_B;

    // Read word list from file
    std::ifstream infile("absurdle-list-1.txt");
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        if (line.length() == 5) {
            word_list_A.push_back(Word(line));
        }
    };

    // Read word list from file
    std::ifstream infile_B("absurdle-list-2.txt");
    while (std::getline(infile_B, line)) {
        std::istringstream iss(line);
        if (line.length() == 5) {
            word_list_B.push_back(Word(line));
        }
    };

    //std::string word_list[] = {};
    for (Word w : word_list_A) {
        for (int i = 0; i < 5; i++)
            std::cout << w.char_at(i);
        std::cout << "\n";
    }


    std::cout << "\n";

    for (Word w1 : word_list_A) {

        int freq_counts[245] = { 0 };

        for (Word w2 : word_list_A) {
            freq_counts[w1.interrogate(w2)] ++;
        }

        std::cout << "\n";

        double avg = 0;
        double sd = 0;
        for (int i = 0; i < 243; i++) {
            avg += freq_counts[i];
        }
        w1.set_avg( avg / 243.0 );

        for (int i = 0; i < 243; i++) {

            sd += (avg - freq_counts[i]) * (avg - freq_counts[i]);
            
            if (freq_counts[i]) {
                w1.output();
                std::cout << "[" << Word::index_interpret(i) << "]: " << freq_counts[i] << "\n";
            }
        }
    }
            
        

    




    

}
