// Morning Sunrise

// libraries
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <conio.h>
#include <math.h>
#include <vector>

// Defines
#define ll long long
#define endl '\n'
#define cls system("cls")
#define pause system("pause > nul")
#define WIDTH 93
#define HEIGHT 25

// using
using namespace std;
using lli = long long int;

// Functions
void gotoxy(int, int);
void clsconsole();
void repeatcout(const char *, int);
void stepcout(const char *, int);
void frame();
void box(int, int);
void start();
void menu();
void explain();

int condition_chk(int);
void plow(int, int);
void seed(int, int);
void water(int, int);
void wait();
void harvest(int, int);
void field();
void farm();

void moneystatus();
void buy_something(int);
void buy();
void sell();
void St();
void shop();

void guide();
void end();
void run();

// global variables
const char title[5][70] = {
    ",~-.~-.               o              ,---.               o          ",
    "|  |  |,---.,-~- ,---.!,---.,---.    `---..   .,---.,-~- !,---.,---.",
    "|  |  ||   ||    |   |||   ||   |        ||   ||   ||    |`---.|---'",
    "`  '  '`---'`    `   '``   '`---|    `---'`---'`   '`    ``---'`---'",
    "                            `---'                                   "
};

const char *SEED[] = {  // : ~ / % #
    "\033[1;32m:\033[0m", "\033[1;32m~\033[0m", "\033[1;32m/\033[0m", "\033[1;33m%\033[0m", "\033[1;30m#\033[0m"
};

lli Storage[] = {
    0,  // Sprout        [0]
    0,  // Growing       [1]
    0,  // Ripening      [2]
    0,  // Perfect       [3]
    0   // Wilted        [4]  
};
int sprout=0, growing=1, ripening=2, perfect=3, wilted=4;
lli Money=0;

int skip;
int fieldw=1, fieldh=1;
const int wlimit=20, hlimit=8;
int plow_arr[20][8][2];
int seed_arr[20][8][2];
int water_arr[20][8][2];
int seed_no_water_cnt[200];
int wait_cnt;

const string PlowTools[] = {"Basic Plow", "Reinforced Plow", "Advenced Plow", "\033[9mSold Out\033[0m"};
const string WaterTools[] = {"Watering Can", "Hose", "Irrigation Tool", "\033[9mSold Out\033[0m"};
const string HarvestTools[] = {"Sickle", "Scythe", "Combine Harvester", "\033[9mSold Out\033[0m"};
int currentPlow=0;
int currentWater=0;
int currentHarvest=0;
int plow_count=0;
int water_count=0;
int harvest_count=0;
const int plowPrice[] = {1000, 10000};
const int waterPrice[] = {1000, 15000};
const int harvestPrice[] = {1500, 15000};
const string plowMsg[] = {
    "+------------------------------------------------------+------------------------------------+\n| Which plot do you want to plow? Enter coodinate(x y) | -1 -1 to exit\n+------------------------------------------------------+------------------------------------+\n",
    "+-------------------------------------------------------+-----------------------------------+\n| Which line do you want to plow? Enter the x coodinate | -1 to exit  \n+-------------------------------------------------------+-----------------------------------+\n",
    "+-------------------------------------------------------+-----------------------------------+\n| Which line do you want to plow? Enter the x coodinate | -1 to exit  \n+-------------------------------------------------------+-----------------------------------+\n"
};
const string waterMsg[] = {
    "+-------------------------------------------------------+-----------------------------------+\n| Which plot do you want to water? Enter coodinate(x y) | -1 -1 to exit\n+-------------------------------------------------------+-----------------------------------+\n",
    "+--------------------------------------------------------+----------------------------------+\n| Which line do you want to water? Enter the x coodinate | -1 to exit  \n+--------------------------------------------------------+----------------------------------+\n",
    "+--------------------------------------------------------+----------------------------------+\n| Which line do you want to water? Enter the x coodinate | -1 to exit  \n+--------------------------------------------------------+----------------------------------+\n"
};
const string harvestMsg[] = {
    "+---------------------------------------------------------+---------------------------------+\n| Which plot do you want to harvest? Enter coodinate(x y) | -1 -1 to exit\n+---------------------------------------------------------+---------------------------------+\n",
    "+----------------------------------------------------------+--------------------------------+\n| Which line do you want to harvest? Enter the x coodinate | -1 to exit  \n+----------------------------------------------------------+--------------------------------+\n",
    "+----------------------------------------------------------+--------------------------------+\n| Which line do you want to harvest? Enter the x coodinate | -1 to exit  \n+----------------------------------------------------------+--------------------------------+\n"
};
bool pLineMode = false;
bool wLineMode = false;
bool hLineMode = false;
int land_price=100, land_p_inc=10;


int main() {

    start();
    menu();
    if ( skip ) explain();
    run();

    return 0;
}


