#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;

class rabin_karp {
private:
	int h = 1;
	int queryhash, windowhash, prime;
	int numLetters = 256;
	string text, query;
	vector<int> matches;
	int calculatehash(string txt, int start, int end);
public:
	rabin_karp(string text, string query, int numLetters, int prime);
	void search();
	vector<int> getmatches();
	void print();
};

int main(int argc, char* argv[]) {
	string txt; // text to perform search on
	string query;  // what to search for

	query = "Thank";
	txt = "Thanks for the video, it is great, but I have a question. Why the best case is O(N+M)? Since first we have to calculate the hash value of pattern which is O(1), fine we can get rid of that, but then we have to make (N-M+1) iterations, which should roughly equal to O(N-M)? And then assume we can find the pattern and compare character by character, which needs O(M), then, isn’t the complexity O(N)? Where does M come from? Thanks!";

	unsigned long cstart, cend;

	cstart = clock();
	rabin_karp rk(txt, query, 256, 6841);
	rk.search();
	cend = clock();

	cout << endl << "TIME: " << setprecision(4) << 1.0*(cend - cstart) << endl;

	rk.print();
}

rabin_karp::rabin_karp(string text, string query, int numLetters, int prime) {
	this->text = text;
	this->query = query;
	this->numLetters = numLetters;
	this->prime = prime;

	for (int i = 0; i < query.size() - 1; i++) {
		this->h = (this->h * numLetters) % prime;
	}
}

void rabin_karp::search() {
	this->queryhash = this->calculatehash(this->query, 0, this->query.size());
	for (int i = 0; i < 1 + this->text.size() - this->query.size(); i++) {
		this->windowhash = this->calculatehash(this->text, i, i + this->query.size());

		if (this->windowhash == this->queryhash) {
			this->matches.push_back(i);
		}
		
		if (this->windowhash < 0) {
			this->windowhash += this->prime;
		}
	}
}

int rabin_karp::calculatehash(string txt, int start, int end) {
	int hash = 0;
	for (int i = start; i < end; i++) {
		hash = (this->numLetters * (hash * this->h) + int(txt[i])) % this->prime;
	}
	return hash;
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
