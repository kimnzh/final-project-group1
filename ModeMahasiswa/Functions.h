//MAIN MENU
void mainMenuMahasiswa(AcademicUser user, int *size, char sourceMa[], char sourceAk[]) {
	int cekNilai;
	int opsi = -1;
	char opsiString[10];
	char search[50];
	char pembayaran [15];

	do {
		if (user.tagihan == 0){
			strcpy(pembayaran, "LUNAS");
		} else {
			strcpy(pembayaran, "BELUM LUNAS");
		}
		printf("++=========================================++===========================================================++\n");
		printf("||          UNIVERSITAS PROGLAN 2          ||              SISTEM AKADEMIK MAHASISWA                    ||\n");
		printf("||                                         |+===+=======================================================||\n");
		printf("|+=========================================+| 1 | Tambahkan pilihan mata kuliah                         ||\n");
		printf("|| NPM                                     || 2 | Batalkan pilihan mata kuliah                          ||\n");
		printf("||  %s%                          -*s\033[0m|| 3 | Tampilkan pilihan mata kuliah                         ||\n", CYAN, 39, user.npm);
		printf("||=========================================||   |                                                       ||\n");
		printf("|| Nama                                    || 4 | Tampilkan nilai mata kuliah                           ||\n");
		printf("||  %s%                          -*s\033[0m|| 5 | Lihat/cari mata kuliah yang tersedia                  ||\n", BLUE, 39, user.name);
		printf("|| Angkatan                                ||   |                                                       ||\n");
		printf("||  %s%                          -*d\033[0m|| 6 | Lihat tagihan UKT semester ini                        ||\n", MAGENTA, 39, user.batch);
		printf("|| Program Studi                           ||   |                                                       ||\n");
		printf("||  %s%                          -*s\033[0m|| 7 | Panduan Penggunaan Program                            ||\n", CYAN, 39, user.major);
		printf("|| Pembimbing Akademis                     ||   |                                                       ||\n");
		printf("||  %s%s%                        -*s\033[0m|| 8 | Update profil mahasiswa                               ||\n", BLUE, "Prof. ", 33, user.advisorName);
		printf("||  %s%                          -*s\033[0m||   |                                                       ||\n", CYAN, 39, user.advisorNumber);
		printf("|| Status Akademis                         || 9 | Keluar                                                ||\n");
		printf("||  %s%                          -*s\033[0m||===+=======================================================++\n", (strcmp(user.academicStatus, "Aktif") == 0) ? GREEN : RED, 39, user.academicStatus);
		printf("|| Total SKS Lulus                         ||%s  ____  _       _      _   ___                             \033[0m||\n", YELLOW);
		printf("||  %s%                          -*d\033[0m||%s / ___|(_) __ _| | __ / | / _ \\                            \033[0m||\n", GREEN, 39, user.totalPassedCredits, YELLOW);
		printf("|| Total Mutu                              ||%s \\___ \\| |/ _` | |/ / | || | | |                           \033[0m||\n", YELLOW);
		printf("||  %s%                        -*.2f\033[0m||%s  ___) | | (_| |   <  | || |_| |                           \033[0m||\n", GREEN, 39, user.totalGradePoints, YELLOW);
		printf("|| IPK                                     ||%s |____/|_|\\__,_|_|\\_\\ |_(_)___/                            \033[0m||\n", YELLOW);
		printf("||  %s%                        -*.2f\033[0m||%s / ___|  ___  __| | ___ _ __| |__   __ _ _ __   __ _       \033[0m||\n", GREEN, 39, user.gpa, YELLOW);
		printf("|| SKS Diperoleh                           ||%s \\___ \\ / _ \\/ _` |/ _ \\ '__| '_ \\ / _` | '_ \\ / _` |      \033[0m||\n", YELLOW);
		printf("||  %s%                          -*d\033[0m||%s  ___) |  __/ (_| |  __/ |  | | | | (_| | | | | (_| |      \033[0m||\n", GREEN, 39, user.totalCredits, YELLOW);
		printf("|| Status Pembayaran                       ||%s |____/ \\___|\\__,_|\\___|_|  |_| |_|\\__,_|_| |_|\\__,_|      \033[0m||\n", YELLOW);
		printf("||  %s%                          -*s\033[0m||                                                           ||\n", (user.tagihan == 0) ? GREEN : RED, 39, pembayaran, YELLOW);
		printf("++===========================++============++===========================================================++\n");
		printf("|| Grafik Semester Anda :    ||\n");
		printf("||===========================||\n\n");		
		printHistogram(user.semesterGrades, user.semesterSekarang);
		printf("Pilihan: ");
		scanf(" %[^\n]", opsiString);
		opsi = atoi(opsiString);

		switch(opsi) {
			case 1:
				system("cls");
				tambahMataKuliah(&user);
				printf("Press ANY key to continue!");
				getch();
				system("cls");
				break;
			case 2:
				system("cls");
				hapusMataKuliah(&user);
				printf("Press ANY key to continue!");
				getch();
				system("cls");
				break;
			case 3:
				system("cls");
				tampilkanMataKuliah(&user);
				printf("Press ANY key to continue!");
				getch();
				system("cls");
				break;
			case 4:
				system("cls");
				tampilkanNilai(user);
				printf("Press ANY key to continue!");
				getch();
				system("cls");
				break;
			case 5:
				system("cls");
				searchMataKuliah();
				printf("Press ANY key to continue!");
				getch();
				system("cls");
				break;
			case 6:
                system("cls");
                tampilkanTagihan(&user);
                printf("Press ANY key to continue!");
                getch();
                system("cls");
                break;
			case 7:
				system("cls");
				programGuide();
				printf("Press ANY key to continue!");
				getch();
				system("cls");
				break;
			case 8:
				system("cls");
				updateProfile(&user);
				printf("Press ANY key to continue!");
				getch();
				system("cls");
				break;
			case 9:
				system("cls");
				printf("Kembali ke beranda...\n\n");
				writeStudentData(&user, sourceMa);
				writeCourses(&user, sourceAk);
				printf("Press ANY key to continue!");
				getch();
				break;
			default:
				printf("Input tidak valid\n");
				printf("Press ANY key to continue!");
				getch();
				system("cls");
		}
	} while (opsi != 9);
}

