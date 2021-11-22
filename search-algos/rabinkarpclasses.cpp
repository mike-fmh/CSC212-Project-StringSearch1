#include <iostream>
#include <vector>
#include <string>
using namespace std;

class rabin_karp {
private:
	int prime = 101;
	int h = 1;
	int queryhash, windowhash;
	int numLetters = 256;
	string text, query;
	vector<int> matches;
	void calculatehash(int* hash, char letter, int slide);
public:
	rabin_karp(string text, string query, int numLetters, int prime);
	void search();
	vector<int> getmatches();
	void print();
};

int main(int argc, char* argv[]) {
	string txt; // text to perform search on
	string query;  // what to search for

//	query = argv[2];
//	txt = argv[1];

	query = "Thanks";
	txt = "Thanks for the video, it is great, but I have a question. Why the best case is O(N+M)? Since first we have to calculate the hash value of pattern which is O(1), fine we can get rid of that, but then we have to make (N-M+1) iterations, which should roughly equal to O(N-M)? And then assume we can find the pattern and compare character by character, which needs O(M), then, isn’t the complexity O(N)? Where does M come from? Thanks!";


	cout << "Input text: \"" << txt << "\"\nQuery: \"" << query << "\"\n";

	rabin_karp rk(txt, query, 256, 101);
	rk.search();

	vector<int> matches = rk.getmatches();

	if (matches.size() > 0) {
		cout << "\nFound matches at indices:\n";
	}
	else {
		cout << "\nNo matches found\n";
	}

	for (int i = 0; i < matches.size(); i++) {
		cout << matches[i] << endl;
	}

	rk.print();
}

rabin_karp::rabin_karp(string text, string query, int numLetters, int prime) {
	this->text = text;
	this->query = query;
	this->numLetters = numLetters;
	this->prime = prime;
	// calculate our h value, which will help with our hash calculations later
	for (int i = 0; i < query.size() - 1; i++) {
		this->h = (this->h * numLetters) % prime;
	}
}

void rabin_karp::search() {
	// rabinkarp works by creating "windows" of length query.size() over the input text, and then iterates over each window to check if it matches the query

	// in this implimentation it creates the windows as the seach progresses instead of creating them all beforehand
	for (int i = 0; i < query.size(); i++) {
		// calculate the hash values of the query, and first window of input text
		this->calculatehash(&this->queryhash, this->query[i], 0);
		this->calculatehash(&this->windowhash, this->text[i], 0);
	}
	
	// now start the search
	for (int i = 0; i < 1 + this->text.size() - this->query.size(); i++) {
		if (this->windowhash == this->queryhash) {
			// if the current window == query, we may have found a match
			int j;
			// to make sure it's a match, check each letter of the query against the corresponding letter of the window
			for (j = 0; j < this->query.size(); j++) {
				if (this->text[j + i] != this->query[j]) {
					break;
				}
			}
			if (j == this->query.size()) {
				this->matches.push_back(i);
			}
		}

		// now calculate the hash for the next window and repeat the loop
		this->calculatehash(&this->windowhash, this->text[i + this->query.size()], int(this->text[i]));
		if (this->windowhash < 0) {
			// if we get a negative hash value, we can convert it to positive using the same prime number we used to create it
			this->windowhash += this->prime;
		}		
	}
}

void rabin_karp::calculatehash(int* hash, char letter, int slide) {
	(*hash) = (this->numLetters * ((*hash) - slide * this->h) + int(letter)) % this->prime;
}

void rabin_karp::print() {
	cout << "\n>>\"";
	for (int i = 0; i < this->text.size(); i++) {
		for (int n = 0; n < this->matches.size(); n++) {
			if (i == this->matches[n]) {
				cout << "[";
			}
			if (i == this->matches[n] + this->query.size()) {
				cout << "]";
			}
		}
		cout << this->text[i];
	}
	cout << "\"\n\n";
	
}

vector<int> rabin_karp::getmatches() {
	return this->matches;
}
