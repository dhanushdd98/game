

#include <iostream>
#include <string>
#include <cctype>

using namespace std;
int N,A[1000][1000]={0},x,y,x1,y1,bx,by,ballcount,wallhit=0,flag=0,baseR,baseL,Bhit=0;
char Q;
string direction;
void traverse();
void check();
void play();
bool wincheck();
void demolish(int,int);
void baseset();
/*Function to check whether input string is an integer*/
bool isInt(string s){
    for(int i=0;i<s.length();i++){
        if(isdigit(s[i])==false){
            return false;
        }
    }
    return true;
}
/*Function to display the matrix*/
void print(){
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            if(A[i][j]==0){cout<<"  ";}
            else if(A[i][j]>0){cout<<A[i][j]<<" ";}
            else{
                if(A[i][j]==-1||A[i][j]==-2||A[i][j]==-3){cout<<"W "; }
                if(A[i][j]==-4){cout<<"G "; }
                if(A[i][j]==-5){cout<<"o "; }
                if(A[i][j]==-10){cout<<"DE"; }
                if(A[i][j]==-15){cout<<"DS"; }
                if(A[i][j]==-20){cout<<"B "; }
                if(A[i][j]==-8){cout<<"_ "; }
                
            }
        }
    cout<<"\n";        
    }
    cout<<"Ball count is "<<ballcount<<endl;
}
/*Function to  initialise matrix and accept inputs*/
void initialise(){
    int brickstrength;
    string brick;
    
    for(int i=1;i<N-1;++i){
        A[0][i]=-1;
        A[N-1][i]=-4;
    }
    for(int i=0;i<N;++i){
        A[i][0]=-2;
        A[i][N-1]=-3;
    }
    x=N-1;y=(N/2);
    A[x][y]=-5;
    baseR=N/2;
    baseL=N/2;
    do{
        cout<<"Enter the brick's position and the brick type :";
        cin>>bx>>by;
        cin>>brick;
        if(isInt(brick)){
            brickstrength=stoi(brick);
            A[bx][by]=brickstrength;
        }
        else{
            if(brick=="DE"){ A[bx][by]=-10; }
            if(brick=="DS"){ A[bx][by]=-15; }
            if(brick=="B"){ A[bx][by]=-20; }
        }
        cout<<"Do you want to continue(Y or N)?";
        cin>>Q;
    }while(Q!='N');
    cout<<"Enter ball Count :";
    cin>>ballcount;
}
/*Function to input dirction of brick movement by user*/
void play(){
    int p=wincheck();
    print();
    if(p&&(ballcount>=0)){
        cout<<"\n\n\n\tYou win HURRAY..!!";
        exit(0);
    }
    if((ballcount<=0)&&(p==0)){
        cout<<"\n\n\n\tGAME OVER";
        exit(0);
    }
    x1=x; y1=y;
    cout<<"Enter the direction in which the ball need to traverse :";
    cin>>direction;
    if(direction=="ST"){flag=1; traverse(); }
    if(direction=="LD"){flag=2; traverse(); }
    if(direction=="RD"){flag=3; traverse(); }
}
/*Function to execute ball movement*/
void traverse(){
    while(flag==1){                         //Straight
        --x;
        check();
        }
    while(flag==2){                         //Left Diagonal
        --x; --y;
        if(A[x][y]==-2){ ++wallhit;}
        check();
        }
    while(flag==3){                         //Right Diagonal
        --x; ++y;
        if(A[x][y]==-3){ ++wallhit;}
        check();
        }
    while(flag==4){                         //Down Travel
        ++x;
        check();
        }
    while(flag==5){                         //Horizontal Right
        ++y;
        if(A[x][y]==-3){ ++wallhit;}
        check();
        }
    while(flag==6){                         //Horizontal Left
        --y;
        if(A[x][y]==-2){ ++wallhit;}
        check();
        }
    
}
/*Function to check ball and brick status for each movement*/
void check(){
    if(A[x][y]!=0){
        if(wallhit==2){
            --ballcount;
            wallhit=0;
            x=N-1; y=N/2;
            A[x1][y1]=-4;
            A[x][y]=-5;
            baseset();
            flag=0;
            play();
        }
        
        if(A[x][y]>0){
            --A[x][y];
            wallhit=0;
            flag=4;
            traverse();
        }
        else if(A[x][y]<0){
            if(A[x][y]==-1){
                flag=4;
                traverse();
            }
            else if(A[x][y]==-2){
                flag=5;
                traverse();
            }
            else if(A[x][y]==-3){
                flag=6;
                traverse();
            }
            else if(A[x][y]==-4){
                if((y!=y1)&&(A[x][y]!=-8)){
                    --ballcount;
                }
                A[x1][y1]=-4;
                A[x][y]=-5;
                baseset();
                flag=0;
                play();
            }
            else if(A[x][y]==-5){
                flag=0;
                play();
            }
            else if(A[x][y]==-8){
                A[x1][y1]=-4;
                A[x][y]=-5;
                baseset();
                flag=0;
                play();
            }
            else if((A[x][y]==-10)||(A[x][y]==-15)){
                demolish(x,y);
                flag=4;
                traverse();
            }
            else if(A[x][y]==-20){
                baseset();
                flag=4;
                traverse();
            }
        }
    }
}
/*Function to check whether every bricks are broken*/
bool wincheck(){
    bool p=1;
    for(int i=1;i<N-1;++i){
        for(int j=1;j<N-1;++j){
            if(A[i][j]!=0){
                p=0;
                return p;
            }
        }
    }
    return p;
}
/*Function to demolish bricks*/
void demolish(int m,int n){
    if(A[m][n]==-15){
        A[m][n]=0;
        for(int u=m-1;u<=m+1;++u){
            for(int v=n-1;v<=n+1;++v){
                if((u>0)&&(u<N-1)&&(v>0)&&(v<N-1)){
                    if((A[u][v]==-10)||A[u][v]==-15){
                        demolish(u,v);
                    }
                    else{
                        A[u][v]=0;
                    }
                }
                else{
                    continue;
                }
            }
        }
    }
    else if(A[m][n]==-10){
        A[m][n]=0;
        for(int v=1;v<N-1;++v){
            if(A[m][v]==-15){
                demolish(m,v);
            }
            else{
                A[m][v]=0;
            }
        }
    }
}
/*Function to execute ball base for power bricks*/
void baseset(){
    if(A[x][y]==-20){
       ++Bhit;
       A[x][y]=0;
       if(Bhit==1){
            if((A[N-1][baseR+1]==-4)||(A[N-1][baseR+1]==-5)){
                ++baseR;
            }
        }
        if(Bhit==2){
            if((A[N-1][baseL-1]==-4)||(A[N-1][baseL-1]==-5)){
                --baseL;
            }
            Bhit=0;
        }
    }
    if(baseR!=baseL){
        for(int y=baseL;y<=baseR;++y){
            if(A[N-1][y]!=-5){
                A[N-1][y]=-8;
            }
        }
    }
}

int main(){
    cout<<"Enter size of the NxN matrix :";
    cin>>N;
    initialise();
    play();
    return 0;
}