//OPTIONS
// CASE 1
void tambahMataKuliah(AcademicUser *user) {
    int choice;

    printf("++====++=========++======================================================++=====++==================++\n");
    printf("|| NO || KODE MK ||                   NAMA MATA KULIAH                   || SKS || SEMESTER         ||\n");
    printf("++====++=========++======================================================++=====++==================++\n");

    // Print available courses
    for (int i = 0; i < sizeof(availableCourses)/sizeof(availableCourses[0]); i++) {
        printf("|| %-2d || %-7s || %s%-52s\033[0m || %s%-3d\033[0m || %-16d ||\n", i + 1, availableCourses[i].courseCode, MAGENTA, availableCourses[i].courseName, GREEN, availableCourses[i].credits, availableCourses[i].semester);
    }

    printf("++====++=========++======================================================++=====++==================++\n\n");
    printf("Masukkan 0 jika tidak ada yang ingin diubah");
    printf("\n\nPilih mata kuliah (masukkan nomor): ");
    scanf("%d", &choice);

    if (choice == 0) {
        return;
    }

    choice--; // To match array index (0-based)

    if (choice >= 0 && choice < sizeof(availableCourses)/sizeof(availableCourses[0])) {
        Course *selectedCourse = &availableCourses[choice];

        // Check if the course is already in the user's course list
        Course *tempCourse = user->courses_head;
        while (tempCourse != NULL) {
            if (strcmp(tempCourse->courseCode, selectedCourse->courseCode) == 0) {
                printf("Mata kuliah sudah diambil.\n");
                return;
            }
            tempCourse = tempCourse->next;
        }

        // Add course to user's list
        if (user->totalCourses < user->maximumCourses) {
            // Add the course to the end of the user's course list
            Course *newCourse = (Course *)malloc(sizeof(Course));
            if (newCourse == NULL) {
                printf("Memory allocation failed.\n");
                return;
            }
            *newCourse = *selectedCourse; // Copy course details

            // Append the new course to the end of the list
            if (user->courses_head == NULL) {
                user->courses_head = newCourse;
            } else {
                Course *lastCourse = user->courses_head;
                while (lastCourse->next != NULL) {
                    lastCourse = lastCourse->next;
                }
                lastCourse->next = newCourse;
            }

            user->totalCourses++;
            printf("Mata kuliah berhasil ditambahkan.\n");
        } else {
            printf("Jumlah mata kuliah yang diambil sudah mencapai maksimum.\n");
        }
    } else {
        printf("Pilihan tidak valid.\n");
    }
}

