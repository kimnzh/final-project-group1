void hitungRataRata() {
    FILE *file = fopen("DatabaseMahasiswa/allData.txt", "r");
    if (file == NULL) {
        perror("Failed to open allData file");
        return;
    }

    int totalMahasiswa = 0;
    float totalGPA = 0.0;
    float totalGradePoints = 0.0;
    float totalSemesterGrades[8] = {0.0};
    float grade[8];
    int totalPassedCredits = 0;

    char name[50], npm[50];
    
    // Buffer to store all names and npms to process in parallel
    char names[100][50];
    char npms[100][50];
    int count = 0;

    while (!feof(file)) {
        fscanf(file, " %[^\n]", names[count]);
        fscanf(file, "%s", npms[count]);
        count++;
    }

    fclose(file);

    #pragma omp parallel for reduction(+:totalGPA, totalGradePoints, totalPassedCredits) reduction(+:totalSemesterGrades[:8]) 
    for (int i = 0; i < count; i++) {
        char sourceMa[100] = "DatabaseMahasiswa/data_";
        char appMa[MAX_APPEND_LENGTH];

        sprintf(appMa, "%s/mahasiswa.txt", names[i]);
        append(sourceMa, appMa);

        AcademicUser user;
        int stat = 1;
        loadStudentData(&user, sourceMa, &stat);

        if (stat) {
            #pragma omp critical
            totalMahasiswa++;

            totalGPA += user.gpa;
            totalGradePoints += user.totalGradePoints;
            for (int j = 0; j < 8; j++) {
                totalSemesterGrades[j] += user.semesterGrades[j];
            }
            totalPassedCredits += user.totalPassedCredits;
        }
    }

    if (totalMahasiswa == 0) {
        printf("Tidak ada data mahasiswa yang ditemukan.\n");
        return;
    }

    printf("Rata-rata IPK: %.2f\n", totalGPA / totalMahasiswa);
    printf("Rata-rata Total Mutu: %.2f\n", totalGradePoints / totalMahasiswa);
    for (int i = 0; i < 8; i++) {
        printf("Rata-rata IP Semester %d: %.2f\n", i + 1, totalSemesterGrades[i] / totalMahasiswa);
        grade[i] = totalSemesterGrades[i]/totalMahasiswa;
    }
    printHistogram(grade, MAX_SEMESTERS);
    printf("Rata-rata SKS Lulus: %.2f\n", (float)totalPassedCredits / totalMahasiswa);
}

