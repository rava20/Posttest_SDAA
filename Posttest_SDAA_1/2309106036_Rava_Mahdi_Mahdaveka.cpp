#include <iostream>

int pascal(int baris, int kolom) {
    if (kolom == 0 || kolom == baris) {
        return 1;
    } else {
        return pascal(baris - 1, kolom - 1) + pascal(baris - 1, kolom);
    }
}

void SegitigaPascal(int n) {
    for (int baris = 0; baris < n; baris++) {
        for (int kolom = 0; kolom <= baris; kolom++) {
        std ::  cout << pascal(baris, kolom) << " ";
        }
        std ::  cout << std :: endl;
    }
}

int main() {
    int n = 3; 
    SegitigaPascal(n);
    return 0;
}  
