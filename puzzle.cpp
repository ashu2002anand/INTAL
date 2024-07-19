#include<bits/stdc++.h>
using namespace std;

int help(int i,int n,vector<int>&time,vector<int>&search,int k,vector<int>&dp){
    if(i==n)
        return 0;
    
    if(dp[i]!=-1)return dp[i];
    int pick = time[i]+help(i+1,n,time,search,k,dp);
    int notpick = search[i]+help(i+k,n,time,search,k,dp);
    return dp[i] = min(pick,notpick);
}
int soln(int n,vector<int>&time,vector<int>&search,int k){
    vector<int> dp(n,-1);
    return help(0,n,time,search,k,dp);
}
int main(){
    int n,k;
    cin>>n>>k;
    vector<int> time;
    for(int i=0;i<n;i++){
        int temp;
        cin>>temp;
        time.push_back(temp);
    }
    vector<int> search;
    for(int i=0;i<n;i++){
        int temp;
        cin>>temp;
        search.push_back(temp);
    }
    cout<<soln(n,time,search,k)<<endl;
    return 0;
}