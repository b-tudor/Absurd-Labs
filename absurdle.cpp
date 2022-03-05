// Absurdle-Abs.cpp
//

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include "Word.h"

int main()
{
    std::vector<Word> word_list_complete;
    std::vector<Word> word_list_common;

    // Read Complete word list from file
    std::ifstream infile("absurdle-list-COMPLETE.txt");
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        if (line.length() == 5) {
            word_list_complete.push_back(Word(line));
        }
    };

    // Read possible - answers word list from file
    std::ifstream infile_B("absurdle-list-COMMON.txt");
    while (std::getline(infile_B, line)) {
        std::istringstream iss(line);
        if (line.length() == 5) {
            word_list_common.push_back(Word(line));
        }
    };
    
    
    for (Word &words : word_list_complete) {

        std::vector<Word> word_list_compromised[243];

        int freq_counts[245] = { 0 };
        for (Word &commoners : word_list_common) {

            int index = words.compute_match_code(commoners);
            word_list_compromised[index].push_back(commoners);  
            freq_counts[index]++;
        }
        
        // Compute average for each word
        double avg = 0;
        for (int i = 0; i < 243; i++) {
            avg += freq_counts[i];
        }
        avg = avg / 243.0;
        words.set_avg( avg );


        // Compute sd for each word
        double sd = 0;
        for (int i = 0; i < 243; i++) {
            sd += (avg - freq_counts[i]) * (avg - freq_counts[i]);
        }
        sd = sqrt(sd/243.0);
        words.set_sd(sd);

        

        // if(words.equals("AROSE")) {
			for (int i = 0; i < 243; i++) {

                if (freq_counts[i]) {
                    std::cout << words << "[" << Word::render_match_code(i) << "]: " << freq_counts[i] << "\n";
                    if(word_list_compromised[i].size() == 1){
                        // Traversing of vectors word_list_compromised to print
                        std::cout << "Words at index " << i << ": ";
                        for( auto &matched : word_list_compromised[i]) {
                            std::cout << matched << ' ';
                        }
                        std::cout << "\n";
                    }
                }
            }
    }


    for (Word& words : word_list_complete) {
        std::cout << std::fixed << std::setprecision(2);
        if (words.sd() < 25.0)
            std::cout << words << " ... " << words.sd() << "\n";
    }


  
}