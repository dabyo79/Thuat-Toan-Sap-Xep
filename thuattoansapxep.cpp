#include <iostream>
#include <conio.h>
#include <windows.h>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include <string.h>
#include <string>   
#include <math.h>
#include <limits>
#include <ios>

bool daxet[100]={false};
using namespace std;
void resetDaxet(int n) {
    for (int i = 0; i < 100; ++i) daxet[i] = false;
}
bool daktra[100] = {false}; 

void resetDaktra(int n) {
    for (int k = 0; k < n && k < 100; ++k) daktra[k] = false;
}
int calcCellWidth(int n, int a[]) {
    int mx = 1;
    for (int i = 0; i < n; ++i) {
        int len = (int)std::to_string(a[i]).size();
        if (len > mx) mx = len;
    }
    return mx + 2; 
}

void anConTro() {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = FALSE; 
    SetConsoleCursorInfo(out, &cursorInfo);
}
void tatNhapChu() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);

    
    mode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_PROCESSED_INPUT | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
    SetConsoleMode(hStdin, mode);
}
void setConsoleColor(int colorCode) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
}

void resetConsoleColor() {
    setConsoleColor(15); 
}

void printCell(int val, int color, int width) {
    setConsoleColor(color);
    string s = std::to_string(val);
    int pad = width - (int)s.size();
    if (pad < 0) pad = 0;
    int left = pad / 2, right = pad - left;   
    cout << string(left, ' ') << s << string(right, ' ');
    resetConsoleColor();
}
void gotoxy(int x, int y)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c;
    c.X = (SHORT)x;
    c.Y = (SHORT)y;
    SetConsoleCursorPosition(h, c);
}

struct Toado{
    int x, y;
};
void hienthimenu(int &chon);
void hienthide();
void nhapmang(int n, int a[]);
void xuatmang(int n, int a[]);
void landoicho(int n, int a[]);
void clearScreenRegion(int x, int y, int width, int height)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    DWORD count;
    for (int i = 0; i < height; ++i)
    {
        coord.X = x;
        coord.Y = y + i;
        FillConsoleOutputCharacter(hConsole, ' ', width, coord, &count);
    }
}


bool readIntOrEsc(int &out) {
    std::string buf;
    while (true) {
        int ch = _getch();
        if (ch == 27) {               
            return false;
        } else if (ch == 13) {         
            if (buf.empty()) continue; 
            try {
                out = std::stoi(buf);
                std::cout << "\n";
                return true;
            } catch (...) {
                std::cout << "\n\t Nhập không hợp lệ. Vui lòng nhập lại.\n";
                buf.clear();
            }
        } else if (ch == 8) {          
            if (!buf.empty()) {
                buf.pop_back();
                std::cout << "\b \b";
            }
        } else if ((ch >= '0' && ch <= '9') || (ch == '-' && buf.empty())) {
            buf.push_back((char)ch);
            std::cout << (char)ch;     
        }
      
    }
}

void hienthimenu(int &chon)
{
    int toado = 0;
    const int soluachon = 6;
    string menu[soluachon] = {
        "Đổi chỗ trực tiếp    [Interchange Sort]",
        "Chọn trực tiếp       [Selection Sort]  ",
        "Chèn                 [Insertion Sort]  ",
        "Nổi bọt              [Bubble Sort]     ",
        "Nhanh                [Quick Sort]      ",
        "Thoát chương trình                     "
    };

    system("cls");
    hienthide();

    setConsoleColor(14);
    gotoxy(33, 17);
    cout << "↑ ↓ để di chuyển | Enter để chọn";
    resetConsoleColor();

    setConsoleColor(8);
    gotoxy(33, 18);
    cout << "ESC: thoát chương trình";
    resetConsoleColor();

    int yStart = 20;

    while (true)
    {
        clearScreenRegion(25, yStart, 80, soluachon + 1);

        for (int i = 0; i < soluachon; i++)
        {
            gotoxy(30, yStart + i);
            if (i == toado)
            {
                setConsoleColor(176);
                cout << " ➤ " << menu[i] << " ";
                resetConsoleColor();
            }
            else
            {
                cout << "   " << menu[i] << " ";
                resetConsoleColor();
            }
        }

        char key = getch();
        if (key == 72) toado = (toado - 1 + soluachon) % soluachon;
        else if (key == 80) toado = (toado + 1) % soluachon;
        else if (key == 13) {
            system("cls");
            chon = toado;
            return;
        } else if (key == 27) { 
            chon = 5; 
            return;
        }
    }
}


