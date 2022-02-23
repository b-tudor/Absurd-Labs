#include "Word.h"
#include <iostream>

Word::Word(std::string candidate) {
	if (candidate.length() != 5) {
		letter[0] = (char)0;
		return;
	}

	for( int i=0; i<5; i++ )
		letter[i] = candidate.c_str()[i];
	std_dev =  0;
	avg     = -1;
	min     = -1;
	min_qty = -1;
}

char Word::char_at(int i) {
	return letter[i];
}



int Word::interrogate(Word testee) {

	char results[5] = {0,0,0,0,0};

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if( this->letter[i] == testee.letter[j] ) {
				if (i == j) {
					results[i] = 2;
					break;
				}
				else
					results[i] = 1;
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

void Word::output() {
	
	for (int i = 0; i < 5; i++)
		std::cout << letter[i];
}

