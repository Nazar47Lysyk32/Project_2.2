#include <iostream>
#include <string>
#include <vector>

// Базовий клас для файлів і папок
class FileSystemObject {
public:
    FileSystemObject(const std::string& name) : name(name) {}

    // Віртуальна функція для виводу інформації про об'єкт
    virtual void display() const = 0;

    // Віртуальна функція для перейменування об'єкта
    virtual void rename(const std::string& new_name) {
        name = new_name;
    }

    virtual ~FileSystemObject() {}

    std::string getName() const {
        return name;
    }

private:
    std::string name;
};

// Клас для представлення файлів
class File : public FileSystemObject {
public:
    File(const std::string& name, int size) : FileSystemObject(name), size(size) {}

    void display() const override {
        std::cout << "File: " << getName() << ", Size: " << size << " bytes" << std::endl;
    }

    int getSize() const {
        return size;
    }

private:
    int size;
};

// Клас для представлення папок
class Directory : public FileSystemObject {
public:
    Directory(const std::string& name) : FileSystemObject(name) {}

    void display() const override {
        std::cout << "Directory: " << getName() << std::endl;
        for (const FileSystemObject* obj : contents) {
            obj->display(); // Рекурсивний вивід вмісту папки
        }
    }

    // Додавання об'єкта (файлу або папки) до папки
    void add(FileSystemObject* obj) {
        contents.push_back(obj);
    }

    // Видалення об'єкта з папки
    void remove(FileSystemObject* obj) {
        contents.erase(std::remove(contents.begin(), contents.end(), obj), contents.end());
    }

private:
    std::vector<FileSystemObject*> contents; // Вміст папки
};

int main() {
    // Створення кореневої папки
    Directory root("C:");

    // Створення файлів і папок
    File file1("document.txt", 1024);
    File file2("image.jpg", 2048);
    Directory folder1("My Documents");
    Directory folder2("Pictures");

    // Додавання файлів і папок до кореневої папки
    root.add(&file1);
    root.add(&file2);
    root.add(&folder1);
    root.add(&folder2);

    // Додавання файлів до папок
    folder1.add(new File("report.pdf", 512));
    folder2.add(new File("vacation.jpg", 4096));

    // Вивід вмісту кореневої папки
    root.display();

    return 0;
}