void gotoxy(int x, int y) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(consoleHandle, pos);
}

void clsconsole() {
    gotoxy(0, 26);
    cout << "|                                                                                           |" << endl;
    cout << "|                                                                                           |" << endl;
    cout << "+-------------------------------------------------------------------------------------------+" << endl;
    gotoxy(2, 26);
}

void repeatcout(const char *str, int n) {
    while (n--)
    {
        if (str[0] == '\0')
            continue;
        else
            cout << str;
    }
}

void stepcout(const char *str, int t) {
    string txt = str;
    int n = txt.size();
    for (int i = 0; i < n; i++)
    {
        printf("%c", txt[i]);
        Sleep(t);
    }
}

void frame() {
    cout << "+-------------------------------------------------------------------------------------------+" << endl;
    repeatcout("|                                                                                           |\n", 23);
    cout << "+-------------------------------------------------------------------------------------------+" << endl;
    repeatcout("|                                                                                           |\n", 3);
    cout << "+-------------------------------------------------------------------------------------------+" << endl;
    gotoxy(2, 26);
}

void box(int w, int h) {
    int zx = (WIDTH - w) / 2, zy = (HEIGHT - h) / 2;
    string ceil_floor = '+' + string(w - 2, '-') + '+';
    string space = '|' + string(w - 2, ' ') + '|';
    gotoxy(zx, zy++);
    cout << ceil_floor << endl;
    int n = h;
    while (n--)
    {
        gotoxy(zx, zy++);
        cout << space << endl;
    }
    gotoxy(zx, zy++);
    cout << ceil_floor << endl;
    gotoxy(2, 26);
}

void start() {
    frame();

    for (int i = 10; i < 15; i++)
    {
        gotoxy(12, i);
        for (int j = 0; j < 68; j++)
        {
            cout << title[i - 10][j];
            if (i % 2)
                Sleep(1);
        }
    }

    gotoxy(35, 16);
    char message[] = "Press any key to start";
    for (int i = 0; i < 22; i++)
    {
        cout << message[i];
        if (i % 2)
            Sleep(1);
    }
    gotoxy(2, 26);
    pause;
    cls;
}

void menu() {
    while (1)
    {
        frame();

        box(15, 7);
        gotoxy(42, 12);
        cout << "1 : Start";
        gotoxy(42, 14);
        cout << "2 : Exit";
        gotoxy(2, 26);

        string start;
        getline(cin, start);
        if (start == "1")
            break;
        else if (start == "2")
            exit(1);
        cls;
    }
    cls;
    while (1)
    {
        frame();

        box(15, 7);
        gotoxy(43, 9);
        cout << "explain";
        gotoxy(42, 12);
        cout << "1 : Listen";
        gotoxy(42, 14);
        cout << "2 : Skip";
        gotoxy(2, 26);

        string sk;
        getline(cin, sk);
        if (sk == "1")
        {
            skip = 1;
            break;
        }
        else if (sk == "2")
        {
            skip = 0;
            break;
        }
        cls;
    }
    cls;
}

void explain() {
    frame();

    gotoxy(2, 10);
    stepcout("Long, long ago, there was a farmer named Yejin who was very fool.", 50);
    Sleep(1000);
    gotoxy(2, 13);
    stepcout("So fool that he doesn't know what fall means.", 50);
    Sleep(1000);
    gotoxy(2, 16);
    stepcout("You step up for him!!!", 100);
    Sleep(100);
    gotoxy(2, 26);

    pause;
    cls;
}

int condition_chk(int condition) {
    if (condition == 3) {
        gotoxy(0, 22);
        cout << "+-------------------------------------------------------------------------------------------+" << endl;
        cout << "| The farmer is having a hard time. Please wait.                                            |" << endl;
        cout << "+-------------------------------------------------------------------------------------------+" << endl;
        clsconsole();
        pause;
        return 1;
    }
    return 0;
}

void plow(int x, int y) {
    int boxWidth = 3, boxHeight = 1;
    int gridWidth = fieldw * (boxWidth + 1) + 1;
    int gridHeight = fieldh * (boxHeight + 1) + 1;

    int startX = (WIDTH - gridWidth) / 2;
    int startY = (HEIGHT - gridHeight) / 2;

    int plotX = startX + x * (boxWidth + 1) + 1;
    int plotY = startY + (fieldh - 1 - y) * (boxHeight + 1) + 1;

    gotoxy(plotX, plotY);
    cout << "\033[0;33m| |\033[0m";

    gotoxy(2, 26);
}

void seed(int x, int y) {
    int boxWidth = 3, boxHeight = 1;
    int gridWidth = fieldw * (boxWidth + 1) + 1;
    int startX = (WIDTH - gridWidth) / 2;
    int startY = (HEIGHT - (fieldh * (boxHeight + 1) + 1)) / 2;

    int plotX = startX + x * (boxWidth + 1) + 2;
    int plotY = startY + (fieldh - 1 - y) * (boxHeight + 1) + 1;

    gotoxy(plotX, plotY);
    cout << SEED[seed_arr[x][y][1] / 3]; // 씨앗 단계에 따른 출력

    gotoxy(2, 26);
}