void hienthide()
{

    setConsoleColor(11);
    gotoxy(3,3); printf("\t	▓▓▓▓▓▓▓ ▓▓▓   ▓▓▓  ▓▓▓    ▓▓▓   ▓▓▓▓▓▓  ▓▓▓▓▓▓▓    ▓▓▓▓▓▓▓▓  ▓▓▓▓▓▓▓▓▓   ▓▓▓▓▓▓   ▓▓▓▓  ▓▓▓\n"); Sleep(40);
    gotoxy(3,4); printf("\t	  ▓▓▓   ▓▓▓   ▓▓▓  ▓▓▓    ▓▓▓  ▓▓▓  ▓▓▓   ▓▓▓        ▓▓▓     ▓▓▓   ▓▓▓  ▓▓▓  ▓▓▓  ▓▓▓▓▓ ▓▓▓\n"); Sleep(40); setConsoleColor(3);
    gotoxy(3,5); printf("\t	  ▓▓▓   ▓▓▓▓▓▓▓▓▓  ▓▓▓    ▓▓▓  ▓▓▓▓▓▓▓▓   ▓▓▓        ▓▓▓     ▓▓▓   ▓▓▓  ▓▓▓▓▓▓▓▓  ▓▓▓ ▓▓▓▓▓\n"); Sleep(40);
    gotoxy(3,6); printf("\t	  ▓▓▓   ▓▓▓   ▓▓▓  ▓▓▓    ▓▓▓  ▓▓▓  ▓▓▓   ▓▓▓        ▓▓▓     ▓▓▓   ▓▓▓  ▓▓▓  ▓▓▓  ▓▓▓  ▓▓▓▓\n"); Sleep(40); setConsoleColor(3);
    gotoxy(3,7); printf("\t	  ▓▓▓   ▓▓▓   ▓▓▓  ▓▓▓▓▓▓▓▓▓▓  ▓▓▓  ▓▓▓   ▓▓▓        ▓▓▓     ▓▓▓▓▓▓▓▓▓  ▓▓▓  ▓▓▓  ▓▓▓   ▓▓▓\n"); Sleep(40);
    setConsoleColor(11);
	gotoxy(3,8);printf("\t                                                                                             \n"); 
    gotoxy(3,9);printf("\t   	        	   ▓▓▓▓▓▓▓    ▓▓▓▓▓▓   ▓▓▓▓▓▓▓     ▓▓▓     ▓▓▓  ▓▓▓▓▓▓▓  ▓▓▓▓▓▓▓            \n"); Sleep(40);
    gotoxy(3,10);printf("\t	                  ▓▓▓    ▓▓  ▓▓▓  ▓▓▓  ▓▓▓  ▓▓▓      ▓▓▓  ▓▓▓   ▓▓▓      ▓▓▓  ▓▓▓           \n"); Sleep(40); setConsoleColor(3);
    gotoxy(3,11);printf("\t	                    ▓▓▓▓     ▓▓▓▓▓▓▓▓  ▓▓▓▓▓▓▓	       ▓▓▓      ▓▓▓▓▓▓▓  ▓▓▓▓▓▓▓            \n"); Sleep(40);
    gotoxy(3,12);printf("\t	                 ▓▓    ▓▓▓   ▓▓▓  ▓▓▓  ▓▓▓           ▓▓▓ ▓▓▓    ▓▓▓      ▓▓▓                \n"); Sleep(40); setConsoleColor(3);
    gotoxy(3,13);printf("\t	                  ▓▓▓▓▓▓▓    ▓▓▓  ▓▓▓  ▓▓▓   	    ▓▓▓   ▓▓▓   ▓▓▓▓▓▓▓  ▓▓▓                \n"); Sleep(40);
}

