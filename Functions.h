void mainMenuMahasiswa(AcademicUser user, int *size);
void addCourse(AcademicUser *user);
void viewCourses(AcademicUser user);
void removeCourse(AcademicUser *user, int *size);
void showGrades(AcademicUser user);
void searchCourse(AcademicUser user, int size);
void payment(AcademicUser user, int size);
void programGuide();
void updateProfile(AcademicUser *user, int *size);
void saveData(AcademicUser user, int size);
void printHistogram(float* grade, int size);
void approveCourse(AcademicUser *user, int *size);
void createNewStudent(AcademicUser *newStudent, Dosen availableAdvisors[]);
void initializeStudent(AcademicUser *newStudent);
void printAvailableAdvisors(Dosen availableAdvisors[]);
void selectAdvisor(AcademicUser *newStudent, Dosen availableAdvisors[]);

void addCourse(AcademicUser *user) {
    int choice;

    printf("++===========================++===============================++\n");
    printf("||   UNIVERSITAS PROGLAN 2   ||   DAFTAR MATA KULIAH          ||\n");
    printf("++===========================++===============================++\n");

    // Print available courses
    for (int i = 0; i < sizeof(availableCourses)/sizeof(availableCourses[0]); i++) {
        printf("|| %d. %-50s %d SKS ||\n", i + 1, availableCourses[i].courseName, availableCourses[i].credits);
    }

    printf("++============================================================++\n\n");
    printf("Pilih mata kuliah (masukkan nomor): ");
    scanf("%d", &choice);
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
            newCourse->status = 0; // Set status to not approved
            newCourse->next = NULL;

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

void TampilkanPilihanMataKuliah(AcademicUser *user) {
    Course *currentCourse = user->courses_head;
    int found = 0;

    printf("++===========================++\n");
    printf("||   Pilihan Mata Kuliah     ||\n");
    printf("++===========================++\n");
    while (currentCourse != NULL) {
        if (currentCourse->status == 0) {
            printf("Kode Matakuliah: %s\n", currentCourse->courseCode);
            printf("Nama Matakuliah: %s\n", currentCourse->courseName);
            printf("SKS: %d\n", currentCourse->credits);
            printf("Status: %s\n\n", currentCourse->status == 0 ? "Belum Disetujui" : "Telah Disetujui");
            found = 1;
        }
        currentCourse = currentCourse->next;
    }

    if (!found) {
        printf("Maaf, anda belum memilih matakuliah untuk semester ini\n");
    }
}
