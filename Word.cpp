#include "Word.h"


Word::Word(std::string candidate) : std_dev(0), index_of_largest_bucket(0) {
	if (candidate.length() != 5) {
		letter = nullptr;
		return;
	}
	letter = new char[5];
	for( int i=0; i<5; i++ )
		letter[i] = candidate.c_str()[i];
}

Word::Word(const Word& w): std_dev(w.std_dev), index_of_largest_bucket(w.index_of_largest_bucket) {
	letter = new char[5];
	for (int i = 0; i < 5; i++) 
		this->letter[i] = w.letter[i];
}

Word::~Word() {	delete letter; }





Word& Word::operator=(Word w) {
	swap(*this, w);
	return *this;
}





int Word::compute_match_code(Word testee) {
	char results[5] = { 0,0,0,0,0 };
	// Check for correct letters in the correct position first
	for (int i = 0; i < 5; i++) {
		if(this->letter[i]==testee.letter[i]) {
			results[i] = 2;
			// If we find a good letter, delete it so that it is not eligible
			// to be matched when checking for good letters in incorrect positions.
			testee.letter[i] = '.';
		}
	}


	for (int i=0; i<5; i++) {

		// If we have a value in this position already, then this letter
		// has already been 'consumed'.
		if (results[i] > 0)
			continue;

		for (int j=0; j<5; j++) {

			// We already checked this case (good letter in correct position)
			if (i == j)
				continue;

			if (this->letter[i] == testee.letter[j]) {
				results[i] = 1;
				// Get rid of this match so it is not double counted
				testee.letter[j] = '.';
				break;
				
			}
		}
	}       
	
	int index = 0;
	int powers_of_3[5] = { 81, 27, 9, 3, 1 };
	for (int i = 0; i < 5; i++) {
		index += results[i] * powers_of_3[i];
	}

	return index;
}





bool Word::operator==(const Word& w) const {
	for (int i = 0; i < 5; i++)
		if ((this->letter[i] | 0x10) != (w.letter[i] | 0x10))
			return false;
	return true;
}


bool Word::operator!=(const Word& w) const {
	return !(*this == w);
}

// Test for equality against string literals
bool Word::operator==(const char test[6]) const {
	for (int i = 0; i < 5; i++)
		if (this->char_at(i) != test[i])
			return false;

	if (test[5])
		return false;

	return true;
}


bool Word::operator!=(const char test[6]) const {
	return !(*this == test);
}