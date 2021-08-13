HOMEWORK 9: MINIBLAST


NAME: Abby Itty


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

#data-stuffs and #ds-questions on Discord, cplusplus.com, Geeks for Geeks,  
http://www.partow.net/programming/hashfunctions/ from lecture for the has 
function, Kyle, Navya, Abdul, God (mostly moral support and miraculous 
autograder points)

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  30+


HASH FUNCTION DESCRIPTION

starts with an astronomically large number (so the table size
is small in comparision, so % won't be the same for too many
numbers)

after heavy Googling, I found out that the program then goes through the 
kmer's length. with each character in kmer, hash gets added to. the << is
actually a shifting bit operator. the char (kmer[i]) 's ascii value gets
used for the addition, and so if it's the same (that's what the ^= is
checking), hash gets added to. If not, hash stays the same.



HASH TABLE IMPLEMENTATION

not sure i understood the question here, but my hash table was 
a vector of points. each point had the kmer, and then a list of 
ints to hold each position the kmer appeared in


ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

L = length of the genome sequence
q - query length
p - number of different locations where key is found
k - key size (k-mer size)

inserting every kmer into the hash_table was O(2L/k)

handling a single query takes O(find function, which is further down) 
+ O(p*q), so about O(find + p*q): best case O(pq), worst case O(L*p*q/k)


How much memory will the hash table data structure require (order notation for memory use)?

O(2*number of unique keys), and the number of unique keys is roughly
2L/k, so the memory for the hash table is O(4L/k) ~ O(L/k) ish



What is the order notation for performance (running time) of each of
the commands? What about for the hash table's insert, find, and resize?

genome -> reading in is about O(L)
table_size -> O(1), just reading in a number
occupancy -> O(1)
kmer -> O(1)
query is above -> O(find + p*q): best case O(pq), worst case O(L*p*q/k)

ds_hashset::insert -> if the table's not resized (so this is just insert)
		      O(1) if the key's already there, O(size of table) in
		      the worst case, so O(L/k)
ds_hashset::find -> O(p) in the best case, O(size of table) in worst case,
		    so O(L/k)
ds_hashset::resize_tables -> we have to go through the whole table every time
			     we resize, so this function is always O(L/k)


EXTRA CREDIT
Add a new command to implement the database using one of the other
 data structures that we have covered so far in the course: 
vectors, lists, arrays etc. 

Compare the performance your alternative method to the homework method
by making a table of run times for each of the genomes and query 
sets provided with the homework  and compare the times to build
the index and the times to process the queries. 
Document any new commands you have added in your README file.



MISC. COMMENTS TO GRADER:  
corny joke of the week:
i didn't understand my hash function at first, but then I Googled and
started to understand, ~bit by bit~ :D :D

also, for the small genome, on submitty it showed my that my text file
was empty, but I got this when running it on my machine:

Query: TATTACTGCCATTTTGCAGATAAGAAATCAGAAGCTC
504 0 TATTACTGCCATTTTGCAGATAAGAAATCAGAAGCTC
Query: TTGACCTTTGGTTAACCCCTCCCTTGAAGGTGAAGCTTGTAAA
5002 2 TTGACCTTTGGTTAACCAATCCCTTGAAGGTGAAGCTTGTAAA
Query: AAACACACTGTTTCTAATTCAGGAGGTCTGAGAAGGGA
4372 0 AAACACACTGTTTCTAATTCAGGAGGTCTGAGAAGGGA
Query: TCTTGTACTTATTCTCCAATTCAGTCACAGGCCTTGTGGGCTACCCTTCA
No Match
Query: TTTTTTTTTTTTTTTCTTTTTT
4428 0 TTTTTTTTTTTTTTTCTTTTTT

missing the last few matches, but otherwise okay? wasn't sure where the difference came from!



