#include<stdio.h>
int arr[] = {5,1,3,7,9,2,4,6,8};
int place[3][3] = {{2,2,2},{2,2,2},{2,2,2}};
int turn = 0;
int p;
int win = 0;
int check[8][3] = {{0,1,2},{0,4,8},{0,3,6},{1,4,7},{2,4,6},{2,5,8},{3,4,5},{6,7,8}};
int checkWin(){
    for(int i=0;i<8;i++){
        int a = check[i][0]/3;
        int b = check[i][0]%3;
        int k = place[a][b];
        if(k == 2)continue;
        int x;
        for(x = 1;x<3;x++){
            int p = check[i][x]/3;
            int q = check[i][x]%3;
            if(place[p][q] != k)break;
        }
        if(x == 3)return 1;
    }
    return 0;
}
int done(){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(place[i][j] == 2)return 0;
        }
    }
    return 1;
}
void matrix(){
    printf("\n");
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(place[i][j] == 2){
                printf("%s","  ");
            }
            else if(place[i][j] == 3){
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
int main(){
    printf("Whose turn is their 1 for computer and 0 for user  ");
    scanf("%d",&turn);
    p = turn;
    matrix();
    while(!win){
        int val,userVal;
        if(p == 1)val = 5;
        else val = 3;
        if(p == 1)userVal = 3;
        else userVal = 5;
        if(turn){
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    if(place[i][j] == 2){
                        place[i][j] = val;
                        int k = checkWin();
                        if(k){
                            matrix();
                            printf("%s","\nComputer won the match");
                            return 0;
                        }
                        place[i][j] = 2;
                    }
                }
            }
            int b = 0;
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    if(place[i][j] == 2){
                        place[i][j] = userVal;
                        int k = checkWin();
                        if(k){
                            place[i][j] = val;
                            b = 1;
                            break;
                        }
                        place[i][j] = 2;
                    }
                }
                if(b)break;
            }
            if(b){
                matrix();
                if(done()){
                    printf("%s","\nMatch Draw");
                    return 0;
                }
                turn = !turn;
                continue;
            }
            for(int i=0;i<9;i++){
                int x = arr[i];
                x--;
                int a = x/3;
                int b = x%3;
                if(place[a][b] == 2){
                    place[a][b] = val;
                    break;
                }
            }
            if(done()){
                printf("%s","\nMatch Draw");
                return 0;
            }
            turn = !turn;
        }
        else{
            int o = 0;
            int k;
            while(!o){
                printf("Enter position you want to select from 1 to 9 ");
                scanf("%d",&k);
                int a = (k-1)/3;
                int b = (k-1)%3;
                if(k>9||k<0||place[a][b] != 2){
                    printf("\nInvalid Position Please enter again\n");
                }
                else{
                    o = 1;
                }
            }
            k--;
            int i = k/3;
            int j = k%3;
            if(p == 0)
            place[i][j] = 5;
            else place[i][j] = 3;
            turn = !turn;
        }
        matrix();
        if(done()){
            printf("%s","\nMatch Draw");
            return 0;
        }
        if(checkWin()){
            printf("%s","\nYou Won the match");
            return 0;
        }
    }
    return 0;
}