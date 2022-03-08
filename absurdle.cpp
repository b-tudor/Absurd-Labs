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


void do_the_thing(std::vector<Word>& guesses, std::vector<Word>& answer_pool, std::vector<Word> &guess_chain);





int main()
{
    std::vector<Word> list_of_attempt_words;
    std::vector<Word> list_of_answer_set_words;
    std::vector<Word> guess_chain;

     
    ///// Read Input //////////////////////////////////////////////////////////////////////////////
    
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

    // --------------------------------------------------------------------------------------------



    
    // Search for answers!
    do_the_thing( list_of_attempt_words, list_of_answer_set_words, guess_chain );
    return 0;
    

    /*
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
            //guess.set_avg(avg);

            //         STANDARD DEVIATION
            double sd = 0;
            for (int i = 0; i < Word::numMATCH_TYPES; i++) {
                double delta = avg - freq_counts[i];
                sd += delta * delta;
            }
            sd = sqrt(sd / (double)Word::numMATCH_TYPES);
            //guess.set_sd(sd);
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
    * /
 
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
            //words.set_avg(avg);

            // Compute sd for each word
            double sd = 0;
            for (int i = 0; i < Word::numMATCH_TYPES; i++) {
                sd += (avg - freq_counts[i]) * (avg - freq_counts[i]);
            }
            sd = sqrt(sd / (double) Word::numMATCH_TYPES );
            //words.set_sd(sd);



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
    */
    std::cout << "\n Done";
    
}





void do_the_thing(std::vector<Word>& list_of_attempt_words, std::vector<Word>& answer_pool, std::vector<Word>& guess_chain )
{
    static int best_answer_size = 100;
    
    // RECURSIVE EXIT CONDITIONS
    ///////////////////////////////////////////////////////////////////////////////////////////////
    
    // If the answer would be worse than what we have discovered so far,
    // then we abandon this line of inquiry.
    if (guess_chain.size() > best_answer_size)
        return;

    // If we found a winner,  spit it out
    if(answer_pool.size() == 1) {
        if (guess_chain.size() <= best_answer_size) {
            best_answer_size = guess_chain.size();
            std::cout << "WINNER WINNER, CHICKEN DINNER! -  ";
            for (auto& w : guess_chain)
                std::cout << w << " ";
            std::cout << answer_pool[0];
            std::cout << "\n";
        }
        return;
    }

    
    // --------------------------------------------------------------------------------------------





    // We will keep and examine the top keeper_count guesses
    const int KEEPER_COUNT = 3;
    typedef struct __SD_data {
        double SD    = 0;
        int    index = 0;
    } SD_data;
    SD_data best_Guesses[KEEPER_COUNT];
    for(int i=0; i<KEEPER_COUNT; i++)
        best_Guesses[i].SD = 1.0e100;

    double avg = (double)answer_pool.size() / (double)Word::numMATCH_TYPES;




    

    // Do all the work
    int guess_index = 0; // index corresponding to the current guess word's position in the vector.
    for( Word& guess : list_of_attempt_words )
    {
        int freq_counts[Word::numMATCH_TYPES] = { 0 };

        for (Word& potential_answer : answer_pool) 
            freq_counts[ guess.compute_match_code(potential_answer) ]++;

        // Record the largest word bucket for this potential guess--this will be Absurdle's
        // answer pool if we go with this guess. 
        int max_word_count = 0;
        for( int i=0; i<Word::numMATCH_TYPES; i++ ) {
            if( freq_counts[i] > max_word_count ) {
                max_word_count = freq_counts[i];
                guess.set_maxIdx(i);
            }
        }
        

        // Compute standard deviation
        double sd = 0;
        for( int i=0; i < Word::numMATCH_TYPES; i++ ) {
            double delta = avg - freq_counts[i];
            sd += delta * delta;
        }
        sd = sqrt( sd / (double)Word::numMATCH_TYPES );
        

        // See if this is one of our best standard deviations, and if so record it
        if( sd < best_Guesses[KEEPER_COUNT - 1].SD ) {

            // If it is better than our worst standard deviation that was worth saving
            // (so far), then we put it in the last postion
            best_Guesses[KEEPER_COUNT - 1].SD = sd;
            best_Guesses[KEEPER_COUNT - 1].index = guess_index;

            // Then it 'bubbles' up the list unti it is in its proper position
            for( int i=KEEPER_COUNT-1; (i>0) && (best_Guesses[i].SD < best_Guesses[i-1].SD); i-- ) {
                SD_data temp = best_Guesses[ i ];
                best_Guesses[ i ]  = best_Guesses[i-1];
                best_Guesses[i-1]  = temp;
            }
        } // --------------------------------------------------------------------------------------
        
        guess_index++;
    }


    



    // else we dig deeper!
    
    for( int i=0; i<KEEPER_COUNT; i++ ) {
        
        Word guess = list_of_attempt_words[best_Guesses[i].index];
        
        guess_chain.push_back( guess ); 
        
        // Build the word bucket for this guess
        std::vector<Word> word_bucket;        
        for (Word& potential_answer : answer_pool) {
            int matchTypeIdx = guess.compute_match_code( potential_answer );
            if (matchTypeIdx == guess.max_Index())
                word_bucket.push_back(potential_answer);
        }
        
        do_the_thing( list_of_attempt_words, word_bucket, guess_chain);
     
        // Take this guess off the guess chain and try the next best guess...
        guess_chain.pop_back();
    }
}
