#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>

using namespace std;

struct MasterMind
{
    vector<int> board;
    vector<int> board_correct;
    vector<int> evaluation;
    int dimension;
    int no_colors;

    MasterMind(unsigned d, unsigned n) : dimension(d), no_colors(n)
    {
        srand((unsigned) time(0));

        evaluation.resize(dimension, 0);
        board.resize(dimension, 0);
        board_correct.resize(dimension, 0);

        for(int i=0; i<dimension; i++){
            board[i] = randint();
            board_correct[i] = randint();
        }

        eval();
    }

    void eval(){
        int p = 0;

        for(int i=0; i<dimension; i++){
            if(board[i] == board_correct[i]){
                evaluation[p] = 2;
                p++;
            }
        }
        vector<int> used;

        for(int i=0; i<dimension; i++){
            for(int j=0; j<dimension && i!=j; j++){
                if(board[i] == board_correct[j]){
                    for(auto& u: used){
                        if(board[i] != u){
                            evaluation[p] = 1;
                            p++;
                            used.push_back(i);
                        }
                    }
                }
            }
        }
    }

    int randint(){
        return rand() % no_colors;
    }
};

void print(vector<int>& b){
    for(int i=0; i<b.size(); i++){
        cout << b[i] << " ";
    }
    cout << endl;
}

int main(){
    MasterMind m(5, 3);

    //m.print();
    std::cout << left << setw(20) << "board";
    print(m.board);
    std::cout << left << setw(20) << "board_correct";
    print(m.board_correct);
    std::cout << left << setw(20) << "evaluation";
    print(m.evaluation);
}
