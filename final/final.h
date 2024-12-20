#ifndef FINAL_H_INCLUDED
#define FINAL_H_INCLUDED

#ifndef GILA_H_INCLUDED
#define GILA_H_INCLUDED
#include <iostream>
#include <stack>
#include <string>
using namespace std;

// Struktur Node untuk menyimpan setiap baris teks
struct Node {
    string text;  // Menyimpan teks
    Node* next;   // Pointer ke node berikutnya
    Node* prev;   // Pointer ke node sebelumnya
};

// Struktur File untuk menyimpan beberapa file
struct File {
    string name;  // Nama file
    Node* head;   // Pointer ke node pertama dalam file
    Node* tail;   // Pointer ke node terakhir dalam file
    int size;     // Jumlah baris teks
    File* next;   // Pointer ke file berikutnya
    bool isActive;
};

// Variabel global untuk file editor
extern File* fileHead;
extern File* currentFile;

void addFile(string fileName);
void displayFiles();
void selectFile(int index);
void displayText();
void insertText(int position, string text);
void deleteText(int position);
void undoOperation(stack<pair<string, pair<int, string>>>& undoStack, stack<pair<string, pair<int, string>>>& redoStack, string& message);
void redoOperation(stack<pair<string, pair<int, string>>>& undoStack, stack<pair<string, pair<int, string>>>& redoStack, string& message);



#endif // GILA_H_INCLUDED


#endif // FINAL_H_INCLUDED
