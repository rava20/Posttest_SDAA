#include <iostream>
#include <string>
#include <unistd.h>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>  

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
    Stack() : head(NULL) {}

    void push();
    void pop();
    void display();
    double total();
    void clear();
    void searchTransaksi();

private:
    Transaksi* head;
    Transaksi* mergeSort(Transaksi* head);
    Transaksi* sortedMerge(Transaksi* a, Transaksi* b);
    vector<double> collectAmounts();
    vector<string> collectDescriptions();
    int fibonacciSearch(vector<double>& arr, double x);
    int jumpSearch(vector<double>& arr, double x);
    int boyerMooreSearch(const string& text, const string& pattern);
};

class Queue {
public:
    Queue() : head(NULL), tail(NULL) {}

    void enqueue();
    void dequeue();
    void display();
    double total();
    void clear();
    void searchTransaksi();

private:
    Transaksi* head;
    Transaksi* tail;
    Transaksi* mergeSort(Transaksi* head);
    Transaksi* sortedMerge(Transaksi* a, Transaksi* b);
    vector<double> collectAmounts();
    vector<string> collectDescriptions();
    int fibonacciSearch(vector<double>& arr, double x);
    int jumpSearch(vector<double>& arr, double x);
    int boyerMooreSearch(const string& text, const string& pattern);
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
    sleep(1);
}

void Stack::pop() {
    if (head == NULL) {
        cout << "Stack kosong.\n";
        return;
    }
    Transaksi* temp = head;
    head = head->next;
    delete temp;
    cout << "Transaksi berhasil dihapus (Stack).\n";
    sleep(1);
}

void Stack::display() {
    if (head == NULL) {
        cout << "Stack kosong.\n";
        return;
    }
    head = mergeSort(head);
    Transaksi* temp = head;
    int i = 1;
    while (temp != NULL) {
        cout << temp->jenis << " ke-" << i << ":\n";
        cout << "Tanggal: " << temp->tanggal << "\n"
             << "Deskripsi: " << temp->deskripsi << "\n"
             << "Jumlah: " << temp->jumlah << "\n\n";
        cout << "+--------------------------------------------------+" << endl;
        temp = temp->next;
        i++;
    }
    sleep(1);
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
    middle->next = NULL;

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
    while (temp != NULL) {
        if (temp->jenis == "pemasukan") {
            total += temp->jumlah;
        } else if (temp->jenis == "pengeluaran") {
            total -= temp->jumlah;
        }
        temp = temp->next;
    }
    sleep(1);
    return total;
}

void Stack::clear() {
    while (head != NULL) {
        Transaksi* temp = head;
        head = head->next;
        delete temp;
    }
    sleep(1);
}


vector<double> Stack::collectAmounts() {
    vector<double> amounts;
    Transaksi* temp = head;
    while (temp != NULL) {
        amounts.push_back(temp->jumlah);
        temp = temp->next;
    }
    return amounts;
}

vector<string> Stack::collectDescriptions() {
    vector<string> descriptions;
    Transaksi* temp = head;
    while (temp != NULL) {
        descriptions.push_back(temp->deskripsi);
        temp = temp->next;
    }
    return descriptions;
}

int Stack::fibonacciSearch(vector<double>& arr, double x) {
    int n = arr.size();
    int fibMMm2 = 0;
    int fibMMm1 = 1;
    int fibM = fibMMm2 + fibMMm1;

    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;

    while (fibM > 1) {
        int i = min(offset + fibMMm2, n - 1);

        if (arr[i] < x) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }
        else if (arr[i] > x) {
            fibM = fibMMm2;
            fibMMm1 -= fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }
        else return i;
    }

    if (fibMMm1 && arr[offset + 1] == x)
        return offset + 1;

    return -1;
}

int Stack::jumpSearch(vector<double>& arr, double x) {
    int n = arr.size();
    int step = sqrt(n);
    int prev = 0;

    while (arr[min(step, n) - 1] < x) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) return -1;
    }

    while (arr[prev] < x) {
        prev++;
        if (prev == min(step, n)) return -1;
    }

    if (arr[prev] == x) return prev;

    return -1;
}

int Stack::boyerMooreSearch(const string& text, const string& pattern) {
    int m = pattern.size();
    int n = text.size();
    int badChar[256]; 

    fill(badChar, badChar + 256, -1);

    for (int i = 0; i < m; i++) {
        badChar[(int)pattern[i]] = i;
    }

    int s = 0;
    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }

        if (j < 0) {
            return s; 
        } else {
            s += max(1, j - badChar[(int)text[s + j]]);
        }
    }
    return -1;
}

void Stack::searchTransaksi() {
    vector<double> amounts = collectAmounts();
    vector<string> descriptions = collectDescriptions();

    int searchOption;
    cout << "Pilih metode pencarian (1: Fibonacci Search, 2: Jump Search, 3: Boyer-Moore Search): ";
    cin >> searchOption;

    if (searchOption == 1 || searchOption == 2) {
        double amount;
        cout << "Masukkan jumlah yang ingin dicari: ";
        cin >> amount;
        int index;
        if (searchOption == 1) {
            index = fibonacciSearch(amounts, amount);
        } else {
            index = jumpSearch(amounts, amount);
        }

        if (index != -1) {
            cout << "Jumlah ditemukan pada transaksi ke-" << index + 1 << endl;
        } else {
            cout << "Jumlah tidak ditemukan." << endl;
        }

    } else if (searchOption == 3) {
        string keyword;
        cout << "Masukkan deskripsi yang ingin dicari: ";
        cin.ignore();
        getline(cin, keyword);
        for (int i = 0; i < descriptions.size(); i++) {
            if (boyerMooreSearch(descriptions[i], keyword) != -1) {
                cout << "Deskripsi ditemukan pada transaksi ke-" << i + 1 << ": " << descriptions[i] << endl;
            }
        }
    }
}

int main() {
    Stack stack;
    int mode;

    do {
        cout << "Pilih Mode (1: Stack): ";
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
            cout << "|5. Cari Transaksi                                 |" << endl;
            cout << "|6. Keluar                                         |" << endl;
            cout << "+--------------------------------------------------+" << endl;
            cout << "Pilih: ";
            cin >> pilihan;

            switch (pilihan) {
                case 1:
                    stack.push();
                    break;
                case 2:
                    stack.display();
                    break;
                case 3:
                    stack.pop();
                    break;
                case 4:
                    cout << "Total: " << stack.total() << endl;
                    sleep(1);
                    break;
                case 5:
                    stack.searchTransaksi();
                    break;
                case 6:
                    cout << "Keluar dari program." << endl;
                    break;
                default:
                    cout << "Pilihan tidak valid." << endl;
                    sleep(1);
                    break;
            }
        } while (pilihan != 6);

    } while (true);

    return 0;
}
