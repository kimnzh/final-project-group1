//MAIN MENU
void mainMenuDosen(AcademicUser user, Dosen advisor, int *size) {
	int opsi = -1;
	char opsiString[10];

	do {
        printf("++===========================++=======================================++\n");
        printf("||   UNIVERSITAS PROGLAN 2   ||        SISTEM AKADEMIK (DOSEN)        ||\n");
        printf("||                           |+===+===================================++\n");
        printf("|+===========================+| 1 | Manage Mahasiswa Bimbingan        ||\n");
        printf("|| NIP                       ||   |                                   ||\n");
        printf("||  %s%            -*s\033[0m|| 0 | Keluar                            ||\n", BLUE, 25, advisor.advisorName);
        printf("|| Nama                      ||   |                                   ||\n");
        printf("||  %s%            -*s\033[0m||   |                                   ||\n", CYAN, 25, advisor.advisorNumber);
        printf("++===========================++===+===================================++\n\n");

        printf("Pilihan: ");
        scanf(" %[^\n]", opsiString);
        if (strcmp(opsiString, "0") != 0)
            strcpy(opsiString, "-1");
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

    char tempName[20][50], tempNPM[50]; // Di-set untuk 20 nama mahasiswa
    int idx = 0, choice, stat = 1; // idx untuk print nomor mahasiswa, choice untuk menyimpan nomor yang dipilih dosen

    printf("++====++============================++=============++\n");
    printf("|| NO ||  NAMA MAHASISWA BIMBINGAN  ||     NPM     ||\n");
    printf("++====++============================++=============++\n");
    while (!feof(file)) {
        fscanf(file, " %[^\n]", tempName[idx]);
        fscanf(file, "%s", tempNPM);
        printf("|| %-2d || %                       -*s|| %s  ||\n", idx + 1, 27, tempName[idx], tempNPM);
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
    
    // Interface untuk opsi pada mahasiswa
    int opsi = -1;
	char opsiString[10];
    do {
        system("cls");
        printf("++===========================++==========================================++\n");
        printf("||   UNIVERSITAS PROGLAN 2   ||                 PILIHAN                  ||\n");
        printf("||                           |+===+======================================++\n");
        printf("|+===========================+| 1 | Berikan nilai pada mata kuliah       ||\n");
        printf("|| Mahasiswa                 || 2 | Setujui mata kuliah                  ||\n");
        printf("||  %s%            -*s\033[0m||   |                                      ||\n", MAGENTA, 25, user.name);
        printf("|| NPM                       || 0 | Kembali                              ||\n");
        printf("||  %s%            -*s\033[0m||   |                                      ||\n", MAGENTA, 25, user.npm);
        printf("++===========================++===+======================================++\n\n");

        printf("Pilihan: ");
        scanf(" %[^\n]", opsiString);
        if (strcmp(opsiString, "0") != 0)
            strcpy(opsiString, "-1");
        opsi = atoi(opsiString);

        switch (opsi) {
            case 0:
                system("cls");
                printf("Kembali ke beranda dosen...!\n\n");
                writeStudentData(&user, sourceMa);
                writeCourses(&user, sourceAk);
                break;
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
            default:
                printf("Input tidak valid\n");
                printf("Press ANY key to continue!");
                getch();
                system("cls");
        }
    } while (opsi != 0); 

}

void beriNilai(AcademicUser *user) {
    // Lakukan iterasi melalui daftar matakuliah yang sudah disetujui
    float floatSkor;
    Course *currentCourse = user->courses_head;
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
                user->totalPassedCredits += currentCourse->credits; // Menambahkan SKS dari matakuliah yang dinilai
                user->totalGradePoints += currentCourse->credits * floatSkor; // Menambahkan total mutu
                user->gpa = user->totalGradePoints / user->totalPassedCredits; // Menghitung IPK baru
                user->semesterGrades[user->semesterSekarang-1] += currentCourse->credits * floatSkor/currentCourse->credits;
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
    printf("++================================================++\n");
    printf("||           SETUJUI MATAKULIAH MAHASISWA        ||\n");
    printf("++================================================++\n");
    while (currentCourse != NULL) {
        if (currentCourse->status == 0) {
            printf("%d. %-25s (%s)   \n", courseIndex, currentCourse->courseName, currentCourse->courseCode);
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
                user->totalPassedCredits += currentCourse->credits;
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