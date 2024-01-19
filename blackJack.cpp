// blackJack.cpp

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <vector>

using namespace std;


int cardsArr[][13] = { {12,1,12,12,12,12,12,12,12,12,12,12,12},
                      { 1,2, 3, 4, 5, 6, 7, 8, 9, 10,10,10,10} };
int scPl = 0, scD = 0;

void title() {
    cout << "Welcome to BlackJack, baby!\n\n"<< "Счет\t"<< scPl <<" : "<< scD << "\n\n";
}

void cardShow(vector <int> who) {
    for (int i = 0; i < who.size(); i++) {
        switch (who[i])
        {
        case 0:
            cout << "A  ";
            break;
        case 1:
            cout << "2  ";
            break;
        case 2:
            cout << "3  ";
            break;
        case 3:
            cout << "4  ";
            break;
        case 4:
            cout << "5  ";
            break;
        case 5:
            cout << "6  ";
            break;
        case 6:
            cout << "7  ";
            break;
        case 7:
            cout << "8  ";
            break;
        case 8:
            cout << "9  ";
            break;
        case 9:
            cout << "10  ";
            break;
        case 10:
            cout << "J  ";
            break;
        case 11:
            cout << "Q  ";
            break;
        case 12:
            cout << "K  ";
            break;
        }
    }
    cout << "\n";
}

void showFild(vector <int> player, vector <int> dealer, int plSum, int dSum) {
    system("cls");
    title();
    cout << "__________________________________________________________________________________________________\n\n";
    cout << "Ваши карты: ";
    cardShow(player);
    cout << "Ваши очки: " << plSum << "\n\n";
    cout << "Карта дилера: ";
    cardShow(dealer);
    cout << "Очки дилера: " << dSum << "\n\n";
    cout << "__________________________________________________________________________________________________\n\n";
}

void chek2by3() {
    float sumArr = 0;
    for (int i = 0; i < 13; i++) {
        sumArr += cardsArr[0][i];
    }
    if (sumArr / (12 * 13) >= (float)2 / 3) {
        for (int i = 0; i < 13; i++) {
            cardsArr[0][i] = 12;
        }
    }
}

bool ifSumMore(int sum, int what) {
    if (sum <= what) {
        return false;
    }
    else {
        return true;
    }

}

bool findAce(vector <int> dealer) {
    for (int i = 0; i < dealer.size(); i++) {
        if (dealer[i] == 0) {
            return true;
        }
    }
    return false;
}

int calcCards(vector<int> who) {
    int sum = 0;
    int ace = 0;
    for (int i = 0; i < who.size(); i++) {
        if (who[i] == 0) {
            ace++;
        }
        else {
            sum += cardsArr[1][who[i]];
        }
    }
    if (ace > 0) {
        if (sum + 11 * ace < 21) {
            sum += 11 * ace;
        }
        else {
            sum += 1 * ace;
        }
    }
    return sum;
}

void deal(vector <int>* who) {
    int chance = 0;
    int card = 0;

    for (int crtINarr = 0; crtINarr < 13; crtINarr++) {//поиск максимального шанса из 13 номиналов
        int temp = 0;
        for (int i = 0; i < cardsArr[0][crtINarr]; i++) {//рандом с учетом оставшихся в игре карт
            temp += rand() % 1000;
        }
        if (temp > chance) {
            chance = temp;
            card = crtINarr;
        }
        else if (temp == chance) {
            if ((rand() % 1 + 100) % 2 == 0) {
                card = crtINarr;
            }
        }
    }
    cardsArr[0][card]--;
    who->push_back(card);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0));

    int lap = 0;

    while (true) {//цикл игры основной
        system("cls");
        title();
        cout << "Будем играть?\n" << "Да (pass any key)/ Нет (pass Esc)";

        if (_getch() == 27) {//если esc
            cout << "\n\nI'll be back!\n\n";
            Sleep(1800);
            break;
        }

        else {//начало раунда
            cout << "\n\nTасуется колода...\n\n";
            Sleep(1800);
            chek2by3();

            vector <int> player;
            vector <int> dealer;

            deal(&player);
            deal(&player);
            deal(&dealer);
            int plSum = calcCards(player);
            int dSum = calcCards(dealer);

            showFild(player, dealer, plSum, dSum);

            if (ifSumMore(plSum, 21)) {//если при первой раздаче выпало больше 21.
                cout << "Перебор, вы проиграли!\n\n";
                scD++;
                Sleep(2000);
            }

            else {//продолжаем игру
                int ans;
                do//цикл добора карт игроком
                {
                    cout << "Добираете еще карты?\n";
                    cout << "Да (pass Enter)/ Нет (pass Esc)\n\n";
                    ans = _getch();

                    if (ans == 27) {//если не берет карту
                        break;
                    }

                    else {//если берет карту
                        deal(&player);
                        plSum = calcCards(player);
                        showFild(player, dealer, plSum, dSum);

                        if (ifSumMore(plSum, 21)) {//выход из цикла добора если больше 21
                            break;
                        }
                    }
                } while (true);

                if (ifSumMore(plSum, 21)) {//если у игрока больше 21
                    scD++;
                    cout << "Перебор, вы проиграли!\n\n";
                    system("pause");
                }

                else {//добор дилера

                    if (dSum< plSum) { 
                        while (dSum < plSum) {
                            cout << "Дилер берет карту.\n\n";
                            Sleep(1200);
                            deal(&dealer);
                            dSum = calcCards(dealer);

                            showFild(player, dealer, plSum, dSum);

                            if (ifSumMore(dSum, 21)) {//выход из цикла, если у дилера перебор
                                break;
                            }
                            Sleep(1200);
                        }
                    }
                    if (!ifSumMore(dSum, 21)) {
                        if (plSum > dSum) {//если у дилера и у игрока не больше 21
                            scPl++;
                            cout << "Вы выйграли!\n\n";
                            system("pause");
                        }
                        else if (plSum == dSum) {
                            cout << "Ничья!\n\n";
                            system("pause");
                        }
                        else {
                            scD++;
                            cout << "Вы проиграли!\n\n";
                            system("pause");
                        }
                    }
                    else {//еслиперебор у дилера
                        scPl++;
                        cout << "Вы выйграли!\n\n";
                        system("pause");
                    }
                }
            }
        }
    }
    return 0;
}
