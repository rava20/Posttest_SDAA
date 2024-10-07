#include <iostream>
#include <string>

using namespace std;

struct Transaksi {
    string jenis;
    string tanggal;
    string deskripsi;
    double jumlah;
    Transaksi* next;
};

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
};

void Stack::push() {
    Transaksi* newTransaksi = new Transaksi;

    cout << "Masukkan Jenis (pemasukan/pengeluaran): ";
    cin >> newTransaksi->jenis;
    cout << "Masukkan Tanggal: ";
    cin >> newTransaksi->tanggal;
    cout << "Masukkan Deskripsi: ";
    cin.ignore();
    getline(cin, newTransaksi->deskripsi);
    cout << "Masukkan Jumlah: ";
    cin >> newTransaksi->jumlah;

    newTransaksi->next = head;  
    head = newTransaksi;        

    cout << newTransaksi->jenis << " berhasil ditambahkan (Stack).\n";
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
}

void Stack::display() {
    if (head == nullptr) {
        cout << "Stack kosong.\n";
        return;
    }
    Transaksi* temp = head;
    int i = 1;
    while (temp != nullptr) {
        cout << temp->jenis << " ke-" << i << ":\n";
        cout << "Tanggal: " << temp->tanggal << "\n"
             << "Deskripsi: " << temp->deskripsi << "\n"
             << "Jumlah: " << temp->jumlah << "\n\n";
        temp = temp->next;
        i++;
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
    return total;
}

void Stack::clear() {
    while (head != nullptr) {
        Transaksi* temp = head;
        head = head->next;
        delete temp;
    }
}

void Queue::enqueue() {
    Transaksi* newTransaksi = new Transaksi;

    cout << "Masukkan Jenis (pemasukan/pengeluaran): ";
    cin >> newTransaksi->jenis;
    cout << "Masukkan Tanggal: ";
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
}

void Queue::display() {
    if (head == nullptr) {
        cout << "Queue kosong.\n";
        return;
    }
    Transaksi* temp = head;
    int i = 1;
    while (temp != nullptr) {
        cout << temp->jenis << " ke-" << i << ":\n";
        cout << "Tanggal: " << temp->tanggal << "\n"
             << "Deskripsi: " << temp->deskripsi << "\n"
             << "Jumlah: " << temp->jumlah << "\n\n";
        temp = temp->next;
        i++;
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
    return total;
}

// Fungsi untuk membersihkan Queue
void Queue::clear() {
    while (head != nullptr) {
        Transaksi* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}

int main() {
    Stack stack;
    Queue queue;
    int pilihan, mode;

    cout << "Pilih Mode (1: Stack, 2: Queue): ";
    cin >> mode;

    do {
        cout << "\nProgram Pencatatan Pemasukan/Pengeluaran Harian\n";
        cout << "1. Tambah pemasukan/pengeluaran\n";
        cout << "2. Tampilkan Semua pemasukan/pengeluaran\n";
        cout << "3. Hapus pemasukan/pengeluaran\n";
        cout << "4. Tampilkan Total pemasukan/pengeluaran\n";
        cout << "5. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        if (mode == 1) {
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
                case 4: {
                    double total = stack.total();
                    cout << "Total Jumlah Pemasukan/Pengeluaran (Stack): " << total << endl;
                    break;
                }
                case 5:
                    stack.clear();
                    cout << "Keluar dari program.\n";
                    break;
                default:
                    cout << "Pilihan tidak valid.\n";
            }
        } else if (mode == 2) {
            switch (pilihan) {
                case 1:
                    queue.enqueue();
                    break;
                case 2:
                    queue.display();
                    break;
                case 3:
                    queue.dequeue();
                    break;
                case 4: {
                    double total = queue.total();
                    cout << "Total Jumlah Pemasukan/Pengeluaran (Queue): " << total << endl;
                    break;
                }
                case 5:
                    queue.clear();
                    cout << "Keluar dari program.\n";
                    break;
                default:
                    cout << "Pilihan tidak valid.\n";
            }
        }
    } while (pilihan != 5);

    return 0;
}
