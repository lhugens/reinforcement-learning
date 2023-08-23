#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>

void print(std::vector<int>& b){
    for(int i=0; i<b.size(); i++){
        std::cout << b[i] << " ";
    }
    std::cout << std::endl;
}

bool int_in(int i, std::vector<int>& v){
    for(auto& x: v){
        if(i == x){
            return true;
        }
    }
    return false;
}

struct MasterMind
{
    //vector<int> board;
    std::vector<int> board;
    std::vector<int> board_correct;
    std::vector<int> evaluation;
    std::vector<int> used;
    int gc;
    int no_colors;


    MasterMind(unsigned d, unsigned n) : gc(d), no_colors(n)
    {
        srand((unsigned) time(0));

        board.resize(gc, 0);
        board_correct.resize(gc, 0);
        evaluation.resize(gc, 0);

        for(int i=0; i<gc; i++){
            board[i] = randint();
            board_correct[i] = randint();
        }

        print_board();
        print_board_correct();

        eval();
        print_evaluation();
    }

    void eval(){
        int p = 0;

        for(int i=0; i<gc; i++){
            if(board[i] == board_correct[i]){
                std::cout << "pretas i=" << i << " j=" << i << std::endl;
                evaluation[p] = 2;
                p++;
                used.push_back(i);
            }
        }

        for(int i=0; i<gc; i++){
            for(int j=0; j<gc && i!=j; j++){
                bool cenas = (board[i]==board_correct[j]);
                std::cout << "i=" << i << " j=" << j << " " << cenas << std::endl;
                print(used);
                if(board[i]==board_correct[j] && !int_in(i, used)){
                    std::cout << "brancas i=" << i << " j=" << j << std::endl;
                    evaluation[p] = 1;
                    p++;
                    used.push_back(i);
                }
            }
        }
    }

    int randint(){
        return std::rand() % no_colors;
    }

    void print_board(){
        std::cout << std::left << std::setw(20) << "board";
        print(board);
    }

    void print_board_correct(){
        std::cout << std::left << std::setw(20) << "board_correct";
        print(board_correct);
    }

    void print_evaluation(){
        std::cout << std::left << std::setw(20) << "evaluation";
        print(evaluation);
    }
};


int main(){
    MasterMind m(5, 3);
}
