#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<string.h>
#include<queue>
#include<vector>

using namespace std;

class Point{
public:
    Point(int x = 0,int y = 0):x(x),y(y){}
    int x;
    int y;
};


void CalBFS_head(Point &);
void CalBFS_tail(Point &);

int row,col;
char **board;
int **BFS_head;
int **BFS_tail;
Point current,start,recharge;

int main(int argc,char* argv[]){
    ifstream file;
    ofstream file_out;
    string s;
    int battery;
    int max_battery;
    file_out.open("ans.path");
    file.open(argv[1]);

    file>>row;
    file>>col;
    file>>max_battery;
    battery = max_battery;
    board = new char*[row];

    for(int i = 0;i < row;i++){
        board[i]= new char[col];
    }

    BFS_head = new int*[row];

    for(int i = 0;i < row;i++){
        BFS_head[i]= new int[col];
    }

    BFS_tail = new int*[row];

    for(int i = 0;i < row;i++){
        BFS_tail[i]= new int[col];
    }

    for(int i =0;i<row;i++){
        for(int j = 0;j<col;j++){
            file>>board[i][j];
            if(board[i][j]=='R'){
                start.x = j;
                start.y = i;
                current.x = j;
                current.y = i;
                recharge.x = j;
                recharge.y = i;
            }
        }
    }

    for(int i =0;i<row;i++){
        for(int j = 0;j<col;j++){
            BFS_head[i][j] = -1;
        }
    }


    for(int i =0;i<row;i++){
        for(int j = 0;j<col;j++){
            BFS_tail[i][j] = -1;
        }
    }

    BFS_tail[start.y][start.x] = 1000001;

    CalBFS_head(start);

    bool finish = false;
    bool farrest = false;
    bool reset = false;
    bool finding = false;
    int max_bfs;
    Point max_bfs_point;
    int step = 0;
    int times = 0;
    Point ans[100000];
    ans[step] = current;
    while(!finish){
        times++;
        max_bfs = -1;
        if(!finding){
            for(int i =0;i<row;i++){
                for(int j = 0;j<col;j++){
                    if(board[i][j]=='0'&&BFS_head[i][j]>max_bfs){
                        finding = true;
                        max_bfs = BFS_head[i][j];
                        max_bfs_point.x = j;
                        max_bfs_point.y = i;
                    }
                }
            }
            CalBFS_tail(max_bfs_point);
            if(finding==false)
                finish = true;
        }
        while(finding){
            if(BFS_tail[current.y-1][current.x]!=-1&&BFS_tail[current.y-1][current.x]<BFS_tail[current.y][current.x]){
                board[current.y][current.x] = '2';
                current.y--;
                battery--;
                }
            else if(BFS_tail[current.y][current.x+1]!=-1&&BFS_tail[current.y][current.x+1]<BFS_tail[current.y][current.x]){
                board[current.y][current.x] = '2';
                current.x++;
                battery--;
                }
            else if(BFS_tail[current.y+1][current.x]!=-1&&BFS_tail[current.y+1][current.x]<BFS_tail[current.y][current.x]){
                board[current.y][current.x] = '2';
                current.y++;
                battery--;
                }
            else if(BFS_tail[current.y][current.x-1]!=-1&&BFS_tail[current.y][current.x-1]<BFS_tail[current.y][current.x]){
                board[current.y][current.x] = '2';
                current.x--;
                battery--;
                }
            else{
                board[current.y][current.x] = '2';
                farrest = true;
                finding = false;
                break;
                }
        step++;
        ans[step] = current;
        }
        while(farrest){
            if(board[current.y][current.x-1]=='0'){
                board[current.y][current.x] = '2';
                current.x--;
                battery--;
            }
            else if(board[current.y+1][current.x]=='0'){
                board[current.y][current.x] = '2';
                current.y++;
                battery--;
            }
            else if(board[current.y][current.x+1]=='0'){
                board[current.y][current.x] = '2';
                current.x++;
                battery--;
            }
            else if(board[current.y-1][current.x]=='0'){
                board[current.y][current.x] = '2';
                current.y--;
                battery--;
            }
            else{
                farrest = false;//at the same time?
                reset = true;
                break;
            }
            if(battery==BFS_head[current.y][current.x]||battery==BFS_head[current.y][current.x]+1){
                farrest = false;//at the same time?
                reset = true;
                step++;
                ans[step] = current;
                break;
            }
            step++;
            ans[step] = current;
        }
        while(reset){
            if(current.y==recharge.y&&current.x==recharge.x){
                reset = false;
                battery = max_battery;
                break;
            }
            if(BFS_head[current.y-1][current.x]<BFS_head[current.y][current.x]&&BFS_head[current.y-1][current.x]!=-1){
                board[current.y][current.x] = '2';
                current.y--;
                battery--;
                }
            else if(BFS_head[current.y][current.x+1]<BFS_head[current.y][current.x]&&BFS_head[current.y][current.x+1]!=-1){
                board[current.y][current.x] = '2';
                current.x++;
                battery--;
                }
            else if(BFS_head[current.y+1][current.x]<BFS_head[current.y][current.x]&&BFS_head[current.y+1][current.x]!=-1){
                board[current.y][current.x] = '2';
                current.y++;
                battery--;
                }
            else if(BFS_head[current.y][current.x-1]<BFS_head[current.y][current.x]&&BFS_head[current.y][current.x-1]!=-1){
                board[current.y][current.x] = '2';
                current.x--;
                battery--;
                }
        step++;
        ans[step] = current;
        }
    }
    file_out<<step<<endl;
    for(int i = 0;i<row;i++){
        for(int j = 0;j<row;j++){
            cout<<board[i][j];
        }
        cout<<endl;
    }
    for(int i=0;i<step;i++){
        file_out<<ans[i].y<<" "<<ans[i].x<<endl;
    }
    file_out<<current.y<<" "<<current.x<<endl;

    for(int i = 0;i < row;i++){
        delete[]board[i];
        board[i] = NULL;
    }
    delete[] board;
    board = NULL;

    file.close();
    file_out.close();
    return 0;
}