void xuatmangsx(int n, int a[]){
    setConsoleColor(15);
	cout<<endl<<endl<<"< Kết thúc quá trình sắp xếp ! >"<<endl;
	setConsoleColor(11);
    cout<<setw(25)<<left << "\t "<<"▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬"<<endl;
	cout<<setw(25)<<left <<"\t "<<"Mảng đã sắp xếp là: ";
	int W = calcCellWidth(n, a);
    for (int i = 0; i <= n - 1; i++) {
        cout << "  ";
        printCell(a[i], 47, W); 
    }
	setConsoleColor(11);
	cout<<endl<<setw(25)<<left<<"\t "<<"▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬"<<endl;	
 
	setConsoleColor(116); printf("  EXIT  ");
 
    setConsoleColor(0);
}
//doi cho truc tiep
void xuat(int a[], int n, int xet1, int xet2, int doi1, int doi2) {
    int W = calcCellWidth(n, a);
    for (int i = 0; i <= n-1; i++) {
        int color=240;
        if (i == xet1 || i == xet2) color=71;
        else if (i == doi1 || i == doi2) color=63;
        else if (daxet[i]) color=47;
        else if (daktra[i]) color=143;
        
        cout << "\t";
        printCell(a[i], color, W);
    }
    resetConsoleColor();
    cout << endl;
}


// Đổi chỗ trực tiếp (Interchange Sort)
void landoicho(int n, int a[])
{
    setConsoleColor(240);
    cout << "\t   ";
    setConsoleColor(15);
    cout << ": Vị trí chưa xét" << endl;

    setConsoleColor(63);
    cout << "\t   ";
    setConsoleColor(15);
    cout << ": Vị trí được đổi chỗ" << endl;

    setConsoleColor(143);
    cout << "\t   ";
    setConsoleColor(15);
    cout << ": Vị trí đã kiểm tra qua" << endl;

    setConsoleColor(71);
    cout << "\t   ";
    setConsoleColor(15);
    cout << ": Vị trí đang xét" << endl;

    setConsoleColor(47);
    cout << "\t   ";
    setConsoleColor(15);
    cout << ": Vị trí đã cố định (đã xét xong)" << endl;

    setConsoleColor(8);
    cout << "\nHướng dẫn: ENTER để xem bước tiếp theo, ESC để quay lại menu.\n\n";
    resetConsoleColor();

    int ss, i, j;
    int W = calcCellWidth(n, a);
    
    for (int x = 0; x <= n-1; x++) {
        resetDaktra(n);
        cout << endl << "\t[ Với i = " << x << " ]";
        i = x;
        if(x==n-1){
			xuat(a, n, i, j, -1, -1);
			getch();
			cout<<"\t\t ➥ ";
			for(int i=0; i<=n-1; i++){
			
        	cout << "\t";
            printCell(a[i], /*color*/47, W);   
			}
		}
        for (j = i + 1; j <= n-1; j++) {
    cout << endl << "Kiểm tra với j=" << j << ":";
    xuat(a, n, i, j, -1, -1);
    char k = getch();
    if (k == 27) { system("cls"); return; }
            
    if (a[i] > a[j]) {
        ss = a[i]; a[i] = a[j]; a[j] = ss;
        cout << "\t\t ➥ ";
        xuat(a, n, -1, -1, i, j);
        k = getch(); if (k == 27) { system("cls"); return; }
    } else {
        
    }

    daktra[j] = true;  
}
daxet[i] = true;       

    }

    xuatmangsx(n, a);
    while (true) {
        char key = getch();
        if (key == 13 || key == 27) {
            system("cls");
            return;
        }
    }
}



//chon truc tiep
void xuatchon(int a[], int n, int chon, int thay, int doi1, int doi2) {
    int W = calcCellWidth(n, a);

    for (int i = 0; i < n; i++) {
        int color = 240; 

        if (i == doi1 || i == doi2) {
            color = 63;                
        } else if (daxet[i]) {
            color = 47;                
        } else if (i == chon) {
            color = 71;
        }else if (i == thay) {
            color = 222;             
        } else if (daktra[i]) {
            color = 143;                  
        }

        std::cout << "\t";
        printCell(a[i], color, W);
    }
    std::cout << std::endl;
}

