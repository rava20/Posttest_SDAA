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

void tambahTransaksi(Transaksi** head);
void bacaTransaksi(Transaksi* head);
void updateTransaksi(Transaksi* head);
void hapusTransaksi(Transaksi** head);
double totalTransaksi(Transaksi* head);
void bersihkan(Transaksi** head);  

int main() {
    Transaksi* head = nullptr; 
    int pilihan;

    do {
        cout << "\nProgram Pencatatan Pemasukan/Pengeluaran Harian\n";
        cout << "1. Tambah pemasukan/pengeluaran\n";
        cout << "2. Tampilkan Semua pemasukan/pengeluaran\n";
        cout << "3. Update pemasukan/pengeluaran\n";
        cout << "4. Hapus pemasukan/pengeluaran\n";
        cout << "5. Tampilkan Total pemasukan/pengeluaran\n";
        cout << "6. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahTransaksi(&head);
                break;
            case 2:
                bacaTransaksi(head);
                break;
            case 3:
                updateTransaksi(head);
                break;
            case 4:
                hapusTransaksi(&head);
                break;
            case 5: {
                double total = totalTransaksi(head);
                cout << "Total Jumlah Pemasukan/Pengeluaran: " << total << endl;
                break;
            }
            case 6:
                bersihkan(&head);
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 6);

    return 0;
}

void tambahTransaksi(Transaksi** head) {
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

    newTransaksi->next = *head;  
    *head = newTransaksi;        

    cout << newTransaksi->jenis << " berhasil ditambahkan.\n";
}

void bacaTransaksi(Transaksi* head) {
    if (head == nullptr) {
        cout << "Tidak ada transaksi untuk ditampilkan.\n";
    } else {
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
}

void updateTransaksi(Transaksi* head) {
    if (head == nullptr) {
        cout << "Tidak ada transaksi untuk diupdate.\n";
        return;
    }

    int index;
    cout << "Masukkan nomor transaksi yang ingin diupdate: ";
    cin >> index;

    Transaksi* temp = head;
    int i = 1;
    while (temp != nullptr && i < index) {
        temp = temp->next;
        i++;
    }

    if (temp != nullptr) {
        cout << "Masukkan Jenis baru (pemasukan/pengeluaran): ";
        cin >> temp->jenis;
        cout << "Masukkan Tanggal baru (YYYY-MM-DD): ";
        cin >> temp->tanggal;
        cout << "Masukkan Deskripsi baru: ";
        cin.ignore();
        getline(cin, temp->deskripsi);
        cout << "Masukkan Jumlah baru: ";
        cin >> temp->jumlah;

        cout << "Data transaksi berhasil diupdate.\n";
    } else {
        cout << "Transaksi tidak ditemukan.\n";
    }
}

void hapusTransaksi(Transaksi** head) {
    if (*head == nullptr) {
        cout << "Tidak ada transaksi untuk dihapus.\n";
        return;
    }

    int index;
    cout << "Masukkan nomor transaksi yang ingin dihapus: ";
    cin >> index;

    Transaksi* temp = *head;
    if (index == 1) {
        *head = temp->next;  // Head dipindahkan ke transaksi berikutnya
        delete temp;
        cout << "Transaksi berhasil dihapus.\n";
    } else {
        Transaksi* prev = nullptr;
        int i = 1;
        while (temp != nullptr && i < index) {
            prev = temp;
            temp = temp->next;
            i++;
        }

        if (temp != nullptr) {
            prev->next = temp->next;
            delete temp;
            cout << "Transaksi berhasil dihapus.\n";
        } else {
            cout << "Transaksi tidak ditemukan.\n";
        }
    }
}

double totalTransaksi(Transaksi* head) {
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

void bersihkan(Transaksi** head) {
    Transaksi* temp = *head;
    while (temp != nullptr) {
        Transaksi* next = temp->next;
        delete temp;
        temp = next;
    }
    *head = nullptr;
}