// CASE 2
void hapusMataKuliah(AcademicUser *user) {
    int choice;

    printf("++====++=======================================================++========++=====++=================++\n");
    printf("|| NO ||                      MATA KULIAH                      ||  KODE  || SKS ||     STATUS      ||\n");
    printf("++====++=======================================================++========++=====++=================++\n");
    // Print the courses currently taken by the user
    Course *currentCourse = user->courses_head;
    int courseIndex = 1;

    if (currentCourse == NULL) {
    printf("++   TIDAK ADA MATA KULIAH YANG DIPILIH                                             ++\n");
    }

    while (currentCourse != NULL) {
        printf("|| %-3d|| %s%-54s\033[0m|| %-6s || %s%-3d\033[0m || %s%s\033[0m ||\n", courseIndex, MAGENTA, currentCourse->courseName, currentCourse->courseCode, GREEN, currentCourse->credits, (currentCourse->status == 0) ? RED : GREEN, (currentCourse->status == 0) ? "Belum Disetujui" : "Telah Disetujui");
        currentCourse = currentCourse->next;
        courseIndex++;
    }
    printf("++====++=======================================================++========++=====++=================++\n\n");
    printf("Masukkan 0 jika tidak ada yang ingin diubah");
    
    printf("\n\nPilih mata kuliah yang akan dibatalkan (masukkan nomor): ");
    scanf("%d", &choice);
    
    if (choice == 0) {
        return;
    }

    choice--; // To match array index (0-based)

    if (choice >= 0) {
        // Find the course to delete
        Course *prevCourse = NULL;
        currentCourse = user->courses_head;
        for (int i = 0; i < choice; i++) {
            prevCourse = currentCourse;
            currentCourse = currentCourse->next;
        }

        if (currentCourse->status == 1) {
            printf("Mata kuliah sudah disetujui dan tidak dapat dibatalkan.\n");
            return;
        }

        if (prevCourse == NULL) {
            // Deleting the first node
            user->courses_head = currentCourse->next;
        } else {
            prevCourse->next = currentCourse->next;
        }

        free(currentCourse);
        user->totalCourses--;
        printf("Mata kuliah berhasil dibatalkan.\n");
    } else {
        printf("Pilihan tidak valid.\n");
    }
}

// CASE 3
void tampilkanMataKuliah(AcademicUser *user) {
    Course *currentCourse = user->courses_head;
    int found = 0, idx = 1;

    printf("++====++=======================================================++========++=====++=================++\n");
    printf("|| NO ||                      MATA KULIAH                      ||  KODE  || SKS ||     STATUS      ||\n");
    printf("++====++=======================================================++========++=====++=================++\n");
    while (currentCourse != NULL) {
        printf("|| %-3d|| %s%-54s\033[0m|| %-6s || %s%-3d\033[0m || %s%s\033[0m ||\n", idx, MAGENTA, currentCourse->courseName, currentCourse->courseCode, GREEN, currentCourse->credits, (currentCourse->status == 0) ? RED : GREEN, (currentCourse->status == 0) ? "Belum Disetujui" : "Telah Disetujui");
        found = 1;
        idx++;
        currentCourse = currentCourse->next;
    }

    if (!found)
        printf("||         BELUM ADA MATA KULIAH YANG DIPILIH                                                      ||\n");
    printf("++====++=======================================================++========++=====++=================++\n");
}

// CASE 4

void bubbleSort(Course **array, int n, int ascending) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if ((ascending && array[j]->score > array[j+1]->score) || (!ascending && array[j]->score < array[j+1]->score)) {
                Course *temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}

Course** createCourseArray(Course *head, int *size) {
    *size = 0;
    Course *current = head;
    while (current != NULL) {
        (*size)++;
        current = current->next;
    }

    Course **array = (Course**)malloc(*size * sizeof(Course*));
    current = head;
    for (int i = 0; i < *size; i++) {
        array[i] = current;
        current = current->next;
    }

    return array;
}

