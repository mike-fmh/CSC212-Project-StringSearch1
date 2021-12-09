#include <iostream>
#include <vector>
#include <string>

class BMS{
    private:
        //the various members we will need like our text and query string, our indice vector and our bad character array.
        //members:
        std::string text; //string holding the text that will be searched
        std::string query; //string holding the query we are searching for within text
        std::vector<int> starts; //vector that holds the beginning indices of the locations of query found in text
        std::vector<int>badList; //vector that holds a a -1 at indices equal to ascii values not found in query, while if the letter is found in query it holds the idex of its last position in the query
        //methods:
        void badProcess();
        int badVal(char b); //badVal returns the value from the badList stored at the indice equal to the ascii value of the parameter character
        void equal(int &i); //equal checks whether or not query == text at this position if not it shifts.
        void print();
    public:
        BMS(std::string text, std::string query); //assigns the value of text and query based on the command line arguments entered
        void search(); //does the searching through text for all appearences of query
};

int main(int argc, char *argv[]){
    BMS bms(argv[1], argv[2]);
    bms.search();
}

void BMS::badProcess(){
    int c;
    for(int i = 0; i < 256; i++){
        badList.push_back(-1);
    }
    for(int j = 0; j < query.size(); j++){
        c = query[j];
        badList[c] = j;
    }
}

int BMS::badVal(char b){
    int c = b;
    return badList[c];
}

void BMS::equal(int &i){
    int j = query.size() - 1;
    int shift;
    while(j >= 0){
        if(text[i + j] != query[j]){
            shift = j - badVal(text[i + j]);
            if(shift > 0){
                i += shift;
                std::cout << text << "\n";
                for(int g = 0; g < i; g++){
                    std::cout << ' ';
                }
                std::cout << query << "\n";
                return;
            }
            else{
                i++;
                std::cout << text << "\n";
                for(int g = 0; g < i; g++){
                    std::cout << ' ';
                }
                std::cout << query << "\n";
                return;
            }
        }
        j--;
    }
    starts.push_back(i);
    i++;
    if(i + (query.size() - 1) < text.size()){
        std::cout << text << "\n";
        for(int f = 0; f < i; f++){
            std::cout << ' ';
        }
        std::cout << query << "\n";
    }
}

void BMS::print(){
    std::cout << "Query found at indices:";
    for(int i = 0; i < starts.size(); i++){
        std::cout << ' ' << starts[i];
    }
}

//Private:

BMS::BMS(std::string text, std::string query){
    this -> text = text;
    this -> query = query;
}

void BMS::search(){
    badProcess();
    int i = 0;
    std::cout << text << "\n";
    std::cout << query << "\n";
    int limit = text.size() - query.size();
    limit += 1;
    while(i < limit){
        equal(i);
    }
    print();
}
