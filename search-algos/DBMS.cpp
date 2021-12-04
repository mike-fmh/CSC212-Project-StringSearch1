#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <iomanip>

class Dual{
    private:
        //members:
        std::string text;
        std::string query;
        std::vector<int> goodList;
        std::vector<int> badList;
        std::vector<int> starts;
        //methods:

        int equal(int i);
        int shifter(int j, int ch);
    public:
        Dual(std::string text, std::string query);
        void search();
        void print();
        void goodProcess();
        void badProcess();
};

int main(int argc, char *argv[]){
    Dual dual(argv[1], argv[2]);
    dual.goodProcess();
    dual.badProcess();
    dual.search();
    dual.print();
}

//private:

void Dual::goodProcess(){
    std::vector<int> border;
    for(int f = 0; f <= query.size(); f++){
        goodList.push_back(0);
        border.push_back(0);
    }
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
    j = border.front();
    for(int f = 0; f <= query.size(); f++){
        if(!goodList[f]){
            goodList[f] = j;
        }
        if(f == j){
            j = border[j];
        }
    }
}

void Dual::badProcess(){
    for(int i = 0; i < 256; i++){
        badList.push_back(-1);
    }
    for(int j = 0; j < query.size(); j++){
        badList[query[j]] = j;
    }
}

int Dual::equal(int i){
    for(int j = query.size() - 1; j >= 0; j--){
        if(text[i + j] != query[j]){
            return shifter(j, text[i + j]);
        }
    }
    starts.push_back(i);
    return 1;
}

int Dual::shifter(int j, int ch){
    int bad = j - badList[ch];
    int good = goodList[j + 1];
    if(good > bad){
        return good;
    }
    else{
        return bad;
    }
}

//public:

Dual::Dual(std::string text, std::string query){
    this -> text = text;
    this -> query = query;
}

void Dual::search(){
    //goodProcess();
    //badProcess();
    int i = 0;
    while(i <= text.size() - query.size()){
        i += equal(i);
    }
}

void Dual::print(){
    if(starts.size()){
        std::cout << "Pattern found at Indices:";
        for(int i = 0; i < starts.size(); i++){
            std::cout << ' ' << starts[i];
        }
    }
    else{
        std::cout << "Pattern Not Found!";
    }
    std::cout << "\n" << testStr << "\n";
}