//MAIN MENU
void mainMenuDosen(AcademicUser user, Dosen advisor, int *size) {
	int opsi = -1;
	char opsiString[10];

	do {
        printf("++===========================++=======================================++\n");
        printf("||   UNIVERSITAS PROGLAN 2   ||        SISTEM AKADEMIK (DOSEN)        ||\n");
        printf("||                           |+===+===================================++\n");
        printf("|+===========================+| 1 | Manage Mahasiswa Bimbingan        ||\n");
        printf("|| NIP                       || 2 | Hitung rata-rata/keseluruhan data ||\n");
        printf("||  %s%            -*s\033[0m||   | mahasiswa                         ||\n", BLUE, 25, advisor.advisorName);
        printf("|| Nama                      ||   |                                   ||\n");
        printf("||  %s%            -*s\033[0m|| 0 | Keluar                            ||\n", CYAN, 25, advisor.advisorNumber);
        printf("++===========================++===+===================================++\n\n");

        printf("Pilihan: ");
        scanf(" %[^\n]", opsiString);
        opsi = atoi(opsiString);

        switch (opsi) {
            case 0:
                system("cls");
                printf("Keluar dari mode dosen...\n\n");
                printf("Press ANY key to continue!");
                getch();
                break;
            case 1:
                system("cls");
                pilihMahasiswa(user);
                printf("Press ANY key to continue!");
                getch();
                system("cls");
                break;
           case 2: 
                system("cls");
                hitungRataRata();
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
    } while (opsi != 0); 
}

//OPTIONS
// CASE 1
void pilihMahasiswa(AcademicUser user) {
    char sourceMa[100] = "DatabaseMahasiswa/data_", sourceAk[100] = "DatabaseMahasiswa/data_";
    char appMa[MAX_APPEND_LENGTH], appAk[MAX_APPEND_LENGTH];

    FILE *file = fopen("DatabaseMahasiswa/allData.txt", "r");


    char **tempName = NULL; // Start with no allocated memory
    char tempNPM[50];
    int idx = 0, choice, stat = 1; // idx for printing student number, choice for storing the selected number

    printf("++====++============================++=============++\n");
    printf("|| NO ||  NAMA MAHASISWA BIMBINGAN  ||     NPM     ||\n");
    printf("++====++============================++=============++\n");
    while (!feof(file)) {
        // Reallocate memory for each new student
        tempName = (char **)realloc(tempName, (idx + 1) * sizeof(char *));
        tempName[idx] = (char *)malloc(50 * sizeof(char)); // Allocate memory for the new string

        fscanf(file, " %[^\n]", tempName[idx]);
        fscanf(file, "%s", tempNPM);
        printf("|| %-2d || %-26s || %s  ||\n", idx + 1, tempName[idx], tempNPM);
        idx++;
    }
    printf("++====++============================++=============++\n\n");

    fclose(file);

    printf("Masukkan nomor mahasiswa: ");
    scanf("%d", &choice);
    printf("%s", tempName[0]);
    printf("%s", tempName[1]);

    // Menyiapkan source dari database
    sprintf(appMa, "%s/mahasiswa.txt", tempName[choice - 1]);
    sprintf(appAk, "%s/akademik.txt", tempName[choice - 1]); 
    append(sourceMa, appMa);
    append(sourceAk, appAk);

    // Memuat data dari mahasiswa beserta mata kuliahnya
    loadStudentData(&user, sourceMa, &stat);
    loadCourses(&user, sourceAk);
    
    #pragma omp parallel for
    for (int i = 0; i < idx; i++) {
        free(tempName[i]);
    }
    free(tempName);
    // Interface untuk opsi pada mahasiswa
    int opsi = -1;
	char opsiString[10];
	char pembayaran [15];
    do {
		if(user.tagihan == 0){
			strcpy(pembayaran, "LUNAS");
		}
		else{
			strcpy(pembayaran, "BELUM LUNAS");
		}
        system("cls");
        printf("++===========================++==========================================++\n");
        printf("||   UNIVERSITAS PROGLAN 2   ||                 PILIHAN                  ||\n");
        printf("||                           |+===+======================================++\n");
        printf("|+===========================+| 1 | Berikan nilai pada mata kuliah       ||\n");
        printf("|| Mahasiswa                 || 2 | Setujui mata kuliah                  ||\n");
        printf("||  %s%            -*s\033[0m||   |                                      ||\n", MAGENTA, 25, user.name);
        printf("|| NPM                       || 3 | Nyatakan Lulus untuk semester ini    ||\n");
        printf("||  %s%            -*s\033[0m||   | (mahasiswa akan lanjut ke semester   ||\n", MAGENTA, 25, user.npm);
        printf("|| IP Semester Sebelumnya    ||   | berikutnya)                          ||\n", MAGENTA, 25, user.npm);
        printf("||  %s%          -*.2f\033[0m||   |                                      ||\n", GREEN, 25, user.semesterGrades[user.semesterSekarang-2]); 
        printf("|| Semester Sekarang         || 4 | Konfirmasi status akademis mahasiswa ||\n", MAGENTA, 25, user.npm);
        printf("||  %s%            -*d\033[0m||   |                                      ||\n", GREEN, 25, user.semesterSekarang); 
        printf("|| Status Akademis           || 5 | Kembali ke menu sebelumnya           ||\n");   
        printf("||  %s%            -*s\033[0m||   |                                      ||\n",(strcmp(user.academicStatus,"Aktif") == 0) ? GREEN : RED, 25, user.academicStatus);
        printf("|| SKS yang diambil sekarang ||   |                                      ||\n");   
        printf("||  %s%            -*d\033[0m||   |                                      ||\n",(user.sksSekarang == 0) ? RED : GREEN, 25, user.sksSekarang);
		printf("|| Status Pembayaran         ||   |                                      ||\n");          
		printf("||  %s%            -*s\033[0m||   |                                      ||\n", (user.tagihan == 0) ? GREEN : RED, 25, pembayaran, YELLOW);
        printf("++===========================++===+======================================++\n\n");

        printf("Pilihan: ");
        scanf(" %[^\n]", opsiString);
        opsi = atoi(opsiString);

        switch (opsi) {
            case 1:
                system("cls");
                beriNilai(&user);
                printf("Press ANY key to continue!");
                getch();
                system("cls");
                break;
            case 2:
                system("cls");
                setujuiMatakuliah(&user);
                printf("Press ANY key to continue!");
                getch();
                system("cls");
                break;
            case 3:
                system("cls");
                user.semesterSekarang++;
                user.sksSekarang = 0;
                user.tagihan+=1000000;
                printf("Mahasiswa telah lulus ke semester berikutnya.\n");
                printf("Semester sekarang: %d\n", user.semesterSekarang);
                printf("Press ANY key to continue!");
                getch();
                system("cls");
                break;
            case 4:
                system("cls");
                printf("Pilih status akademis baru:\n");
                printf("1. Aktif\n");
                printf("2. Kosong\n");
                printf("3. Dikeluarkan\n");
                printf("Pilihan: ");
                int statusChoice;
                scanf("%d", &statusChoice);

                switch (statusChoice) {
                    case 1:
                        strcpy(user.academicStatus, "Aktif");
                        break;
                    case 2:
                        strcpy(user.academicStatus, "Kosong");
                        break;
                    case 3:
                        strcpy(user.academicStatus, "Dikeluarkan");
                        break;
                    default:
                        printf("Pilihan tidak valid.\n");
                        printf("Press ANY key to continue!");
                        getch();
                        system("cls");
                        continue;
                }
            case 5:
                system("cls");
                printf("Kembali ke beranda dosen...!\n\n");
                writeStudentData(&user, sourceMa);
                writeCourses(&user, sourceAk);
                break;
            default:
                printf("Input tidak valid\n");
                printf("Press ANY key to continue!");
                getch();
                system("cls");
        }
    } while (opsi != 5); 

}

void beriNilai(AcademicUser *user) {
    // Pengecekan jika ada mata kuliah yang belum disetujui
    Course *currentCourse = user->courses_head;
    int allApproved = 1; // Asumsikan semua mata kuliah telah disetujui
    while (currentCourse != NULL) {
        if (currentCourse->status == 0) {
            allApproved = 0; // Set ke 0 jika ada mata kuliah yang belum disetujui
            break;
        }
        currentCourse = currentCourse->next;
    }

    // Jika ada mata kuliah yang belum disetujui, tidak dapat memberikan nilai
    if (!allApproved) {
        printf("Tidak dapat memberikan nilai. Ada mata kuliah yang belum disetujui.\n");
        printf("Silakan tunggu hingga semua mata kuliah disetujui oleh dosen.\n");
        return;
    }

    // Melakukan iterasi melalui daftar matakuliah yang sudah disetujui
    currentCourse = user->courses_head;
    int courseIndex = 1;
    printf("++================================================++\n");
    printf("||         BERI NILAI MATAKULIAH MAHASISWA        ||\n");
    printf("++================================================++\n");
    while (currentCourse != NULL) {
        if (currentCourse->status == 1) {
            printf("%d. %-25s (%s)   \n", courseIndex, currentCourse->courseName, currentCourse->courseCode);
            courseIndex++;
        }
        currentCourse = currentCourse->next;
    }

    // Meminta input nilai dari dosen untuk setiap matakuliah
    printf("\nMasukkan nomor matakuliah untuk memberi nilai lengkap: ");
    int choice;
    scanf("%d", &choice);
    choice--; // Sesuaikan dengan indeks array (dimulai dari 0)

    currentCourse = user->courses_head;
    int selectedCourseIndex = 0;
    while (currentCourse != NULL) {
        if (currentCourse->status == 1) {
            if (selectedCourseIndex == choice) {
                float floatSkor;
                printf("\n++================================================++\n");
                printf("||           BERI NILAI MATAKULIAH               ||\n");
                printf("++================================================++\n");
                printf("|| Nama Matakuliah   : %-26s ||\n", currentCourse->courseName);
                printf("|| Kode Matakuliah   : %-26s ||\n", currentCourse->courseCode);
                printf("|| Nilai Kuis        : ");
                scanf("%f", &currentCourse->kuis);
                printf("|| Nilai UAS         : ");
                scanf("%f", &currentCourse->uas);
                printf("|| Nilai UTS         : ");
                scanf("%f", &currentCourse->uts);
                printf("|| Nilai Tugas       : ");
                scanf("%f", &currentCourse->tugas);
                // Hitung total nilai dan simpan dalam struktur data
                currentCourse->score = (currentCourse->kuis + currentCourse->uas + currentCourse->uts + currentCourse->tugas) / 4.0;
                
                // Update grade dan gradeFloat berdasarkan nilai skor baru
                if (currentCourse->score > 85) {
                    strcpy(currentCourse->grade, "A");
                    floatSkor = 4.0;
                } else if (currentCourse->score > 80) {
                    strcpy(currentCourse->grade, "A-");
                    floatSkor = 3.7;
                } else if (currentCourse->score > 75) {
                    strcpy(currentCourse->grade, "B+");
                    floatSkor = 3.3;
                } else if (currentCourse->score > 70) {
                    strcpy(currentCourse->grade, "B");
                    floatSkor = 3.0;
                } else if (currentCourse->score > 65) {
                    strcpy(currentCourse->grade, "B-");
                    floatSkor = 2.7;
                } else if (currentCourse->score > 60) {
                    strcpy(currentCourse->grade, "C+");
                    floatSkor = 2.3;
                } else if (currentCourse->score > 55) {
                    strcpy(currentCourse->grade, "C");
                    floatSkor = 2.0;
                } else if (currentCourse->score > 40) {
                    strcpy(currentCourse->grade, "D");
                    floatSkor = 1.0;
                } else {
                    strcpy(currentCourse->grade, "E");
                    floatSkor = 0.0;
                }
                
                // Perbarui Total SKS Lulus, Total Mutu, dan IPK mahasiswa
                if (floatSkor > 1.0) {
                    user->totalPassedCredits += currentCourse->credits; // Menambahkan SKS lulus dari matakuliah yang dinilai
                }
                user->totalGradePoints += currentCourse->credits * floatSkor; // Menambahkan total mutu
                user->gpa = user->totalGradePoints / user->totalCredits; // Menghitung IPK baru
                user->semesterGrades[user->semesterSekarang - 1] += currentCourse->credits * floatSkor / user->sksSekarang;
                printf("++================================================++\n\n");
                return;
            }
            selectedCourseIndex++;
        }
        currentCourse = currentCourse->next;
    }
    printf("Nomor matakuliah yang Anda pilih tidak valid atau tidak dapat memberi nilai.\n");
}


// CASE 2
void setujuiMatakuliah(AcademicUser *user) {
    Course *currentCourse = user->courses_head;
    int courseIndex = 1;
    printf("++===================================================================++\n");
    printf("||                  SETUJUI MATAKULIAH MAHASISWA                     ||\n");
    printf("++===================================================================++\n");
    while (currentCourse != NULL) {
        if (currentCourse->status == 0) {
            printf("%d. %-25s (%s) (Matakuliah semester %d)  \n", courseIndex, currentCourse->courseName, currentCourse->courseCode,currentCourse->semester);
            courseIndex++;
        }
        currentCourse = currentCourse->next;
    }

    // Meminta input dari dosen untuk menyetujui matakuliah
    printf("\nMasukkan nomor matakuliah untuk disetujui: ");
    int choice;
    scanf("%d", &choice);
    choice--; // Sesuaikan dengan indeks array (dimulai dari 0)

    currentCourse = user->courses_head;
    int selectedCourseIndex = 0;
    while (currentCourse != NULL) {
        if (currentCourse->status == 0) {
            if (selectedCourseIndex == choice) {
                currentCourse->status = 1; // Set status matakuliah menjadi disetujui
                printf("Matakuliah %s telah disetujui.\n", currentCourse->courseName);
                user->sksSekarang += currentCourse->credits;
                user->totalCredits += currentCourse->credits;
                return;
            }
            selectedCourseIndex++;
        }
        currentCourse = currentCourse->next;
    }
    printf("Nomor matakuliah yang Anda pilih tidak valid atau tidak dapat disetujui.\n");
}

//FILE HANDLING
void loadAdvisorData(Dosen *advisor, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open advisor data file");
        exit(EXIT_FAILURE);
    }
    
    fscanf(file, "%s", advisor->advisorNumber);
    fscanf(file, " %[^\n]", advisor->advisorName);
    fscanf(file, "%s", advisor->password);
    
    fclose(file);
}

void writeAdvisorData(Dosen *advisor, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open advisor data file for writing");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s\n", advisor->advisorNumber);
    fprintf(file, "%s\n", advisor->advisorName);
    fprintf(file, "%s\n", advisor->password);

    fclose(file);
}

//MISCELLANEOUS
void getAccessDosen(Dosen user, int *pass) {
	int i, ch;
	char buffer[50];

    i = 0;
    printf("Masukkan PASSWORD: ");

    do {
        ch = getch();
        if (ch == ' ' || ch == 27) {
            continue;
        } else if (ch == '\b') {
            if (i > 0) {
                printf("\b \b");
                --i;
            } else {
                continue;
            }
        } else if (ch == '\r' || ch == '\t') {
            break;
        } else if (ch == 0 || ch == 224) {
            ch = getch();
            continue;
        } else {
            buffer[i++] = ch;
            printf("*");
        }
    } while(1);

    buffer[i] = '\0';
    printf("\n");

    if (strcmp(user.password, buffer) != 0) {
        printf("PASSWORD yang dimasukkan salah\n\n");
        printf("Press ANY key to continue!");
        getch();
        system("cls");
    } else if (strcmp(user.password, buffer) == 0) {
        *pass = 1;
        system("cls");
        return;
    }
}