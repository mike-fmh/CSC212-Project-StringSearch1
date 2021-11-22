#include <iostream>
#include <vector>
#include <string>

class BMS{
    private:
        //the various members we will need like our text and query string, our indice vector and our bad character array.
        std::string text;
        std::string query;
        std::vector<int> starts;
        int badList[256];
        //badVal returns the value from the badList stored at the indice equal to the ascii value of the parameter character
        int badVal(char b);
        //equal checks whether or not query == text at this position if not it shifts.
        void equal(int &i);
        void print();
    public:
        BMS(std::string text, std::string query);
        void search();
};

int main(int argc, char *argv[]){
    BMS bms(argv[1], argv[2]);
    bms.search();
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

BMS::BMS(std::string text, std::string query){
    this -> text = text;
    this -> query = query;
    int c;
    for(int i = 0; i < 256; i++){
        badList[i] = -1;
    }
    for(int j = 0; j < query.size(); j++){
        c = query[j];
        badList[c] = j;
    }
}

void BMS::search(){
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
