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
	int q = 79; // any prime number
	int d = 256; // length of alphabet

	int M = query->size();
	int N = text->size();
	int i, j;

	int h = pow(d, M - 1);
	h %= q;

	int p = 0, t = 0;
	for (i = 0; i < M; i++) {
		p = (d * p + int(query->at(i))) % q;
		t = (d * t + int(text->at(i))) % q;
	}

	for (i = 0; i < (N - M + 1); i++) {
		if (p == t) {
			for (j = 0; j < M; j++) {
				if (text->at(i + j) != query->at(j)) {
					break;
				}
			}
			if (j == M) {
				matchIndices.push_back(i);
			}
		}
		if (i < N - M) {
			t = (d * (t - int(text->at(i) * h)) + int(text->at(i + M))) % q;

			if (t < 0) {
				t += q;
			}
		}
	}
	return matchIndices;
}
 
