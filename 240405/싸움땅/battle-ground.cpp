#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> guns[21][21];
int playerBoard[21][21];
int player[31][5]; //x y 방향 초기능력치 총
int point[31];
int n,m,k,x,y,d,s;

int dx[4]={0,1,0,-1};
int dy[4]={-1,0,1,0};

bool cmp(int a,int b){
    return a>b;
}

void playerboardPrinter(){
    cout<<"현재 플레이어 배치 출력\n";
    for(int i=1;i<=n;i++) {
        for (int j = 1; j <= n; j++) {
            cout << playerBoard[i][j] << " ";
        }
        cout<<endl;
    }
}

void input(){
    int tmp;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            cin>>tmp;
            guns[i][j].push_back(tmp);
        }

    for(int i=1;i<=m;i++){
        for(int j=0;j<4;j++){cin>>player[i][j];}
        playerBoard[player[i][0]][player[i][1]]=i;
    }

}

void movePlayer(int i){
    int curdirection=player[i][2];
    int nxtY=player[i][0]+dy[curdirection];
    int nxtX=player[i][1]+dx[curdirection];
    while(nxtY>n||nxtY<1||nxtX>n||nxtX<1){
        curdirection= (curdirection+2)%4;
        nxtY=player[i][0]+dy[curdirection];
        nxtX=player[i][1]+dx[curdirection];
    }
    playerBoard[player[i][0]][player[i][1]]=0;//원래 칸 0으로
    player[i][2]=curdirection;
    player[i][0]=nxtY;
    player[i][1]=nxtX;
}

void getGun(int personNum, int curY, int curX){
    int curPersonGun=player[personNum][4];
    sort(guns[curY][curX].begin(),guns[curY][curX].end(),cmp);
    if(guns[curY][curX][0]>curPersonGun){
        int tmp=curPersonGun;
        curPersonGun=guns[curY][curX][0];
        guns[curY][curX][0]=tmp;
    }
    player[personNum][4]=curPersonGun;
}

int fight(int playerA, int playerB){
    int statA=player[playerA][3]+player[playerA][4];
    int statB=player[playerB][3]+player[playerB][4];

    if(statA==statB&&player[playerA][3]>player[playerB][3])return playerA;
    if(statA>statB){
        point[playerA]+=statA-statB;
        return playerA;
    }
    point[playerB]+=statB-statA;
    return playerB;
}

void losePlayer(int personNum,int curY, int curX){
    //총 내려놓기
    int curHaveGun=player[personNum][4];
    guns[curY][curX].push_back(curHaveGun);
    player[personNum][4]=0;

    //가던 방향 이동
    int curdirection=player[personNum][2];
    int nxtY=player[personNum][0]+dy[curdirection];
    int nxtX=player[personNum][1]+dx[curdirection];
    while(nxtY>n||nxtY<1||nxtX>n||nxtX<1||playerBoard[nxtY][nxtX]!=0){//범위밖 or 다른 플레이어
        curdirection= (curdirection+1)%4;
        nxtY=player[personNum][0]+dy[curdirection];
        nxtX=player[personNum][1]+dx[curdirection];
    }
    player[personNum][2]=curdirection;
    player[personNum][0]=nxtY;
    player[personNum][1]=nxtX;

    //총 있으면 줍기
    getGun(personNum,nxtY,nxtX);
}




void playOneRound(){
    //사람 한명씩 이동
    for(int i=1;i<=m;i++){
        movePlayer(i);
        int curPlayerY=player[i][0];
        int curPlayerX=player[i][1];
        if(playerBoard[curPlayerY][curPlayerX]==0){//플레이어 없으면 총 줍기 시도
            playerBoard[curPlayerY][curPlayerX]=i; //현재 플레이어 표기
//            cout<<"플레이어 없어서 바로 이동\n";
//            playerboardPrinter();
            getGun(i,curPlayerY,curPlayerX);
        }else{//플레이어 있으면
            int existPlayer = playerBoard[curPlayerY][curPlayerX];
            int winner = fight(i,existPlayer);
            if(winner == i){
                playerBoard[curPlayerY][curPlayerX]=i;
//                cout<<"새로온 애가 승리\n";
//                playerboardPrinter();
                losePlayer(existPlayer,curPlayerY,curPlayerX);
                getGun(i,curPlayerY,curPlayerX);

            }else{
                //i패배, exist우승
//                cout<<"있던 애 승리\n";
//                playerboardPrinter();
                losePlayer(i,curPlayerY,curPlayerX);
                getGun(existPlayer,curPlayerY,curPlayerX);
            }
        }
    }
}


int main() {
    cin>>n>>m>>k;
    input();
    //playerboardPrinter();
    for(int i=0;i<k;i++){
        playOneRound();
    }
    for(int i=1;i<=m;i++){
        cout<<point[i]<<" ";
    }
}