//chon truc tiep
void selectionSort(int a[], int n) {
   
    setConsoleColor(240); std::cout << "\t   "; setConsoleColor(15); std::cout << ": Vị trí chưa xét (hoặc đang đợi xét)\n";
    setConsoleColor(71);  std::cout << "\t   "; setConsoleColor(15); std::cout << ": Vị trí đang xét\n";
    setConsoleColor(143);   std::cout << "\t   "; setConsoleColor(15); std::cout << ": Vị trí đã kiểm tra qua\n";
    setConsoleColor(222);   std::cout << "\t   "; setConsoleColor(15); std::cout << ": Vị trí min\n";
    setConsoleColor(63);  std::cout << "\t   "; setConsoleColor(15); std::cout << ": Vị trí vừa đổi chỗ\n";
    setConsoleColor(47);  std::cout << "\t   "; setConsoleColor(15); std::cout << ": Vị trí đã xét (cố định)\n";

    setConsoleColor(8);
    std::cout << "\nHướng dẫn: ENTER để xem bước tiếp theo, ESC để quay lại menu.\n\n";
    resetConsoleColor();

    for (int i = 0; i < n; i++) {
        resetDaktra(n);             
        int min = i;

        std::cout << "\n\t[ Với i = " << i << " ]:";
        xuatchon(a, n, i, min, -1, -1);

        for (int j = i + 1; j < n; j++) {
            std::cout << "  Kiểm tra j = " << j << ":";
            xuatchon(a, n, i, min, -1, -1);

            char k = getch(); if (k == 27) { system("cls"); return; }

            if (a[j] < a[min]) {
                min = j;
                std::cout << "\n【Cập nhật min】:";
                xuatchon(a, n, i, min, -1, -1);
                k = getch(); if (k == 27) { system("cls"); return; }
            }

            daktra[j] = true;          
        }

        if (min != i) {
            std::swap(a[i], a[min]);
            std::cout << "\t➥ Đổi chỗ:";
            xuatchon(a, n, -1, -1, i, min);     
            char k = getch(); if (k == 27) { system("cls"); return; }
        }

        daxet[i] = true;
        std::cout << "\t\t";             
        xuatchon(a, n, -1, -1, -1, -1);
        char k2 = getch(); if (k2 == 27) { system("cls"); return; }
    }

    xuatmangsx(n, a);
    while (true) {
        char key = getch();
        if (key == 13 || key == 27) {
            system("cls");
            return;
        }
    }
}


void printBlankCell(int color, int width) {
    setConsoleColor(color);          
    cout << string(width, ' ');
    resetConsoleColor();
}



//chen
void xuatChen(int a[], int n,
              int k, int chon, int doi1, int doi2,
              int hole, int keyIdx, int fixedUpto,
              int keyVal, bool keyComparing) {
    int W = calcCellWidth(n, a);

    
    for (int i = 0; i < n; ++i) {
        if (i == hole) { 
            cout << "\t";
            printBlankCell((doi1 != -1 || doi2 != -1) ? 63 : 0, W);

            continue;
        }
        int color = 240;                 

       
        if (i == doi1 || i == doi2) {
            color = 63;
        }
        
        else if (k >= 0 && chon >= 0 && (i == k || i == chon)) {
            color = 71;
        }
        
        else if (fixedUpto >= 0 && i <= fixedUpto) {
            color = 47;
        }

        cout << "\t";
        printCell(a[i], color, W);
    }
    cout << "\n";

    
    if (keyIdx >= 0) {
        for (int i = 0; i < keyIdx; ++i) cout << "\t" ;
        cout << "\t";
        printCell(keyVal, keyComparing ? 71 : 222, W);
        cout << "\n";
    }

}

