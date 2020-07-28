#include <iostream>
#include <array>
 
using namespace std;
 
#define K 	100
#define alpha 	0.4
#define lambda 	0.9
#define gamma 	1

class walker{
public:
    float pos[2];
    float newpos[2];
    float moves[4][2] = {{0, -1}, {1, 0}, {-1, 0}, {0, 1}};
    float elig[7][10][4] = {0};
    unsigned act;
    unsigned newact;
};

int main(){
    walker bot;

    bot.elig[0][0][0] = 1;
    
    for(int i = 0; i!=7; i++){
        for(int j = 0; j!=10; j++){
            for(int k = 0; k!=4; k++){
                cout << bot.elig[i][j][k];
            }    
            cout << '\n';
        }    
    cout << '\n';
    }
}
