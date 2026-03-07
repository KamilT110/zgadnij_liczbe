#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
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
    return tooLow ? tooLowMessages[index] : tooHighMessages[index];
}

// ---------------------------
// BEZPIECZNY ODCZYT LICZB
// ---------------------------
int safeInput() {
    int x;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Nieprawidlowe dane. Podaj liczbe: ";
    }
    return x;
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

// ---------------------------
// SPRAWDZANIE CZY SA WYNIKI
// ---------------------------
bool hasScores() {
    ifstream file("scores.txt");
    return file.good() && file.peek() != ifstream::traits_type::eof();
}

// ---------------------------
// SORTOWANY RANKING
// ---------------------------
void showScores() {
    ifstream file("scores.txt");
    if (!file.is_open()) {
        cout << "Brak zapisanych wynikow.\n";
        return;
    }

    vector<Score> scores;
    Score s;

    while (file >> s.name >> s.attempts >> s.difficulty) {
        scores.push_back(s);
    }
    file.close();

    if (scores.empty()) {
        cout << "Brak zapisanych wynikow.\n";
        return;
    }

    sort(scores.begin(), scores.end(), [](const Score &a, const Score &b) {
        if (a.difficulty == b.difficulty)
            return a.attempts < b.attempts;
        return a.difficulty < b.difficulty;
    });

    cout << "\n=== RANKING ===\n";
    for (auto &x : scores) {
        cout << x.name << " | proby: " << x.attempts
             << " | poziom: " << x.difficulty << endl;
    }
}

int main() {
    srand(time(NULL));

    while (true) {
        cout << "\n=========================\n";
        cout << "     ZGADNIJ LICZBE      \n";
        cout << "=========================\n";
        cout << "1. Nowa gra\n";

        if (hasScores())
            cout << "2. Wyniki\n";

        cout << "3. Wyjscie\n";

        int menu = safeInput();

        if (menu == 3) break;

        if (menu == 2 && hasScores()) {
            showScores();
            continue;
        }

        if (menu == 1) {
            cout << "\nWybierz poziom trudnosci:\n";
            cout << "1. Latwy (1 - 50)\n";
            cout << "2. Sredni (1 - 100)\n";
            cout << "3. Trudny (1 - 250)\n";
            cout << "Twoj wybor: ";

            int diff = safeInput();
            if (diff < 1 || diff > 3) {
                cout << "Nieprawidlowy wybor poziomu. Sprobuj ponownie.\n";
                continue;
            }

            int maxNum = (diff == 1 ? 50 : diff == 2 ? 100 : 250);
            int secret = rand() % maxNum + 1;
            int attempts = 0;
            int guess;

            cout << "\nTryb zakladu? (1 = tak, 0 = nie): ";
            int betMode = safeInput();

            int betLimit = 0;
            if (betMode == 1) {
                cout << "Podaj maksymalna liczbe prob: ";
                betLimit = safeInput();
            }

            while (true) {
                attempts++;
                cout << "\nProba nr " << attempts << ". Podaj liczbe : ";
                guess = safeInput();

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