//chen
void Chen(int n, int a[]) {
    setConsoleColor(240); cout << "\t   "; setConsoleColor(15); cout << ": Vị trí chưa xét\n";
    setConsoleColor(47); cout << "\t   "; setConsoleColor(15); cout << ": Ví trí tạm thời cố định\n";
    setConsoleColor(71); cout << "\t   "; setConsoleColor(15); cout << ": Vị trí xét (so sánh)\n";
    setConsoleColor(63); cout << "\t   "; setConsoleColor(15); cout << ": Vị trí di chuyển\n";
    setConsoleColor(222); cout << "\t   "; setConsoleColor(15); cout << ": KEY\n";
    setConsoleColor(8); cout << "\nHướng dẫn: ENTER để xem bước tiếp theo, ESC để quay lại menu.\n\n";
    resetConsoleColor();

    for (int i = 1; i < n; ++i) {             
        resetDaktra(n);
        int x = a[i];
        int pos = i;

        
        {
            setConsoleColor(8);
            cout<< "\nChon KEY = " + to_string(x) + ", tai vi tri " + to_string(i)+"\n";
            resetConsoleColor();
            xuatChen(a, n,-1,-1,-1,-1,i, i, i-1,x,false);
            int c = _getch(); if (c==27) { system("cls"); return; }
        }

        
        while (pos > 0 && x < a[pos-1]) {
           
            {
                setConsoleColor(8);
                cout<< "So sánh: a[" + to_string(pos-1) + "]=" + to_string(a[pos-1]) +
                            " > KEY=" + to_string(x) + "  -> Dời a[" + to_string(pos) + "] = a[" + to_string(pos-1) + "]\n";
                resetConsoleColor();
                            xuatChen(a, n,pos-1, pos, -1,-1,pos, i, i-1,x, true);
                int c = _getch(); if (c==27) { system("cls"); return; }
            }

            
            a[pos] = a[pos-1];
            int oldPos = pos;
            pos--;

            
            {
                setConsoleColor(8);
                cout<< "Đã di chuyển: \n";
                resetConsoleColor();
                xuatChen(a, n,-1, -1, oldPos,-1,pos, i,i-1,x, false);
                int c = _getch(); if (c==27) { system("cls"); return; }
            }
        }
        if (pos > 0) {
    setConsoleColor(8);
    cout<< "So sánh: a[" + to_string(pos-1) + "]=" + to_string(a[pos-1]) +
                   " <= KEY=" + to_string(x) + " -> Không thay đổi \n" ;
    resetConsoleColor();
    xuatChen(a, n,pos-1,pos, -1, -1,pos, i, i-1, x, true);
    int c = _getch(); if (c == 27) { system("cls"); return; }
        }
        
        a[pos] = x;

        
        {
            setConsoleColor(8);
            cout<<"Cập nhật mảng: [0.." + to_string(i) + "] \n";
            resetConsoleColor();
            xuatChen(a, n,-1, -1,-1, -1,-1, -1,i,x, false);
            int c = _getch(); if (c==27) { system("cls"); return; }
        }
    }

    xuatmangsx(n, a);
    while (true) {
        int k = _getch();
        if (k == 13 || k == 27) { system("cls"); return; }
    }
}







//noi bot

void xuatnoibot(int n, int a[], int xet1, int xet2, int doi1, int doi2, int xetrui) {
    for (int i = 0; i < n; i++) {
        if (i == xet1 || i == xet2) {
            setConsoleColor(71);        
        } else if (i == doi1 || i == doi2) {
            setConsoleColor(63);         
        } else if (daxet[i]) {
            setConsoleColor(47);         
        } else if (i <= xetrui) {
            setConsoleColor(143);          
        } else {
            setConsoleColor(240);        
        }
        cout << "\t" << " " << a[i] << " ";
    }
    setConsoleColor(15);
    cout << endl;
}
//noi bot

void NoiBot(int n, int a[]) {
   
    setConsoleColor(240); cout << "\t   "; setConsoleColor(15); cout << ": Vị trí chưa xét\n";
    setConsoleColor(143);   cout << "\t   "; setConsoleColor(15); cout << ": Đã qua trong lần xét hiện tại\n";
    setConsoleColor(71);  cout << "\t   "; setConsoleColor(15); cout << ": Vị trí đang xét\n";
    setConsoleColor(63);  cout << "\t   "; setConsoleColor(15); cout << ": Vị trí vừa đổi chỗ\n";
    setConsoleColor(47);  cout << "\t   "; setConsoleColor(15); cout << ": Vị trí đã cố định\n";
    setConsoleColor(8);   cout << "\nHướng dẫn: ENTER để xem bước tiếp theo, ESC để quay lại menu.\n\n";
    resetConsoleColor();

    for (int t = 0; t < n; ++t) daxet[t] = false;

    for (int i = 0; i < n - 1; i++) {
        cout << endl << "[ Với lần thứ " << i + 1 << " ]:\n";
        int xetrui = -1;                            

        for (int j = 0; j < n - i - 1; j++) {
            setConsoleColor(8); cout << "\tXét: ";
            xuatnoibot(n, a, j, j + 1, -1, -1, xetrui);
            { int k = getch(); if (k == 27) { system("cls"); return; } }

            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                cout << "\t➥ ";
                xuatnoibot(n, a, -1, -1, j, j + 1, xetrui);
                { int k = getch(); if (k == 27) { system("cls"); return; } }
            } else {
                cout << "\t➥ ";
                xuatnoibot(n, a, -1, -1, j, j + 1, xetrui);
                { int k = getch(); if (k == 27) { system("cls"); return; } }
            }

            xetrui = j;                              
        }

        daxet[n - i - 1] = true;                     

        cout << "\tKết thúc vòng " << i + 1 << ":\n\t  ";
        xuatnoibot(n, a, -1, -1, -1, -1, xetrui);
        { int k = getch(); if (k == 27) { system("cls"); return; } }
    }

    xuatmangsx(n, a);
    while (true) {
        int k = _getch();
        if (k == 13 || k == 27) { system("cls"); return; }
    }
}



