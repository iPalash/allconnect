#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <vector> 
#define FOR(i,n) for (int i = 0; i < n; i++)
#define INF 10000
#define PB push_back

using namespace std; 
int MODE=0;
int f1(vector<string> &board, int N, int M, int K)
{
    int arr[2] = {0, 0};
    int k = K;
    for(int i = 0; i < N; i++)
    {
        FOR(j, M)
        {
            if(board[i][j] == '.')
                continue;
            int l_k = 0;
            // diagonally upwards
            for(;l_k < k && i >= l_k && j + l_k < M; l_k++)
            {
                if(board[i][j] != board[i - l_k][j + l_k])
                    break;
            }
            if(l_k == k)
                arr[board[i][j] == 'O']++;

            l_k = 0;
            // rightside
            for(;l_k < k && j + l_k < M; l_k++)
            {
                if(board[i][j] != board[i][j + l_k])
                    break;
            }
            if(l_k == k)
                arr[board[i][j] == 'O']++;          

            l_k = 0;
            // diagonally downwards
            for(;l_k < k && i + l_k < N && j + l_k < M; l_k++)
            {
                if(board[i][j] != board[i + l_k][j + l_k])
                    break;
            }
            if(l_k == k)
                arr[board[i][j] == 'O']++;

            l_k = 0;
            // downwards
            for(;l_k < k && i + l_k < N; l_k++)
            {
                if(board[i][j] != board[i + l_k][j])
                    break;
            }
            if(l_k == k)
                arr[board[i][j] == 'O']++;
        }
    }
    return arr[0] - arr[1]; 
}
int f3(vector<string> &board, int N, int M, int K)
{
    int arr[2] = {0, 0};
    int k = K;
    for(int i = 0; i < N; i++)
    {
        FOR(j, M)
        {
            if(board[i][j] == '.')
                continue;
            int l_k = 0;
            bool flag =true;
            // diagonally upwards
            for(;l_k < k && i >= l_k && j + l_k < M; l_k++)
            {
                if (board[i-l_k][j+l_k]=='.' && flag) {
                    flag=false;
                }
                else if(board[i][j] != board[i - l_k][j + l_k])
                    break;
            }
            if(l_k == k && !flag)
                arr[board[i][j] == 'O']++;

            l_k = 0;
            flag=true;
            // rightside
            for(;l_k < k && j + l_k < M; l_k++)
            {
                if (board[i][j+l_k]=='.' && flag) 
                    flag=false;
                else if(board[i][j] != board[i][j + l_k])
                    break;
            }
            if(l_k == k && !flag)
                arr[board[i][j] == 'O']++;          

            l_k = 0;
            flag=true;
            // diagonally downwards
            for(;l_k < k && i + l_k < N && j + l_k < M; l_k++)
            {
                if (board[i + l_k][j + l_k]=='.' && flag)
                    flag=false;
                else if(board[i][j] != board[i + l_k][j + l_k])
                    break;
            }
            if(l_k == k && !flag)
                arr[board[i][j] == 'O']++;

            l_k = 0;
            flag=true;
            // downwards
            for(;l_k < k && i + l_k < N; l_k++)
            {
                if (board[i + l_k][j]=='.' && flag)
                    flag=false;
                else if(board[i][j] != board[i + l_k][j])
                    break;
            }
            if(l_k == k && !flag)
                arr[board[i][j] == 'O']++;
        }
    }
    if (MODE==1) arr[0]+=arr[0];
    if (MODE==-1) arr[0]-=arr[1];
    return arr[0] - arr[1]; 
}

