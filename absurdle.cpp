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
    std::vector<Word> list_of_attempt_words;
    std::vector<Word> list_of_answer_set_words;


     
    ///// Read our word lists in from their files /////////////////////////////////////////////////
    
    // Read Complete word list from file
    std::ifstream infile("absurdle-list-COMPLETE.txt");
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        if (line.length() == 5) {
            list_of_attempt_words.push_back(Word(line));
        }
    };
    std::cout << "Size of Complete list: " << list_of_attempt_words.size() << "\n";

    // Read possible-answers word list from file
    std::ifstream infile_B("absurdle-list-COMMON.txt");
    while (std::getline(infile_B, line)) {
        std::istringstream iss(line);
        if (line.length() == 5) {
            list_of_answer_set_words.push_back(Word(line));
        }
    };
    std::cout << "Size of Common list: " << list_of_answer_set_words.size() << "\n";

    ///////////////////////////////////////////////////////////////////////////////////////////////



    

    double avg = 0;
    bool average_computed = false;
    int attempt_index = 0;
    int second_round_index = 0;
    int  third_round_index = 0;
    std::vector<Word>* second_round_answer_set_words = (std::vector<Word>*) calloc(sizeof(std::vector<Word>), list_of_attempt_words.size());
    std::vector<Word>*  third_round_answer_set_words = (std::vector<Word>*) calloc(sizeof(std::vector<Word>), list_of_attempt_words.size());
    int min_of_maxWordCounts = list_of_attempt_words.size(); // I think we expect this to be 11700 though: research





    // Do all the work
    for (Word& guess : list_of_attempt_words) {

        // Array of Word-vectors to store a list of all the words corresponding to each 'way' of matching
        std::vector<Word> word_buckets_compromised[Word::numMATCH_TYPES];


        // Compare each guess with every possible word in the answer pool and see which 
        // "color indicator string" (i.e. match type) would be returned. For each match 
        // type, keep a count of words that would have fallen into that category as well
        // as a complete list of all those words. The index of largest bucket is recorded
        // for posterity.
        ///////////////////////////////////////////////////////////////////////////////////////////
        int freq_counts[Word::numMATCH_TYPES] = { 0 };
        int max_word_count = 0;
        for (Word& potential_answer : list_of_answer_set_words) {

            // Do the actual matching
            int index = guess.compute_match_code(potential_answer);

            // Store the matched words for later
            word_buckets_compromised[index].push_back(potential_answer);
            freq_counts[index]++;

            // Track the largest bucket
            if (freq_counts[index] > max_word_count) {
                max_word_count = freq_counts[index];
                guess.set_maxIdx(index);
            }
        }//----------------------------------------------------------------------------------------




         // Compute some statistics for this guess
        ///////////////////////////////////////////////////////////////////////////////////////////
        {
            //             AVERAGE
            if (!average_computed) {
                for (int i = 0; i < Word::numMATCH_TYPES; i++)
                    avg += freq_counts[i];
                avg = avg / (double)Word::numMATCH_TYPES;
                average_computed = true;
            }
            guess.set_avg(avg);

            //         STANDARD DEVIATION
            double sd = 0;
            for (int i = 0; i < Word::numMATCH_TYPES; i++) {
                double delta = avg - freq_counts[i];
                sd += delta * delta;
            }
            sd = sqrt(sd / (double)Word::numMATCH_TYPES);
            guess.set_sd(sd);
        }//-----------------------------------------------------------------------------------------

    








       
         for (int i = 0; i < Word::numMATCH_TYPES; i++) {
            if (i == guess.max_Index()) {
                    if (max_word_count <= min_of_maxWordCounts) {
                        std::cout << guess << "[" << Word::render_match_code(i) << "]: " << freq_counts[i] << " \t";
                        std::cout << "Word at index " << attempt_index << "\n";
                   //     std::cout << "\n";
                    }
                // Traversing of vectors word_buckets_compromised to print
               
                    for (auto &matched : word_buckets_compromised[i]) {
                        second_round_answer_set_words[second_round_index].push_back(matched);
                    //    std::cout << matched << ' ';
                    }
                

                //setting the min max word count
                if (max_word_count < min_of_maxWordCounts) {
                    min_of_maxWordCounts = max_word_count;
                }
            }
        }
        second_round_index++;
        attempt_index++;
    }

  /*  // display the secound round list
    std::cout << "Display Second Round Lists \n ";
    for (int i = 0; i < list_of_attempt_words.size(); i ++){
        std::cout << "For Word:" << list_of_attempt_words[i] << " - ";
        for (auto entry = second_round_answer_set_words[i].begin(); entry != second_round_answer_set_words[i].end(); entry++) {
            std::cout << *entry << ' ';
        }
        std::cout << "\n";
    }
    */
 
 // Do a lot of work on the list of second answer lists  <<=============================================================>>
    //initial second_round_index again
    second_round_index = 8858;
    // This used to be (int i = 0; i <= list_of_attempt_words.size(); i++)
    for(int i = 0; i < 2; i++){
        min_of_maxWordCounts = list_of_attempt_words.size();
        list_of_answer_set_words.clear();
        // Read possible - answers word list from array of buckets
        for (auto entry = second_round_answer_set_words[second_round_index].begin(); entry != second_round_answer_set_words[second_round_index].end(); entry++) {
            list_of_answer_set_words.push_back(*entry);
        }
        std::cout << "Size of answer set list " << second_round_index << " : " << list_of_answer_set_words.size() << "\n";
        
   
        for (Word& words : list_of_attempt_words) {    
           
            // array of vectors to store all the match buckets
            std::vector<Word> word_buckets_compromised[Word::numMATCH_TYPES];

            int freq_counts[Word::numMATCH_TYPES] = { 0 };
            for (Word& commoners : list_of_answer_set_words) {
                //do the actual matching
                int index = words.compute_match_code(commoners);
                //store the matched words for later
                word_buckets_compromised[index].push_back(commoners);
                freq_counts[index]++;
            }

            // Compute largest match index
            int max_index = 0;
            int max_word_count = 0;
            for (int i = 0; i < Word::numMATCH_TYPES; i++) {
                if (freq_counts[i] > max_word_count) {
                    max_word_count = freq_counts[i];
                    max_index = i;
                }
            }
            words.set_maxIdx(max_index);

            // Compute average for each word
            double avg = 0;
            for (int i = 0; i < Word::numMATCH_TYPES; i++) {
                avg += freq_counts[i];
            }
            avg = avg / (double) Word::numMATCH_TYPES;
            words.set_avg(avg);

            // Compute sd for each word
            double sd = 0;
            for (int i = 0; i < Word::numMATCH_TYPES; i++) {
                sd += (avg - freq_counts[i]) * (avg - freq_counts[i]);
            }
            sd = sqrt(sd / (double) Word::numMATCH_TYPES );
            words.set_sd(sd);



            for (int i = 0; i < Word::numMATCH_TYPES; i++) {
                if (i == max_index) {
                    if (max_word_count <= min_of_maxWordCounts) {
                        std::cout << words << "[" << Word::render_match_code(i) << "]: " << freq_counts[i] << "\t";
                        std::cout << "Words at match index: " << i << "\n ";
                    }
 
                    // Traversing of vectors word_buckets_compromised to print
                 //   std::cout << "More Words Should be Shorter " << i << ": ";
                        for (auto &matched : word_buckets_compromised[i]) {
                            third_round_answer_set_words[third_round_index].push_back(matched);
                        //    std::cout << matched << ' ';
                        }

                    //setting the min max word count
                    if (max_word_count < min_of_maxWordCounts) {
                        min_of_maxWordCounts = max_word_count;
                    }
                }
            }
            

            third_round_index++;
        } 
    second_round_index++;
    }
    std::cout << "\n Done";
    
}