//nhanh

inline bool waitOrEsc() { int k = getch(); if (k == 27) { system("cls"); return false; } return true; }


static void printQSLegendOnce() {
    setConsoleColor(222); cout << "\t   "; setConsoleColor(15); cout << ": Vị trí pivot\n";
    setConsoleColor(240);   cout << "\t   "; setConsoleColor(15); cout << ": Vị trí chưa xét\n";
    setConsoleColor(71);  cout << "\t   "; setConsoleColor(15); cout << ": Phần tử bên trái\n";
    setConsoleColor(63);  cout << "\t   "; setConsoleColor(15); cout << ": Phần tử bên phải\n";
    
    setConsoleColor(8);   cout << "\nHướng dẫn: ENTER để xem bước tiếp theo, ESC để quay lại menu.\n\n";
    resetConsoleColor();

    
}


void printArrayWithCompare(int arr[], int start, int end, int pivotVal, int pivotIdx) {
    int width = calcCellWidth(end - start + 1, arr + start);

    for (int i = start; i <= end; ++i) {
        int color = (i == pivotIdx) ? 222 : 240;
        printCell(arr[i], color, width);
        cout << ' ';
    }
    cout << '\n';

    for (int i = start; i <= end; ++i) {
        if (i == pivotIdx) {
            cout << string(width, ' ') << ' ';
            continue;
        }
        bool le = (arr[i] <= pivotVal);
        int color = le ? 4 : 9;
        setConsoleColor(color);
        const char* mark = le ? "<=" : ">="; 
        int mlen = 2;
        int pad = width - mlen; if (pad < 0) pad = 0;
        int L = pad/2, R = pad - L;
        cout << string(L, ' ') << mark << string(R, ' ')<<' ' ;
        resetConsoleColor();
    }
    cout << "\n";
}


static inline std::string spaces(int n){ return std::string(n>0?n:0,' '); }

static void printCenteredPlain(const std::string& s, int width) {
    int L = (int)s.size();
    if (L >= width) { std::cout.write(s.c_str(), width); return; }
    int pad = width - L, left = pad/2, right = pad - left;
    std::cout << spaces(left) << s << spaces(right);
}
static void printCenteredColor(const std::string& s, int width, int color) {
    setConsoleColor(color);
    printCenteredPlain(s, width);
    resetConsoleColor();
}

static void printColumnValues(int arr[], int start, int end, int color, int cellW, int colW) {
    std::ostringstream buf;
    if (start <= end) {
        for (int i = start; i <= end; ++i) {
            std::string s = std::to_string(arr[i]);
            int pad = cellW - (int)s.size(); if (pad < 0) pad = 0;
            int L = pad/2, R = pad - L;
            buf << spaces(L) << s << spaces(R);
            if (i < end) buf << ' ';               
        }
    } else {
    }
    std::string out = buf.str();
    if ((int)out.size() < colW) out += spaces(colW - (int)out.size());
    setConsoleColor(color);
    std::cout << out;
    resetConsoleColor();
}