#define inboard(x,y) (0<=(x) && (x)<N && 0<=(y) && (y)<M)
vector<int> f2(vector<string> &board, int N, int M, int K)
{
    int a[2] = {0, 0};
    int b[2] = {0, 0};
    int k = K;
    for(int i = 0; i < N; i++)
    {
        FOR(j, M)
        {
            if(board[i][j] == '.')
                continue;
            int l_k = 0;
            // diagonally upwards
            for(;l_k < k && i >= l_k && j + l_k < M; l_k++)
            {
                if(board[i][j] != board[i - l_k][j + l_k])
                    break;
            }
            if(l_k == k){
                if( ( inboard(i+1,j-1) && board[i+1][j-1] == '.') || ( inboard(i-l_k,j+l_k) && board[i-l_k][j+l_k] == '.') )
                    a[board[i][j] == 'O']++;
                if( ( inboard(i+1,j-1) && board[i+1][j-1] == '.') && ( inboard(i-l_k,j+l_k) && board[i-l_k][j+l_k] == '.') )
                    b[board[i][j] == 'O']++;
            }

            l_k = 0;
            // rightside
            for(;l_k < k && j + l_k < M; l_k++)
            {
                if(board[i][j] != board[i][j + l_k])
                    break;
            }
            if(l_k == k){
                if( ( inboard(i,j-1) && board[i][j-1] == '.') || ( inboard(i,j+l_k) && board[i][j+l_k] == '.') )
                    a[board[i][j] == 'O']++;       
                if( ( inboard(i,j-1) && board[i][j-1] == '.') && ( inboard(i,j+l_k) && board[i][j+l_k] == '.') )
                    b[board[i][j] == 'O']++;       
            }

            l_k = 0;
            // diagonally downwards
            for(;l_k < k && i + l_k < N && j + l_k < M; l_k++)
            {
                if(board[i][j] != board[i + l_k][j + l_k])
                    break;
            }
            if(l_k == k){
                if( ( inboard(i-1,j-1) && board[i-1][j-1] == '.') || ( inboard(i+l_k,j+l_k) && board[i+l_k][j+l_k] == '.') )
                    a[board[i][j] == 'O']++;       
                if( ( inboard(i-1,j-1) && board[i-1][j-1] == '.') && ( inboard(i+l_k,j+l_k) && board[i+l_k][j+l_k] == '.') )
                    b[board[i][j] == 'O']++;       
            }

            l_k = 0;
            // downwards
            for(;l_k < k && i + l_k < N; l_k++)
            {
                if(board[i][j] != board[i + l_k][j])
                    break;
            }
            if(l_k == k){
                if( ( inboard(i-1,j) && board[i-1][j] == '.') || ( inboard(i+l_k,j) && board[i+l_k][j] == '.') )
                    a[board[i][j] == 'O']++;       
                if( ( inboard(i-1,j) && board[i-1][j] == '.') && ( inboard(i+l_k,j) && board[i+l_k][j] == '.') )
                    b[board[i][j] == 'O']++;       
            }
        }
    }
    vector<int> v;  
    if (MODE==1) a[0]+=a[0],b[0]+=b[0];
    if (MODE==-1) a[0]-=a[1],b[0]-=b[1];
    v.push_back(a[0] - a[1]); 
    v.push_back(b[0] - b[1]); 
    return v;
}
vector<int> f4(vector<string> &board, int N, int M, int K)
{
    int a[2] = {0, 0};
    int b[2] = {0, 0};
    int c[2] = {0, 0};
    int k = K;
    for(int i = 0; i < N; i++)
    {
        FOR(j, M)
        {
            if(board[i][j] == '.')
                continue;
            int l_k = 0,r=0;
            // diagonally upwards towards right
            for(;l_k < k && i >= l_k && j + l_k < M; l_k++)
            {
                if (board[i - l_k][j + l_k] =='.' && r<k-2)
                    r+=1;
                else if(board[i][j] != board[i - l_k][j + l_k])
                    break;
            }
            if(l_k == k){
                if (r==1)
                a[board[i][j] == 'O']++;
                if (r==2)
                b[board[i][j]=='O']++;
                if (r==3)
                c[board[i][j]=='O']++;
            }
            l_k = 0,r=0;
            // diagonally upwards towards left
            for(;l_k < k && i + l_k < N && j - l_k >= 0; l_k++)
            {
                if (board[i + l_k][j - l_k] =='.' && r<k-2)
                    r+=1;
                else if(board[i][j] != board[i + l_k][j - l_k])
                    break;
            }
            if(l_k == k){
                if (r==1)
                a[board[i][j] == 'O']++;
                if (r==2)
                b[board[i][j]=='O']++;
                if (r==3)
                c[board[i][j]=='O']++;
            }
            l_k = 0,r=0;
            // rightside
            for(;l_k < k && j + l_k < M; l_k++)
            {
                if (board[i][j+l_k]=='.' && r<k-2)
                    r+=1;
                else if(board[i][j] != board[i][j + l_k])
                    break;
            }
            if(l_k == k){
                if (r==1)
                a[board[i][j] == 'O']++;
                if (r==2)
                b[board[i][j]=='O']++;
                if (r==3)
                c[board[i][j]=='O']++;
            }
            l_k = 0,r=0;
            // leftside
            for(;l_k < k && j - l_k >= 0; l_k++)
            {
                if (board[i][j-l_k]=='.' && r<k-2)
                    r+=1;
                else if(board[i][j] != board[i][j - l_k])
                    break;
            }
            if(l_k == k){
                if (r==1)
                a[board[i][j] == 'O']++;
                if (r==2)
                b[board[i][j]=='O']++;
                if (r==3)
                c[board[i][j]=='O']++;
            }

            l_k = 0,r=0;
            // diagonally downwards towards right
            for(;l_k < k && i + l_k < N && j + l_k < M; l_k++)
            {
                if (board[i + l_k][j + l_k]=='.' && r<k-2)
                    r+=1;
                else if(board[i][j] != board[i + l_k][j + l_k])
                    break;
            }
            if(l_k == k){
                if (r==1)
                a[board[i][j] == 'O']++;
                if (r==2)
                b[board[i][j]=='O']++;
                if (r==3)
                c[board[i][j]=='O']++;
            }
            l_k = 0,r=0;
            // diagonally downwards towards left
            for(;l_k < k && i - l_k >= 0 && j - l_k >= 0; l_k++)
            {
                if (board[i - l_k][j - l_k]=='.' && r<k-2)
                    r+=1;
                else if(board[i][j] != board[i - l_k][j - l_k])
                    break;
            }
            if(l_k == k){
                if (r==1)
                a[board[i][j] == 'O']++;
                if (r==2)
                b[board[i][j]=='O']++;
                if (r==3)
                c[board[i][j]=='O']++;
            }
            l_k = 0,r=0;
            // downwards
            for(;l_k < k && i + l_k < N; l_k++)
            {
                if (board[i + l_k][j]=='.' && r<k-2)
                    r+=1;
                else if(board[i][j] != board[i + l_k][j])
                    break;
            }
            if(l_k == k){
                if (r==1)
                a[board[i][j] == 'O']++;
                if (r==2)
                b[board[i][j]=='O']++;
                if (r==3)
                c[board[i][j]=='O']++;
            }
            l_k = 0,r=0;
            // upwards
            for(;l_k < k && i - l_k >= 0; l_k++)
            {
                if (board[i - l_k][j]=='.' && r<k-2)
                    r+=1;
                else if(board[i][j] != board[i - l_k][j])
                    break;
            }
            if(l_k == k){
                if (r==1)
                a[board[i][j]=='O']++;
                if (r==2)
                b[board[i][j]=='O']++;
                if (r==3)
                c[board[i][j]=='O']++;
            }
        }
    }
    vector<int> temp;
    if (MODE==1) a[0]+=a[0],b[0]+=b[0],c[0]+=c[0];
    if (MODE==-1) a[0]-=a[1],b[0]-=b[1],c[0]-=c[1];
    temp.PB(a[0]-a[1]);
    temp.PB(b[0]-b[1]);
    temp.PB(c[0]-c[1]);
    return temp;
}
int retEval(vector<string> &board, int N, int M, int K,int m){
    MODE=m;
    int weight[] = {5, 3, 4}; // K-1, K-2, K-3}; 
    int ret = weight[0] * f1(board, N, M, K); 
    vector<int> v = f2(board, N, M, K-1); 
    //vector<int> v2= f4(board,N,M,K);
    ret += weight[1]*v[0] + weight[2]*v[1];
    //ret +=weight[3]*v2[0];
    //ret +=weight[4]*v2[1]+weight[5]*v2[2]; 
    return ret; 
}
// int main(){
//     vector<string> v; 

//     v.push_back(string(".XOX"));
//     v.push_back(string("XOXO"));
//     v.push_back(string("XXO."));
//     v.push_back(string("...."));

//     for(int i=0;i<4;i++)cout << v[i] << endl; 
//     cout << f1(v, 4, 4, 3) << endl; 
//     cout << f2(v, 4, 4, 2)[0]<< endl; 
//     cout << f4(v, 4, 4, 3)[0] << endl; 
// }