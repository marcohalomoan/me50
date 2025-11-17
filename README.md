# AI to Answer Questions

AI that can find sentences from these files that are relevant to a user’s query. 
It is possible to add, remove, or modify files in the corpus if you’d like to experiment with answering queries based on a different corpus of documents. 
The global variable FILE_MATCHES specifies how many files should be matched for any given query. The global variable SENTENCES_MATCHES specifies 
how many sentences within those files should be matched for any given query. The AI will find the top sentence from the top matching document as the answer to our question.

In main function, we first load the files from the corpus directory into memory (via the load_files function). Each of the files is then tokenized (via tokenize) into a list of words, which then allows us to compute inverse document frequency values for each of the words (via compute_idfs). The user is then prompted to enter a query. The top_files function identifies the files that are the best match for the query. From those files, sentences are extracted, and the top_sentences function identifies the sentences that are the best match for the query.

&copy; Harvard CS50 AI
