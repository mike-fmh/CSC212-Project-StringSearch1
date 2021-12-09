#include <iostream>
#include <vector>
#include <string>

class BMS{
    private:
        //the various members we will need like our text and query string, our indice vector and our badList vector.
        //members:
        std::string text; //string holding the text that will be searched
        std::string query; //string holding the query we are searching for within text
        std::vector<int> starts; //vector that holds the beginning indices of the locations of query found in text
        std::vector<int>badList; //vector that holds a a -1 at indices equal to ascii values not found in query, while if the letter is found in query it holds the idex of its last position in the query
        //methods:
        void badProcess();
        int badVal(char b); //badVal returns the value from the badList stored at the indice equal to the ascii value of the parameter character
        void equal(int &i); //equal checks whether or not query == substring text at this position if not it shifts using j and the badlist, if query == substring of text it shifts by just 1.
        void print();
    public:
        BMS(std::string text, std::string query); //assigns the value of text and query based on the command line arguments entered
        void search(); //does the searching through text for all appearences of query
};

int main(int argc, char *argv[]){
    BMS bms(argv[1], argv[2]); //calling the constructor
    bms.search(); //calls the search method
}

void BMS::badProcess(){
    //intiallizes the vector with -1
    int c;
    for(int i = 0; i < 256; i++){
        badList.push_back(-1);
    }
    //assigns the values at the index of the character's ascii value with the character's index within the query.
    //this will leave us with a vector containing -1s for any character that is not found within query and for characters in query the index of their last position within the query
    for(int j = 0; j < query.size(); j++){
        c = query[j];
        badList[c] = j;
    }
}

int BMS::badVal(char b){
    //function that converts the char paremter to its ascii value then returns the value found at that index with badList
    int c = b;
    return badList[c];
}

void BMS::equal(int &i){
    int j = query.size() - 1; //this initializes j to the last index of query
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
    print(); //print is called to return the location of the query within the text
}
