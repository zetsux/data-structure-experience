// FINAL PROJECT STRUKTUR DATA C
// Oleh : Kevin Nathanael Halim ( 5025211140 )

// Program untuk menentukan keikutsertaan suatu online course berbasis Decision Tree sederhana
// Menggunakan 9 Faktor/Aspek berupa : 
// Benefit, Kendala, Keinginan, Urgency, Kualitas serta Kredibilitas, Harga, Ketertarikan, Budget, dan Waktu

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
// Jumlah aspek yang digunakan di dalam Decision Tree untuk mencapai keputusan akhir
#define ASPECT 9

// Melihat apakah traversal sudah mencapai keputusan akhir
bool done = false;

// String untuk berinteraksi dengan user
char questions[ASPECT][1000];
char reasons[ASPECT][1000];

// Index untuk alasan penolakan
int noIndex = 1;

// String untuk masuk ke opsi kiri pada Decision Tree
char leftOption[ASPECT][1000];

// String untuk masuk ke opsi kanan pada Decision Tree
char rightOption[ASPECT][1000];

// String untuk masuk ke opsi tengah pada Decision Tree
char midOption[ASPECT][1000];

// Struktur data Decision Tree
typedef struct dtnode_t {
    int key;
    struct dtnode_t \
        *left, *mid, *right;
} dtNode;

typedef struct dt_t {
    dtNode *_root;
} dt;

