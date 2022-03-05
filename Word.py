# Python version of the Absurdle C++ Word class

import copy 


class Word:

    
    def __init__(self, candidate_word: str):

        self.letter = []
        
        if len(candidate_word)==5  or (len(candidate_word)>=6 and candidate_word[5]=="\0") or (len(candidate_word)>=6 and candidate_word[5]=="\n"):
            for i in range(5):
                self.letter.append(candidate_word.upper()[i]);

        else:
            print("ERROR: Tried to add word of incorrect length.\nTerminating...")
            exit()

        self.avg     = 0.0
        self.std_dev = 0.0





    def equals( self, test ):

        length = len(test)

        if length != 5:
            return False

        for i in range(5):
            if self.letter[i] != test[i]:
                return False

        return True

    



    def compute_match_type( self, testee ) -> int:

        guess = self

        using_a_copy = False

        results: int[5] = [0,0,0,0,0]

        # Check for correct letters in the correct position first
        for i in range(5):
            if guess.letter[i] == testee.letter[i]:
                results[i] = 2
                
                # If we have not already done so: Make a copy of the word object--we are 
                # about to alter it for the sake of the algorithm, but we want to keep the
                # original intact for checking against other word pairs
                if not( using_a_copy ):
                    testee = copy.deepcopy(testee)
                    using_a_copy = True
                # If we find a good letter we delete it so that it is not eligible 
                # to be matched when checking for good letters in incorrect positions
                testee.letter[i] = '.'



        # Check for good letters that are not in the correct position
        for i in range(5):
            if results[i] > 0:
                # This letter has already been consumed... next!
                continue

            for j in range(5):

                # We already handled this case (good letter in correct position)
                if i==j:
                    continue

                if guess.letter[i] == testee.letter[j]:
                    results[i] = 1
                    # Get rid of this match so it is not double counted
                    if not( using_a_copy ):
                        testee = copy.deepcopy(testee)
                        using_a_copy = True
                    testee.letter[j] = '.'
                    break
        
        index: int = 0
        powers_of_3: int[5] = [ 81, 27, 9, 3, 1 ]
        for i in range(5):
            index += results[i] * powers_of_3[i]


        return index





    def to_str( self ) -> str :
        output = ""
        for char in self.letter:
            output += char

        return output