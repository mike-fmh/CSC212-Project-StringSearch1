#include <iostream>
#include <vector>
#include <string>
#include <math.h>
using namespace std;

vector<int> rabin_karp(string* text, string* query);

int main(int argc, char* argv[]) {
	string txt = argv[1]; // text to perform search on
	string query = argv[2];  // what to search for
//	query = "l";
//	txt = "Hello world"; 


	cout << "Input text: \"" << txt << "\"\nQuery: \"" << query << "\"\n";
	vector<int> matches = rabin_karp(&txt, &query);

	if (matches.size() > 0) {
		cout << "\nFound matches at indices:\n";
	}
	else {
		cout << "\nNo matches found\n";
	}

	for (int i = 0; i < matches.size(); i++) {
		cout << matches[i] << endl;
	}
}


vector<int> rabin_karp(string* text, string* query) {
	// returns a vector of indices where a query match was found in the text
	vector<int> matchIndices;
	int prime = 101; // any prime number
	int numLetters = 256; // length of alphabet

	int h = 1;
	for (int i = 0; i < query->size() - 1; i++) {
		h = (h * numLetters) % prime;
	}

	int patternHash = 0;
	int textHash = 0;
	for (int i = 0; i < query->size(); i++) {
		patternHash = (numLetters * patternHash + int(query->at(i))) % prime;
		textHash = (numLetters * textHash + int(text->at(i))) % prime;
	}

	for (int i = 0; i < (text->size() - query->size() + 1); i++) {
		if (patternHash == textHash) {
			int j; // initialize outside for loop so the next if statement can use j
			for (j = 0; j < query->size(); j++) {
				if (text->at(i + j) != query->at(j)) {
					break;
				}
			}
			if (j == query->size()) {
				matchIndices.push_back(i);
			}
		}
		if (i < text->size() - query->size()) {
			textHash = (numLetters * (textHash - int(text->at(i)) * h) + int(text->at(i + query->size()))) % prime;
			if (textHash < 0) {
				textHash += prime;
			}
		}
	}
	return matchIndices;
}

