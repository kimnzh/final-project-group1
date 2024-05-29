void tambahDataMahasiswa() {
    int i, ch, stat = 0;
    char nama[100], password[50], major[50], confirm;
    int batch, opsiMajor, statMajor;

    printf("Masukkan nama mahasiswa: ");
    scanf(" %[^\n]", nama);
    printf("Buat PASSWORD: ");
    scanf("%s", &password);
    printf("\nTahun Angkatan : ");
    scanf("%d", &batch);
    printf("\n1) Teknik Komputer, S1 Reg.");
    printf("\n2) Teknik Komputer, S1 Par.");
    do {
        printf("\nJurusan (1 / 2) : ");
        scanf("%d", &opsiMajor);
        if (opsiMajor == 1) {
            statMajor = 1;
            strcpy(major, "Teknik Komputer, S1 Reg.");
        } else if (opsiMajor == 2) {
            statMajor = 1;
            strcpy(major, "Teknik Komputer, S1 Par.");
        } else {
            statMajor = 0;
            printf("INPUT TIDAK VALID!");
        }
    } while (!statMajor);

    getchar();

    system("cls");
    while (stat != 1) {
        char buff;
        printf("Nama     : %s\n", nama);
        printf("PASSWORD : %s\n", password);
        printf("Angkatan : %d\n", batch);
        printf("Jurusan  : %s\n\n", major);

        printf("Apakah Anda yakin untuk menyimpan? (y / n) : ");
        scanf("%c", &confirm);

        if (confirm == 'y') {
            stat = 1;
        } else if (confirm == 'n') {
            printf("Data tidak berhasil ditambah\n");
            return;
        } else {
            system("cls");
            printf("INPUT TIDAK VALID!\n\n");
        }
    };

    char dirName[100] = "Database/DatabaseMahasiswa/data_";
    append(dirName, nama);

    if (_mkdir(dirName) == 0) {
        printf("\nDatabase berhasil ditambahkan!\n");
    } else {
        perror("Gagal membuat database");
    }

    char sourceMa[100], sourceAk[100];
    char sourceDo[100] = "Database/DatabaseDosen/allData.txt";
    strcpy(sourceMa, dirName);
    strcpy(sourceAk, dirName);
    append(sourceMa, "/mahasiswa.txt");
    append(sourceAk, "/akademik.txt");

    FILE *fileDo = fopen(sourceDo, "r");

    char **tempName = NULL;
    char **tempNIP = NULL;
    int idx = 0;

    while (!feof(fileDo)) {
        tempName = (char **)realloc(tempName, (idx + 1) * sizeof(char *));
        tempName[idx] = (char *)malloc(50 * sizeof(char));
        tempNIP = (char **)realloc(tempNIP, (idx + 1) * sizeof(char *));
        tempNIP[idx] = (char *)malloc(20 * sizeof(char));

        fscanf(fileDo, " %[^\n]", tempName[idx]);
        fscanf(fileDo, "%s", tempNIP[idx]);
        idx++;
    }

    int advisorIndex = generateAdvisorIndex(idx);

    fclose(fileDo);

    int NPM = generateNPM(batch);


    FILE *fileMa = fopen(sourceMa, "w");

    fprintf(fileMa, "%s\n", password);
    fprintf(fileMa, "%lu\n", NPM);
    fprintf(fileMa, "%s\n", nama);
    fprintf(fileMa, "%d\n", batch);
    fprintf(fileMa, "%s\n", major);
    fprintf(fileMa, "%s\n", tempName[advisorIndex]);
    fprintf(fileMa, "%s\n", tempNIP[advisorIndex]);
    fprintf(fileMa, "%s\n", "Kosong");
    fprintf(fileMa, "%d\n", 0);
    fprintf(fileMa, "%.2f\n", 0.00);
    fprintf(fileMa, "%.2f\n", 0.00);
    fprintf(fileMa, "%d\n", 1000000);
    fprintf(fileMa, "%d\n", 1);
    for (int i = 0; i < 8; i++) {
        fprintf(fileMa, "%.2f ", 0.00);
    }
    fprintf(fileMa,"\n");
    for (int i = 0; i < 8; i++) {
        fprintf(fileMa, "%d ", 0);
    }
    fprintf(fileMa,"\n");
    fprintf(fileMa, "%d\n", 0);
    fprintf(fileMa, "%d\n", 70);
    fprintf(fileMa, "%d\n", 0);
    fprintf(fileMa, "%d\n", 0);

    fclose(fileMa);

    FILE *fileAk = fopen(sourceAk, "w");
    fclose(fileAk);

    char doSource[100] = "Database/DatabaseDosen/data_dosen_";
    append(doSource, tempName[advisorIndex]);
    append(doSource, ".txt");

    FILE *doFile = fopen(doSource, "a");

    fprintf(doFile, "%s\n", nama);
    fprintf(doFile, "%lu\n", NPM);

    fclose(doFile);

    FILE *fileData = fopen("Database/DatabaseMahasiswa/allData.txt", "a");

    fprintf(fileData, "%s\n", nama);
    fprintf(fileData, "%lu\n", NPM);

    fclose(fileData);

    #pragma omp parallel for
    for (int i = 0; i < idx; i++) {
        free(tempName[i]);
        free(tempNIP[i]);
    }
    free(tempName);
    free(tempNIP);
}

int generateNPM(int batch) {
    srand(time(NULL));
    int i, ranNum;
    unsigned NPM = batch % 100;

    for (i = 0; i < 8; i++) {
        ranNum = rand() % (10);
        NPM = NPM * 10 + ranNum;
    }

    return NPM;
}

int generateAdvisorIndex(int idx) {
    srand(time(NULL));

    return (rand() % idx) + 1;
}

void tambahDataDosen() {
    int i, stat = 0;
    char nama[50], password[20], confirm;

    printf("Masukkan nama Dosen: ");
    scanf(" %[^\n]", nama);
    printf("Buat PASSWORD: ");
    scanf("%s", &password);

    char dirName[100] = "Database/DatabaseDosen/data_dosen_";
    append(dirName, nama);
    append(dirName, ".txt");

    FILE *file = fopen(dirName, "r");

    if (file != NULL) {
        printf("Nama dosen sudah ada.\n");
        return;
    }

    fclose(file);

    getchar();

    system("cls");
    while (stat != 1) {
        char buff;
        printf("Nama     : %s\n", nama);
        printf("PASSWORD : %s\n\n", password);

        printf("Apakah Anda yakin untuk menyimpan? (y / n) : ");
        scanf("%c", &confirm);

        if (confirm == 'y') {
            stat = 1;
        } else if (confirm == 'n') {
            printf("Data tidak berhasil ditambah\n");
            return;
        } else {
            system("cls");
            printf("INPUT TIDAK VALID!\n\n");
        }
    };


    char NIP[20];
    generateNIP(NIP);

    FILE *fileDo = fopen(dirName, "w");

    fprintf(fileDo, "%s\n", NIP);
    fprintf(fileDo, "%s\n", nama);
    fprintf(fileDo, "%s\n\n", password);

    fclose(fileDo);

    FILE *fileData = fopen("Database/DatabaseDosen/allData.txt", "a");

    fprintf(fileData, "%s\n", nama);
    fprintf(fileData, "%s\n", NIP);

    fclose(fileData);
}

void generateNIP(char NIP[]) {
    srand(time(NULL));
    int i, ranNum;

    for (i = 0; i < 15; i++) {
        NIP[i] = '0' + (rand() % 10);
    }
    NIP[15] = '\0';
}