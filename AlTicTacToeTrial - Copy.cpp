#include<iostream>
#include<vector>
#include<limits.h>
using namespace std;

int check[8][3] = {{0,1,2},{0,4,8},{0,3,6},{1,4,7},{2,4,6},{2,5,8},{3,4,5},{6,7,8}};
int start,curr,valC,valU,position;
vector<vector<int>> matrix(3,vector<int>(3,2));
int checkWin(){
    for(int i=0;i<8;i++){
        int a = check[i][0]/3;
        int b = check[i][0]%3;
        int k = matrix[a][b];
        if(k == 2)continue;
        int x;
        for(x = 1;x<3;x++){
            int p = check[i][x]/3;
            int q = check[i][x]%3;
            if(matrix[p][q] != k)break;
        }
        if(x == 3)return 1;
    }
    return 0;
}
int done(){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(matrix[i][j] == 2)return 0;
        }
    }
    return 1;
}
void put(int position,int k){
    int i = position/3;
    int j = position%3;
    matrix[i][j] = k;
}

void printMatrix(){
    printf("\n");
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(matrix[i][j] == 2){
                printf("%s","  ");
            }
            else if(matrix[i][j] == 3){
                printf("%s","O ");
            }
            else{
                printf("%s","X ");
            }
        }
        printf("\n");
        for(int k=0;k<6;k++)printf("%s","-");
        printf("\n");
    }
}

int getMinC(){
    int ans = 0;
    for(int i=0;i<8;i++){
        bool b = true;
        for(int j=0;j<3;j++){
            int x = check[i][j]/3;
            int y = check[i][j]%3;
            if(matrix[x][y] != valC && matrix[x][y] != 2){
                b = false;
                break;
            }
        }
        if(b)ans++;
    }
    return ans;
}

int getMinU(){
    int ans = 0;
    for(int i=0;i<8;i++){
        bool b = true;
        for(int j=0;j<3;j++){
            int x = check[i][j]/3;
            int y = check[i][j]%3;
            if(matrix[x][y] != valU && matrix[x][y] != 2){
                b = false;
                break;
            }
        }
        if(b)ans++;
    }
    return ans;
}

int getMin(){
    return getMinC() - getMinU();
}

int getMax(int getM,int turn,int kk,bool maximize){
    if(kk>0){
        int ans;
        if(!maximize)
        ans = INT_MAX;
        else 
        ans = INT_MIN;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(matrix[i][j] == 2){
                    matrix[i][j] = turn;
                    int tt = turn == valU ? valC : valU;
                    if(!maximize)
                    ans = min(ans,getMax(getM,tt,kk-1,!maximize));
                    else
                    ans = max(ans,getMax(getM,tt,kk-1,!maximize));
                    matrix[i][j] = 2;
                }
            }
        }
        return ans;
    }
    else{
        return getMin();
    }
}

int getEmptyCells(){
    int ans = 0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(matrix[i][j] == 2)ans++;
        }
    }
    return ans;
}

int main(){
    int kk = 1;
    cout<<"Choose first turn 1 for computer and 0 for you "<<endl;
    cin>>start;
    cout<<"Enter which level Al you want to play 1 to 9 "<<endl;
    cin>>kk;
    curr = start;
    valC = (start == 1)?5:3;
    valU = (start == 1)?3:5;
    printMatrix();
    while(1){
        if(curr){
            int x,y;
            int get = INT_MIN;
            kk = min(kk,getEmptyCells());
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    if(matrix[i][j] == 2){
                        matrix[i][j] = valC;
                        int p = getMax(get,valU,kk-1,false);
                        if(p > get){
                            x = i;
                            y = j;
                            get = p;
                        }
                        matrix[i][j] = 2;
                    }
                }
            }
            put(x*3+y,valC);
            curr = 0;
        }
        else{
            bool b = true;
            while(b){
                cout<<endl<<"Enter value between 1 to 9 "<<endl;
                cin>>position;
                position--;
                int i = position/3;
                int j = position%3;
                if(matrix[i][j] != 2||i>2){
                    cout<<endl<<"Invalid move try again "<<endl;
                }
                else{
                    break;
                }
            }
            put(position,valU);
            curr = 1;
        }
        printMatrix();
        bool b1 = checkWin();
        if(b1&&!curr)cout<<endl<<"Oops Computer won the match"<<endl;
        else if(b1&&curr)cout<<endl<<"Yes you won the match"<<endl;
        if(b1)break;
        if(done()){
            cout<<endl<<"Match Draw "<<endl;
            break;
        }
    }
    return 0;
}