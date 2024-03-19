#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin>>n;
    vector<int> v;
    while(n--){

        string s;
        int n;
        cin>>s;
        if(s=="push_back"){
            cin>>n;
            v.push_back(n);
        }
        else if(s=="get"){
            cin>>n;
            cout<<v[n-1]<<"\n";
        }else if(s=="size"){
            cout<<v.size()<<"\n";
        }else if(s=="pop_back"){
            v.pop_back();
        }
    }
    return 0;
}