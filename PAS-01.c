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
#include "DefineStruct.h"
#include "Functions.h"
#include "Filehandling.h"
#include "MainMenu.h"
#include "StringManipule.h"


int main(){
	char source[100] = "akademik_", app[MAX_APPEND_LENGTH];
    AcademicUser student = {0};
    Dosen advisor = {0};
	int size = 0;
	int mode;
	loadStudentData(&student, "data_mahasiswa.txt");
    loadAdvisorData(&advisor, "data_dosen.txt");
	sprintf(app, "%s.txt",student.name);
    append(source, app);
    loadCourses(&student, source);
    printf("Pilih akun yang ingin digunakan : \n");
    printf("1. Mahasiswa  \n");
    printf("2. Dosen \n");
    printf("Pilihan : ");
    scanf("%d",&mode);
    printf("\n");
    if(mode == 1){
    	getAccess(student);
		mainMenuMahasiswa(student, &size,source);
	}
	else{
		getAccessDosen(advisor);
		mainMenuDosen(student,advisor,&size,source);
	}
	return 0;
}