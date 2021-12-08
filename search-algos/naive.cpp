#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> naive_search(string* text, string* query);
void print(string* text, string* query, vector<int>* matches);

int main(int argc, char* argv[]) {
	string txt; // text to perform search on
	string query;  // what to search for

//	query = argv[2];
//	txt = argv[1];

	query = "Thank";
	txt = "Thanks for the video, it is great, but I have a question. Why the best case is O(N+M)? Since first we have to calculate the hash value of pattern which is O(1), fine we can get rid of that, but then we have to make (N-M+1) iterations, which should roughly equal to O(N-M)? And then assume we can find the pattern and compare character by character, which needs O(M), then, isn’t the complexity O(N)? Where does M come from? Thanks!";


	cout << "Input text: \"" << txt << "\"\nQuery: \"" << query << "\"\n";
	vector<int> matches = naive_search(&txt, &query);

	if (matches.size() > 0) {
		print(&txt, &query, &matches);
	}
	else {
		cout << "\nNo matches found\n";
	}
}


vector<int> naive_search(string* text, string* query) {
	// returns a vector of indices where a query match was found in the text
	vector<int> matchIndices;

	for (int i = 0; i < (text->size() - query->size() + 1); i++) {
		int j;
		for (j = 0; j < query->size(); j++) {
			if (text->at(i + j) != query->at(j)) {
				break;
			}
		}
		if (j == query->size()) {
			matchIndices.push_back(i);
		}
	}
	return matchIndices;
}

void print(string* text, string* query, vector<int>* matches) {
	cout << "\n>>\"";
	for (int i = 0; i < text->size(); i++) {
		for (int n = 0; n < matches->size(); n++) {
			if (i == (*matches)[n]) {
				cout << "[";
			}
			if (i == (*matches)[n] + query->size()) {
				cout << "]";
			}
		}
		cout << (*text)[i];
	}
	if ((*matches)[(*matches).size() - 1] + query->size() == text->size()) {
		// if there needs to be a "]" at the end
		cout << "]";
	}
	cout << "\"\n\n";

}