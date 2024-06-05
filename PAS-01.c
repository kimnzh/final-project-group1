/*
Proyek Akhir Semester - Pemrograman Lanjut 02 (REVISI)
Program Simulasi SIAK Sederhana

Anggota Kelompok 1:
1. Daffa Sayra Firdaus (2306267151)
2. Muhamad Hakim Nizami (2306210001)

Versi Program : 2.0 (Rabu, 5 Juni 2024)

DISCLAIMER : 
Program ini masih terus diubah/direvisi seiring berjalannya waktu dan mungkin berbeda dengan file yang diupload di Emas.
Untuk mendapatkan versi terbaru dan penjelasan lebih lanjut, dapat melewati link github kami :
"https://github.com/kimnzh/final-project-group1"

Deskripsi:
Tujuan dari program adalah untuk melakukan olah data mahasiswa untuk grading individu, ataupun grading keseluruhan
mahasiswa beserta status mereka sebagai simulasi SIAK sederhana dengan fitur-fitur sebagai berikut:

1. Mode Mahasiswa

- Menunjukkan data diri seperti nama, NPM, angkatan, program studi, nama dosen pembimbing, status akademik, SKS yang lulus, Mutu, IPK, SKS
  yang diperoleh, status pembayaran biaya operasional pendidikan.
- Menampilkan indeks prestasi keseluruhan dalam bentuk grafik.
- Mengajukan mata kuliah/kelas yang ingin ditempuh dalam satu semester (dengan persetujuan dosen pembimbing).
- Dapat membatalkan mata kuliah yang sebelumnya diajukan, selama belum disetujui oleh dosen pembimbing.
- Dapat melihat riwayat mata kuliah yang sudah diajukan selama perkuliahan.
- Melihat nilai dari mata kuliah yang sudah ditempuh (dinilai oleh dosen pembimbing) (Dapat disort secara ascending ataupun descending).
- Men-search mata kuliah yang dapat dipilih selama satu semester.
- Dapat memilih untuk membayar biaya operasional pendidikan atau UKT, jika membayar, maka status pembayaran dianggap lunas
- Disertai dengan panduan dalam menggunakan program dan opsi-opsi yang bisa dilakukan dalam program.
- Mahasiswa dapat merubah profile dari mahasiswa, seperti nama dan password.

2. Mode Dosen

- Dosen dapat menyetujui mata kuliah yang diajukan oleh mahasiswa berdasarkan pertimbangan batas SKS dan persyaratan nilai/IP
- Dosen dapat menilai mata kuliah yang ditempuh oleh mahasiswa bimbingan selama satu semester
- Memilih untuk meluluskan mahasiswa bimbingan dalam satu semester
- Menghitung data tendencies dari seluruh data nilai mahasiswa yang dibimbing
- Mengonfirmasi status akademik atau keaktifan masing-masing mahasiswa
- Memsetujui matkul yang dipilih oleh mahasiswa
- Menampilkan bagan nilai mahasiswa (tampilan secara chart kasar)

Selain mode mahasiswa dan dosen, terdapat pilihan untuk menambah data mahasiswa dan data dosen baru. Setiap data dari mahasiswa 
maupun dosen, seperti nilai, mata kuliah yang diambil, dan sebagainya disimpan dalam database berupa directory yang masing-masing
merujuk kepada satu orang mahasiswa/dosen. Untuk data pribadi seperti nama, NPM/NIP, program studi, dan lainnya disimpan dalam 
struct yang datanya diambil (read) dari database yang menyimpan data dari masing-masing mahasiswa atau dosen. Setiap data pada 
struct memiliki method atau function yang dikhususkan untuk meng-edit nilai yang tersimpan di dalam variabel struct tersebut.
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