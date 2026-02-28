#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

string tooLowMessages[] = {
    "Za malo !",
    "Zdecydowanie za nisko .",
    "Sprobuj wiekszej liczby .",
    "Ta liczba jest mniejsza niz potrzeba .",
    "Podbij troche wyzej ."
}; 

string tooHighMessages[] = {
    "Za duzo !",
    "Oj, przesadziles w gore .",
    "Ta liczba jest za wysoka .",
    "Sprobuj mniejszej liczby .",
    "Zejdz troche nizej ."
};


string randomMessage(bool tooLow) {
    int index = rand() % 5; 

    if (tooLow)
        return tooLowMessages[index];
    else
        return tooHighMessages[index];
}


struct Score {
    string name;
    int attempts;
    int difficulty;
};

void saveScore(string name, int attempts, int difficulty) {
    ofstream file("scores.txt", ios::app);
    if (file.is_open()) {
        file << name << " " << attempts << " " << difficulty << endl;
        file.close();
    }
}

void showScores() {
    ifstream file("scores.txt");
    if (!file.is_open()) {
        cout << "Brak zapisanych wynikow.\n";
        return;
    }

    cout << "\n=== TOP WYNIKOW ===\n";
    string name;
    int attempts, difficulty;

    while (file >> name >> attempts >> difficulty) {
        cout << name << " | proby: " << attempts << " | poziom: " << difficulty << endl;
    }

    file.close();
}

int main() {
    srand(time(NULL));

    while (true) {
        cout << "\n=========================\n";
        cout << "     ZGADNIJ LICZBE      \n";
        cout << "=========================\n";
        cout << "1. Nowa gra\n";
        cout << "2. Wyniki\n";
        cout << "3. Wyjscie\n";

        int menu;
        cin >> menu;

        if (menu == 3) break;

        if (menu == 2) {
            showScores();
            continue;
        }

        if (menu == 1) {
            cout << "\nWybierz poziom trudnosci:\n";
            cout << "1. Latwy (1 - 50)\n";
            cout << "2. Sredni (1 - 100)\n";
            cout << "3. Trudny (1 - 250)\n";
            cout << "Twoj wybor: ";

            int diff;
            cin >> diff;
if (diff < 1 || diff > 3) {
                cout << "Nieprawidlowy wybor poziomu. Sprobuj ponownie.\n";
                continue;
            }
            int maxNum = (diff == 1 ? 50 : diff == 2 ? 100 : 250);
            int secret = rand() % maxNum + 1;
            int attempts = 0;
            int guess;

            cout << "\nTryb zakladu? (1 = tak, 0 = nie): ";
            int betMode;
            cin >> betMode;

            int betLimit = 0;
            if (betMode == 1) {
                cout << "Podaj maksymalna liczbe prob: ";
                cin >> betLimit;
            }

            while (true) {
                attempts++;
                cout << "\nProba nr " << attempts << ". Podaj liczbe : ";
                cin >> guess;

                if (guess == secret) {
                    cout << "Brawo! Trafiles liczbe!\n";
                    cout << "Podaj swoje imie: ";
                    string name;
                    cin >> name;

                    saveScore(name, attempts, diff);
                    break;
                }

                if (guess < secret)
    cout << randomMessage(true) << endl;
else
    cout << randomMessage(false) << endl;


                if (betMode == 1 && attempts >= betLimit) {
                    cout << "\nPrzekroczono limit prob! Przegrales zaklad.\n";
                    cout << "Prawidlowa liczba to: " << secret << endl;
                    break;
                }
            }
        }
    }

    cout << "\nDziekujemy za gre !\n";
    return 0;
}
