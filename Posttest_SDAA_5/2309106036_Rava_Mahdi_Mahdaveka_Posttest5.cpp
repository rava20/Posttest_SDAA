#include <iostream>
#include <string>
#include <unistd.h>  
#include <sstream>

using namespace std;

struct Transaksi {
    string jenis;
    string tanggal;  
    string deskripsi;
    double jumlah;
    Transaksi* next;
};

int compareDate(const string& date1, const string& date2) {
    int d1, m1, y1;
    int d2, m2, y2;

    
    sscanf(date1.c_str(), "%d-%d-%d", &d1, &m1, &y1);
    sscanf(date2.c_str(), "%d-%d-%d", &d2, &m2, &y2);

    if (y1 != y2) return y1 - y2; 
    if (m1 != m2) return m1 - m2; 
    return d1 - d2;              
}

class Stack {
public:
    Stack() : head(nullptr) {}

    void push();
    void pop();
    void display();
    double total();
    void clear();

private:
    Transaksi* head;
    Transaksi* mergeSort(Transaksi* head);
    Transaksi* sortedMerge(Transaksi* a, Transaksi* b);
};

class Queue {
public:
    Queue() : head(nullptr), tail(nullptr) {}

    void enqueue();
    void dequeue();
    void display();
    double total();
    void clear();

private:
    Transaksi* head;
    Transaksi* tail;
    Transaksi* mergeSort(Transaksi* head);
    Transaksi* sortedMerge(Transaksi* a, Transaksi* b);
};

void Stack::push() {
    Transaksi* newTransaksi = new Transaksi;

    cout << "Masukkan Jenis (pemasukan/pengeluaran): ";
    cin >> newTransaksi->jenis;
    cout << "Masukkan Tanggal (DD-MM-YYYY): ";
    cin >> newTransaksi->tanggal;
    cout << "Masukkan Deskripsi: ";
    cin.ignore();
    getline(cin, newTransaksi->deskripsi);
    cout << "Masukkan Jumlah: ";
    cin >> newTransaksi->jumlah;

    newTransaksi->next = head;  
    head = newTransaksi;        

    cout << newTransaksi->jenis << " berhasil ditambahkan (Stack).\n";
    sleep(3);  
}

void Stack::pop() {
    if (head == nullptr) {
        cout << "Stack kosong.\n";
        return;
    }
    Transaksi* temp = head;
    head = head->next;
    delete temp;
    cout << "Transaksi berhasil dihapus (Stack).\n";
    sleep(3);  
}

void Stack::display() {
    if (head == nullptr) {
        cout << "Stack kosong.\n";
        return;
    }
    head = mergeSort(head); 
    Transaksi* temp = head;
    int i = 1;
    while (temp != nullptr) {
        cout << temp->jenis << " ke-" << i << ":\n";
        cout << "Tanggal: " << temp->tanggal << "\n"
             << "Deskripsi: " << temp->deskripsi << "\n"
             << "Jumlah: " << temp->jumlah << "\n\n";
        cout << "+--------------------------------------------------+" << endl; 
        temp = temp->next;
        i++;
    }
    sleep(3);  
}

Transaksi* Stack::mergeSort(Transaksi* head) {
    if (!head || !head->next) return head; 

    Transaksi* middle = head;
    Transaksi* fast = head->next;
    while (fast && fast->next) {
        middle = middle->next;
        fast = fast->next->next;
    }
    Transaksi* left = head;
    Transaksi* right = middle->next;
    middle->next = nullptr;

    return sortedMerge(mergeSort(left), mergeSort(right));
}

Transaksi* Stack::sortedMerge(Transaksi* a, Transaksi* b) {
    if (!a) return b;
    if (!b) return a;

    if (compareDate(a->tanggal, b->tanggal) <= 0) {
        a->next = sortedMerge(a->next, b);
        return a;
    } else {
        b->next = sortedMerge(a, b->next);
        return b;
    }
}

double Stack::total() {
    double total = 0;
    Transaksi* temp = head;
    while (temp != nullptr) {
        if (temp->jenis == "pemasukan") {
            total += temp->jumlah;
        } else if (temp->jenis == "pengeluaran") {
            total -= temp->jumlah;
        }
        temp = temp->next;
    }
    sleep(3);  
    return total;
}

void Stack::clear() {
    while (head != nullptr) {
        Transaksi* temp = head;
        head = head->next;
        delete temp;
    }
    sleep(3);  
}

