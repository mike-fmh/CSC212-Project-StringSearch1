#include <iostream>
#include <vector>
#include <string>

using namespace std;


class BMS {
private:
    string text;
    string query;
    vector<int> starts;
    int badList[256];
    int badVal(char b);
    void equal(int& i);
    void print();
public:
    BMS(string text, string query);
    vector<int> getMatches();
    void search();
};

int main(int argc, char* argv[]) {
	string txt; // text to perform search on
	string query;  // what to search for
	vector<int> bChars;
	
    //txt = argv[1];
    //query = argv[2];

	txt = "helloworldhelloworldskworld";
	query = "world";

    BMS matches(txt, query);
    	
    cout << "input txt: \"" << txt << "\"\nquery: \"" << query << "\"\n\n";

    matches.search();
}

int BMS::badVal(char b) {
    int c = b;
    return badList[c];
}

void BMS::equal(int& i) {
    int j = query.size() - 1;
    int shift;
    while (j >= 0) {
        if (text[i + j] != query[j]) {
            shift = j - badVal(text[i + j]);
            if (shift > 0) {
                i += shift;
                return;
            }
            else {
                i++;
                return;
            }
        }
        j--;
    }
    starts.push_back(i);
    i++;
}

void BMS::print() {
    std::cout << "Query found at indices:";
    for (int i = 0; i < starts.size(); i++) {
        std::cout << ' ' << starts[i];
    }
}

BMS::BMS(std::string text, std::string query) {
    this->text = text;
    this->query = query;
    int c;
    for (int i = 0; i < 256; i++) {
        badList[i] = -1;
    }
    for (int j = 0; j < query.size(); j++) {
        c = query[j];
        badList[c] = j;
    }
}

void BMS::search() {
    int i = 0;
    int limit = text.size() - query.size();
    limit += 1;
    while (i < limit) {
        equal(i);
    }
    print();
}

vector<int> BMS::getMatches() {
    return this->starts;
}