#pragma once
#include <string>
#include <iostream>

class Word
{
private:
	char   letter[5];
	int    min;
	int    min_qty;
	float  avg;
	float  std_dev;

public:
	Word(std::string);
	char char_at(int i) const { return letter[i]; };
	bool equals(const char test[6]);
	int compute_match_type (Word testee, std::vector<std::vector<Word> > &compromised_words);
	void set_avg(double a) { avg = (float)a; };
	double Avg() { return (double)avg; }
	void set_sd(double s) { std_dev = (float)s; }
	double sd() { return (double) std_dev; }
	bool operator==(const Word& w);
	bool operator!=(const Word& w);

	static std::string index_interpret(int i) {
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