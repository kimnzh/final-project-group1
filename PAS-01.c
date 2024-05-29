/*
Proyek Akhir Semester - Pemrograman Lanjut 02
Program Simulasi SIAK Sederhana

Anggota Kelompok 1:
1. Daffa Sayra Firdaus (2306267151)
2. Muhamad Hakim Nizami (2306210001)

Versi Program : 1.0

DISCLAIMER : 
Program ini masih terus diubah/direvisi seiring berjalannya waktu dan mungkin berbeda dengan file yang diupload di Emas.
Untuk mendapatkan versi terbaru dan penjelasan lebih lanjut, dapat melewati link github kami :
"https://github.com/kimnzh/final-project-group1"

Deskripsi:
Tujuan dari program adalah untuk melakukan olah data mahasiswa untuk grading individu, ataupun grading keseluruhan mahasiswa beserta status mereka sebagai simulasi SIAK sederhana dengan fitur-fitur sebagai berikut:
1. Mode Dosen
- Program menerima input data nilai mahasiswa
- Menghitung data tendencies dari seluruh data nilai mahasiswa
- Mengkonfirmasi Status keaktifan masing-masing mahasiswa 
- Mempersetujui matkul yang dipilih oleh mahasiswa berdasarkan pertimbangan batas SKS dan persyaratan nilai/IP
- Menentukan jika mahasiswa lulus atau tidak
- Menampilkan bagan nilai mahasiswa (tampilan secara kasar)
- Multithreading digunakan untuk menjalankan hitungan program pada jumlah data yang sangat besar untuk meningkatkan efisiensi 
(>50.000 data, untuk proyek akhir ini data yang diberikan hanya sedikit demi menghemat waktu dan size file yang tidak terlalu besar)

2. Mode Mahasiswa
- Memilih matakuliah/kelas yang dipelajari untuk satu semester
- Membayar UKT untuk menjaga status aktif sebagai mahasiswa
- Melihat Chart/Data nilai semester/semasa kuliah
*/
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <omp.h>
#include <math.h>
#include <direct.h>

#define RED "\033[1;31m" //Red
#define YELLOW "\033[1;33m" //Yellow
#define GREEN "\033[1;32m" //Green
#define CYAN "\033[1;36m" //Cyan
#define BLUE "\033[1;34m" //Blue
#define MAGENTA "\033[1;35m" //Magenta

#include "DefineStruct.h"
#include "Prototype.h"
#include "StringManipule.h"

#include "ModeAdmin/Functions.h"
#include "ModeDosen/Functions.h"
#include "ModeMahasiswa/Functions.h"

int main(){
    char appMa[MAX_APPEND_LENGTH], appAk[MAX_APPEND_LENGTH], appDo[MAX_APPEND_LENGTH];
    char namaMahasiswa[50], namaDosen[50];
    AcademicUser student = {0};
    Dosen advisor = {0};
	int size = 0; 
    int stat, pass;

    int mode = -1;
	char modeString[10];
	do {
        char sourceMa[100] = "Database/DatabaseMahasiswa/data_";
        char sourceAk[100] = "Database/DatabaseMahasiswa/data_";
        char sourceDo[100] = "Database/DatabaseDosen/data_dosen_";
        system("cls");
        printf("Pilih akun yang ingin digunakan : \n");
        printf("1. Mahasiswa\n");
        printf("2. Dosen\n");
        printf("3. Exit\n\n");
        printf("4. Tambah Akun Mahasiswa\n");
        printf("5. Tambah Akun Dosen\n\n");
        printf("Pilihan : ");

        scanf(" %[^\n]", &modeString);
        mode = atoi(modeString);
        switch (mode) {
            case 1:
                printf("Nama : ");
                scanf(" %[^\n]", namaMahasiswa);

                // Menyiapkan source dari database
                sprintf(appMa, "%s/mahasiswa.txt", namaMahasiswa);
                sprintf(appAk, "%s/akademik.txt", namaMahasiswa);
                append(sourceMa, appMa);
                append(sourceAk, appAk);

                // Memuat data dari mahasiswa beserta mata kuliahnya
                stat = 1;
                loadStudentData(&student, sourceMa, &stat);
                loadCourses(&student, sourceAk);
                if (stat == 0) {
                    printf("Press ANY key to continue!");
                    getch();
                    system("cls");
                    break;
                }

                // Interface oleh Mahasiswa
                pass = 0;
                getAccessMahasiswa(student, &pass);
                if (pass == 1)
                    mainMenuMahasiswa(student, &size, sourceMa, sourceAk);
                memset(&student, 0, sizeof(student));
                break;
            case 2:
                printf("Nama : ");
                scanf(" %[^\n]", namaDosen);

                // Menyiapkan source dari database
                append(sourceDo, namaDosen);
                append(sourceDo, ".txt");

                // Memuat data dari dosen
                stat = 1;
                loadAdvisorData(&advisor, sourceDo, &stat);
                if (stat == 0) {
                    printf("Press ANY key to continue!");
                    getch();
                    system("cls");
                    break;
                }

                // Interface oleh dosen
                pass = 0;
                getAccessDosen(advisor, &pass);
                if (pass == 1)
                    mainMenuDosen(student, advisor, &size);
                memset(&advisor, 0, sizeof(advisor));
                break;
            case 3:
                printf("Berhasil keluar program\n\n");
                printf("Press ANY key to continue!");
                getch();
                system("cls");
                break;
            case 4:
                tambahDataMahasiswa();
                printf("Press ANY key to continue!");
                getch();
                system("cls");
                break;
            case 5:
                tambahDataDosen();
                printf("Press ANY key to continue!");
                getch();
                system("cls");
                break;
            default:
                printf("Input tidak valid\n");
                printf("Press ANY key to continue!");
                getch();
                system("cls");
        }
    } while (mode != 3);
	return 0;

}