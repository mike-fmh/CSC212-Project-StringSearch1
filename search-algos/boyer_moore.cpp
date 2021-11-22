#include <iostream>
#include <vector>
#include <string>

using namespace std;
void badChar(vector<int>* bChars, string* query);
vector<int> boyer_moore(string* txt, string* query, vector<int>* bChars);


int main() {
	string txt; // text to perform search on
	string query;  // what to search for
	vector<int> bChars;

	txt = "helloworld hello world";
	query = "world";
	vector<int> matches = boyer_moore(&txt, &query, &bChars);

	cout << "input txt: \"" << txt << "\"\nquery: \"" << query << "\"\n\nfound matches at in txt at indices:\n";
	for (int i = 0; i < matches.size(); i++) {
		cout << matches[i] << endl;
	}
}

void badChar(vector<int>* bChars, string* query) {
	int CHARNUM = 256; // length of alphabet
	for (int i = 0; i < CHARNUM; i++) {
		bChars->push_back(-1);
	}
	for (int i = 0; i < query->size(); i++) {
		bChars->at(int(query->at(i))) = i;
	}
}

vector<int> boyer_moore(string* txt, string* query, vector<int>* bChars) {
	vector<int> matches;
	badChar(bChars, query);
	int shift = 0;
	while (shift <= txt->size() - query->size()) {
		int j = query->size() - 1;
		while ((j >= 0) && (txt->at(shift + j) == query->at(j))) {
			j--;
		}
		if (j < 0) {
			matches.push_back(shift);
			if (shift + query->size() < txt->size()) {
				shift += query->size() - bChars->at(int(txt->at(shift + query->size())));
			}
			else {
				shift++;
			}
		}
		else {
			// change shift by n if n>1, otherwise change it by 1
			int n = j - bChars->at(int(txt->at(shift + j)));
			if (n > 1) {
				shift += n;
			}
			else {
				shift++;
			}
		}
	}
	return matches;
}