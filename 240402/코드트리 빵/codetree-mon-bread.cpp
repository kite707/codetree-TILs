#include <iostream>
#include <queue>
#include <tuple>
using namespace std;

int board[15][15];
int n,m,t,a,b;
int convLocation[2][31];

int dx[4]={0,1,-1,0};
int dy[4]={1,0,0,-1};

void boardPrinter(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

pair<int,int> bfs(int curX,int curY,int convX,int convY){
    //cout<<curX<<" "<<curY<<" "<<convX<< "  "<<convY<<endl;
    queue<pair<int,int>> q;
    q.push({convY,convX});
    while(!q.empty()){
        auto tp=q.front();
        int curx=tp.second;
        int cury=tp.first;
        q.pop();

        for(int i=0;i<4;i++){
            int nxtX=curx+dx[i];
            int nxtY=cury+dy[i];
            if(nxtX>n||nxtY>n||nxtX<0||nxtY<0)continue;
            if(nxtX==curX&&nxtY==curY){return {cury,curx};}
            if(board[nxtY][nxtX]==-1)continue;
            q.push({nxtY,nxtX});

        }
    }
    return{-1,-1};
}

pair<int,int> getBaseLocatioin(int curX,int curY){
    //cout<<curX<< "  "<<curY<<endl;
    //boardPrinter();
    queue<pair<int,int>> q;
    q.push({curY,curX});
    while(!q.empty()){
        auto tp=q.front();
        int curx=tp.second;
        int cury=tp.first;
        if(board[cury][curx]==1){
            return {cury,curx};
        }
        q.pop();
        for(int i=3;i>=0;i--){
            int nxtX=curx+dx[i];
            int nxtY=cury+dy[i];
            if(nxtX>n||nxtY>n||nxtX<0||nxtY<0)continue;
            if(board[nxtY][nxtX]==-1)continue;
            q.push({nxtY,nxtX});
        }
    }
}


int main(){
    cin>>n>>m;
    queue<tuple<int,int,int>> conv;
    queue<tuple<int,int,int>> curloc;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>board[i][j];
        }
    }
    for(int i=0;i<2;i++){
        for(int j=0;j<31;j++){
            convLocation[i][j]=-1;
        }
    }
    for(int i=1;i<=m;i++){
        cin>>a>>b;
        convLocation[0][i]=a-1;//y
        convLocation[1][i]=b-1;//x
        //board[a-1][b-1]=m+1000;
    }

    int curTime = 1;
    int arrivedPerson=0;
    queue<tuple<int,int,int>>onboard;
    queue<pair<int,int>> toMark;
    while(arrivedPerson!=m){
        //if 격자에 있는 사람 있으면 이동
        if(!onboard.empty()){
            int curSize=onboard.size();
            for(int i=0;i<curSize;i++){
                auto bb=onboard.front();
                int personNum=get<0>(bb);
                int curY = get<1>(bb);
                int curX=get<2>(bb);
                onboard.pop();
                auto newLoc=bfs(curX,curY,convLocation[1][personNum],convLocation[0][personNum]);
                int newX=newLoc.second;
                int newY=newLoc.first;
                if(convLocation[1][personNum]==newX&&convLocation[0][personNum]==newY){
                    arrivedPerson++;
                    toMark.push({newY,newX});
                }else{
                    onboard.push({personNum,newY,newX});
                }
            }
            //도착한 칸들 못지나가게 마크
            while(!toMark.empty()){
                auto tmp = toMark.front();
                board[tmp.first][tmp.second]=-1;
                toMark.pop();
            }

        }
        //베이스캠프 배치
        if(curTime<=m&&convLocation[1][curTime]!=-1&&convLocation[0][curTime]!=-1){
            //cout<<"curTime is : "<<curTime<<endl;
            //cout<<"convloc: x,y  "<<convLocation[1][curTime]<<"  "<<convLocation[0][curTime]<<endl;
            auto base= getBaseLocatioin(convLocation[1][curTime],convLocation[0][curTime]);
            board[base.first][base.second]=-1;
            //cout<<"베이스캠프 표시 후: "<<endl;
            //boardPrinter();
            //cout<<"debug: "<<base.first<<"  "<<base.second<<endl;
            onboard.push({curTime,base.first,base.second});//사람, y, x
        }
        //cout<<"시간증가\n";
        curTime++;
    }
    cout<<curTime-1<<endl;
    //    auto k= bfs(2,1);
    //    cout<<k.first<<"  "<<k.second<<endl;


}