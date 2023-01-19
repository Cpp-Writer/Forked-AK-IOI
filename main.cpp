#include <algorithm>
#include <windows.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <conio.h>
#include <ctype.h>
#include <cstdio>
#include <cmath>
#include <ctime>
using namespace std;
int game_answer=0;
 
int setBackColor(unsigned char bColor){
    HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbInfo;
    GetConsoleScreenBufferInfo(hd, &csbInfo);
    return SetConsoleTextAttribute(hd, (bColor << 4) | (csbInfo.wAttributes&~0xF0));
} 
int setTextColor(unsigned char fColor){
    HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbInfo;
    GetConsoleScreenBufferInfo(hd, &csbInfo);
    return SetConsoleTextAttribute(hd, fColor | (csbInfo.wAttributes&~0x0F));
}
 
void appGetXY() 
{ 
    HANDLE hStdout;
    CONSOLE_SCREEN_BUFFER_INFO pBuffer; 
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
    GetConsoleScreenBufferInfo(hStdout, &pBuffer); 
    cout << pBuffer.dwCursorPosition.X <<" "<< pBuffer.dwCursorPosition.Y <<endl;; 
}
void appGotoXY(int x,int y)  
{
    swap(x,y);
    CONSOLE_SCREEN_BUFFER_INFO    csbiInfo;                            
    HANDLE    hConsoleOut;
    hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);
    csbiInfo.dwCursorPosition.X = x;                                    
    csbiInfo.dwCursorPosition.Y = y;                                    
    SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);   
}
inline int Get_X(int x,int y){
    if(x==1)    return 5;
    if(x==2)    return 9;
    if(x==3)    return 13;
    if(x==4)    return 17;
}
inline int Get_Y(int x,int y){
    if(y==1)    return 24;
    if(y==2)    return 33;
    if(y==3)    return 42;
    if(y==4)    return 51;
}
void HideCursor(){
    CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
int a[5][5];
bool if_game_over(){
    for(int i=1;i<=4;i++)
        for(int j=1;j<=4;j++)
            if(!a[i][j])
                return 1;
    for(int i=1;i<=4;i++)
        for(int j=1;j<=4;j++){
            if(a[j][i]==a[j][i-1])
                return 1;
            if(a[i][j]==a[i-1][j])
                return 1;
        }
    return 0;
}
bool vis[20];
 
void Pr_a_num_with_color(int x){
    switch (x){
        case 2:setTextColor(6);printf("CE  ");setTextColor(0);break ;
        case 4:setTextColor(3);printf("○  ");setTextColor(0);break ;
        case 8:setTextColor(5);printf("RE  ");setTextColor(0);break ;
        case 16:setTextColor(9);printf("TLE ");setTextColor(0);break ;
        case 32:setTextColor(9);printf("MLE ");setTextColor(0);break ;
        case 64:setTextColor(9);printf("ILE ");setTextColor(0);break ;
        case 128:setTextColor(9);printf("OLE ");setTextColor(0);break ;
        case 256:setTextColor(8);printf("UKE ");setTextColor(0);break ;
        case 512:setTextColor(12);printf("WA  ");setTextColor(0);break ;
        case 1024:setTextColor(2);printf("PC  ");setTextColor(0);break ;
        case 2048:setTextColor(10);printf("AC  ");setTextColor(0);break ;
        case 4096:setTextColor(13);printf("PE  ");setTextColor(0);break ;
        case 8192:setTextColor(4);printf("DoJ ");setTextColor(0);break ;
        case 16384:setTextColor(15);printf("SJE ");setTextColor(0);break ;
        case 32768:setTextColor(14);printf("AU  ");setTextColor(0);break ;
        case 65536:setTextColor(11);printf("AK  ");setTextColor(0);break ;
    }
}
 
void Pr_all_num(){
    for(int i=1;i<=4;i++)
        for(int j=1;j<=4;j++){
            int x=Get_X(i,j),y=Get_Y(i,j); 
            appGotoXY(x,y);
            if(a[i][j]==0)
                printf("    ");
            else{
                Pr_a_num_with_color(a[i][j]);
                
            }
        }
    return ;
}

bool clear_up(){
    bool bb=0;
    for(int k=1;k<=4;k++)
        for(int i=3;i>=1;i--)
            for(int j=1;j<=4;j++)
                if(a[i][j]==0&&a[i+1][j]!=0){
                    swap(a[i][j],a[i+1][j]);
                    bb=1;
                }
    if(bb==1)
        return 1;
    return 0;
}
bool do_up(){
    if(!if_game_over())
        return 1;
    bool bb=1;
    if(!clear_up())
        bb=0;
    for(int j=1;j<=4;j++){
        int i=1;
        while(i<4){
            if(!a[i+1][j])
                break ;
            if(a[i][j]!=a[i+1][j]||a[i][j]==65536){
                i++;
                continue ;
            }
            else if(a[i][j]==a[i+1][j]){
                a[i][j]+=a[i+1][j]; game_answer+=a[i][j];
                a[i+1][j]=0; 
                i+=2;
                bb=1;
            }
        }
    }
    if(bb==0)
        return 0;
    clear_up();
    if(!if_game_over())
        return 1;
    return 1;
}

bool clear_down(){
    bool bb=0;
    for(int k=1;k<=4;k++)
        for(int i=2;i<=4;i++)
            for(int j=1;j<=4;j++)
                if(a[i][j]==0&&a[i-1][j]!=0){
                    swap(a[i][j],a[i-1][j]);
                    bb=1;
                }
    if(bb==1)
        return 1;
    return 0;
}
bool do_down(){
    if(!if_game_over())
        return 1;
    bool bb=1;
    if(!clear_down())
        bb=0;
    for(int j=1;j<=4;j++){
        int i=4;
        while(i>1){
            if(!a[i-1][j])
                break ;
            if(a[i][j]!=a[i-1][j]||a[i][j]==65536){
                i--;
                continue ;
            }
            else if(a[i][j]==a[i-1][j]){
                a[i][j]+=a[i-1][j];  game_answer+=a[i][j];
                a[i-1][j]=0; 
                i-=2;
                bb=1;
            }
        }
    }
    if(bb==0)
        return 0;
    clear_down();
    if(!if_game_over())
        return 1;
    return 1;
}

bool clear_left(){
    bool bb=0;
    for(int k=1;k<=4;k++)
        for(int i=1;i<=4;i++)
            for(int j=3;j>=1;j--)
                if(a[i][j]==0&&a[i][j+1]!=0){
                    swap(a[i][j],a[i][j+1]);
                    bb=1;
                }
    if(bb==1)
        return 1;
    return 0;
}
bool do_left(){
    if(!if_game_over())
        return 1;
    bool bb=1;
    if(!clear_left())
        bb=0;
    for(int i=1;i<=4;i++){
        int j=1;
        while(j<4){
            if(!a[i][j+1])
                break ;
            if(a[i][j]!=a[i][j+1]||a[i][j]==65536){
                j++;
                continue ;
            }
            else if(a[i][j]==a[i][j+1]){
                a[i][j]+=a[i][j+1];  game_answer+=a[i][j];
                a[i][j+1]=0; 
                j+=2;
                bb=1;
            }
        }
    }
    if(bb==0)
        return 0;
    clear_left();
    if(!if_game_over())
        return 1;
    return 1;
}

bool clear_right(){
    bool bb=0;
    for(int k=1;k<=4;k++)
        for(int i=1;i<=4;i++)
            for(int j=2;j<=4;j++)
                if(a[i][j]==0&&a[i][j-1]!=0){
                    swap(a[i][j],a[i][j-1]);
                    bb=1;
                }
    if(bb==1)
        return 1;
    return 0;
}
bool do_right(){
    if(!if_game_over())
        return 1;
    bool bb=1;
    if(!clear_right())
        bb=0;
    for(int i=1;i<=4;i++){
        int j=4;
        while(j>1){
            if(!a[i][j-1])
                break ;
            if(a[i][j]!=a[i][j-1]||a[i][j]==65536){
                j--;
                continue ;
            }
            else if(a[i][j]==a[i][j-1]){
                a[i][j]+=a[i][j-1];  game_answer+=a[i][j];
                a[i][j-1]=0; 
                j-=2;
                bb=1;
            }
        }
    }
    if(bb==0)
        return 0;
    clear_right();
    if(!if_game_over())
        return 1;
    return 1; 
}
 
void START(); 
void END();
 
int main(){
    srand(time(0));
    HideCursor();
	    
    START();
 
    while(if_game_over()){
        
        
 
        int bb=0;
        for(int i=1;i<=4;i++)
            for(int j=1;j<=4;j++)
                if(!a[i][j])
                    bb=1;
        if(bb==1){
            int num_new=rand()%10+1;
            if(num_new==1)  num_new=4;
            else    num_new=2;
            int place_new=0,x=0,y=0;
            while(1){
                place_new=rand()%16+1;
                x=(place_new-1)/4+1,y=place_new%4+1;
                if(!a[x][y])
                    break ;
            }
            a[x][y]=num_new;    
        }
 
        Pr_all_num();
 
    again:
        char ch_1=getch(),ch_2;
        if(ch_1!=-32){
            
            goto again;
        }
        ch_2=getch();
        if(ch_2==72)
            if(!do_up())
                goto again;
        if(ch_2==80)
            if(!do_down())
                goto again;
        if(ch_2==75)
            if(!do_left())
                goto again;
        if(ch_2==77)
            if(!do_right())
                goto again;
        appGotoXY(20,30);
        printf("Score: %8d",game_answer); 
    }
    appGotoXY(20,30);
    printf("                     "); 
    END();
    getch();
}
void START(){
	system("mode con cols=80 lines=26");
	SetConsoleTitleA("AK IOI");
	game_answer=0;
    appGotoXY(0,0);
    setBackColor(15);
    for(int i=1;i<=2680;i++)
        cout<<" ";
    appGotoXY(0,0);
    cout<<" ";
    appGotoXY(20,19);
    setBackColor(7);
    for(int i=1;i<=38;i++)
        cout<<" ";
    setTextColor(0);
    appGotoXY(2,19);
    printf("    akioi      合并评测状态以达到AK   "); 
    appGotoXY(3,19);
    printf("┏━━━━━━━━┳━━━━━━━━┳━━━━━━━━┳━━━━━━━━┓ \n");
    appGotoXY(4,19);
    printf("┃        ┃        ┃        ┃        ┃ \n");
    appGotoXY(5,19);
    printf("┃        ┃        ┃        ┃        ┃ \n");
    appGotoXY(6,19); 
    printf("┃        ┃        ┃        ┃        ┃ \n");
    appGotoXY(7,19);
    printf("┣━━━━━━━━╋━━━━━━━━╋━━━━━━━━╋━━━━━━━━┫ \n");
    appGotoXY(8,19);
    printf("┃        ┃        ┃        ┃        ┃ \n");
    appGotoXY(9,19);
    printf("┃        ┃        ┃        ┃        ┃ \n");
    appGotoXY(10,19);
    printf("┃        ┃        ┃        ┃        ┃ \n");
    appGotoXY(11,19);
    printf("┣━━━━━━━━╋━━━━━━━━╋━━━━━━━━╋━━━━━━━━┫ \n");
    appGotoXY(12,19);
    printf("┃        ┃        ┃        ┃        ┃ \n");
    appGotoXY(13,19);
    printf("┃        ┃        ┃        ┃        ┃ \n");
    appGotoXY(14,19);
    printf("┃        ┃        ┃        ┃        ┃ \n");
    appGotoXY(15,19);
    printf("┣━━━━━━━━╋━━━━━━━━╋━━━━━━━━╋━━━━━━━━┫ \n");
    appGotoXY(16,19);
    printf("┃        ┃        ┃        ┃        ┃ \n");
    appGotoXY(17,19);
    printf("┃        ┃        ┃        ┃        ┃ \n");
    appGotoXY(18,19);
    printf("┃        ┃        ┃        ┃        ┃ \n");
    appGotoXY(19,19);
    printf("┗━━━━━━━━┻━━━━━━━━┻━━━━━━━━┻━━━━━━━━┛ \n");
    
    return ;
}
void END(){
    setBackColor(15);
    appGotoXY(11,37);
    char s_1[30]="AFO";
    Sleep(500);
    cout<<s_1;
    setBackColor(7);
    setTextColor(0);
    appGotoXY(20,30);
    printf("Score: %8d",game_answer); 
    Sleep(500);
    appGotoXY(22,28);
    setBackColor(15);
    char s_2[30]="Press space to exit.";
    for(int i=0;i<strlen(s_2);i++){
        cout<<s_2[i];
        Sleep(30);
    }
    while(1){
    	if(getch()==' ')exit(0);
	}
}
 
