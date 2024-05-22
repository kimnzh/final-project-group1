#ifndef DEFINE_H
#define DEFINE_H

#define MAX_COURSES 50
#define MAX_SEMESTERS 8
#define MAX_DOSEN 3
#define MAX_APPEND_LENGTH 100

typedef struct Course{
    char courseCode[10];
    char courseName[53];
    float tugas;
    float uas;
    float uts;
    float kuis;
    float score;
    int credits;
    char grade[3];
    int status; //0 kalau belum disetujui dosen, 1 kalau sudah disetujui dosen
    struct Course *next;
} Course;

typedef struct {
    char npm[25];
    char name[25];
    int batch;
    char advisorNumber[15];
    char advisorName[25];
    char password[20];
    char academicStatus[20];
    int totalPassedCredits;
    float totalGradePoints;
    float gpa;
    int tagihan;
    int semesterSekarang;
    float semesterGrades[8]; 
    int jumlahNilai[8];
    int totalCourses;
	int maximumCourses;
	Course *courses_head;  
} AcademicUser;

typedef struct {
	char advisorNumber[15];
    char advisorName[25];
    char password[20];
} Dosen;

// List of available courses
Course availableCourses[] = {
    {"AGM101", "Agama", 0, 0, 0, 0, 0, 2, "", 0, NULL},
    {"ENG101", "Bahasa Inggris", 0, 0, 0, 0, 0, 2, "", 0, NULL},
    {"MATH101", "Kalkulus", 0, 0, 0, 0, 0, 4, "", 0, NULL},
    {"PHY101", "Fisika Listrik", 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"PHY102", "Praktikum Fisika Listrik", 0, 0, 0, 0, 0, 1, "", 0, NULL},
    {"CS101", "Pemrograman Dasar", 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"ECE101", "Dasar Sistem Digital", 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"MPK101", "MPK Terintegrasi", 0, 0, 0, 0, 0, 6, "", 0, NULL},
    {"MATH102", "Aljabar Linier", 0, 0, 0, 0, 0, 4, "", 0, NULL},
    {"PHY103", "Fisika Mekanika", 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"PHY104", "Praktikum Fisika Mekanika", 0, 0, 0, 0, 0, 1, "", 0, NULL},
    {"CS102", "Organisasi Arsitektur Komputer", 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"CS103", "Pemrograman Lanjut", 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"ECE102", "Perancangan Sistem Digital", 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"MATH103", "Struktur Diskrit", 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"CS104", "Jaringan Komputer", 0, 0, 0, 0, 0, 4, "", 0, NULL},
    {"CS105", "Pemrograman Berorientasi Objek", 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"ECE103", "Dasar Rangkaian Elektronika", 0, 0, 0, 0, 0, 2, "", 0, NULL},
    {"ECE104", "Rangkaian Listrik", 0, 0, 0, 0, 0, 2, "", 0, NULL},
    {"STAT101", "Statistika", 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"MATH104", "Aljabar Linier Lanjut", 0, 0, 0, 0, 0, 2, "", 0, NULL},
    {"ECE105", "Sistem Siber Fisik", 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"CS106", "Analisis Algoritma", 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"CS107", "Sistem Operasi", 0, 0, 0, 0, 0, 2, "", 0, NULL},
    {"CS108", "Desain dan Manajemen Jaringan Komputer", 0, 0, 0, 0, 0, 4, "", 0, NULL},
    {"CS109", "Sistem Basis Data", 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"MATH105", "Matematika Teknik", 0, 0, 0, 0, 0, 4, "", 0, NULL},
    {"ECE106", "Praktikum Rangkaian Listrik dan Elektronik", 0, 0, 0, 0, 0, 1, "", 0, NULL},
    {"CS110", "Rekayasa Perangkat Lunak", 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"CS111", "Sistem Waktu Nyata dan IOT", 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"CS112", "Cybersecurity", 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"CS113", "Jaringan Telekomunikasi", 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"CS114", "Arsitektur Komputer Modern", 0, 0, 0, 0, 0, 2, "", 0, NULL},
    {"STAT102", "Probabilitas dan Proses Stokastik", 0, 0, 0, 0, 0, 2, "", 0, NULL},
    {"ECE107", "Teori Sinyal dan Analisis Sistem", 0, 0, 0, 0, 0, 2, "", 0, NULL},
    {"ECE108", "Desain Proyek Teknik Komputer", 0, 0, 0, 0, 0, 2, "", 0, NULL},
    {"ECE109", "Pemrosesan Sinyal Multimedia", 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"CS115", "Artificial Intelligence", 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"BUS101", "Kewirausahaan dalam Teknologi Informasi", 0, 0, 0, 0, 0, 2, "", 0, NULL},
    {"CS116", "Profesionalisme dan Etika dalam Teknologi Informasi", 0, 0, 0, 0, 0, 2, "", 0, NULL}
};


#endif