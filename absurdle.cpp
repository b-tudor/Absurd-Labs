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
    std::vector<std::vector<Word> > word_list_compromised;

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
        int freq_counts[245] = { 0 };
        for (Word &commoners : word_list_common) {

            freq_counts[words.compute_match_type(commoners, word_list_compromised)] ++;
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

              //  if (freq_counts[i]) {
                    std::cout << words << "[" << Word::index_interpret(i) << "]: " << freq_counts[i] << "\n";
              //  }
                for (int j = 0; j < word_list_compromised[i].size(); j++){
                    std::cout << word_list_compromised[i][j] << " ";
                    }
                    std::cout << "\n";
            }
        //}
    }
  
}