#include <iostream>
#include <string>

using namespace std;

struct Transaksi {
    string jenis;       
    string tanggal;
    string deskripsi;
    double jumlah;
};

void tambahTransaksi(Transaksi *transaksi, int *jumlahData);
void bacaTransaksi(Transaksi *transaksi, int jumlahData);
void updateTransaksi(Transaksi *transaksi, int jumlahData);
void hapusTransaksi(Transaksi *transaksi, int *jumlahData);
double totalTransaksi(Transaksi *transaksi, int jumlahData); 

const int maksimal_transaksi = 100;

int main() {
    Transaksi transaksi[maksimal_transaksi];  
    int jumlahData = 0;               
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
                tambahTransaksi(transaksi, &jumlahData); 
                break;
            case 2:
                bacaTransaksi(transaksi, jumlahData);   
                break;
            case 3:
                updateTransaksi(transaksi, jumlahData); 
                break;
            case 4:
                hapusTransaksi(transaksi, &jumlahData);  
                break;
            case 5: {
                double total = totalTransaksi(transaksi, jumlahData); 
                cout << "Total Jumlah Pemasukan/Pengeluaran: " << total << endl;
                break;
            }
            case 6:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 6);

    return 0;
}

void tambahTransaksi(Transaksi *transaksi, int *jumlahData) {
    if (*jumlahData < maksimal_transaksi) {
        Transaksi *t = &transaksi[*jumlahData];

        cout << "Masukkan Jenis (pemasukan/pengeluaran): ";
        cin >> t->jenis;
        cout << "Masukkan Tanggal : ";
        cin >> t->tanggal;
        cout << "Masukkan Deskripsi: ";
        cin.ignore();
        getline(cin, t->deskripsi);
        cout << "Masukkan Jumlah: ";
        cin >> t->jumlah;

        (*jumlahData)++;
        cout << t->jenis << " berhasil ditambahkan.\n";
    } else {
        cout << "Data penuh, tidak bisa menambah lebih banyak Data\n";
    }
}

void bacaTransaksi(Transaksi *transaksi, int jumlahData) {
    if (jumlahData == 0) {
        cout << "Tidak ada transaksi untuk ditampilkan.\n";
    } else {
        for (int i = 0; i < jumlahData; i++) {
            Transaksi *t = &transaksi[i];
            cout << t->jenis << " ke-" << i + 1 << ":\n";
            cout << "Tanggal: " << t->tanggal << "\n"
                 << "Deskripsi: " << t->deskripsi << "\n"
                 << "Jumlah: " << t->jumlah << "\n\n";
        }
    }
}

void updateTransaksi(Transaksi *transaksi, int jumlahData) {
    int index;

    cout << "Masukkan nomor transaksi yang ingin diupdate (1 hingga " << jumlahData << "): ";
    cin >> index;

    if (index > 0 && index <= jumlahData) {
        Transaksi *t = &transaksi[index - 1];

        cout << "Masukkan Jenis baru (Pemasukan/Pengeluaran): ";
        cin >> t->jenis;
        cout << "Masukkan Tanggal baru (YYYY-MM-DD): ";
        cin >> t->tanggal;
        cout << "Masukkan Deskripsi baru: ";
        cin.ignore();
        getline(cin, t->deskripsi);
        cout << "Masukkan Jumlah baru: ";
        cin >> t->jumlah;

        cout << t->jenis << " Data berhasil diupdate.\n";
    } else {
        cout << "input tidak valid.\n";
    }
}

void hapusTransaksi(Transaksi *transaksi, int *jumlahData) {
    int index;

    cout << "Masukkan nomor transaksi yang ingin dihapus (1 hingga " << *jumlahData << "): ";
    cin >> index;

    if (index > 0 && index <= *jumlahData) {
        for (int i = index - 1; i < *jumlahData - 1; i++) {
            transaksi[i] = transaksi[i + 1];
        }

        (*jumlahData)--;
        cout << "Data berhasil dihapus.\n";
    } else {
        cout << "input tidak valid.\n";
    }
}

// Fungsi untuk menghitung total transaksi
double totalTransaksi(Transaksi *transaksi, int jumlahData) {
    double total = 0;
    for (int i = 0; i < jumlahData; i++) {
        if (transaksi[i].jenis == "pemasukan") {
            total += transaksi[i].jumlah; 
        } else if (transaksi[i].jenis == "pengeluaran") {
            total -= transaksi[i].jumlah; 
        }
    }
    return total;
}
