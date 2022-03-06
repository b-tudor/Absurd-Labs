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
    std::vector<Word> second_round_list;

    int min_max_word_count = 11700;


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

    // Do all the work
    for (Word& words : word_list_complete) {

        // array of vectors to store all the match buckets
        std::vector<Word> word_list_compromised[243];

        int freq_counts[243] = { 0 };
        for (Word& commoners : word_list_common) {
            //do the actual matching
            int index = words.compute_match_code(commoners);
            //store the matched words for later
            word_list_compromised[index].push_back(commoners);
            freq_counts[index]++;
        }

        // Compute largest match index
        int max_index = 0;
        int max_word_count = 0;
        for (int i = 0; i < 243; i++) {
            if (freq_counts[i] > max_word_count) {
                max_word_count = freq_counts[i];
                max_index = i;
            }
        }
        words.set_max(max_index);

        // Compute average for each word
        double avg = 0;
        for (int i = 0; i < 243; i++) {
            avg += freq_counts[i];
        }
        avg = avg / 243.0;
        words.set_avg(avg);

        // Compute sd for each word
        double sd = 0;
        for (int i = 0; i < 243; i++) {
            sd += (avg - freq_counts[i]) * (avg - freq_counts[i]);
        }
        sd = sqrt(sd / 243.0);
        words.set_sd(sd);


        if (max_word_count <= min_max_word_count) {
                second_round_list.clear();
            for (int i = 0; i < 243; i++) {
            
                if (i == max_index) {
                    std::cout << words << "[" << Word::render_match_code(i) << "]: " 
                    << freq_counts[i] << "\n";
                    // Traversing of vectors word_list_compromised to print
                    std::cout << "Words at index " << i << ": ";
                        for (auto &matched : word_list_compromised[i]) {
                            second_round_list.push_back(matched);
                            std::cout << matched << ' ';
                        }
                    std::cout << "\n";

                    //setting the min max word count
                    if (max_word_count < min_max_word_count) {
                        min_max_word_count = max_word_count;
                    }
                }
            }
        }
    }

    // Test the secound round list
    std::cout << "Second Round List: ";
    std::cout << "size of second list " << second_round_list.size() << "\n";
    for (auto &entry : second_round_list) {
        std::cout << entry << ' ';
    }
    std::cout << "\n Done";
}