void showParallelSplit2Rows(int arr[], int low, int high, int pivotIdx) {
    if (low > high || pivotIdx < low || pivotIdx > high) return;

    const int COL_L = 71, COL_P = 222, COL_R = 63;
    const int GAP = 6;  

    int cellW = calcCellWidth(high - low + 1, arr + low);
    auto widthOfArrayLine = [&](int countCells){ return countCells>0 ? (countCells*(cellW+1)-1) : 0; };
    int lineW = widthOfArrayLine(high - low + 1);

    int nLeft  = std::max(0, pivotIdx - low);
    int nRight = std::max(0, high - pivotIdx);  

    int colL = widthOfArrayLine(nLeft);    
    int colP = widthOfArrayLine(1);        
    int colR = widthOfArrayLine(nRight);

    int minL = (int)std::string("Trái").size() + 1;
    int minP = (int)std::string("Pivot").size();           
    int minR = (int)std::string("Phải").size() + 1;

    if (nLeft  == 0) colL = std::max(colL, cellW);
    if (nRight == 0) colR = std::max(colR, cellW);

    colL = std::max(colL, minL);
    colP = std::max(colP, std::max(minP, cellW));
    colR = std::max(colR, minR);

    int totalColsW = colL + GAP + colP + GAP + colR;
    int leftPad = std::max((lineW - totalColsW) / 2, 0);

  
    std::cout << "\n\t\t\t\t\t\t" << spaces(leftPad)<<" ";
    printCenteredColor("Trái",  colL, COL_L);
    std::cout << spaces(GAP);
    printCenteredColor("Pivot", colP, COL_P);
    std::cout << spaces(GAP);
    printCenteredColor("Phải",  colR, COL_R);
    std::cout << "\n\t\t\t\t\t\t";

   
    std::cout << spaces(leftPad);
    printColumnValues(arr, low,        pivotIdx-1, COL_L, cellW, colL);
    std::cout << spaces(GAP);
    printColumnValues(arr, pivotIdx,   pivotIdx,   COL_P, cellW, colP);
    std::cout << spaces(GAP);
    printColumnValues(arr, pivotIdx+1, high,       COL_R, cellW, colR);
    std::cout << "\n";
}



static bool stepChoosePivot(int arr[], int low, int high) {
    setConsoleColor(15);
    cout << "\n[Xét] \n";
    printArrayWithCompare(arr, low, high, arr[high], high);
    return waitOrEsc();
}


int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int left  = low;
    int right = high - 1;

   
    while (true) {
        while (left  <= right && arr[left]  < pivot) left++;
        while (right >= left  && arr[right] > pivot) right--;
        if (left >= right) break;
        std::swap(arr[left++], arr[right--]);
    }

    std::swap(arr[left], arr[high]);  

    return left;
}



static bool stepPartitionAndShow(int arr[], int low, int high, int &pivotIndex) {
    pivotIndex = partition(arr, low, high);
    setConsoleColor(15);
    cout << "\nSau khi phân hoạch:\n";
    printArrayWithCompare(arr, low, high, arr[pivotIndex], pivotIndex);
    showParallelSplit2Rows(arr, low, high, pivotIndex);

    return waitOrEsc();
}



static bool quickSortCore2Steps(int arr[], int low, int high) {
    if (low >= high) return true;
    if (!stepChoosePivot(arr, low, high)) return false;          

    int pivotIndex = -1;
    if (!stepPartitionAndShow(arr, low, high, pivotIndex)) return false;

    if (!quickSortCore2Steps(arr, low, pivotIndex - 1)) return false;
    if (!quickSortCore2Steps(arr, pivotIndex + 1, high)) return false;
    return true;
}


bool quickSortVisual2Steps(int arr[], int low, int high) {
    printQSLegendOnce();
    return quickSortCore2Steps(arr, low, high);
}







void nhapMang(int& n, int*& a) {
    while (true) {
        setConsoleColor(15);
        cout << "Nhập số phần tử của mảng: ";
        if (cin >> n) {
            break; 
        } else {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                setConsoleColor(207);
            cout << "\t Nhập không hợp lệ. Vui lòng nhập lại\n";
        }
    }

    a = new int[n];

    for (int i = 0; i < n; i++) {
        while (true) {
            setConsoleColor(15);
            cout << "Nhập phần tử thứ a[" << i << "]: ";
            if (cin >> a[i]) {
                break; 
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                setConsoleColor(207);
                cout << "\t Nhập không hợp lệ. Vui lòng nhập lại.\n";
            }
        }
    }
}

