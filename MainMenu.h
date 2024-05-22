void mainMenuDosen(AcademicUser user,Dosen advisor, int *size) {
	int opsi = -1;
	char opsiString[50];
	do{
			
	}while(1);
}

void mainMenuMahasiswa(AcademicUser user, int *size) {
	int cekNilai;
	int opsi = -1;
	char opsiString[50];
	char search[50];
	char pembayaran [15];

	do {
		if(user.tagihan == 0){
			strcpy(pembayaran, "LUNAS");
		}
		else{
			strcpy(pembayaran, "BELUM LUNAS");
		}
		printf("++===========================++=========================================================++\n");
		printf("||   UNIVERSITAS PROGLAN 2   ||              SISTEM AKADEMIK MAHASISWA                  ||\n");
		printf("||                           |+===+=====================================================||\n");
		printf("|+===========================+| 1 | Tampilkan pilihan mata kuliah                       ||\n");
		printf("|| NPM                       || 2 | Tambah pilihan mata kuliah                          ||\n");
		printf("||  %                     -*s|| 3 | Batalkan pilihan mata kuliah                        ||\n",25,user.npm);
		printf("||===========================||   |                                                     ||\n");
		printf("|| Nama                      || 4 | Tampilkan nilai mata kuliah                         ||\n");
		printf("||  %                     -*s|| 5 | Lihat/cari mata kuliah yang tersedia di             ||\n",25,user.name);
		printf("|| Angkatan                  ||   | semester ini                                        ||\n");
		printf("||  %                     -*d|| 6 | Lihat tagihan UKT semester ini                      ||\n",25,user.batch);
		printf("|| Program Studi             || 7 | Panduan Penggunaan Program                          ||\n");
		printf("||  Teknik Komputer, S1 Reg. || 8 | Update profil mahasiswa                             ||\n");
		printf("|| Pembimbing Akademis       || 9 | Keluar                                              ||\n");
		printf("||  %                     -*s||===+=====================================================++\n",25,user.advisorNumber);
		printf("||  %                     -*s|| ____  _       _      _   ___                            ||\n",25,user.advisorName);
		printf("|| Status Akademis           ||/ ___|(_) __ _| | __ / | / _ \\                           ||\n");
		printf("||  %                     -*s||\\___ \\| |/ _` | |/ / | || | | |                          ||\n",25,user.academicStatus);
		printf("|| Total SKS Lulus           || ___) | | (_| |   <  | || |_| |                          ||\n");
		printf("||  %                     -*d|||____/|_|\\__,_|_|\\_\\ |_(_)___/                           ||\n",25,user.totalPassedCredits);
		printf("|| Total Mutu                ||/ ___|  ___  __| | ___ _ __| |__   __ _ _ __   __ _      ||\n");
		printf("||  %                   -*.2f||\\___ \\ / _ \\/ _` |/ _ \\ '__| '_ \\ / _` | '_ \\ / _` |     ||\n",25,user.totalGradePoints);
		printf("|| IPK                       || ___) |  __/ (_| |  __/ |  | | | | (_| | | | | (_| |     ||\n");
		printf("||  %                   -*.2f|||____/ \\___|\\__,_|\\___|_|  |_| |_|\\__,_|_| |_|\\__,_|     ||\n",25,user.gpa);
		printf("|| SKS Diperoleh             ||                                                         ||\n");
		printf("||  %                     -*d||                                                         ||\n",25,user.totalPassedCredits);
		printf("|| Status Pembayaran         ||                                                         ||\n");
		printf("||  %                     -*s||                                                         ||\n",25,pembayaran);
		printf("++===========================++=========================================================++\n");
		printf("|| Grafik Semester Anda :    ||\n");
		printf("||===========================||\n\n");		
		printHistogram(user.semesterGrades, user.semesterSekarang);
		printf("Pilihan: ");
		scanf(" %[^\n]", opsiString);
		opsi = atoi(opsiString);

		switch(opsi) {
			case 1:
				system("cls");
				TampilkanPilihanMataKuliah(&user);
				printf("Press ANY key to continue!");
				getch();
				system("cls");
				break;
			case 2:
				system("cls");
				addCourse(&user);
				printf("Press ANY key to continue!");
				getch();
				system("cls");
				break;
			case 3:
				system("cls");
				deleteCourse(&user);
				printf("Press ANY key to continue!");
				getch();
				system("cls");
				break;
			case 4:
				system("cls");
				showGrades(user);
				printf("Press ANY key to continue!");
				getch();
				system("cls");
				break;
			case 5:
				system("cls");
				printf("Ketik matakuliah yang ingin anda cari : ");
				scanf(" %[^\n]",&search);
				searchCourse(search);
				printf("Press ANY key to continue!");
				getch();
				system("cls");
				break;
			case 6:
    			system("cls");
    			printf("Tagihan UKT semester ini: %d\n", user.tagihan);
    			if (user.tagihan == 0) {
        			printf("Tagihan UKT untuk semester ini telah lunas.\n");
    			} 
				else {
        			printf("Anda memiliki tagihan UKT sebesar %d. Silakan lakukan pembayaran.\n", user.tagihan);
        			printf("Apakah Anda ingin melakukan pembayaran sekarang? (1 untuk ya, 0 untuk tidak): ");
        			int bayar;
        			scanf("%d", &bayar);
        			if (bayar == 1) {
            			printf("Pembayaran UKT berhasil dilakukan. Tagihan Anda sekarang adalah 0.\n");
            			user.tagihan = 0; // Set tagihan menjadi 0 karena telah dilakukan pembayaran
        			} 
					else {
            			printf("Pembayaran UKT dibatalkan.\n");
        			}
    			}
    			printf("Press ANY key to continue!");
    			getch();
    			system("cls");
    			break;
			case 7:
				system("cls");
				programGuide();
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
				printf("Terimakasih karena sudah menggunakan program ini!\n\n");
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

void showGrades(AcademicUser user) {
    const char* nilaiString[] = {"A", "B+", "B", "C+", "C", "D+", "D", "E"};
    int jumlahNilai[8] = {0};  // Initialize count of each grade to 0
    // Print the list of graded courses
    Course *currentCourse = user.courses_head;
    while (currentCourse != NULL) {
        for (int j = 0; j < 8; j++) {
            if (strcmp(currentCourse->grade, nilaiString[j]) == 0) {
                jumlahNilai[j]++;
                break;
            }
        }
        currentCourse = currentCourse->next;
    }
    printf("||===========================||\n");
    printf("|| Statistik Nilai:          ||\n");
    printf("||===========================||\n");
    printf("|| Nilai            Jumlah   ||\n");
    int cekNilai = 0;
    for (int i = 0; i < 8; i++) {
        if (jumlahNilai[i] != 0) {
            cekNilai++;
            printf("|| %-15s    %-5d  ||\n", nilaiString[i], jumlahNilai[i]);
        }
    }
    if (cekNilai == 0) {
        printf("|| -                 -       ||\n");
    }
    printf("||===========================||\n\n");
    currentCourse = user.courses_head;
    int courseIndex = 1;
    while (currentCourse != NULL) {
        if (strcmp(currentCourse->grade, "") != 0) {
            printf("%d. %-25s (%s)   \n", courseIndex, currentCourse->courseName, currentCourse->courseCode);
            courseIndex++;
        }
        currentCourse = currentCourse->next;
    }

    // Prompt user to select a course to view grades
    printf("\nPilih nomor matakuliah untuk menampilkan nilai lengkap: ");
    int choice;
    scanf("%d", &choice);
    choice--; // To match array index (0-based)

    // Find the selected course
    currentCourse = user.courses_head;
    int selectedCourseIndex = 0;
    while (currentCourse != NULL) {
        if (strcmp(currentCourse->grade, "") != 0) {
            if (selectedCourseIndex == choice) {
                printf("\n++================================================++\n");
                printf("||          NILAI LENGKAP MATAKULIAH              ||\n");
                printf("++================================================++\n");
                printf("|| Nama Matakuliah   : %-26s ||\n", currentCourse->courseName);
                printf("|| Kode Matakuliah   : %-26s ||\n", currentCourse->courseCode);
                printf("|| Nilai Total       : %-26s ||\n", currentCourse->grade);
                printf("|| Nilai Kuis        : %-26.2f ||\n", currentCourse->kuis);
                printf("|| Nilai UAS         : %-26.2f ||\n", currentCourse->uas);
                printf("|| Nilai UTS         : %-26.2f ||\n", currentCourse->uts);
                printf("|| Nilai Tugas       : %-26.2f ||\n", currentCourse->tugas);
                printf("++================================================++\n\n");
                return;
            }
            selectedCourseIndex++;
        }
        currentCourse = currentCourse->next;
    }

    printf("Nomor matakuliah yang Anda pilih tidak valid atau tidak memiliki nilai.\n");
}




void printHistogram(float *grade, int size) {
	int data[size];
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

    for (int i = 0; i < size; i++) {
        allcounts[i] = data[i];
    }

    // Determine max occurring number
    do {
        if (allcounts[index] >= MAX) {
            MAX = allcounts[index];
        }
        index++;
    } while (index < size);
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

void updateProfile(AcademicUser *user) {
    printf("== Update Profil Mahasiswa ==\n");
    printf("Pilihan:\n");
    printf("1. Ubah Nama\n");
    printf("2. Ubah Password\n");
    printf("3. Kembali ke Menu Utama\n");

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