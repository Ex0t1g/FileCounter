#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 
#include <iostream> 
#include <fstream>
#include <string> 
#include <experimental/filesystem> 
namespace fs = std::experimental::filesystem;
using namespace std;

unsigned long long getDirectorySize(const string& directoryPath) {
    unsigned long long totalSize = 0;

    try {
        for (const auto& entry : fs::directory_iterator(directoryPath)) {
            if (fs::is_regular_file(entry)) {
                ifstream file(entry.path(), ios::binary | ios::ate);
                totalSize += file.tellg();
                file.close();
            }
            else if (fs::is_directory(entry)) {
                totalSize += getDirectorySize(entry.path().string());
            }
        }
    }
    catch (const exception& ex) {
        throw runtime_error(ex.what());
    }

    return totalSize;
}

int main() {
    setlocale(LC_ALL, "ru");
    string directoryPath = ""; // Сюда надов вставить ваш путь даектории
    //Либо можно прописать чтобы пользователь его сам вводил

    // cout << "Введите даекторию которую хотитет подсчитать" << endl
    // cin >> directoryPath

    try {
        if (!fs::is_directory(directoryPath)) {
            cout << "Путь не является директорией" << endl;
            return 0;
        }

        unsigned long long totalSize = getDirectorySize(directoryPath);
        cout << "Объем директории: " << totalSize << " байт" << endl;
    }
    catch (const exception& ex) {
        cout << "Ошибка: " << ex.what() << endl;
    }

    return 0;
}