void xuatMang(int n, int* a){
    setConsoleColor(11);
    cout<<setw(25)<<left << "\t "<<"▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬"<<endl;
    cout<<setw(25)<<left <<"\t "<<"Mảng vừa nhập là: ";
    for(int i=0; i<n; i++){
        setConsoleColor(0);
        cout<<" ";
        setConsoleColor(240);
        cout<<" "<<a[i]<<" ";}
    setConsoleColor(11);
    cout<<endl<<setw(25)<<left<<"\t "<<"▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬"<<endl<<endl;
    resetConsoleColor();
    
}

bool nhapLaiDuLieu(int*& a, int& n)
{
    
    setConsoleColor(8);
    cout << "[ Hướng dẫn: ENTER để xác nhận | ESC để quay lại menu ]";
    resetConsoleColor();

  
    while (true) {
        setConsoleColor(15);
        cout << "\nNhập số phần tử của mảng: ";
        resetConsoleColor();
        if (!readIntOrEsc(n)) return false; 
        if (n >= 1 && n <= 100) break;
        setConsoleColor(207);
        cout << "Giá trị n không hợp lệ. Vui lòng nhập trong khoảng 1..100.";
        resetConsoleColor();
    }

   
    if (a != nullptr) { delete[] a; a = nullptr; }
    a = new int[n];

 
    for (int i = 0; i < n; i++) {
        setConsoleColor(15);
        cout << "Nhập phần tử a[" << i << "]: ";
        resetConsoleColor();
        if (!readIntOrEsc(a[i])) { 
            delete[] a; a = nullptr; n = 0;
            return false;
        }
    }

    xuatMang(n, a);
    return true;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    anConTro();
    tatNhapChu(); 
    int chon = 0;
    int* a = nullptr;
    int n = 0;

    while (true) 
    {
        system("cls");
        setConsoleColor(15);
        hienthimenu(chon); 

        if (chon == 0) 
        {
            if (!nhapLaiDuLieu(a, n)) { continue; }
            resetDaxet(n); 
            cout << setw(35) << left << "\t ";
            setConsoleColor(143);
            cout << " Đổi chỗ trực tiếp (Interchange Sort) ";
            resetConsoleColor();
            cout << endl << endl;

            landoicho(n, a); 
        }
        else if (chon == 1) 
        {
            if (!nhapLaiDuLieu(a, n)) { continue; }
            resetDaxet(n);
            cout << setw(35) << left << "\t ";
            setConsoleColor(143);
            cout << " Chọn trực tiếp (Selection Sort) ";
            resetConsoleColor();
            cout << endl << endl;

            selectionSort(a, n);
        }
        else if (chon == 2) 
        {
            if (!nhapLaiDuLieu(a, n)) { continue; }
            resetDaxet(n);
            cout << setw(35) << left << "\t ";
            setConsoleColor(143);
            cout << " Chèn (Insertion Sort) ";
            resetConsoleColor();
            cout << endl << endl;

            Chen(n, a);
        }
        else if (chon == 3) 
        {
            if (!nhapLaiDuLieu(a, n)) { continue; }
            resetDaxet(n);
            cout << setw(35) << left << "\t ";
            setConsoleColor(143);
            cout << " Nổi bọt (Bubble Sort) ";
            resetConsoleColor();
            cout << endl << endl;

            NoiBot(n, a);
        }
        else if (chon == 4) 
        {
            if (!nhapLaiDuLieu(a, n)) { continue; }
            resetDaxet(n);
            cout << setw(35) << left << "\t ";
            setConsoleColor(143);
            cout << " Nhanh (Quick Sort) ";
            resetConsoleColor();
            cout << endl << endl;

            setConsoleColor(15);
            bool ok = quickSortVisual2Steps(a, 0, n - 1);   
    if (ok) {
        xuatmangsx(n, a);
        while (true) {
            char key = getch();
            if (key == 13 || key == 27) break;
        }
    }
        }
        else if (chon == 5) 
        {
            system("cls");
            setConsoleColor(10);
            cout << "\nCam on ban da su dung chuong trinh!\n";
            resetConsoleColor();
            break; 
        }

        delete[] a;
        a = nullptr;
        n = 0;
    }

    return 0;
}