void water(int x, int y) {
    int boxWidth = 3, boxHeight = 1;
    int gridWidth = fieldw * (boxWidth + 1) + 1;
    int startX = (WIDTH - gridWidth) / 2;
    int startY = (HEIGHT - (fieldh * (boxHeight + 1) + 1)) / 2;

    int plotX = startX + x * (boxWidth + 1);
    int plotY = startY + (fieldh - 1 - y) * (boxHeight + 1);

    gotoxy(plotX + 2, plotY);
    cout << "\033[1;34m-\033[0m";
    gotoxy(plotX + 2, plotY + 2);
    cout << "\033[1;34m-\033[0m";

    water_arr[x][y][0] = 1; // 물 뿌림 상태 설정
    seed_no_water_cnt[y * fieldw + x] = 0; // 물 없는 카운트 초기화

    gotoxy(2, 26);
}

void wait() {
    for (int x = 0; x < fieldw; ++x) {
        for (int y = 0; y < fieldh; ++y) {
            if (water_arr[x][y][0]&&currentWater<2) {
                water_arr[x][y][1]++;
                if (water_arr[x][y][1] >= 5) {
                    water_arr[x][y][0] = 0; // 물 말라버림
                    water_arr[x][y][1] = 0;
                }
            }

            if (plow_arr[x][y][0] && !seed_arr[x][y][0]) {
                plow_arr[x][y][1]++;
                if (plow_arr[x][y][1] >= 6) {
                    plow_arr[x][y][0] = 0; // 땅 원래대로
                    plow_arr[x][y][1] = 0;
                }
            }

            if (seed_arr[x][y][0] && seed_arr[x][y][1] < 4 * 3) {
                seed_arr[x][y][1]++;
                if (water_arr[x][y][0]&&currentWater<2) {
                    seed_no_water_cnt[y * fieldw + x] = 0;
                } else {
                    seed_no_water_cnt[y * fieldw + x]++;
                    if (seed_no_water_cnt[y * fieldw + x] >= 2) {
                        seed_arr[x][y][1] = 4 * 3; // 씨앗 죽음
                    }
                }
            }
        }
    }
}

void harvest(int x, int y) {
    if (seed_arr[x][y][0]) {
        seed_arr[x][y][0] = 0;
        int stage = seed_arr[x][y][1] / 3;

        // 상태에 따른 저장 처리
        if (stage == 3) {
            Storage[3]++; // 완벽한 수확
        } else if (stage == 4) {
            Storage[4]++; // 죽은 상태
        } else {
            Storage[stage]++;
        }

        seed_arr[x][y][1] = 0; // 상태 초기화
    }
}

void field() {
    int rows = fieldh, cols = fieldw;
    int boxWidth = 3, boxHeight = 1;
    int gridWidth = cols * (boxWidth + 1) + 1;
    int gridHeight = rows * (boxHeight + 1) + 1;
    int startX = (WIDTH - gridWidth) / 2;
    int startY = (HEIGHT - gridHeight) / 2;

    for (int r = 0; r <= rows; ++r) {
        int y = startY + r * (boxHeight + 1);
        gotoxy(startX, y);

        for (int c = 0; c < cols; ++c) {
            cout << "\033[0;33m+\033[0m" << "\033[0;33m---\033[0m";
        }
        cout << "\033[0;33m+\033[0m" << endl;

        if (r < rows) {
            for (int line = 0; line < boxHeight; ++line) {
                gotoxy(startX, y + line + 1);
                for (int c = 0; c < cols; ++c) {
                    cout << "\033[0;33m|\033[0m" << "   ";
                }
                cout << "\033[0;33m|\033[0m" << endl;
            }
        }
    }

    for (int x = 0; x < fieldw; ++x) {
        for (int y = 0; y < fieldh; ++y) {
            if (plow_arr[x][y][0]) plow(x, y);
            if (seed_arr[x][y][0]) seed(x, y);
            if (water_arr[x][y][0]) water(x, y);
        }
    }

    gotoxy(0, 22);
    cout << "+--------+--------+---------+--------+-----------+---------+--------------------------------+" << endl;
    cout << "| 1.plow | 2.seed | 3.water | 4.wait | 5.harvest | 6.leave |" << endl;
    cout << "+--------+--------+---------+--------+-----------+---------+--------------------------------+" << endl;
    moneystatus();
    gotoxy(0, 0);
    cout << "+-------------------------+----------------------------------------+------------------------+" << endl;
    cout << "|                         | Harvest: " 
         << setw(12) << "\033[1;32m" << Storage[0] << "\033[0m"
         << setw(12) << "\033[1;32m" << Storage[1] << "\033[0m" 
         << setw(12) << "\033[1;32m" << Storage[2] << "\033[0m" 
         << setw(12) << "\033[1;33m" << Storage[3] << "\033[0m" 
         << setw(12) << "\033[1;30m" << Storage[4] << "\033[0m" << "|" << endl;
    cout << "+-------------------------+----------------------------------------+------------------------+" << endl;
    gotoxy(2, 26);
}