void tampilkanNilai(AcademicUser user) {
    const char* nilaiString[] = {"A","A-","B+", "B","B-","C+", "C", "D+", "D", "E"};
    int jumlahNilai[10] = {0};  

   
    Course *currentCourse = user.courses_head;
    while (currentCourse != NULL) {
        for (int j = 0; j < 10; j++) {
            if (strcmp(currentCourse->grade, nilaiString[j]) == 0) {
                jumlahNilai[j]++;
                break;
            }
        }
        currentCourse = currentCourse->next;
    }
    
    printf("++===========================++\n");
    printf("|| Statistik Nilai:          ||\n");
    printf("++===========================++\n");
    printf("|| Nilai            Jumlah   ||\n");
    int cekNilai = 0;
    for (int i = 0; i < 10; i++) {
        if (jumlahNilai[i] != 0) {
            cekNilai++;
            printf("|| %-15s    %-5d  ||\n", nilaiString[i], jumlahNilai[i]);
        }
    }
    if (cekNilai == 0) {
        printf("|| -                 -       ||\n");
    }
    printf("++===========================++\n\n");

    int option = 0;
    while (option != 1 && option != 2 && option != 3) {
        printf("1. Tampilkan nilai lengkap untuk mata kuliah tertentu\n");
        printf("2. Urutkan mata kuliah berdasarkan score (ascending)\n");
        printf("3. Urutkan mata kuliah berdasarkan score (descending)\n\n");
        printf("Pilihan: ");
        scanf("%d", &option);
    }

    int size;
    Course **courseArray = createCourseArray(user.courses_head, &size);

    if (option == 2 || option == 3) {
        bubbleSort(courseArray, size, option == 2);
    }

    currentCourse = user.courses_head;
    int courseIndex = 1;
    printf("\n++====++=======================================================++========++=========++\n");
    printf("|| NO ||                      MATA KULIAH                      ||  KODE  ||  SCORE  ||\n");
    printf("++====++=======================================================++========++=========++\n");
    for (int i = 0; i < size; i++) {
        if (strcmp(courseArray[i]->grade, "") != 0) {
            printf("|| %-3d|| %s%-54s\033[0m|| %-6s || %s%-7.2f\033[0m ||\n", courseIndex, MAGENTA, courseArray[i]->courseName, courseArray[i]->courseCode, (courseArray[i]->score < 55) ? RED : GREEN, courseArray[i]->score);
            courseIndex++;
        }
    }
    printf("++====++=======================================================++========++=========++\n");

    if (option == 1) {
        // Prompt user to select a course to view grades
        printf("\nPilih nomor matakuliah untuk menampilkan nilai lengkap: ");
        int choice;
        scanf("%d", &choice);
        choice--; // To match array index (0-based)

        // Find the selected course
        system("cls");
        int selectedCourseIndex = 0;
        for (int i = 0; i < size; i++) {
            if (strcmp(courseArray[i]->grade, "") != 0) {
                if (selectedCourseIndex == choice) {
                    printf("\n++==========================================================================++\n");
                    printf("||          NILAI LENGKAP MATAKULIAH                                        ||\n");
                    printf("++==========================================================================++\n");
                    printf("|| Nama Matakuliah   : %s%-52s\033[0m ||\n", MAGENTA, courseArray[i]->courseName);
                    printf("|| Kode Matakuliah   : %s%-52s\033[0m ||\n", MAGENTA, courseArray[i]->courseCode);
                    printf("|| Nilai Kuis        : %s%-52.2f\033[0m ||\n", (courseArray[i]->kuis < 55) ? RED : GREEN, courseArray[i]->kuis);
                    printf("|| Nilai UAS         : %s%-52.2f\033[0m ||\n", (courseArray[i]->uas < 55) ? RED : GREEN, courseArray[i]->uas);
                    printf("|| Nilai UTS         : %s%-52.2f\033[0m ||\n", (courseArray[i]->uts < 55) ? RED : GREEN, courseArray[i]->uts);
                    printf("|| Nilai Tugas       : %s%-52.2f\033[0m ||\n", (courseArray[i]->tugas < 55) ? RED : GREEN, courseArray[i]->tugas);
                    printf("|| Grade             : %s%-52s\033[0m ||\n", (courseArray[i]->score < 55) ? RED : GREEN, courseArray[i]->grade);
                    printf("|| Nilai Rata-rata   : %s%-52.2f\033[0m ||\n", (courseArray[i]->score < 55) ? RED : GREEN, courseArray[i]->score);
                    printf("++==========================================================================++\n\n");
                    free(courseArray);
                    return;
                }
                selectedCourseIndex++;
            }
        }

        printf("Nomor matakuliah yang Anda pilih tidak valid atau tidak memiliki nilai.\n");
    }

    free(courseArray);
}

