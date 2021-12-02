#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>

class BMS{
    private:
        std::string text;
        std::string query;
        std::vector<int> starts;
        std::vector<int> goodList;
        std::vector<int> border;
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

void BMS::preProcess(){
    int i = query.size();
    int j = query.size() + 1;
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
void BMS::secondary(){
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

BMS::BMS(std::string text, std::string query){
    this -> text = text;
    this -> query = query;
    for(int i = 0; i <= query.size(); i++){
        border.push_back(0);
        goodList.push_back(0);
    }
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