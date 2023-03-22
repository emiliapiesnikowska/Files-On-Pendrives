#include <iostream>

using namespace std;
struct File {
    int id;
    int r;
};
struct Pendrive {
    File* files = nullptr;
    int size;
    int usedsize = 0;
    int filecount = 0;
};

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int* a, int l, int r, int* b) {
    int pivot = a[l];
    int l_m = l - 1;
    int r_m = r + 1;

    while (true) {
        while (true) {
            l_m = l_m + 1;
            if (a[l_m] >= pivot) {
                break;
            }
        }
        while (true) {
            r_m = r_m - 1;
            if (a[r_m] <= pivot) {
                break;
            }

        }
        if (l_m < r_m) {

            swap(&a[l_m], &a[r_m]);
            if (b != NULL) swap(&b[l_m], &b[r_m]);
        }
        else
            return r_m;
    }
}

void quicksort(int* A, int first, int last, int* b) {

    if (first < last) {
        int q = partition(A, first, last, b);
        quicksort(A, first, q, b);
        quicksort(A, q + 1, last, b);
    }

}

int countfiles(int n, File* plik, int p, int& r1, int& r2) {
    int pendrive1 = 0, pendrive2 = 0;
    int pliki = 0;
    for (int i = 0; i < n; i++) {
        if (pendrive1 + plik[i].r <= p) {
            pendrive1 += plik[i].r;
            pliki++;
            r1++;
        }
        else if (pendrive2 + plik[i].r <= p) {
            pendrive2 += plik[i].r;
            pliki++;
            r2++;
        }
    }
    return pliki;
}
void fillfiles(int r[], int id[], int n, File* plik) {
    int maxr = r[0];

    for (int i = 0; i < n; i++) {
        if (r[i] > maxr)maxr = r[i];
    }

    for (int j = 0; j < n; j++) {
        plik[j].r = r[j];
        plik[j].id = id[j];
    }

}

void fillpendrives(int n, Pendrive p1, Pendrive p2, File* plik) {
    int filenum = 0;
    int z = 0;
    while (true) {
        if (filenum < n) {
            p1.files[z] = plik[filenum];
            p1.usedsize += plik[filenum].r;
            filenum++; z++;
            if (filenum == p1.filecount)break;
        }
    }
    z = 0;
    while (true) {
        if (filenum < n) {

            p2.files[z] = plik[filenum];
            filenum++; z++;
            if (filenum == p2.filecount + 1)break;
            p2.usedsize += plik[filenum].r;
            if (p2.usedsize >= p2.size)break;
        }
        else break;
    }
}
void writeout(Pendrive p1, Pendrive p2, int r[]) {

    int* pendrive1 = new int[p1.filecount];
    int* pendrive2 = new int[p2.filecount];
    for (int i = 0; i < p1.filecount; i++) {
        pendrive1[i] = p1.files[i].id;
    }
    for (int i = 0; i < p2.filecount; i++) {
        pendrive2[i] = p2.files[i].id;
    }

    quicksort(pendrive1, 0, p1.filecount - 1, r);
    quicksort(pendrive2, 0, p2.filecount - 1, r);


    printf("1: ");
    for (int i = p1.filecount - 1; i >= 0; i--) {
        printf("%d ", pendrive1[i]);
    }
    printf("\n2: ");
    for (int i = p2.filecount - 1; i >= 0; i--) {
        printf("%d ", pendrive2[i]);
    }
    delete[] pendrive1;
    delete[] pendrive2;
}
int main()
{
    //n- ilosc plikow, p- rozmiar pendrive'ow, id- id pliku, r- rozmiar pliku
    int n, p;

    //wczytanie ilosci plikow oraz ilosci pendrive'ow
    scanf_s("%d %d", &n, &p);

    File* plik = new File[n];
    int* id = new int[n], * r = new int[n];

    //wczytanie id i wielkosci n plików 
    for (int i = 0; i < n; i++) {
        scanf_s("%d %d", &id[i], &r[i]);
    }

    //sortowanie tablicy r wzgledem rozmiarow i zmiana indeksow tablicy id
    quicksort(r, 0, n - 1, id);

    //wypelnienie tablicy plikow posortowanymi tablica rozmiarow i identyfikaroami
    fillfiles(r, id, n, plik);

    Pendrive p1, p2;
    p1.size = p;
    p2.size = p;


    printf("%d\n", countfiles(n, plik, p, p1.filecount, p2.filecount));

    p1.files = new File[p1.filecount + 1];
    p2.files = new File[p2.filecount + 1];

    fillpendrives(n, p1, p2, plik);

    writeout(p1, p2, r);




    delete[] id;
    delete[] r;
    delete[] plik;
    delete[] p1.files;
    delete[] p2.files;

}



/*


15
8
9 1
4 1
6 1
35 6
35 2
6 8
4 8
7 7
7 3
5 3
2 3
4 3
15 7
5 8
2 9*/