void Queue::enqueue() {
    Transaksi* newTransaksi = new Transaksi;

    cout << "Masukkan Jenis (pemasukan/pengeluaran): ";
    cin >> newTransaksi->jenis;
    cout << "Masukkan Tanggal (DD-MM-YYYY): ";
    cin >> newTransaksi->tanggal;
    cout << "Masukkan Deskripsi: ";
    cin.ignore();
    getline(cin, newTransaksi->deskripsi);
    cout << "Masukkan Jumlah: ";
    cin >> newTransaksi->jumlah;

    newTransaksi->next = nullptr;

    if (tail == nullptr) {
        head = tail = newTransaksi;
    } else {
        tail->next = newTransaksi;
        tail = newTransaksi;
    }

    cout << newTransaksi->jenis << " berhasil ditambahkan (Queue).\n";
    sleep(3);  
}

void Queue::dequeue() {
    if (head == nullptr) {
        cout << "Queue kosong.\n";
        return;
    }
    Transaksi* temp = head;
    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    }
    delete temp;
    cout << "Transaksi berhasil dihapus (Queue).\n";
    sleep(3);  
}

void Queue::display() {
    if (head == nullptr) {
        cout << "Queue kosong.\n";
        return;
    }
    head = mergeSort(head); 
    Transaksi* temp = head;
    int i = 1;
    while (temp != nullptr) {
        cout << temp->jenis << " ke-" << i << ":\n";
        cout << "Tanggal: " << temp->tanggal << "\n"
             << "Deskripsi: " << temp->deskripsi << "\n"
             << "Jumlah: " << temp->jumlah << "\n\n";
        cout << "+--------------------------------------------------+" << endl; 
        temp = temp->next;
        i++;
    }
    sleep(3);  
}

Transaksi* Queue::mergeSort(Transaksi* head) {
    if (!head || !head->next) return head;

    Transaksi* middle = head;
    Transaksi* fast = head->next;
    while (fast && fast->next) {
        middle = middle->next;
        fast = fast->next->next;
    }
    Transaksi* left = head;
    Transaksi* right = middle->next;
    middle->next = nullptr;

    return sortedMerge(mergeSort(left), mergeSort(right));
}

Transaksi* Queue::sortedMerge(Transaksi* a, Transaksi* b) {
    if (!a) return b;
    if (!b) return a;

    if (compareDate(a->tanggal, b->tanggal) >= 0) {
        a->next = sortedMerge(a->next, b);
        return a;
    } else {
        b->next = sortedMerge(a, b->next);
        return b;
    }
}

double Queue::total() {
    double total = 0;
    Transaksi* temp = head;
    while (temp != nullptr) {
        if (temp->jenis == "pemasukan") {
            total += temp->jumlah;
        } else if (temp->jenis == "pengeluaran") {
            total -= temp->jumlah;
        }
        temp = temp->next;
    }
    sleep(3);  
    return total;
}

void Queue::clear() {
    while (head != nullptr) {
        Transaksi* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    sleep(3);  
}

int main() {
    Stack stack;
    Queue queue;
    int mode;

    do {
        cout << "Pilih Mode (1: Stack, 2: Queue): ";
        cin >> mode;

        int pilihan;
        do {
            cout << "+--------------------------------------------------+" << endl;
            cout << "|  Program Pencatatan Pemasukan/Pengeluaran Harian |" << endl;
            cout << "+--------------------------------------------------+" << endl; 
            cout << "|1. Tambah pemasukan/pengeluaran                   |" << endl;
            cout << "|2. Tampilkan Semua pemasukan/pengeluaran          |" << endl;
            cout << "|3. Hapus pemasukan/pengeluaran                    |" << endl;
            cout << "|4. Tampilkan Total pemasukan/pengeluaran          |" << endl;
            cout << "|5. Keluar                                         |" << endl;
            cout << "+--------------------------------------------------+" << endl;  
            cout << "Pilih: ";
            cin >> pilihan;

            switch (pilihan) {
                case 1:
                    if (mode == 1) stack.push();
                    else queue.enqueue();
                    break;
                case 2:
                    if (mode == 1) stack.display();
                    else queue.display();
                    break;
                case 3:
                    if (mode == 1) stack.pop();
                    else queue.dequeue();
                    break;
                case 4:
                    if (mode == 1) {
                        cout << "Total: " << stack.total() << endl;
                    } else {
                        cout << "Total: " << queue.total() << endl;
                    }
                    sleep(3);  
                    break;
                case 5:
                    cout << "Keluar dari program." << endl;
                    break;
                default:
                    cout << "Pilihan tidak valid." << endl;
                    sleep(3);  
                    break;
            }
        } while (pilihan != 5);  

    } while (true);  

    return 0;
}