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

//bool int_in(int i, std::vector<int>& v){
//    for(auto& x: v){
//        if(i == x){
//            return true;
//        }
//    }
//    return false;
//}

bool int_in(int i, const std::vector<int>& v) {
    return std::find(v.begin(), v.end(), i) != v.end();
}

struct MasterMind
{
    //vector<int> board;
    std::vector<int> board;
    std::vector<int> board_correct;
    std::vector<int> evaluation;
    std::vector<int> used;
    int dim;
    int no_colors;


    MasterMind(unsigned d, unsigned n) : dim(d), no_colors(n)
    {
        srand((unsigned) time(0));

        board.resize(dim, 0);
        board_correct.resize(dim, 0);

        for(int i=0; i<dim; i++){
            board[i] = randint();
            board_correct[i] = randint();
        }

        print_board();
        print_board_correct();

        eval();
        print_evaluation();
    }

    void eval(){
        std::vector<int> used_i;
        std::vector<int> used_j;

        for(int i=0; i<dim; i++){
            for(int j=0; j<dim; j++){
                if(i==j && !int_in(i, used_i) && !int_in(j, used_j) && board[i]==board_correct[j]){
                    evaluation.push_back(2);
                    used_i.push_back(i);
                    used_j.push_back(j);
                    std::cout << "pretas i=" << i << " j=" << j << std::endl;
                } else if(i!=j && !int_in(i, used_i) && !int_in(j, used_j) && board[i]==board_correct[j]){
                    evaluation.push_back(1);
                    used_i.push_back(i);
                    used_j.push_back(j);
                    std::cout << "brancas i=" << i << " j=" << j << std::endl;
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
