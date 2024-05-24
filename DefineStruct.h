#ifndef DEFINE_H
#define DEFINE_H

#define MAX_COURSES 50
#define MAX_SEMESTERS 8
#define MAX_DOSEN 3
#define MAX_APPEND_LENGTH 100

typedef struct Course{
    char courseCode[10];
    char courseName[53];
    int semester;

    float tugas;
    float uas;
    float uts;
    float kuis;
    float score;

    int credits;
    char grade[3];
    int status; // 0 kalau belum disetujui dosen, 1 kalau sudah disetujui dosen

    struct Course *next;
} Course;

typedef struct {
    char password[20];
    
    char npm[25];
    char name[25];
    int batch;
    char major[50];

    char advisorName[25];
    char advisorNumber[15];

    char academicStatus[20];
    int totalPassedCredits;
    float totalGradePoints;
    float gpa;

    int tagihan;

    int semesterSekarang;
    float semesterGrades[8]; 
    int jumlahNilai[10];

    int totalCourses;
	int maximumCourses;
	int sksSekarang;
	int totalCredits;

	Course *courses_head;  
} AcademicUser;

typedef struct {
    char password[20];
    
	char advisorNumber[15];
    char advisorName[25];
} Dosen;

// List of available courses
Course availableCourses[] = {
    {"AGM101", "Agama", 1, 0, 0, 0, 0, 0, 2, "", 0, NULL},
    {"ENG101", "Bahasa Inggris", 1, 0, 0, 0, 0, 0, 2, "", 0, NULL},
    {"MATH101", "Kalkulus", 1, 0, 0, 0, 0, 0, 4, "", 0, NULL},
    {"PHY101", "Fisika Listrik", 1, 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"PHY102", "Praktikum Fisika Listrik", 1, 0, 0, 0, 0, 0, 1, "", 0, NULL},
    {"CS101", "Pemrograman Dasar", 1, 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"ECE101", "Dasar Sistem Digital", 1, 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"MPK101", "MPK Terintegrasi", 2, 0, 0, 0, 0, 0, 6, "", 0, NULL},
    {"MATH102", "Aljabar Linier", 2, 0, 0, 0, 0, 0, 4, "", 0, NULL},
    {"PHY103", "Fisika Mekanika", 2, 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"PHY104", "Praktikum Fisika Mekanika", 2, 0, 0, 0, 0, 0, 1, "", 0, NULL},
    {"CS102", "Organisasi Arsitektur Komputer", 2, 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"CS103", "Pemrograman Lanjut", 2, 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"ECE102", "Perancangan Sistem Digital", 3, 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"MATH103", "Struktur Diskrit", 3, 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"CS104", "Jaringan Komputer", 3, 0, 0, 0, 0, 0, 4, "", 0, NULL},
    {"CS105", "Pemrograman Berorientasi Objek", 3, 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"ECE103", "Dasar Rangkaian Elektronika", 3, 0, 0, 0, 0, 0, 2, "", 0, NULL},
    {"ECE104", "Rangkaian Listrik", 3, 0, 0, 0, 0, 0, 2, "", 0, NULL},
    {"STAT101", "Statistika", 3, 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"MATH104", "Aljabar Linier Lanjut", 4, 0, 0, 0, 0, 0, 2, "", 0, NULL},
    {"ECE105", "Sistem Siber Fisik", 4, 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"CS106", "Analisis Algoritma", 4, 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"CS107", "Sistem Operasi", 4, 0, 0, 0, 0, 0, 2, "", 0, NULL},
    {"CS108", "Desain dan Manajemen Jaringan Komputer", 4, 0, 0, 0, 0, 0, 4, "", 0, NULL},
    {"CS109", "Sistem Basis Data", 4, 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"MATH105", "Matematika Teknik", 4, 0, 0, 0, 0, 0, 4, "", 0, NULL},
    {"ECE106", "Praktikum Rangkaian Listrik dan Elektronik", 4, 0, 0, 0, 0, 0, 1, "", 0, NULL},
    {"CS110", "Rekayasa Perangkat Lunak", 5, 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"CS111", "Sistem Waktu Nyata dan IOT", 5, 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"CS112", "Cybersecurity", 5, 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"CS113", "Jaringan Telekomunikasi", 5, 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"CS114", "Arsitektur Komputer Modern", 5, 0, 0, 0, 0, 0, 2, "", 0, NULL},
    {"STAT102", "Probabilitas dan Proses Stokastik", 5, 0, 0, 0, 0, 0, 2, "", 0, NULL},
    {"ECE107", "Teori Sinyal dan Analisis Sistem", 5, 0, 0, 0, 0, 0, 2, "", 0, NULL},
    {"ECE108", "Desain Proyek Teknik Komputer", 6, 0, 0, 0, 0, 0, 2, "", 0, NULL},
    {"ECE109", "Pemrosesan Sinyal Multimedia", 6, 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"CS115", "Artificial Intelligence", 6, 0, 0, 0, 0, 0, 3, "", 0, NULL},
    {"BUS101", "Kewirausahaan dalam Teknologi Informasi", 6, 0, 0, 0, 0, 0, 2, "", 0, NULL},
    {"CS116", "Profesionalisme dan Etika dalam Teknologi Informasi", 6, 0, 0, 0, 0, 0, 2, "", 0, NULL}
};


#endif