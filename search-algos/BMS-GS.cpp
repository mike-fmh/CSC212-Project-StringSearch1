#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>

class BMS{
    private:
        //Members:
        std::string text; //The text that we will be searching
        std::string query; //the string that will be searched for in the text
        std::vector<int> starts; //This vector will hold the indices of the matches
        std::vector<int> goodList; //This vector will hold the values we shift by (determined by the good suffix hueristic)
        std::vector<int> border;
        //Methods
        void preProcess();
        void secondary();
        int equal(int i);
    public:
        BMS(std::string text, std::string query);
        void search();
        void print();
};

int main(int argc, char *argv[]){
    BMS bms(argv[1], argv[2]);
    bms.search();
    bms.print();
}

//Private:

void BMS::preProcess(){
    int i = query.size();
    int j = query.size() + 1;
    std::vector<int> border;
    for(int i = 0; i <= query.size(); i++){
        border.push_back(0);
        goodList.push_back(0);
    }
    border[i] = j;
    while( i > 0){
        while(j <= query.size() && query[j - 1] != query[i - 1]){
            if(!goodList[j]){
                goodList[j] = j - i;
            }
            j = border[j];
        }
        i--;
        j--;
        border[i] = j;
    }
    secondary();
}
void BMS::secondary(std::vector<int> border){
    int j = border.front();
    for(int i = 0; i <= query.size(); i++){
        if(!goodList[i]){
            goodList[i] = j;
        }
        if(i == j){
            j = border[j];
        }
    }
}

int BMS::equal(int i){
    int j = query.size() - 1;
    while(j >= 0){
        if(text[i + j] != query[j]){
            if(goodList[j + 1]){
                return goodList[j + 1];
            }
            else{
                return 1;
            }
        }
        j--;
    }
    starts.push_back(i);
    return 1;
}

//Public:

BMS::BMS(std::string text, std::string query){
    this -> text = text;
    this -> query = query;
}

void BMS::search(){
    preProcess();
    int i = 0;
    while(i <= text.size() - query.size()){
        i += equal(i);
    }
}

void BMS::print(){
    if(starts.size()){
        std::cout << "Pattern found at Indices:";
        for(int i = 0; i < starts.size(); i++){
            std::cout << ' ' << starts[i];
        }
    }
    else{
        std::cout << "Pattern Not Found!";
    }
    std::cout << "\n";
}
