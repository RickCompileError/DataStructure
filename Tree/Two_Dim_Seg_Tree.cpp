#include <bits/stdc++.h>

using namespace std;

const int mxX=1e2, mxY=1e2;
int origin[mxX][mxY], st[mxX][mxY], lenx=4, leny=4;

void print(int a[][mxX], int starty, int endy, int startx, int endx){
    for (int i=starty;i<endy;i++){
        for (int j=startx;j<endx;j++){
            printf("%3d ",a[i][j]);
        }
        cout <<endl;
    }
}

int findx(int x1, int x2, int nx, int lx, int rx, int ny){
    if (x1>x2) return 0;
    if (x1==lx && x2==rx) return st[ny][nx];
    else{
        int mx=(lx+rx)/2;
        return findx(x1, min(mx, x2), nx*2, lx, mx, ny)+
                findx(max(mx+1, x1), x2, nx*2+1, mx+1, rx, ny);
    }
}

int findy(int y1, int y2, int x1, int x2, int ny, int ly, int ry){
    if (y1>y2) return 0;
    if (y1==ly && y2==ry) return findx(x1, x2, 1, 0, lenx-1, ny);
    else{
        int my=(ly+ry)/2;
        return findy(y1, min(my,y2), x1, x2, ny*2, ly, my)+
                findy(max(my+1,y1), y2, x1, x2, ny*2+1, my+1, ry);
    }
}

int query(int y1, int y2, int x1, int x2){
    return findy(y1, y2, x1, x2, 1, 0, leny-1);
}

void buildx(int y, int x, int val, int ny, int ly, int ry, int nx, int lx, int rx){
    if (lx==rx){
        if (ly==ry) st[ny][nx]=val;
        else st[ny][nx]=st[ny*2][nx]+st[ny*2+1][nx];
    }else{
        int mx=(lx+rx)/2;
        if (x<=mx) buildx(y, x, val, ny, ly, ry, nx*2, lx, mx);
        else buildx(y, x, val, ny, ly, ry, nx*2+1, mx+1, rx);
        st[ny][nx]=st[ny][nx*2]+st[ny][nx*2+1];
    }
}

void buildy(int y, int x, int val, int ny, int ly, int ry){
    if (ly!=ry){
        int my=(ly+ry)/2;
        if (y<=my) buildy(y, x, val, ny*2, ly, my);
        else buildy(y, x, val, ny*2+1, my+1, ry);
    }
    buildx(y, x, val, ny, ly ,ry, 1, 0, lenx-1);
}

void run(){
    srand(time(NULL));
    for (int i=0;i<leny;i++){
        for (int j=0;j<lenx;j++){
            int val=rand()%10+1;
            origin[i][j]=val;
            buildy(i, j, val, 1, 0, leny-1);
        }
    }
    print(origin, 0, leny, 0, lenx);
    print(st, 1, 4*leny, 1, 4*lenx);
    cout <<query(1,2,1,2) <<endl;
}

int main(){
    run();
}