import nltk
import sys
import os
import math
import string

FILE_MATCHES = 1
SENTENCE_MATCHES = 1

def main():

    # Check command-line arguments
    if len(sys.argv) != 2:
        sys.exit("Usage: python questions.py corpus")

    # Calculate IDF values across files
    files = load_files(sys.argv[1])
    file_words = {
        filename: tokenize(files[filename])
        for filename in files
    }
    file_idfs = compute_idfs(file_words)

    # Prompt user for query
    query = set(tokenize(input("Query: ")))

    # Determine top file matches according to TF-IDF
    filenames = top_files(query, file_words, file_idfs, n=FILE_MATCHES)

    # Extract sentences from top files
    sentences = dict()
    for filename in filenames:
        for passage in files[filename].split("\n"):
            for sentence in nltk.sent_tokenize(passage):
                tokens = tokenize(sentence)
                if tokens:
                    sentences[sentence] = tokens

    # Compute IDF values across sentences
    idfs = compute_idfs(sentences)

    # Determine top sentence matches
    matches = top_sentences(query, sentences, idfs, n=SENTENCE_MATCHES)
    for match in matches:
        print(match)


def load_files(directory):
    """
    Given a directory name, return a dictionary mapping the filename of each
    `.txt` file inside that directory to the file's contents as a string.
    """
    result = {}
    files = [f for f in os.listdir(directory)]
    for file in files:
        with open(os.path.join(directory, file), errors="ignore") as f:
            content = f.read()
            result[file] = content
    return result


def tokenize(document):
    """
    Given a document (represented as a string), return a list of all of the
    words in that document, in order.

    Process document by coverting all words to lowercase, and removing any
    punctuation or English stopwords.
    """
    tokens = []
    tokenized = []
    for words in nltk.tokenize.word_tokenize(document):
        tokens.append(words.lower())
    for words in tokens:
        if words in nltk.corpus.stopwords.words("english"):
            continue
        elif words in string.punctuation:
            continue
        else:
            tokenized.append(words)
    return tokenized


def compute_idfs(documents):
    """
    Given a dictionary of `documents` that maps names of documents to a list
    of words, return a dictionary that maps words to their IDF values.

    Any word that appears in at least one of the documents should be in the
    resulting dictionary.
    """
    result = {}
    each_doc = {}
    for doc in documents:
        for word in documents[doc]:
            if word not in result.keys():
                result[word] = 1
                each_doc[word] = []
                each_doc[word].append(doc)
            elif doc not in each_doc[word]:
                result[word] += 1
                each_doc[word].append(doc)
    result.update((k, math.log(len(documents)/v, math.e)) for k, v in result.items())
    return result


def top_files(query, files, idfs, n):
    """
    Given a `query` (a set of words), `files` (a dictionary mapping names of
    files to a list of their words), and `idfs` (a dictionary mapping words
    to their IDF values), return a list of the filenames of the the `n` top
    files that match the query, ranked according to tf-idf.
    """
    count = {}
    for filename in files:
        count[filename] = 0
    for filename in files:
        for word in files[filename]:
            if word in query:
                count[filename] += idfs[word]
    result = dict(sorted(count.items(), key=lambda item: item[1], reverse=True))
    result = list(result.keys())[:n]
    return result

def top_sentences(query, sentences, idfs, n):
    """
    Given a `query` (a set of words), `sentences` (a dictionary mapping
    sentences to a list of their words), and `idfs` (a dictionary mapping words
    to their IDF values), return a list of the `n` top sentences that match
    the query, ranked according to idf. If there are ties, preference should
    be given to sentences that have a higher query term density.
    """
    count = {}
    for sent in sentences:
        count[sent] = [0, 0]
    """
    there are 2 values to sort based on:
    matching word measure and query term density
    """
    # first loop to get matching word measure
    for sent in sentences:
        for word in query:
            if word in sentences[sent]:
                count[sent][0] += idfs[word]

    # second loop to get query term density
    for sent in sentences:
        for word in query:
            if word in sentences[sent]:
                count[sent][1] += 1/len(sentences[sent])
    """
    Count how many times there is a word in query that is also in sentence
    Since in the end it will be divided by number of words in a sentence, it is the same
    if I divide it each count
    """

    result = dict(sorted(count.items(), key=lambda item: (item[1][0], item[1][1]), reverse=True))
    # sort based on matching word measure = item[1][0], then query term density = item[1][1]
    result = list(result.keys())[:n]

    return result


if __name__ == "__main__":
    main()