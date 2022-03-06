#pragma once
#include <string>
#include <iostream>

class Word
{
public:

	// Total number of ways an arbitrary guess can reveal info about any given answer.
	static const int numMATCH_TYPES = 3*3*3*3*3;

private:
	char   letter[5];
	int    index_of_largest_bucket;
	float  average;
	float  std_dev;

public:

	Word(std::string);

	// Getters/Setters
	char   char_at    (int i   ) const { return letter[i]; };
	void   set_sd     (double s)       { std_dev = (float)s; }
	double sd         (        ) const { return (double)std_dev; }
	void   set_maxIdx (int i   )       { index_of_largest_bucket = i; }
	int    maxIdx     (        ) const { return index_of_largest_bucket; }
	void   set_avg    (double a)       { average = (float)a; };
	double avg        (        ) const { return (double) average; }

	// Utility functions
	int compute_match_code (Word testee);

	// operators
	Word& operator=(const Word& w);
	bool operator==(const Word& w) const;
	bool operator!=(const Word& w) const;
	bool operator==(const char test[6]) const; // equality vs string literals
	bool operator!=(const char test[6]) const; 
	

	static std::string render_match_code(int i) {
		char result[6] = { 0 };
		int powers_of_3[5] = { 81, 27, 9, 3, 1 };


		for (int p = 0; p < 5; p++) {
			if (i >= powers_of_3[p]) {
				result[p] = (char)( i / powers_of_3[p]);
				i = i - result[p] * powers_of_3[p];
			}
		}

		for (int j = 0; j < 5; j++) {
			if (result[j] == 0)
				result[j] = '.';
			else if (result[j] == 1)
				result[j] = 'o';
			else if (result[j] == 2)
				result[j] = 'X';
		}

		return std::string(result);
	};

	friend std::ostream& operator << (std::ostream& out, const Word w) {
		out << w.char_at(0) << w.char_at(1) << w.char_at(2) << w.char_at(3) << w.char_at(4);
		return out;
	};
};