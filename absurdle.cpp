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


void do_the_thing(std::vector<Word>& guesses, std::vector<Word>& answer_pool, std::vector<Word> &guess_chain, std::ofstream& oFile, int level, int current_top_level_progress);





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


    // Open the output file
    const std::string outfileName("output.txt");

    std::ofstream outFile(outfileName);
    if (outFile.is_open()) {
        // Search for answers!
        std::cout << "Writing output to: " << outfileName << std::endl;
        do_the_thing(list_of_attempt_words, list_of_answer_set_words, guess_chain, outFile, 0, 0);
    }
    else {
        std::cout << "Failed to open output file: " << outfileName << "\n.Exiting..." << std::endl;
    }


    
    outFile.close();
    std::cout << "Output file closed.\n";
    std::cout << "\n Done";

    return 0;
        
}





void do_the_thing(std::vector<Word>& list_of_attempt_words, std::vector<Word>& answer_pool, std::vector<Word>& guess_chain, std::ofstream& oFile, int level, int current_top_level_progress )
{
    constexpr int KEEPER_COUNT = 25;
    constexpr double INCREMENT = 1.0 / (double) KEEPER_COUNT;
    
    int TLP = 0; // Top level progress indicator (progress in original parent instance)
    
    static int word_count_of_best_answer__so_far = 3;
    
    // RECURSIVE EXIT CONDITIONS
    ///////////////////////////////////////////////////////////////////////////////////////////////
    
    // If the answer would be worse than what we have discovered so far,
    // then we abandon this line of inquiry.
    if (guess_chain.size() > word_count_of_best_answer__so_far)
        return;

    // If we found a winner,  spit it out
    if(answer_pool.size() == 1) {
        if (guess_chain.size() <= word_count_of_best_answer__so_far) {
            word_count_of_best_answer__so_far = (int) guess_chain.size();
            for (auto& w : guess_chain) {
                oFile << w << " ";
            }
            oFile << answer_pool[0] << std::endl;
        }
        return;
    }

    
    // --------------------------------------------------------------------------------------------





    // We will keep and examine the top keeper_count guesses
    
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

        // If we are at the base level, we set the top level progress indicator. If we are one
        // of the child instances, we use what was passed to us (i.e. current_top_level_progress)
        TLP = (level) ? current_top_level_progress : i;
        double glob_prog = 0;
        double local_prog = 0;

        switch (level) {
            case 0:
                std::cout << "\rProgress: " << std::fixed << std::setprecision(3) << 100.0 * (double)i / (double)KEEPER_COUNT << "%           ";
                break;
            case 1:
                glob_prog  = current_top_level_progress * INCREMENT;
                local_prog = i * INCREMENT / (double) KEEPER_COUNT;
                std::cout << "\rProgress: " << std::fixed << std::setprecision(3) << 100.0 * (glob_prog + local_prog) << "%           ";
                break;
            default:
                // Do nothing... only report progress at levels 1 & 2
                break;
        }
            

        
        
        
        
        Word guess = list_of_attempt_words[best_Guesses[i].index];
        //Word guess = std::string("TESTY");
        guess_chain.push_back( guess ); 
        
        /*/ Build the word bucket for this guess 
        std::vector<Word> word_bucket;        
        for (Word& potential_answer : answer_pool) {
            int matchTypeIdx = guess.compute_match_code( potential_answer );
            if (matchTypeIdx == guess.max_Index())
                word_bucket.push_back(potential_answer);
        }*/
        
        std::vector<Word> word_bucket[Word::numMATCH_TYPES];
        for (Word& potential_answer : answer_pool) {
            int matchTypeIdx = guess.compute_match_code(potential_answer);
            word_bucket[matchTypeIdx].push_back(potential_answer);
        }
        int max_bucket = 0;
        int max_bucket_size = 0;
        for(int i=0; i<Word::numMATCH_TYPES; i++ )
            if (word_bucket[i].size() > max_bucket_size) {
                max_bucket_size = (int) word_bucket[i].size();
                max_bucket = i;
            }
        
        do_the_thing( list_of_attempt_words, word_bucket[max_bucket], guess_chain, oFile, level+1, TLP );
     
        // Take this guess off the guess chain and try the next best guess...
        guess_chain.pop_back();
    }

    if (!level)
        std::cout << "\rProgress: 100.000%            \n";
}