void farm() {
    while (1) {
        cls;
        frame();
        
        field();

        string inp;
        getline(cin, inp);
        lli tx, ty;
        if (inp == "1" || inp == "plow") {  // plow
            while(1) {
                if (condition_chk(plow_count)) break;
                gotoxy(0, 22);
                cout << plowMsg[currentPlow] << endl;
                
                clsconsole();
                if (!pLineMode) {
                    string txty;
                    getline(cin, txty);
                    istringstream iss(txty);
                    iss >> tx >> ty;
                    if (tx >= 1 && tx <= fieldw && ty >= 1 && ty <= fieldh && !plow_arr[tx - 1][ty - 1][0]) {
                        if (currentPlow < 2) {
                            plow_count++;
                        }
                        clsconsole();
                        stepcout("Plowing", 100);
                        stepcout("...", 300);
                        plow_arr[tx-1][ty-1][0] = 1;
                        field();
                    }
                    else if (tx==-1&&ty==-1) break;
                }
                else {
                    cin >> tx;
                    if (tx >= 1 && tx <= fieldw) {
                        if (currentPlow < 2) {
                            plow_count++;
                        }
                        clsconsole();
                        stepcout("Plowing", 100);
                        stepcout("...", 300);
                        for (int r = 1; r <= fieldh; r++) {  // line plowing
                            plow_arr[tx-1][r-1][0] = 1;
                        }
                        field();
                    }
                    else if (tx==-1&&ty==-1) break;
                }

            }
        }
        else if (inp == "2" || inp == "seed") {  // seed
            while (1) {
                gotoxy(0, 22);
                cout << "+------------------------------------------------------+------------------------------------+" << endl;
                cout << "| Which plot do you want to seed? Enter coodinate(x y) | -1 -1 to exit" << endl;
                cout << "+------------------------------------------------------+------------------------------------+" << endl;
                clsconsole();
                string txty;
                getline(cin, txty);
                istringstream iss(txty);
                iss >> tx >> ty;
                if (tx >= 1 && tx <= fieldw && ty >= 1 && ty <= fieldh && plow_arr[tx-1][ty-1][0] && !seed_arr[tx-1][ty-1][0]) {
                    clsconsole();
                    stepcout("Seeding", 50);
                    stepcout("...", 50);
                    seed_arr[tx-1][ty-1][0] = 1;
                    field();
                }
                else if (tx==-1&&ty==-1) break;
            }
        }
        else if (inp == "3" || inp == "water") {  // water
            if (currentWater == 2) {
                for (int tx=0; tx<fieldw; tx++) {
                    for (int ty=0; ty<fieldh; ty++) {
                        water_arr[tx][ty][0] = 1;
                        water_arr[tx][ty][1] = 0;
                        seed_no_water_cnt[ty*fieldw+tx] = 0;
                    }
                }
                continue;
            }
            while (1) {
                if (condition_chk(water_count)) break;
                gotoxy(0, 22);
                cout << waterMsg[currentWater];
                clsconsole();
                if (!wLineMode) {
                    string txty;
                    getline(cin, txty);
                    istringstream iss(txty);
                    iss >> tx >> ty;
                    if (tx >= 1 && tx <= fieldw && ty >= 1 && ty <= fieldh && !water_arr[tx-1][ty-1][0]) {
                        if (currentWater < 2) {
                            water_count++;
                        }
                        clsconsole();
                        stepcout("Watering", 50);
                        stepcout("...", 300);
                        water_arr[tx-1][ty-1][0] = 1;
                        water_arr[tx-1][ty-1][1] = 0;
                        seed_no_water_cnt[(ty-1)*fieldw+tx-1] = 0;
                        field();
                    }
                    else if (tx==-1&&ty==-1) break;
                }
                else {
                    cin >> tx;
                    if (tx >= 1 && tx <= fieldw) {
                        if (currentWater < 2) {
                            water_count++;
                        }
                        clsconsole();
                        stepcout("Watering", 50);
                        stepcout("...", 300);
                        for (int r=1; r<=fieldh; r++) {
                            water_arr[tx-1][r-1][0] = 1;
                            water_arr[tx-1][r-1][1] = 0;
                            seed_no_water_cnt[(r-1)*fieldw+tx-1] = 0;
                        }
                        field();
                    }
                    else if (tx==-1) break;
                }
            }
        }
        else if (inp == "4" || inp == "wait") {
            plow_count = 0;
            water_count = 0;
            harvest_count = 0;
            clsconsole();
            stepcout(".....", 600);
            wait();
        }
        else if (inp == "5" || inp == "harvest") {
            if (currentHarvest == 2) {
                for (int tx=0; tx<fieldw; tx++) {
                    for (int ty=0; ty<fieldh; ty++) {
                        harvest(tx, ty);
                    }
                }
                continue;
            }
            while (1) {
                if (condition_chk(harvest_count)) break;
                gotoxy(0, 22);
                cout << harvestMsg[currentHarvest];
                clsconsole();
                if (!hLineMode) {
                    string txty;
                    getline(cin, txty);
                    istringstream iss(txty);
                    iss >> tx >> ty;
                    if (tx >= 1 && tx <= fieldw && ty >= 1 && ty <= fieldh && seed_arr[tx-1][ty-1][0]) {
                        if (currentHarvest < 1) {
                            harvest_count++;
                        }
                        clsconsole();
                        stepcout("Harvesting", 50);
                        stepcout("...", 400);
                        harvest(tx-1, ty-1);
                        field();
                    }
                    else if (tx==-1&&ty==-1) break;
                }
                else {
                    cin >> tx;
                    if (tx >= 1 && tx <= fieldw) {
                        if (currentHarvest < 2) {
                            harvest_count++;
                        }
                        clsconsole();
                        stepcout("Harvesting", 50);
                        stepcout("...", 400);
                        for (int r=1; r<=fieldh; r++) {
                            harvest(tx-1, r-1);
                        }
                        field();
                    }
                    else if (tx==-1) break;
                }
            }
        }
        else if (inp == "6" || inp == "leave") {
            gotoxy(2, 26);
            stepcout("Leave the farm", 50);
            stepcout("...", 500);
            break;
        }
    }
    cls;
}

