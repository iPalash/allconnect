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
#define INF 1000000
#define PB push_back

#include "feature.cpp" 

using namespace std;

/* Complete the function below to print 1 integer which will be your next move 
   */
int N, M, K, player;
int DEPTH_LIMIT;
vector<string> board;
int totaltime = 47; 
int starttime;
int moves,moveCount; 
void update(int n)
{
    for(int i = 0; i < N; i++)
        if(board[i][n] == '.')
        {
            board[i][n] = 'X';
            return;
        }
}

void updateother(int n)
{
    for(int i = 0; i < N; i++)
        if(board[i][n] == '.')
        {
            board[i][n] = 'O';
            return;
        }
}
void printboard(){
  for(int i=N-1; i>=0; i--)cout << board[i] << endl;
}
int eval()
{
  if (moveCount<M*N/6)
    return retEval(board, N, M, K,1);
  else if (moveCount<M*N/3)
    return retEval(board, N, M, K,0);
  else
    return retEval(board, N, M, K,-1);
}
int mini(int,int,int);
int maxi(int,int,int);

int mini(int alpha,int beta, int depth){
  vector<int> v;
  for(int j = M/2; j>=0; j--)
  {
      if(board[N-1][j] == '.')
      {
        v.push_back(j);
      }
      if(board[N-1][M-j-1] == '.' && M-j-1 != j)
      {
        v.push_back(M-j-1);
      }
  }
  if(v.size() == 0 || depth > DEPTH_LIMIT)return eval();
  int ret = INF;

  FOR(ii, v.size()){
    int col = v[ii]; 
    updateother(col);
    int temp=maxi(alpha,beta,depth+1);
    ret = min(ret, temp);
    beta=min(beta,temp);
    for(int i=N-1; i>= 0; i--){
      if(board[i][col] != '.') {
         board[i][col] = '.';
         break;
      }
    }
    if (alpha>=beta) return ret;

  }
  return ret; 
}
int maxi(int alpha,int beta, int depth){
  vector<int> v;
  for(int j = M/2; j>=0; j--)
  {
      if(board[N-1][j] == '.')
      {
        v.push_back(j);
      }
      if(board[N-1][M-j-1] == '.' && M-j-1 != j)
      {
        v.push_back(M-j-1);
      }
  }
  if(v.size() == 0 || depth > DEPTH_LIMIT)return eval();
  int ret = -INF;
 
  FOR(ii, v.size()){
    int col = v[ii];
    update(col);
    int temp=mini(alpha,beta,depth+1);
    ret = max(ret, temp);
    alpha=max(alpha,temp);
    
    for(int i=N-1; i>=0; i--){
      if(board[i][col] != '.'){
        board[i][col] = '.';
        break;
      }
    }
    if (alpha>=beta) return ret;
  }
  return ret;
}
int nextMove()
{
  moveCount++;
  DEPTH_LIMIT = (10 -log10(6*M*N*(M+N)))*(totaltime - (time(0) - starttime))/log10(M); 
  DEPTH_LIMIT /= moves; 
  int iSecret;
  vector<int> v;
  
  for(int j = M/2; j>=0; j--)
  {
      if(board[N-1][j] == '.')
      {
        v.push_back(j);
      }
      if(board[N-1][M-j-1] == '.' && M-j-1 != j)
      {
        v.push_back(M-j-1);
      }
  }
  iSecret = v[0];
  int mu = -INF; 
  FOR(ii, v.size()){
    int col = v[ii]; 
    // cout << "Col: "<<col << endl;
    update(col); 
    
    int u = mini(-INF,INF,1); 
  
    if(u > mu){
      mu = u; 
      iSecret = col; 
    }
    for(int i=N-1; i>=0; i--){
      if(board[i][col] != '.'){
        board[i][col] = '.';
        break;
      }
    }
  }
  cout << "We: " << iSecret << endl;
  update(iSecret);
  printboard();
  moves --; 
  return iSecret;
}




int main(int argc, char *argv[])
{
  starttime = time(0); 
    int sockfd = 0, n = 0;
    char recvBuff[1024];
    char sendBuff[1025];
    struct sockaddr_in serv_addr; 

    if(argc != 3)
    {
        printf("\n Usage: %s <ip of server> <port no> \n",argv[0]);
        return 1;
    } 

    
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2])); 

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 

    cout<<"Connect(N,M,K) will start"<<endl;

    memset(recvBuff, '0',sizeof(recvBuff));
    n = read(sockfd, recvBuff, sizeof(recvBuff)-1);
    recvBuff[n] = 0;
    sscanf(recvBuff, "%d", &N);

    cout<<"N: "<<N<<endl;
    memset(recvBuff, '0',sizeof(recvBuff));
    n = read(sockfd, recvBuff, sizeof(recvBuff)-1);
    recvBuff[n] = 0;
    sscanf(recvBuff, "%d", &M);

    cout<<"M: "<<M<<endl;
    memset(recvBuff, '0',sizeof(recvBuff));
    n = read(sockfd, recvBuff, sizeof(recvBuff)-1);
    recvBuff[n] = 0;
    sscanf(recvBuff, "%d", &K);    
    
    cout<<"K: "<<K<<endl;
    memset(recvBuff, '0',sizeof(recvBuff));
    n = read(sockfd, recvBuff, sizeof(recvBuff)-1);
    recvBuff[n] = 0;
    sscanf(recvBuff, "%d", &player);  

    cout<<"Player "<<player<<endl;


    moves = M * N / 2;


    string temp = "";
    for(int j = 0; j< M; j++)
        temp += ".";
    FOR(i, N)
        board.PB(temp);

    if(player == 1)
    {
        //cout << "hello" << endl;
        memset(sendBuff, '0', sizeof(sendBuff)); 
        int temp = nextMove();
        //cout << "temp" << endl;
        snprintf(sendBuff, sizeof(sendBuff), "%d", temp);
        write(sockfd, sendBuff, strlen(sendBuff));
    }

    while(1)
    {
        int nextColumn;

        memset(recvBuff, '0',sizeof(recvBuff));
        n = read(sockfd, recvBuff, sizeof(recvBuff)-1);
        recvBuff[n] = 0;
        sscanf(recvBuff, "%d", &nextColumn);
        //cout << "Rec: "<< nextColumn << endl;
      updateother(nextColumn);

      cout << nextColumn << endl;
      
        memset(sendBuff, '0', sizeof(sendBuff)); 
        int temp = nextMove();
        //cout << "temp" << endl;
        snprintf(sendBuff, sizeof(sendBuff), "%d", temp);
        write(sockfd, sendBuff, strlen(sendBuff));
    }

    return 0;
}
