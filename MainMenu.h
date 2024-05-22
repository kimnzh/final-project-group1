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

	do {
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
				
				printf("Press ANY key to continue!");
				getch();
				system("cls");
				break;
			case 6:
				system("cls");
				
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

    // Count occurrences of each grade from the list of courses
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

    // Display the results
    printf("||===========================||\n");
    printf("|| Statistik Nilai:          ||\n");
    printf("||===========================||\n");
    printf("|| Nilai            Jumlah   ||\n");
    int cekNilai = 0;
    for (int i = 0; i < 8; i++) {
        if (jumlahNilai[i] != 0) {
            cekNilai++;
            printf("|| %-15s    %-5d ||\n", nilaiString[i], jumlahNilai[i]);
        }
    }
    if (cekNilai == 0) {
        printf("|| -                 -       ||\n");
    }
    printf("||===========================||\n");      
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
