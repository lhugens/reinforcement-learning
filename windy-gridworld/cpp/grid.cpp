#include <iostream>
#include <random>
#include <algorithm>
 
#define K 	100
#define alpha 	0.4
#define lambda 	0.9
#define gamma 	1

using namespace std;
mt19937 rnd;
uniform_real_distribution<double> uniform_dist_double{0., 1.};
uniform_int_distribution<> uniform_dist_int{0, 3};

struct walker{
    int pos[2];
    int newpos[2];
    unsigned act;
    unsigned newact;

    float moves[4][2] = {{0, -1}, {1, 0}, {-1, 0}, {0, 1}};

    float value[7][10][4] = {0};
    float  elig[7][10][4];
    double epsi;
    float delta;

    void wipe_eligibility(){
        for(int l = 0; l != 7; l++)
            for(int m = 0; m != 10; m++)
                for(int n = 0; n != 5; n++)
                    elig[l][m][n] = 0;
    }

    void is_inside(){
        if(newpos[0] < 0 || newpos[0] > 6)
            newpos[0] = pos[0];
        else if(newpos[1] < 0 || newpos[1] > 9)
            newpos[1] = pos[1];
    }

    bool terminated(){
        if(pos[0] == 3 && pos[1] == 7)
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

    void calc_delta(){
        float new_estimate = -1 + gamma * value[newpos[0]][newpos[1]][newact];
        float old_estimate = value[pos[0]][pos[1]][act];
        delta = new_estimate - old_estimate;
    }

    inline double get_rdouble(){
        return uniform_dist_double(rnd);
    }

    inline int get_rint(){
        return uniform_dist_int(rnd);
    }

    void choose_action(){
        if(get_rdouble() > epsi){
            int i = newpos[0], j = newpos[1];
            newact = distance(value[i][j], max_element(value[i][j], value[i][j] + 4));
            //cout << "greedy" << endl;
        } else {
            newact = get_rint();
            //cout << "random" << endl;
        }
    }

    void run(){

        // initialize Q(s, a) arbitrarily, already done at declaration
        int n_steps;

        for(int k = 0; k != K; k++){ // for each episode

            n_steps = 0;

            // set epsilon for exploration
            epsi = static_cast<float>(1/(k + 1));

            // initialize eligilibily = 0 for all s,a
            wipe_eligibility();

            // initialize state S
            pos[0] = 3; 
            pos[1] = 0; 

            // initialize action A
            int i = pos[0], j = pos[1];
            act = distance(value[i][j], max_element(value[i][j], value[i][j] + 4)); 
            
            while (!terminated()) { // for each step
            //for(int i=0; i!=100; i++){
                n_steps++;
                take_action();
                choose_action();

                elig[pos[0]][pos[1]][act]++;

                calc_delta();

                for(int l = 0; l != 7; l++)
                    for(int m = 0; m != 10; m++)
                        for(int n = 0; n != 4; n++){
                            value[l][m][n] += alpha * delta * elig[l][m][n];
                            elig[l][m][n] *= gamma * lambda;
                        }

                pos[0] = newpos[0]; 
                pos[1] = newpos[1]; 
                act = newact;

                if(k == K - 1)
                    cout << "pos: " << pos[0] << pos[1] << endl;
            }
            cout << n_steps << " " << epsi << endl;
        }
    }
};

int main(){
    walker bot;
    bot.run();
}
