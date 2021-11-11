#include <iostream>
#include <vector>
#include <string>
#include <math.h>
using namespace std;

vector<int> rabin_karp(string* text, string* query, int d);
vector<int> rabin_karp2(string* text, string* query, int d);

int main(int argc, char* argv[]) {
	string query = argv[1];  // what to search for
	query = "el";  
	
	string txt = "Hello world";  // text to seach
	
	int alphabetLen = 256;
	cout << "Input text: \"" << txt << "\"\nQuery: \"" << query << "\"\n";
	vector<int> matches = rabin_karp(&txt, &query, alphabetLen);

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


vector<int> rabin_karp(string* text, string* query, int d) {
	vector<int> matchIndices;
	int q = 79; // any prime number will work

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
				else {
					j++;
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