#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int treeSaver[100001][3];
int authority[100001];
bool isDisabled[100001];
int curAns;
vector <pair<int,int>> parents;
int Q,N;

int findloc(int parents, int son){
    if(treeSaver[parents][0]==son)return 0;
    return 1;
}

int findParents(int tmp){
    int start =1;
    int end=Q;
    while(true){
        int mid=(start+end)/2;
        int cand=parents[mid].first;
        if(cand<tmp)start=mid+1;
        if(cand>tmp)end=mid-1;
        if(cand==tmp)return parents[mid].second;
    }
    return -1;
}

void findAlarm(int num,int curDepth){
    int left=treeSaver[num][0];
    int right=treeSaver[num][1];
    //cout<<"curnum, left right is : "<<num<<" "<<left<<" "<<right<<endl;
    if(left!=0&&isDisabled[left]==false){
        if(authority[left]>=curDepth){
            curAns++; 
        }
        findAlarm(left,curDepth+1);
        
    }
    if(right!=0&&isDisabled[right]==false){
        if(authority[right]>=curDepth){
            curAns++;
        }
        findAlarm(right,curDepth+1);
    }
}
int main() {

    cin>>Q>>N;
    int code,par,auth;
    for(int i=0;i<N;i++){
        cin>>code;
        if(code==100){
            for(int i=1;i<=Q;i++){
                cin>>par;
                parents.push_back({i,par});
                if(treeSaver[par][0]==0){
                    treeSaver[par][0]=i;
                }else{
                    treeSaver[par][1]=i;
                }
            }
            sort(parents.begin(),parents.end());
            for(int i=1;i<=Q;i++){
                cin>>authority[i];
            }
        }
        else if(code==200){
            cin>>par;
            if(isDisabled[par])isDisabled[par]=false;
            else isDisabled[par]=true;
        }
        else if(code==300){
            cin>>par>>auth;
            authority[par]=auth;
        }
        else if(code==400){
            cin>>par>>auth;
            int parents1=findParents(par);
             int parents2=findParents(auth);
             int locPar=findloc(parents1,par);
             int locAuth=findloc(parents2,auth);
             treeSaver[parents1][locPar]=auth;
             treeSaver[parents2][locAuth]=par;

        }
        else if(code==500) {
            //cout<<"500 돌입"<<endl;
             cin >> par;
             curAns = 0;
             findAlarm(par, 1);
             cout << curAns << "\n";
        }

    }
    return 0;
}