#include <iostream>
#include <random>
 
#define K 	100
#define alpha 	0.4
#define lambda 	0.9
#define gamma 	1

using namespace std;
mt19937 rnd;
uniform_real_distribution<double> uniform_dist_double{0., 1.};
uniform_int_distribution<> uniform_dist_int{0, 3};

struct walker{
    int pos[2] = {0, 3};
    int newpos[2] = {0, 3};
    unsigned act = 2;
    unsigned newact = 2;

    float moves[4][2] = {{0, -1}, {1, 0}, {-1, 0}, {0, 1}};
    float elig[7][10][4] = {0};
    float value[7][10][4] = {0};
    float epsi;

    void is_inside(){
        if(newpos[0] < 0 || newpos[0] > 6)
            newpos[0] = pos[0];
        else if(newpos[1] < 0 || newpos[1] > 9)
            newpos[1] = pos[1];
    }

    bool terminated(){
        if(pos[0] == 3 || pos[1] == 7)
            return true;
        return false;
    }

    void wind(){
        if(newpos[1] > 2 && newpos[1] < 9){
            if(newpos[1] == 6 || newpos[1] == 7)
                newpos[0] -= 2;
            else
                newpos[0] -= 1;
        }
        if(newpos[0] < 0)
            newpos[0] = 0;
    }

    void take_action(){
        for(int i = 0; i != 2; i++)
            newpos[i] = pos[i] + moves[act][i];
        is_inside();
    }

    float delta(){
        float new_estimate = -1 + gamma * value[newpos[0]][newpos[1]][newact];
        float old_estimate = value[pos[0]][pos[1]][act];
        return new_estimate - old_estimate;
    }

    inline double get_rdouble(){
        return uniform_dist_double(rnd);
    }

    inline int get_rint(){
        return uniform_dist_int(rnd);
    }

    void choose_action(){
        newact = get_rint();
    }


};

int main(){
    walker bot;

    cout << bot.newact << endl;
    bot.choose_action();
}