void moneystatus() {
    gotoxy(0, 0);
    cout << "+------------------------------------------------------------------+------------------------+" << endl;

    string moneyStr = to_string(Money);
    const int maxMoneyWidth = 15;
    int count = maxMoneyWidth - moneyStr.length();
    cout << "|                                                                  | Money: " 
         << string(count, ' ') << "\033[1;34m" << moneyStr << "\033[0m |" << endl;

    cout << "|                                                                  +------------------------+" << endl;

    gotoxy(2, 26);
}

void buy_something(int something) {
    if (something == 1) {
        moneystatus();
        gotoxy(0, 22);
        cout << "+------------------------------+------------------------------------------------------------+" << endl;
        cout << "| Expand width or height (W/H) | Current field size : " << fieldw << "x" << fieldh << endl;
        cout << "+------------------------------+------------------------------------------------------------+" << endl;
        clsconsole();

        string WorH;
        getline(cin, WorH);
        if ((WorH=="W"||WorH=="w")&&fieldw<wlimit) {
            Money -= land_price;
            land_price += land_p_inc;
            land_p_inc *= 2;
            fieldw++;
        }
        else if ((WorH=="H"||WorH=="h")&&fieldh<hlimit) {
            Money -= land_price;
            land_price += land_p_inc;
            land_p_inc *= 2;
            fieldh++;
        }
    }
    else if (something == 2) {
        Money -= plowPrice[currentPlow];
        currentPlow++;
        pLineMode = true;
    }
    else if (something == 3) {
        Money -= waterPrice[currentWater];
        currentWater++;
        wLineMode = true;
    }
    else if (something == 4) {
        Money -= harvestPrice[currentHarvest];
        currentHarvest++;
        hLineMode = true;
    }
    cls;
    frame();
    box(50, 9);

    gotoxy(30, 10);
    cout << "1. Land Expansion";
    gotoxy(30, 12);
    cout << "2. " << PlowTools[currentPlow+1];
    gotoxy(30, 14);
    cout << "3. " << WaterTools[currentWater+1];
    gotoxy(30, 16);
    cout << "4. " << HarvestTools[currentHarvest+1];

    moneystatus();
}