// CASE 5
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void searchMataKuliah() {
    int found = 0;
    char lowerSearchTerm[100], searchTerm[100];
    printf("Ketik mata kuliah yang ingin anda cari : ");
	scanf(" %[^\n]", &searchTerm);

    strncpy(lowerSearchTerm, searchTerm, sizeof(lowerSearchTerm));
    toLowerCase(lowerSearchTerm);

    printf("++====++=========++======================================================++=====++==================++\n");
    printf("|| NO || KODE MK ||                   NAMA MATA KULIAH                   || SKS || SEMESTER         ||\n");
    printf("++====++=========++======================================================++=====++==================++\n");

    for (int i = 0; i < sizeof(availableCourses) / sizeof(availableCourses[0]); ++i) {
        char lowerCourseCode[10];
        char lowerCourseName[100];
        strncpy(lowerCourseCode, availableCourses[i].courseCode, sizeof(lowerCourseCode));
        strncpy(lowerCourseName, availableCourses[i].courseName, sizeof(lowerCourseName));
        toLowerCase(lowerCourseCode);
        toLowerCase(lowerCourseName);

        if (strstr(lowerCourseCode, lowerSearchTerm) != NULL || 
            strstr(lowerCourseName, lowerSearchTerm) != NULL) {
            printf("|| %-2d || %-7s || %-52s || %-3d || %-16d ||\n", i + 1, availableCourses[i].courseCode, availableCourses[i].courseName, availableCourses[i].credits, availableCourses[i].semester);
            found = 1;
        }
    }

    if (!found) {
        printf("||         TIDAK ADA MATA KULIAH YANG COCOK DENGAN PENCARIAN ANDA                                   ||\n");
    }
    printf("++====++=========++======================================================++=====++==================++\n");
}


// CASE 6
void tampilkanTagihan(AcademicUser *user) {
    printf("Tagihan UKT semester ini: %d\n", user->tagihan);
    if (user->tagihan == 0) {
        printf("Tagihan UKT untuk semester ini telah lunas.\n");
    } 
    else {
        printf("Anda memiliki tagihan UKT sebesar %d. Silakan lakukan pembayaran.\n", user->tagihan);
        printf("Apakah Anda ingin melakukan pembayaran sekarang? (1 untuk ya, 0 untuk tidak): ");
        int bayar;
        scanf("%d", &bayar);
        if (bayar == 1) {
            printf("Pembayaran UKT berhasil dilakukan. Tagihan Anda sekarang adalah 0.\n");
            user->tagihan = 0; // Set tagihan menjadi 0 karena telah dilakukan pembayaran
        } 
        else {
            printf("Pembayaran UKT dibatalkan.\n");
        }
    }
}

// CASE 7
void programGuide() {
    printf("++===========================++===============================++\n");
    printf("||   UNIVERSITAS PROGLAN 2   ||   PANDUAN PENGGUNAAN          ||\n");
    printf("++===========================++===============================++\n");
    printf("|Tujuan program ini adalah untuk melakukan olah data mahasiswa |\n");
    printf("|untuk grading individu, ataupun grading keseluruhan mahasiswa |\n");
    printf("|beserta status mereka sebagai simulasi SIAK sederhana dengan  |\n");
    printf("|fitur-fitur sebagai berikut:                                  |\n");
    printf("|                                                              |\n");
    printf("|1. Mode Dosen:                                                |\n");
    printf("|- Menerima input data nilai mahasiswa                         |\n");
    printf("|- Menghitung data tendencies dari seluruh data nilai mahasiswa|\n");
    printf("|- Mengkonfirmasi status keaktifan masing-masing mahasiswa     |\n");
    printf("|- Mempersetujui matkul yang dipilih oleh mahasiswa            |\n");
    printf("|  berdasarkan batas SKS dan persyaratan nilai/IP              |\n");
    printf("|- Menentukan kelulusan mahasiswa                              |\n");
    printf("|- Menampilkan bagan nilai mahasiswa (tampilan kasar)          |\n");
    printf("|- Menggunakan multithreading untuk efisiensi pada data besar  |\n");
    printf("|  (>50.000 data, untuk proyek akhir ini data yang diberikan   |\n");
    printf("|  hanya sedikit demi menghemat waktu dan size file yang       |\n");
    printf("|  tidak terlalu besar)                                        |\n");
	printf("|                                                              |\n");
    printf("|2. Mode Mahasiswa:                                            |\n");
    printf("|- Memilih matakuliah/kelas untuk satu semester                |\n");
    printf("|- Membayar UKT untuk menjaga status aktif                     |\n");
    printf("|- Melihat Chart/Data nilai semester/semasa kuliah             |\n");
    printf("|++===========================++==============================++\n");
}

