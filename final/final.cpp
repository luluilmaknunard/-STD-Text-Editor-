#include <iostream>
#include "final.h"
using namespace std;

// Variabel global untuk file editor
File* fileHead = nullptr;
File* currentFile = nullptr;

stack<pair<string, string>> undoStack;
stack<pair<string, string>> redoStack;

//menambahkan file
void addFile(string fileName) {
    File* newFile = new File;
    newFile->name = fileName;
    newFile->head = nullptr;
    newFile->tail = nullptr;
    newFile->size = 0;
    newFile->next = nullptr;

    if (!fileHead) {
        fileHead = newFile;
    } else {
        File* temp = fileHead;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newFile;
    }
    currentFile = newFile;
    cout << "File " << fileName << " berhasil ditambahkan dan dipilih.\n";
}

// Menampilkan daftar file
void displayFiles() {
    if (!fileHead) {
        cout << "Tidak ada file yang tersedia.\n";
        return;
    }
    File* temp = fileHead;
    int index = 1;
    while (temp) {
        cout << index++ << ". " << temp->name << (temp == currentFile ? " (aktif)" : "") << endl;
        temp = temp->next;
    }
}

// Memilih file berdasarkan indeks
void selectFile(int index) {
    File* temp = fileHead;
    int count = 1;
    while (temp && count < index) {
        temp = temp->next;
        count++;
    }
    if (temp) {
        currentFile = temp;
        cout << "File " << currentFile->name << " dipilih.\n";
    } else {
        cout << "File dengan indeks " << index << " tidak ditemukan.\n";
    }
}


// Menampilkan seluruh teks dalam file aktif
void displayText() {
    if (!currentFile) {
        cout << "Tidak ada file yang dipilih.\n";
        return;
    }
    Node* current = currentFile->head;
    int line = 1;
    while (current) {
        cout << current->text << endl;
        current = current->next;
    }
    cout << endl;
}

// Menyisipkan teks di posisi tertentu dalam file aktif
void insertText(int position, string text) {
    if (!currentFile) {
        cout << "Tidak ada file yang dipilih.\n";
        return;
    }
    if (position < 1 || position > currentFile->size + 1) {
        cout << "Posisi tidak valid!" << endl;
        return;
    }

    Node* newNode = new Node;
    newNode->text = text;
    newNode->next = nullptr;
    newNode->prev = nullptr;

    if (position == 1) { // Sisipkan di awal
        newNode->next = currentFile->head;
        if (currentFile->head) currentFile->head->prev = newNode;
        currentFile->head = newNode;
        if (!currentFile->tail) currentFile->tail = newNode;
    } else if (position == currentFile->size + 1) { // Sisipkan di akhir
        currentFile->tail->next = newNode;
        newNode->prev = currentFile->tail;
        currentFile->tail = newNode;
    } else { // Sisipkan di tengah
        Node* current = currentFile->head;
        for (int i = 1; i < position - 1; ++i)
            current = current->next;
        newNode->next = current->next;
        newNode->prev = current;
        if (current->next) current->next->prev = newNode;
        current->next = newNode;
    }

    currentFile->size++;
}

// Menghapus baris tertentu dalam file aktif
void deleteText(int position) {
    if (!currentFile) {
        cout << "Tidak ada file yang dipilih.\n";
        return;
    }
    if (position < 1 || position > currentFile->size) {
        cout << "Posisi tidak valid!" << endl;
        return;
    }

    Node* toDelete;
    if (position == 1) { // Hapus di awal
        toDelete = currentFile->head;
        currentFile->head = currentFile->head->next;
        if (currentFile->head) currentFile->head->prev = nullptr;
        else currentFile->tail = nullptr;
    } else if (position == currentFile->size) { // Hapus di akhir
        toDelete = currentFile->tail;
        currentFile->tail = currentFile->tail->prev;
        if (currentFile->tail) currentFile->tail->next = nullptr;
        else currentFile->head = nullptr;
    } else { // Hapus di tengah
        toDelete = currentFile->head;
        for (int i = 1; i < position; ++i)
            toDelete = toDelete->next;
        toDelete->prev->next = toDelete->next;
        toDelete->next->prev = toDelete->prev;
    }

    delete toDelete;
    currentFile->size--;
}


// Fungsi undo
void undoOperation(stack<pair<string, pair<int, string>>>& undoStack, stack<pair<string, pair<int, string>>>& redoStack, string& message) {
    if (undoStack.empty()) {
        message = "Tidak ada operasi yang bisa di-undo!";
        return;
    }

    pair<string, pair<int, string>> operation = undoStack.top();
    undoStack.pop();

    if (operation.first == "insert") {
        int position = operation.second.first;
        deleteText(position);
        redoStack.push(operation);
    } else if (operation.first == "delete") {
        int position = operation.second.first;
        string text = operation.second.second;
        insertText(position, text);
        redoStack.push(operation);
    }

    message = "Undo berhasil.";
}

// Fungsi redo
void redoOperation(stack<pair<string, pair<int, string>>>& undoStack, stack<pair<string, pair<int, string>>>& redoStack, string& message) {
    if (redoStack.empty()) {
        message = "Tidak ada operasi yang bisa di-redo!";
        return;
    }

    pair<string, pair<int, string>> operation = redoStack.top();
    redoStack.pop();

    if (operation.first == "insert") {
        int position = operation.second.first;
        string text = operation.second.second;
        insertText(position, text);
        undoStack.push(operation);
    } else if (operation.first == "delete") {
        int position = operation.second.first;
        deleteText(position);
        undoStack.push(operation);
    }

    message = "Redo berhasil.";
}