void buy() {
    while (1) {
        cls;
        frame();
        box(50, 9);

        gotoxy(30, 10);
        if (fieldw==20&&fieldh==8) cout << "1. \033[9mSold Out\033[0m";
        else cout << "1. Land Expansion";
        gotoxy(30, 12);
        cout << "2. " << PlowTools[currentPlow+1];
        gotoxy(30, 14);
        cout << "3. " << WaterTools[currentWater+1];
        gotoxy(30, 16);
        cout << "4. " << HarvestTools[currentHarvest+1];
        
        gotoxy(0, 22);
        cout << "+----------------------------------------+--------------------------------------------------+" << endl;
        cout << "| What would you like to buy? (Exit: -1) |" << endl;
        cout << "+----------------------------------------+--------------------------------------------------+" << endl;
        moneystatus();
        
        string inp;
        getline(cin, inp);
        if (inp == "-1") return;
        string YesNo;
        if (inp == "1"&&!(fieldw==20&&fieldh==8)) {
            while (1) {
                if (fieldw==20&&fieldh==8) break;
                moneystatus();
                gotoxy(0, 22);
                cout << "+------------------------+------------------------------------------------------------------+" << endl;
                cout << "| Expand the land? (Y/n) | Cost: " << setw(10) << land_price << endl;
                cout << "+------------------------+------------------------------------------------------------------+" << endl;

                clsconsole();
                getline(cin, YesNo);
                if (Money < land_price) break;
                if (YesNo == "Y" || YesNo == "y") {
                    buy_something(1);
                }
                else if (YesNo == "N" || YesNo == "n") break;
            }
        }
        else if (inp == "2" && currentPlow < 2) {
            while (1) {
                if (currentPlow >= 2) break;
                gotoxy(0, 22);
                cout << "+--------------------------+----------------------------------------------------------------+" << endl;
                cout << "| Upgrade your plow? (Y/n) | Cost: " << setw(10) << plowPrice[currentPlow] << endl;
                cout << "+--------------------------+----------------------------------------------------------------+" << endl;

                clsconsole();
                getline(cin, YesNo);
                if (Money < plowPrice[currentPlow]) break;
                if (YesNo == "Y" || YesNo == "y") {
                    buy_something(2);
                }
                else if (YesNo == "N" || YesNo == "n") break;
            }
        }
        else if (inp == "3" && currentWater < 2) {
            while (1) {
                if (currentWater >= 2) break;
                gotoxy(0, 22);
                cout << "+-----------------------------------+-------------------------------------------------------+" << endl;
                cout << "| Upgrade your watering tool? (Y/n) | Cost: " << setw(10) << waterPrice[currentWater] << endl;
                cout << "+-----------------------------------+-------------------------------------------------------+" << endl;

                clsconsole();
                getline(cin, YesNo);
                if (Money < waterPrice[currentWater]) break;
                if (YesNo == "Y" || YesNo == "y") {
                    buy_something(3);
                }
                else if (YesNo == "N" || YesNo == "n") break;
            }
        }
        else if (inp == "4" && currentHarvest < 2) {
            while (1) {
                if (currentHarvest >= 2) break;
                gotoxy(0, 22);
                cout << "+----------------------------------+--------------------------------------------------------+" << endl;
                cout << "| Upgrade your harvest tool? (Y/n) | Cost: " << setw(10) << harvestPrice[currentHarvest] << endl;
                cout << "+----------------------------------+--------------------------------------------------------+" << endl;

                clsconsole();
                getline(cin, YesNo);
                if (Money < harvestPrice[currentHarvest]) break;
                if (YesNo == "Y" || YesNo == "y") {
                    buy_something(4);
                }
                else if (YesNo == "N" || YesNo == "n") break;
            }
        }
    }
}

void sell() {
    while (1) {
        cls;
        frame();

        gotoxy(0, 6);
        cout << "|                         +---------------------------------------+                         |" << endl;
        cout << "|                         |                                       |                         |" << endl;
        cout << "|                         |    1. Sell all                        |                         |" << endl;
        cout << "|                         |                                       |                         |" << endl;
        cout << "|                         |    2. Sell only perfect harvests      |                         |" << endl;
        cout << "|                         |                                       |                         |" << endl;
        cout << "|                         |    3. Sell only profitable harvests   |                         |" << endl;
        cout << "|                         |                                       |                         |" << endl;    
        cout << "|                         +---------------------------------------+                         |" << endl;

        lli s = Storage[0];
        lli g = Storage[1];
        lli r = Storage[2];
        lli p = Storage[3];
        lli w = Storage[4];
        gotoxy(0, 15);
        cout << "+-------------------------------------------------------------------------------------------+" << endl;
        cout << "|  < Harvest >" << endl;
        cout << "|  - Sprout: " << setw(11) << "\033[1;32m" << s << "\033[0m" << endl;
        cout << "|  - Growing: " << setw(10) << "\033[1;32m" << g << "\033[0m" << endl;
        cout << "|  - Ripening: " << setw(9) << "\033[1;32m" << r << "\033[0m" << endl;
        cout << "|  - Perfect: " << setw(10) << "\033[1;33m" << p << "\033[0m" << endl;
        cout << "|  - Wilted: " << setw(11) << "\033[1;30m" << w << "\033[0m" << endl;
        cout << "+-----------------------------------------------+-------------------------------------------+" << endl;
        cout << "| What crops would you like to sell? (Exit: -1) |" << endl;
        cout << "+-----------------------------------------------+-------------------------------------------+" << endl;

        moneystatus();
        clsconsole();
        string inp;
        getline(cin, inp);
        if (inp == "-1") break;
        else if (inp == "1") {
            Money += s*0+g*3+r*5+p*10-w*5;
            for (int i = 0; i < 5; i++) Storage[i]=0;
        }
        else if (inp == "2") {
            Money += p*10;
            Storage[perfect]=0;
        }
        else if (inp == "3") {
            Money += s*0+g*3+r*5+p*10;
        }
    }
}

