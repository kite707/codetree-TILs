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
    bool cboard[15][15];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cboard[i][j]=false;
        }
    }
    queue<pair<int,int>> q;
    q.push({convY,convX});
    while(!q.empty()){
        auto tp=q.front();
        int curx=tp.second;
        int cury=tp.first;
        q.pop();
        cboard[cury][curx]=true;

        for(int i=0;i<4;i++){
            int nxtX=curx+dx[i];
            int nxtY=cury+dy[i];
            if(nxtX>=n||nxtY>=n||nxtX<0||nxtY<0)continue;
            if(nxtX==curX&&nxtY==curY){return {cury,curx};}
            if(cboard[nxtY][nxtX])continue;
            if(board[nxtY][nxtX]==-1)continue;

            q.push({nxtY,nxtX});

        }
    }
    return{-1,-1};
}

pair<int,int> getBaseLocatioin(int curX,int curY){
    priority_queue<tuple<int,int,int>,vector<tuple<int,int,int>>,greater<tuple<int,int,int>>> pq;
    int cboard[15][15];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cboard[i][j]=0;
        }
    }
    cboard[curY][curX]=1;
    queue<pair<int,int>> q;
    q.push({curY,curX});
    while(!q.empty()){
        auto tp=q.front();
        int curx=tp.second;
        int cury=tp.first;
        int nxtCost=cboard[cury][curx]+1;
        q.pop();
        for(int i=3;i>=0;i--){
            int nxtX=curx+dx[i];
            int nxtY=cury+dy[i];
            if(nxtX>=n||nxtY>=n||nxtX<0||nxtY<0)continue;
            if(board[nxtY][nxtX]==-1)continue;
            if(cboard[nxtY][nxtX]!=0)continue;
            q.push({nxtY,nxtX});
            cboard[nxtY][nxtX]=nxtCost;
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(board[i][j]==1&&cboard[i][j]!=0)pq.push({cboard[i][j],i,j});
        }
    }
    return {get<1>(pq.top()),get<2>(pq.top())};
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
            //cout<<"curTime is "<<curTime<<endl;
            for(int i=0;i<curSize;i++){
                //cout<<"위치 이동 시작\n";
                auto bb=onboard.front();
                int personNum=get<0>(bb);
                int curY = get<1>(bb);
                int curX=get<2>(bb);
                //cout<<"이동 전 사람, y x is  "<<personNum<<"  " <<curY<<"  "<<curX<<endl;
                onboard.pop();
                auto newLoc=bfs(curX,curY,convLocation[1][personNum],convLocation[0][personNum]);
                int newX=newLoc.second;
                int newY=newLoc.first;
                //cout<<"이동 후 사람 y x "<<personNum<<" "<<newY<<"  "<<newX<<endl;
                if(convLocation[1][personNum]==newX&&convLocation[0][personNum]==newY){
                    arrivedPerson++;
                    //cout<<"이 사람은 도착, cur arrived Person is "<<arrivedPerson<<endl;
                    toMark.push({newY,newX});
                }else{
                    onboard.push({personNum,newY,newX});
                }
            }
            //도착한 칸들 못지나가게 마크
            //cout<<"마킹 시작\n";
            while(!toMark.empty()){
                auto tmp = toMark.front();
                board[tmp.first][tmp.second]=-1;
                toMark.pop();
            }
            //boardPrinter();

        }
        //베이스캠프 배치
        if(curTime<=m&&convLocation[1][curTime]!=-1&&convLocation[0][curTime]!=-1){
            //cout<<"curTime is : "<<curTime<<endl;
            //cout<<"convloc: y,x  "<<convLocation[0][curTime]<<"  "<<convLocation[1][curTime]<<endl;
            auto base= getBaseLocatioin(convLocation[1][curTime],convLocation[0][curTime]);
            //cout<<"base위치는: "<<base.first<<"  "<<base.second<<endl;
            board[base.first][base.second]=-1;
//            cout<<"base 배치 후 \n";
//            boardPrinter();
            onboard.push({curTime,base.first,base.second});//사람, y, x
        }
        curTime++;
    }
    cout<<curTime-1<<endl;
    //    auto k= bfs(2,1);
    //    cout<<k.first<<"  "<<k.second<<endl;


}