#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Company {
public:
    string name;
    string owner;
    string phone;
    string address;
    string activity;

    void saveToFile(ofstream& file) {
        file << name << endl;
        file << owner << endl;
        file << phone << endl;
        file << address << endl;
        file << activity << endl;
    }
};

class Directory {
private:
    vector<Company> companies;
    const string filename = "directory.txt";

public:
    void add(Company company) {
        companies.push_back(company);

        ofstream file(filename, ios::app);
        if (file.is_open()) {
            company.saveToFile(file);
            file.close();
        } else {
            cout << "Ошибка открытия файла." << endl;
        }
    }

    void searchByName(string name) {
        bool found = false;

        for (Company& company : companies) {
            if (company.name == name) {
                printCompany(company);
                found = true;
            }
        }

        if (!found) {
            cout << "Фирма с названием " << name << " не найдена." << endl;
        }
    }

    void searchByOwner(string owner) {
        bool found = false;

        for (Company& company : companies) {
            if (company.owner == owner) {
                printCompany(company);
                found = true;
            }
        }

        if (!found) {
            cout << "Фирма с владельцем " << owner << " не найдена." << endl;
        }
    }

    void searchByPhone(string phone) {
        bool found = false;

        for (Company& company : companies) {
            if (company.phone == phone) {
                printCompany(company);
                found = true;
            }
        }

        if (!found) {
            cout << "Фирма с номером телефона " << phone << " не найдена." << endl;
        }
    }

    void searchByActivity(string activity) {
        bool found = false;

        for (Company& company : companies) {
            if (company.activity == activity) {
                printCompany(company);
                found = true;
            }
        }

        if (!found) {
            cout << "Фирма с родом деятельности " << activity << " не найдена." << endl;
        }
    }

    void showAll() {
        if (companies.empty()) {
            cout << "Справочник пуст." << endl;
        } else {
            for (Company& company : companies) {
                printCompany(company);
            }
        }
    }

    void loadFromFile() {
        ifstream file(filename);
        if (file.is_open()) {
            Company company;
            string line;

            while (getline(file, line)) {
                company.name = line;
                getline(file, line);
                company.owner = line;
                getline(file, line);
                company.phone = line;
                getline(file, line);
                company.address = line;
                getline(file, line);
                company.activity = line;

                companies.push_back(company);
            }

            file.close();
        } else {
            cout << "Ошибка открытия файла." << endl;
        }
    }

private:
    void printCompany(Company& company) {
        cout << "Название фирмы: " << company.name << endl;
        cout << "Владелец: " << company.owner << endl;
        cout << "Телефон: " << company.phone << endl;
        cout << "Адрес: " << company.address << endl;
        cout << "Род деятельности: " << company.activity << endl;
        cout << "---------------------" << endl;

    }
};

int main() {
    Directory directory;
    directory.loadFromFile();

    int choice;
    string input;

    while (true) {
        cout << "Выберите действие:" << endl;
        cout << "1. Добавить запись" << endl;
        cout << "2. Поиск по названию" << endl;
        cout << "3. Поиск по владельцу" << endl;
        cout << "4. Поиск по номеру телефона" << endl;
        cout << "5. Поиск по роду деятельности" << endl;
        cout << "6. Показать все записи" << endl;
        cout << "0. Выход" << endl;

        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                Company company;
                cout << "Название фирмы: ";
                getline(cin, company.name);
                cout << "Владелец: ";
                getline(cin, company.owner);
                cout << "Телефон: ";
                getline(cin, company.phone);
                cout << "Адрес: ";
                getline(cin, company.address);
                cout << "Род деятельности: ";
                getline(cin, company.activity);

                directory.add(company);
                break;
            case 2:
                cout << "Введите название фирмы для поиска: ";
                getline(cin, input);
                directory.searchByName(input);
                break;
            case 3:
                cout << "Введите владельца для поиска: ";
                getline(cin, input);
                directory.searchByOwner(input);
                break;
            case 4:
                cout << "Введите номер телефона для поиска: ";
                getline(cin, input);
                directory.searchByPhone(input);
                break;
            case 5:
                cout << "Введите род деятельности для поиска: ";
                getline(cin, input);
                directory.searchByActivity(input);
                break;
            case 6:
                directory.showAll();
                break;
            case 0:
                return 0;
            default:
                cout << "Неверный выбор. Попробуйте снова." << endl;
                break;
        }
    }
}