void St() {
    cls;
    frame();
    while (1) {
        gotoxy(0, 6);
        cout << "|                         +---------------------------------------+                         |" << endl;
        cout << "|                         |                                       |                         |" << endl;
        cout << "|                         |          1. My tools                  |                         |" << endl;
        cout << "|                         |                                       |                         |" << endl;
        cout << "|                         |          2. Harvests status           |                         |" << endl;
        cout << "|                         |                                       |                         |" << endl;
        cout << "|                         |          3. Exit                      |                         |" << endl;
        cout << "|                         |                                       |                         |" << endl;
        cout << "|                         +---------------------------------------+                         |" << endl;

        clsconsole();

        string inp;
        getline(cin, inp);
        gotoxy(0, 17);
        cout << "+-------------------------------------------------------------------------------------------+" << endl;
        cout << "|                                                                                           |" << endl;
        cout << "|                                                                                           |" << endl;
        cout << "|                                                                                           |" << endl;
        cout << "|                                                                                           |" << endl;
        cout << "|                                                                                           |" << endl;
        cout << "|                                                                                           |" << endl;
        cout << "+-------------------------------------------------------------------------------------------+" << endl;
        if (inp == "1" || inp == "My tools") {
            gotoxy(0, 17);
            cout << "+-------------------------------------------------------------------------------------------+" << endl;
            cout << "|  < Tools >" << endl;
            cout << "|                                                                                           |" << endl;
            cout << "|  - Plow tools: " << "\033[0;33m" << PlowTools[currentPlow] << "\033[0m" << endl;
            cout << "|  - Water tools: " << "\033[1;34m" << WaterTools[currentWater] << "\033[0m" << endl;
            cout << "|  - Harvest tools: " << "\033[1;30m" << HarvestTools[currentHarvest] << "\033[0m" << endl;
            cout << "|                                                                                           |" << endl;
            cout << "+-------------------------------------------------------------------------------------------+" << endl;
            clsconsole();
        }
        else if (inp == "2" || inp == "Harvests status") {
            gotoxy(0, 17);
            cout << "+-------------------------------------------------------------------------------------------+" << endl;
            cout << "|  < Harvest >" << endl;
            cout << "|  - Sprout: " << setw(11) << "\033[1;32m" << Storage[sprout] << "\033[0m" << endl;
            cout << "|  - Growing: " << setw(10) << "\033[1;32m" << Storage[growing] << "\033[0m" << endl;
            cout << "|  - Ripening: " << setw(9) << "\033[1;32m" << Storage[ripening] << "\033[0m" << endl;
            cout << "|  - Perfect: " << setw(10) << "\033[1;33m" << Storage[perfect] << "\033[0m" << endl;
            cout << "|  - Wilted: " << setw(11) << "\033[1;30m" << Storage[wilted] << "\033[0m" << endl;
            cout << "+-------------------------------------------------------------------------------------------+" << endl;
            clsconsole();
        }
        else if (inp == "3" || inp == "Exit") break;
    }
}

void shop() {
    while (1) {
        cls;
        frame();
        box(50, 10);

        gotoxy(30, 10);
        cout << "1. Buy";
        gotoxy(53, 10);
        cout << "2. Sell";
        gotoxy(30, 15);
        cout << "3. Storage";
        gotoxy(53, 15);
        cout << "4. Leave";

        gotoxy(2, 26);
        string inp;
        getline(cin, inp);
        if (inp == "1" || inp == "Buy") {
            buy();
        }
        else if (inp == "2" || inp == "Sell") {
            sell();
        }
        else if (inp == "3" || inp == "Storage") {
            St();
        }
        else if (inp == "4" || inp == "Leave") {
            clsconsole();
            stepcout("Leave the shop", 50);
            stepcout("...", 500);
            break;
        }
    }
}

