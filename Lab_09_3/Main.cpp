#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

struct Note
{
    string surname;
    string name;
    string number;
};

void Create(Note* S, int B[][3], const int N);
void Print(Note* S, int B[][3], const int N);
void sort(Note* S, int B[][3], const int N);
void search(Note* S, int B[][3], const int N, const string f_surname);
void SaveToFile(Note* S, int B[][3], const int N, const char* filename);
void LoadFromFile(Note*& S, int B[][3], int& N, const char* filename);

int main()
{

    int N;
    cout << "Enter the number of users: ";
    cin >> N;

    int(*B)[3] = new int[N][3];
    Note* S = new Note[N];

    string f_surname;
    char filename[100];

    int MenuItem;

    while (true)
    {

        cout << "Choose an action:" << endl;
        cout << "[1] - Enter user information" << endl;
        cout << "[2] - Display user information" << endl;
        cout << "[3] - Sort by dates of birth" << endl;
        cout << "[4] - Search for a person by surname" << endl;
        cout << "[5] - Save data to file" << endl;
        cout << "[6] - Load data from file" << endl;
        cout << "[0] - Exit the program" << endl;
        cout << "Enter: ";
        cin >> MenuItem;
        cout << endl;

        switch (MenuItem)
        {
        case 1:
            Create(S, B, N);
            break;
        case 2:
            Print(S, B, N);
            break;
        case 3:
            sort(S, B, N);
            Print(S, B, N);
            break;
        case 4:
            cout << "Enter search criteria: ";
            cout << "Surname";
            cin.get();
            cin.sync();
            getline(cin, f_surname);
            search(S, B, N, f_surname);
            break;
        case 5:
            cout << "Enter the filename to save data: ";
            cin >> filename;
            SaveToFile(S, B, N, filename);
            break;
        case 6:
            cout << "Enter the filename to load data: ";
            cin >> filename;
            LoadFromFile(S, B, N, filename);
            break;
        }
        if (MenuItem == 0) break;
    }

    delete[] B;
    delete[] S;

    return 0;
}

void Create(Note* S, int B[][3], const int N)
{
    for (int i = 0; i < N; i++)
    {
        cout << "User number: " << i + 1 << endl;
        cin.get();
        cin.sync();
        cout << "Surname: ";
        getline(cin, S[i].surname);
        cout << "Name: ";
        getline(cin, S[i].name);
        cout << "Number: ";
        getline(cin, S[i].number);

        cout << "Enter day of birth: ";
        cin >> B[i][0];
        cout << "Enter month of birth: ";
        cin >> B[i][1];
        cout << "Enter year of birth: ";
        cin >> B[i][2];
        cout << endl;
    }
}

void Print(Note* S, int B[][3], const int N)
{
    cout << "=========================================================================" << endl;
    cout << "|  ¹  |   Surname    |  Name  |  Note  sign  |  Day   | Month  |  Year  |" << endl;
    cout << "-------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "|" << setw(4) << right << i + 1 << " ";
        cout << "|" << setw(14) << left << S[i].surname;
        cout << "|" << setw(8) << left << S[i].name;
        cout << "|" << setw(14) << left << S[i].number;

        for (int j = 0; j < 3; j++)
        {
            cout << "|" << setw(8) << left << B[i][j];
        }

        cout << setw(6) << "|" << endl;
    }
    cout << "=========================================================================" << endl << endl;
}

void sort(Note* S, int B[][3], int N)
{
    Note temp;
    int btemp;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N - i - 1; j++)
        {
            if ((B[j][2] > B[j + 1][2]) ||
                (B[j][2] == B[j + 1][2] && B[j][1] > B[j + 1][1]) ||
                (B[j][2] == B[j + 1][2] && B[j][1] == B[j + 1][1] && B[j][0] > B[j + 1][0]))
            {
                temp = S[j];
                S[j] = S[j + 1];
                S[j + 1] = temp;

                for (int k = 0; k < 3; k++)
                {
                    btemp = B[j][k];
                    B[j][k] = B[j + 1][k];
                    B[j + 1][k] = btemp;
                }
            }
        }
    }
}

void search(Note* S, int B[][3], const int N, const string f_surname)
{
    int flag = 0;
    for (int i = 0; i < N; i++)
    {
        if (S[i].surname == f_surname)
        {
            flag = 1;
            cout << "============================================================================" << endl;
            cout << "|  ¹  |   Surname    |  Name  | Zodiac sign |  Day   |  Month  |   Year   |" << endl;
            cout << "----------------------------------------------------------------------------" << endl;
            cout << "|" << setw(4) << right << i + 1 << " ";
            cout << "|" << setw(14) << left << S[i].surname;
            cout << "|" << setw(8) << left << S[i].name;
            cout << "|" << setw(14) << left << S[i].number;

            for (int j = 0; j < 3; j++)
            {
                cout << "|" << setw(8) << left << B[i][j];
            }

            cout << setw(6) << "|" << endl;
            cout << "============================================================================" << endl << endl;
        }
    }
    if (!flag)
        cout << "User not found" << endl;
}

void SaveToFile(Note* S, int B[][3], const int N, const char* filename)
{
    ofstream fout(filename, ios::binary);
    fout.write((char*)&N, sizeof(N));
    fout.write((char*)S, sizeof(Note) * N);
    fout.write((char*)B, sizeof(int) * 3 * N);
    fout.close();
}

void LoadFromFile(Note*& S, int B[][3], int& N, const char* filename)
{
    delete[] S;
    ifstream fin(filename, ios::binary);
    fin.read((char*)&N, sizeof(N));
    S = new Note[N];
    fin.read((char*)S, sizeof(Note) * N);
    fin.read((char*)B, sizeof(int) * 3 * N);
    fin.close();
}