// Fungsi pembantu untuk membuat node baru pada Decision Tree
dtNode* __dt__createNode(int value) 
{
    dtNode *newNode = (dtNode*) malloc(sizeof(dtNode));
    newNode->key = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Fungsi untuk memasukkan node aspek pada Decision Tree
dtNode* __dt__insert(dtNode *root, int value) 
{
    if (root == NULL) 
        return __dt__createNode(value);

    if (value < root->key)
        root->left = __dt__insert(root->left, value);
    else if (value > root->key)
        root->right = __dt__insert(root->right, value);
    
    return root;
}

// Fungsi untuk mencari node spesifik pada Decision Tree 
dtNode* __dt__search(dtNode *root, int value) 
{
    while (root != NULL) {
        if (value < root->key)
            root = root->left;
        else if (value > root->key)
            root = root->right;
        else
            return root;
    }
    return root;
}

// Fungsi untuk menelusuri Decision Tree guna mendapatkan keputusan akhir
void __dt__traverse(dtNode *root, const int data[]) 
{
    if (root && !done)
    {
        if (root->key < 0)
        {
            printf("\t\t\t\t\t\t   | The Verdict |\n");
            printf("\t\t\t\t\t      Jangan Ikuti Online Course.\n");
            printf(" %s", reasons[root->key*-1]);
            done = true;
            return;
        }

        else if (root->key == 100)
        {
            printf("\t\t\t\t\t\t   | The Verdict |\n");
            printf("\t\t\t\t\t\t Ikuti Online Course!");
            done = true;
            return;
        }

        else if (data[root->key] == 1)
        {
            __dt__traverse(root->left, data);
        }

        else if (data[root->key] == 3)
        {
            __dt__traverse(root->right, data);
        }

        else if (data[root->key] == 2)
        {
            __dt__traverse(root->mid, data);
        }
    }

    return;
}

// Fungsi untuk menginisialisasi Decision Tree
void dt_init(dt *dt) 
{
    dt->_root = NULL;
}

// Fungsi pemanggil untuk mencari node spesifik dalam Decision Tree
bool dt_find(dt *dt, int value) 
{
    dtNode *temp = __dt__search(dt->_root, value);
    if (temp == NULL)
        return false;
    
    if (temp->key == value)
        return true;
    else
        return false;
}

// Fungsi pemanggil untuk menambahkan node aspek baru ke dalam Decision Tree
void dt_insert(dt *dt, int value) 
{
    if (!dt_find(dt, value)) 
    {
        dt->_root = __dt__insert(dt->_root, value);
    }
}

// Fungsi untuk memasukkan keputusan akhir ke dalam Decision Tree yang bernilai positif pada node left
void dt_addYes(dt *dt, int value) 
{
    dtNode *temp = __dt__search(dt->_root, value);
    if (temp == NULL)
        return;
    
    if (temp->key == value)
    {
        dtNode *yes = __dt__createNode(100);
        temp->left = yes;
    }
}

// Fungsi untuk memasukkan keputusan akhir ke dalam Decision Tree yang bernilai negatif pada node right
void dt_addNo(dt *dt, int value) 
{
    dtNode *temp = __dt__search(dt->_root, value);
    if (temp == NULL)
        return;
    
    if (temp->key == value)
    {
        dtNode *no = __dt__createNode(noIndex*-1);
        temp->right = no;
        noIndex++;
    }
}

// Fungsi untuk memasukkan keputusan akhir ke dalam Decision Tree yang bernilai positif pada node middle
void dt_addMidYes(dt *dt, int value) 
{
    dtNode *temp = __dt__search(dt->_root, value);
    if (temp == NULL)
        return;
    
    if (temp->key == value)
    {
        dtNode *yes = __dt__createNode(100);
        temp->mid = yes;
    }
}

// Fungsi untuk memasukkan keputusan akhir ke dalam Decision Tree yang bernilai negatif pada node middle
void dt_addMidNo(dt *dt, int value) 
{
    dtNode *temp = __dt__search(dt->_root, value);
    if (temp == NULL)
        return;
    
    if (temp->key == value)
    {
        dtNode *no = __dt__createNode(noIndex*-1);
        temp->mid = no;
        noIndex++;
    }
}

// Fungsi untuk membuat Decision Tree
void dt_construct(dt *dt)
{
    // 8 : Waktu / Jadwal
    dt_insert(dt, 8);
    // 7 : Budget yang Tersedia
    dt_insert(dt, 7);
    // 2 : Keinginan Ikut
    dt_insert(dt, 2);
    // 1 : Kendala Ikut
    dt_insert(dt, 1);
    // 0 : Benefit Ikut
    dt_insert(dt, 0);
    // 3 : Urgency Ikut
    dt_insert(dt, 3);
    // 6 : Ketertarikan terhadap Materi
    dt_insert(dt, 6);
    // 4 : Kualitas dan Kredibilitas Course
    dt_insert(dt, 4);
    // 5 : Harga Course
    dt_insert(dt, 5);

    // Memasukkan hasil akhir "NO"
    dt_addNo(dt, 8);
    dt_addNo(dt, 7);
    dt_addMidNo(dt, 2);
    dt_addNo(dt, 1);
    dt_addNo(dt, 0);
    dt_addNo(dt, 6);
    dt_addMidNo(dt, 4);
    dt_addNo(dt, 5);

    // Memasukkan hasil akhir "YES"
    dt_addMidYes(dt, 1);
    dt_addYes(dt, 0);
    dt_addYes(dt, 3);
    dt_addYes(dt, 4);
    dt_addYes(dt, 5);
    dt_addMidYes(dt, 5);
}

// Fungsi pemanggil untuk menelusuri Decision Tree guna mencapai keputusan akhir
void dt_traverse(dt *dt, const int data[]) 
{
    __dt__traverse(dt->_root, data);
}

// Fungsi untuk melakukan komparasi antara string masukkan dan string patokan
bool compareString (char str[], char comp[])
{
    if (strlen(str) != strlen(comp))
    {
        return false;
    }   

    int j = 0;
    for (j = 0; j < strlen(str); j++)
    {
        if (str[j] != comp[j] && str[j] != toupper(comp[j]))
        {
            return false;
        }
    }

    return true;
}

// Fungsi untuk menampilkan starting screen
void printMainScreen()
{
    printf("\t\t\t       ________________________________________________________\n\n");
    printf("\t\t\t       Selamat datang di program VOC (Validator Online Course)!\n");
    printf("\t\t\t       ________________________________________________________\n\n");
    printf("\tBingung apakah online course pilihanmu cocok dan 'valid' untuk anda ikuti?\n");
    printf("\tDisini, anda akan dibantu oleh program berbasis Decision Tree sederhana untuk menyelesaikan dilemamu!\n\n");
    printf("\tCaranya mudah sekali, hanya dengan menjawab pertanyaan-pertanyaan berikut ini dengan pilihan yang tersedia.\n");
    printf("\tSelamat mencoba! ( Jawaban boleh dalam bentuk angka / tulisan )\n\n");
    printf("________________________________________________________________________________________________________________________________\n");
    printf("\t\t\t\t\t\t   | QnA BOARD |\n");
    printf("\t\t\t\t\t\t   -------------\n\n");
}

// Fungsi untuk menampilkan end screen
void printEndScreen()
{  
    printf("\n________________________________________________________________________________________________________________________________\n");
    printf("\n\t\t\t\t\t  Terima kasih telah menggunakan VOC!\n");
    printf("\t\t\t\t\t Semoga bantuan kami berguna bagi anda.\n\n");
}

// Fungsi pengisi string berdasarkan opsi untuk membantu proses traversal
void stringFill()
{
    //Isi string untuk diprint saat mengambil user input
    strcpy(questions[0], "Benefit yang didapat bila mengikuti Online Course? (1. Berguna / 2. Kurang)");
    strcpy(questions[1], "Adakah kendala mengikuti Online Course? (1. Ada / 2. Besar / 3. Tidak)");
    strcpy(questions[2], "Keinginan mengikuti Online Course? (1. Antusias / 2. Ragu / 3. Kurang)");
    strcpy(questions[3], "Urgency untuk ikut dalam Online Course? (1. Tinggi / 2. Rendah)");
    strcpy(questions[4], "Kualitas & Kredibilitas Online Course? (1. Tinggi / 2. Standar / 3. Rendah)");
    strcpy(questions[5], "Harga Online Course? (1. Murah / 2. Mahal / 3. Standar)");
    strcpy(questions[6], "Ketertarikan terhadap materi Online Course? (1. Tinggi / 2. Rendah)");
    strcpy(questions[7], "Apakah budget untuk mengikuti Online Course tersedia? (1. Ya / 2. Tidak)");
    strcpy(questions[8], "Kondisi waktu untuk jadwal Online Course? (1. Cocok / 2. Bertabrakan)");

    //Isi string untuk alasan penolakan
    strcpy(reasons[1], "Jadwal Online Course tidak memungkinkan diikuti, coba cari Online Course lain yang jadwalnya lebih sesuai kemudian coba lagi");
    strcpy(reasons[2], "Budget tidak cukup untuk Online Course tersebut, coba kumpulkan budget atau cari yang pas dengan dompet sebelum mencoba lagi");
    strcpy(reasons[3], "Anda tidak ingin mengikuti Online Course tersebut, coba cari yang anda suka, sesuatu yang dipaksakan tidak akan berjalan baik");
    strcpy(reasons[4], "Kendala untuk mengikuti Online Course tersebut terlalu besar, coba selesaikan kendala tersebut terlebih dahulu dan coba lagi");
    strcpy(reasons[5], "Benefit yang didapat dari Online Course tersebut kurang berguna, coba cari yang lebih berdampak pada diri anda dan coba lagi");
    strcpy(reasons[6], "Anda kurang tertarik dengan materi Online Course tersebut, coba cari yang materinya dibutuhkan dan disukai sebelum mencoba lagi");
    strcpy(reasons[7], "Kualitas dan Kredibilitas Online Course terlalu rendah, coba cari yang lebih baik dari sejumlah referensi sebelum mencoba lagi");
    strcpy(reasons[8], "Harga Online Course tidak sesuai dengan kualitas & kredibilitasnya, coba cari yang lebih sesuai dengan harganya sebelum kembali");

    //Isi String untuk opsi kiri
    strcpy(leftOption[0], "berguna");
    strcpy(leftOption[1], "ada");
    strcpy(leftOption[2], "antusias");
    strcpy(leftOption[3], "tinggi");
    strcpy(leftOption[4], "tinggi");
    strcpy(leftOption[5], "murah");
    strcpy(leftOption[6], "tinggi");
    strcpy(leftOption[7], "ya");
    strcpy(leftOption[8], "cocok");

    //Isi String untuk opsi kanan
    strcpy(rightOption[0], "kurang");
    strcpy(rightOption[1], "besar");
    strcpy(rightOption[2], "ragu");
    strcpy(rightOption[3], "rendah");
    strcpy(rightOption[4], "standar");
    strcpy(rightOption[5], "mahal");
    strcpy(rightOption[6], "rendah");
    strcpy(rightOption[7], "tidak");
    strcpy(rightOption[8], "bertabrakan");

    //Isi String untuk opsi tengah
    strcpy(midOption[0], "!@#$^&*()_+<>)(*&^$#@!");
    strcpy(midOption[1], "tidak");
    strcpy(midOption[2], "kurang");
    strcpy(midOption[3], "!@#$^&*()_+<>)(*&^$#@!");
    strcpy(midOption[4], "rendah");
    strcpy(midOption[5], "standar");
    strcpy(midOption[6], "!@#$^&*()_+<>)(*&^$#@!");
    strcpy(midOption[7], "!@#$^&*()_+<>)(*&^$#@!");
    strcpy(midOption[8], "!@#$^&*()_+<>)(*&^$#@!");

    // Ket : !@#$^&*()_+<>)(*&^$#@! artinya tidak ada apapun di tengah
}
 
int main()
{
    // Inisialisasi struktur data Decision Tree
    dt tree;
    dt_init(&tree);

    // Konstruksi Decision Tree
    dt_construct(&tree);

    // Array untuk menyimpan input user terhadap tiap aspek sesuai dengan kode nomor di atas 
    int data[ASPECT];

    // Variabel-variabel pembantu eksekusi program
    int i = 0;
    char str[1000];

    // Isi tiap string dengan opsi untuk menentukan pergerakan berdasarkan user input nantinya
    stringFill();

    // Print terhadap starting screen program saat dijalankan
    printMainScreen();

    // Terima user input untuk menentukan traversal Decision Tree nantinya
    for (i = 0 ; i < ASPECT ; i++)
    {
        while (1)
        {
            printf("\t Question %d : %s\n", i+1, questions[i]);
            printf("\t Answer : ");
            scanf("%s", str);

            if (compareString(str, rightOption[i]) || strcmp(str, "2") == 0)
            {
                data[i] = 3;
                printf("\t Masukkan diterima!\n\n");
                break;
            }

            else if (compareString(str, midOption[i]) || (strcmp(midOption[i], "!@#$^&*()_+<>)(*&^$#@!") != 0 && strcmp(str, "3") == 0))
            {
                data[i] = 2;
                printf("\t Masukkan diterima!\n\n");
                break;
            }

            else if (compareString(str, leftOption[i]) || strcmp(str, "1") == 0)
            {
                data[i] = 1;
                printf("\t Masukkan diterima!\n\n");
                break;
            }

            else
            {
                printf("\t Masukkan tidak sesuai dengan pilihan yang tertera, mohon melakukan input ulang dengan teliti..\n\n");
            }
        }
    }

    // Telusuri Decision Tree untuk mencapai keputusan akhir
    dt_traverse(&tree, data);

    // Print terhadap end screen program setelah selesai digunakan
    printEndScreen();
    return 0;
}