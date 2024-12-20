#include "final.h"

int main() {
    int choice, position;
    string text, fileName;
    string message;

    stack<pair<string, pair<int, string>>> undoStack, redoStack;

    do {
        cout << "\nMenu Text Editor:\n";
        cout << "1. Tambahkan file baru\n";
        cout << "2. Pilih file\n";
        cout << "3. Tampilkan daftar file\n";
        cout << "4. Tampilkan teks\n";
        cout << "5. Sisipkan teks\n";
        cout << "6. Hapus baris\n";
        cout << "7. Undo\n";
        cout << "8. Redo\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Masukkan nama file: ";
                cin >> fileName;
                addFile(fileName);
                break;
            case 2:
                cout << "Masukkan indeks file yang ingin dipilih: ";
                cin >> position;
                selectFile(position);
                break;
            case 3:
                displayFiles();
                break;
            case 4:
                displayText();
                break;

            case 5:
                cout << "Masukkan posisi: ";
                cin >> position;
                cin.ignore();
                cout << "Masukkan teks: ";
                getline(cin, text);
                insertText(position, text);
                undoStack.push({"insert", {position, text}});
                while (!redoStack.empty()) redoStack.pop();
                break;
            case 6:
                cout << "Masukkan posisi baris yang ingin dihapus: ";
                cin >> position;
                if (position >= 1 && position <= currentFile->size) {
                    Node* temp = currentFile->head;
                    for (int i = 1; i < position; ++i) temp = temp->next;
                    undoStack.push({"delete", {position, temp->text}});
                    deleteText(position);
                    while (!redoStack.empty()) redoStack.pop();
                }
                break;
            case 7:
                undoOperation(undoStack, redoStack, message);
                cout << message << endl;
                break;
            case 8:
                redoOperation(undoStack, redoStack, message);
                cout << message << endl;
                break;
            case 0:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (choice != 0);

    return 0;
}
