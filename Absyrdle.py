from numpy import zeros
from math import sqrt
from word import Word



word_list_complete    = []
word_list_common      = []
word_list_compromised = []



# Read Complete word list from file
infile = open("absurdle-list-COMPLETE.txt", "r")
lines = infile.readlines()
for l in lines:
    file_word = Word(l)
    word_list_complete.append(file_word)
infile.close()


# Read possible - answers word list from file
infile_B = open("absurdle-list-COMMON.txt","r")
lines = infile_B.readlines()
for l in lines:
    file_word = Word(l)
    word_list_common.append(file_word)


# Read compromised - word list from file
infile_C = open("absurdle-list-COMPROMISED.txt", "r")
lines = infile_C.readlines()
for l in lines:
    file_word = Word(l)
    word_list_compromised.append(file_word)






for words in word_list_complete :

    freq_counts = zeros((243,),int)

    for commoners in word_list_common :
        index = words.compute_match_type(commoners)
        freq_counts[index] += 1
    
    # Compute average for each word
    avg = 0.0
    for i in range(243):
        avg += freq_counts[i]
    avg = avg / 243.0
    words.avg = avg

    # Compute sd for each word
    sd = 0.0
    for i in range(243):
        delta = avg - freq_counts[i]
        sd += delta * delta
    sd = sqrt( sd/243.0 )
    words.std_dev = sd

    if words.equals("ROATE") or words.equals("IMMIX") :
        for i in range(243):
            if freq_counts[i] > 0 :
                print( words.to_str() + "["+Word.index_interpret(i)+"]: " + str(freq_counts[i]))


print("\n")

for words in word_list_complete:
    if words.std_dev < 25:
        print( words.to_str() + " ... " + str(words.std_dev))