// CASE 8
void updateProfile(AcademicUser *user) {
    printf("== Update Profil Mahasiswa ==\n");
    printf("Pilihan:\n");
    printf("1. Ubah Nama\n");
    printf("2. Ubah Password\n");
    printf("3. Kembali ke Menu Utama\n\n");

    int choice;
    printf("Masukkan pilihan: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            printf("Masukkan nama baru: ");
            scanf(" %[^\n]", user->name);
            printf("Nama berhasil diubah!\n");
            break;
        case 2:
            char currentPassword[50];
            char newPassword[50];
            printf("Masukkan password saat ini: ");
            scanf(" %[^\n]", currentPassword);
            // Proses verifikasi password saat ini
            if(strcmp(currentPassword, user->password) == 0) {
                printf("Masukkan password baru: ");
                scanf(" %[^\n]", newPassword);
                strcpy(user->password, newPassword);
                printf("Password berhasil diubah!\n");
            } else {
                printf("Password saat ini salah. Tidak dapat mengubah password.\n");
            }
            break;
        case 3:
            printf("Kembali ke Menu Utama.\n");
            break;
        default:
            printf("Pilihan tidak valid.\n");
    }
}

//FILE HANDLING
// LOAD/READ DATA
void loadStudentData(AcademicUser *student, const char *filename, int *stat) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Nama mahasiswa tidak ditemukan");
        printf("%s", filename);
        *stat = 0;
        return;
    }
    
    fscanf(file, "%s", student->password);
    fscanf(file, "%s", student->npm);
    fscanf(file, " %[^\n]", student->name);
    fscanf(file, "%d", &student->batch);
    fscanf(file, " %[^\n]", student->major);
    fscanf(file, " %[^\n]", student->advisorName);
    fscanf(file, " %[^\n]", student->advisorNumber);
    fscanf(file, "%s", student->academicStatus);
    fscanf(file, "%d", &student->totalPassedCredits);
    fscanf(file, "%f", &student->totalGradePoints);
    fscanf(file, "%f", &student->gpa);
    fscanf(file, "%d", &student->tagihan);
    fscanf(file, "%d", &student->semesterSekarang);
    for (int i = 0; i < 8; i++) {
        fscanf(file, "%f", &student->semesterGrades[i]);
    }
    for (int i = 0; i < 8; i++) {
        fscanf(file, "%d", &student->jumlahNilai[i]);
    }
    fscanf(file, "%d", &student->totalCourses);
    fscanf(file, "%d", &student->maximumCourses);
    fscanf(file, "%d", &student->sksSekarang);
    fscanf(file, "%d", &student->totalCredits);
    
    fclose(file);
}

void loadCourses(AcademicUser *student, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return;
    }

    Course *currentCourse = NULL;
    while (!feof(file)) {
        Course *newCourse = createCourseNode();
        fscanf(file, "%s\n", newCourse->courseCode);
        fscanf(file, " %[^\n]", newCourse->courseName);
        fscanf(file, "%d\n", &newCourse->semester);
        fscanf(file, "%f\n", &newCourse->tugas);
        fscanf(file, "%f\n", &newCourse->uas);
        fscanf(file, "%f\n", &newCourse->uts);
        fscanf(file, "%f\n", &newCourse->kuis);
        fscanf(file, "%f\n", &newCourse->score);
        fscanf(file, "%d\n", &newCourse->credits);
        fscanf(file, "%s\n", newCourse->grade);
        fscanf(file, "%d\n", &newCourse->status);

        if (student->courses_head == NULL) {
            student->courses_head = newCourse;
            currentCourse = newCourse;
        } else {
            currentCourse->next = newCourse;
            currentCourse = newCourse;
        }
    }
    
    fclose(file);
}