void guide() {
    cls; // 화면 초기화
    frame(); // 기본 UI 출력
    gotoxy(3, 10);
    stepcout("Welcome to Morning Sunrise!", 50);
    
    gotoxy(3, 12);
    cout << "This game is a farming simulation\n\n|  you can grow crops, earn money, and expand your farm.";

    gotoxy(2, 26);
    cout << "Press any key to listen explaination of farm.";
    pause;

    // FARM
    cls;
    frame();
    gotoxy(3, 1);
    cout << "The coordinate structure of the field is as follows:" << endl;
    cout << "|     +---+---+  You can buy land expansions to increase the width or height of your land." << endl;
    cout << "|   2 |1 2|2 2|  " << endl;
    cout << "|     +---+---+  " << endl;
    cout << "|   1 |1 1|2 1|  " << endl;
    cout << "|     +---+---+  " << endl;
    cout << "|       1   2    " << endl;

    // Plowing section
    gotoxy(3, 9);
    cout << "1. Plow the field:";
    gotoxy(5, 10);
    cout << "- Enter the coordinates of a field and it will plow that spot.";
    gotoxy(5, 11);
    cout << "- If you type \"1 1\", the \"1 1\" field will be plowed.";

    // Seeding section
    gotoxy(3, 13);
    cout << "2. Plant seeds:";
    gotoxy(5, 14);
    cout << "- Select a plot to plant seeds.";
    gotoxy(5, 15);
    cout << "- You can only sow seeds in plowed fields.";

    // Watering section
    gotoxy(3, 17);
    cout << "3. Water your crops:";
    gotoxy(5, 18);
    cout << "- Keep your crops hydrated to ensure growth.";

    // Wait section
    gotoxy(3, 20);
    cout << "4. Wait: let time flow.";

    // Harvesting section
    gotoxy(3, 22);
    cout << "5. Harvest crops:";
    gotoxy(5, 23);
    cout << "- When crops are fully grown, harvest them for storage or sale.";

    gotoxy(2, 26);
    cout << "Press any key to listen explaination of tools.";
    pause;
    cls;
    frame();
    // TOOLS
    gotoxy(3, 5);
    cout << "TOOLS";
    gotoxy(3, 8);
    cout << "1. <Plow tools>";
    gotoxy(5, 9);
    cout << "- Basic Plow(free): Can only plow one field. If you plow 3 times, you have to wait.";
    gotoxy(5, 10);
    cout << "- Reinforced Plow(1000): Can plow field vertically + plow limit of Basic Plow.";
    gotoxy(5, 11);
    cout << "- Advenced Plow(10000): Can plow field vertically. There is no limit to plowing.";

    gotoxy(3, 13);
    cout << "1. <Water tools>";
    gotoxy(5, 14);
    cout << "- Water Can(free): Can only water one field. If you water 3 times, you have to wait.";
    gotoxy(5, 15);
    cout << "- Hose(1000): Can water field vertically. If you water 3 times, you have to wait.";
    gotoxy(5, 16);
    cout << "- Irrigation Tool(15000): The fields are irrigated so there is always water on them.";
    
    gotoxy(3, 18);
    cout << "1. <Harvest tools>";
    gotoxy(5, 19);
    cout << "- Sickle(free): Can only harvest one field. If you harvest 3 times, you have to wait.";
    gotoxy(5, 20);
    cout << "- Scythe(1500): Can water field vertically.";
    gotoxy(5, 21);
    cout << "- Combine Harvester(15000): Harvest the entire field at once.";

    gotoxy(2, 26);
    cout << "Press any key to listen explaination of shop.";
    pause;
    cls;
    frame();
    // Selling section
    gotoxy(3, 11);
    cout << "5. Visit the shop:";
    gotoxy(5, 12);
    cout << "- Buy new tools and expand your land.";
    gotoxy(5, 13);
    cout << "- Sell your crops to earn money.";

    // Ending section
    gotoxy(3, 15);
    cout << "Grow your farm, manage your resources, and enjoy the farming life!";

    gotoxy(2, 26);
    cout << "Press any key to return to the main menu.";
    pause;
    cls;
}

void end() {
    clsconsole();
    gotoxy(0, 0);
    for (int i=0; i<30; i++){
        cout << "                                                                                             "<< endl;
        Sleep(100);
    }
    gotoxy(WIDTH/2-7, HEIGHT/2);
    stepcout("End of life", 300);
    stepcout("...", 1000);
    gotoxy(WIDTH/2-8, HEIGHT/2);
    stepcout("                ", 100);
    Sleep(500);
    exit(1);
}

void run() {
    while (1) {
        cls;
        frame();

        box(50, 10);

        gotoxy(30, 10);
        cout << "1. Farm";
        gotoxy(53, 10);
        cout << "2. Shop";
        gotoxy(30, 15);
        cout << "3. Guide";
        gotoxy(53, 15);
        cout << "4. End";

        string input;
        gotoxy(2, 26);
        getline(cin, input);
        if (input == "1" || input == "Farm") {
            clsconsole();
            stepcout("On the way to the farm", 50);
            stepcout("...", 500);
            farm();
        }
        else if (input == "2" || input == "Shop") {
            clsconsole();
            stepcout("On the way to the shop", 50);
            stepcout("...", 500);
            shop();
        }
        else if (input == "3" || input == "Guide") {
            clsconsole();
            stepcout("Unfolding the guidebook", 50);
            stepcout("...", 500);
            guide();
        }
        else if (input == "4" || input == "End") {
            end();
        }
    }
    cls;
}