void CalBFS_tail(Point &cur) {
    for(int i =0;i<row;i++){
        for(int j = 0;j<col;j++){
            BFS_tail[i][j] = -1;
        }
    }
    BFS_tail[start.y][start.x] = 1000001;
	std::queue<Point> que;
	que.push(Point(cur.x, cur.y));
	BFS_tail[cur.y][cur.x] = 0;
	while (!que.empty()) {
		Point p = que.front();
//		cout<<p.x<<" "<<p.y<<endl;
		que.pop();
		auto dis = BFS_tail[p.y][p.x];
		if ((p.y-1>=0)&&(p.y-1<=row-1)&&(p.x>=0)&&(p.x<=col-1)&&(board[p.y-1][p.x]=='2'||board[p.y-1][p.x]=='0')&&(BFS_tail[p.y - 1][p.x] == -1)) {
			que.push(Point(p.x, p.y-1));
			BFS_tail[p.y - 1][p.x] = dis + 1;
		}
		if ((p.y + 1 >= 0) && (p.y + 1 <= row - 1) && (p.x >= 0) && (p.x <= col-1) && (board[p.y+1][p.x] == '2'||board[p.y+1][p.x] == '0') && (BFS_tail[p.y + 1][p.x] == -1)) {
			que.push(Point(p.x, p.y+1));
            BFS_tail[p.y + 1][p.x] = dis + 1;
		}
		if ((p.y >= 0) && (p.y <= row - 1) && (p.x - 1 >= 0) && (p.x - 1 <= col-1) && (board[p.y][p.x-1] == '0'||board[p.y][p.x-1] == '2') && (BFS_tail[p.y][p.x - 1] == -1)) {
			que.push(Point(p.x - 1, p.y));
            BFS_tail[p.y][p.x - 1] = dis + 1;
		}
		if ((p.y >= 0) && (p.y <= row- 1) && (p.x + 1 >= 0) && (p.x + 1 <= col - 1) && (board[p.y][p.x+1] == '0'||board[p.y][p.x+1]=='2') && (BFS_tail[p.y][p.x + 1] == -1)) {
			que.push(Point(p.x+1, p.y));
            BFS_tail[p.y][p.x + 1] = dis + 1;
		}
    }
	return;
}

void CalBFS_head(Point &cur) {
	std::queue<Point> que;
	que.push(Point(cur.x, cur.y));
	BFS_head[cur.y][cur.x] = 0;
	while (!que.empty()) {
		Point p = que.front();
//		cout<<p.x<<" "<<p.y<<endl;
		que.pop();
		auto dis = BFS_head[p.y][p.x];
		if ((p.y-1>=0)&&(p.y-1<=row-1)&&(p.x>=0)&&(p.x<=col-1)&&(board[p.y-1][p.x]=='0')&&(BFS_head[p.y - 1][p.x] == -1)) {
			que.push(Point(p.x, p.y-1));
			BFS_head[p.y - 1][p.x] = dis + 1;
		}
		if ((p.y + 1 >= 0) && (p.y + 1 <= row - 1) && (p.x >= 0) && (p.x <= col-1) && (board[p.y+1][p.x] == '0') && (BFS_head[p.y + 1][p.x] == -1)) {
			que.push(Point(p.x, p.y+1));
            BFS_head[p.y + 1][p.x] = dis + 1;
		}
		if ((p.y >= 0) && (p.y <= row - 1) && (p.x - 1 >= 0) && (p.x - 1 <= col-1) && (board[p.y][p.x-1] == '0') && (BFS_head[p.y][p.x - 1] == -1)) {
			que.push(Point(p.x - 1, p.y));
            BFS_head[p.y][p.x - 1] = dis + 1;
		}
		if ((p.y >= 0) && (p.y <= row- 1) && (p.x + 1 >= 0) && (p.x + 1 <= col - 1) && (board[p.y][p.x+1] == '0') && (BFS_head[p.y][p.x + 1] == -1)) {
			que.push(Point(p.x+1, p.y));
            BFS_head[p.y][p.x + 1] = dis + 1;
		}
    }
	return;
}