// WRITE DATA
void writeStudentData(AcademicUser *student, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open student data file for writing");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s\n", student->password);
    fprintf(file, "%s\n", student->npm);
    fprintf(file, "%s\n", student->name);
    fprintf(file, "%d\n", student->batch);
    fprintf(file, "%s\n", student->major);
    fprintf(file, "%s\n", student->advisorName);
    fprintf(file, "%s\n", student->advisorNumber);
    fprintf(file, "%s\n", student->academicStatus);
    fprintf(file, "%d\n", student->totalPassedCredits);
    fprintf(file, "%.2f\n", student->totalGradePoints);
    fprintf(file, "%.2f\n", student->gpa);
    fprintf(file, "%d\n", student->tagihan);
    fprintf(file, "%d\n", student->semesterSekarang);
    for (int i = 0; i < 8; i++) {
        fprintf(file, "%.2f ", student->semesterGrades[i]);
    }
    fprintf(file,"\n");
    for (int i = 0; i < 8; i++) {
        fprintf(file, "%d ", student->jumlahNilai[i]);
    }
    fprintf(file,"\n");
    fprintf(file, "%d\n", student->totalCourses);
    fprintf(file, "%d\n", student->maximumCourses);
    fprintf(file, "%d\n", student->sksSekarang);
    fprintf(file, "%d\n", student->totalCredits);

    fclose(file);
}

void writeCourses(AcademicUser *student, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open courses file for writing");
        exit(EXIT_FAILURE);
    }

    Course *currentCourse = student->courses_head;
    while (currentCourse != NULL) {
        fprintf(file, "%s\n", currentCourse->courseCode);
        fprintf(file, "%s\n", currentCourse->courseName);
        fprintf(file, "%d\n", currentCourse->semester);
        fprintf(file, "%.2f\n", currentCourse->tugas);
        fprintf(file, "%.2f\n", currentCourse->uas);
        fprintf(file, "%.2f\n", currentCourse->uts);
        fprintf(file, "%.2f\n", currentCourse->kuis);
        fprintf(file, "%.2f\n", currentCourse->score);
        fprintf(file, "%d\n", currentCourse->credits);
        fprintf(file, "%s\n", currentCourse->grade);
        fprintf(file, "%d", currentCourse->status);
        currentCourse = currentCourse->next;
        if (currentCourse != NULL) {
            fprintf(file, "\n");  // Add newline only if there's another course, supaya saat read tidak NULL.
        }
    }
	
    fclose(file);
}

//MISCELLANEOUS
Course* createCourseNode() {
    Course* newCourse = (Course*)malloc(sizeof(Course));
    newCourse->next = NULL;
    return newCourse;
}

void printHistogram(float grade[], int size) {
    int data[size];

    // Parallelize the loop to round the grades
    
    for (int i = 0; i < size; ++i) {
        data[i] = round(grade[i]);
    }

    int MAX = 0; // initialize and declare variables
    int allcounts[MAX_SEMESTERS] = {0}; // store an array of integers
    int yaxis, xaxis = 0;
    int index = 0;
    int counter1 = 0;
    char c = 178;
    char b = 179, y = 192, z = 196;

    // Parallelize the loop to copy data to allcounts
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        allcounts[i] = data[i];
    }

    // Determine max occurring number
    // Use reduction to find the maximum value in parallel
    #pragma omp parallel for reduction(max:MAX)
    for (index = 0; index < size; ++index) {
        if (allcounts[index] >= MAX) {
            MAX = allcounts[index];
        }
    }
    // Printing histogram (cannot be parallelized due to I/O operations)
    for (yaxis = MAX; yaxis >= 0.1; yaxis--) { // yaxis for histogram
        printf("%8d%c", yaxis, b);

        // output data in histogram format
        for (int i = 0; i < size; i++) {
            if (allcounts[i] >= yaxis) {
                printf("%c%c%c%c", c, c, c, c);
            } else {
                printf("    ");
            }
            printf("   ");
        }
        printf("\n");
    }

    printf("%9c", y);

    // loop for ASCII character
    for (counter1 = 0; counter1 < (size * 7); counter1++) {
        printf("%c", z);
    }

    printf("\n");
    printf("     ");

    // loop for xaxis count
    for (xaxis = 0; xaxis < size; xaxis++) {
        printf("%7d", xaxis + 1);
    }
    printf("\n\n");
}

void getAccessMahasiswa(AcademicUser user, int *pass) {
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
    } else {
        *pass = 1;
        system("cls");
    }
}
