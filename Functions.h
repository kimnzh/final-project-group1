void mainMenuMahasiswa(AcademicUser user, int *size);
void addCourse(AcademicUser *user);
void viewCourses(AcademicUser user);
void removeCourse(AcademicUser *user, int *size);
void showGrades(AcademicUser user);
void searchCourse(char searchTerm []);
void payment(AcademicUser *user);
void programGuide();
void updateProfile(AcademicUser *user);
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

void deleteCourse(AcademicUser *user) {
    int choice;

    printf("++===========================++===============================++\n");
    printf("||   UNIVERSITAS PROGLAN 2   ||   DAFTAR MATA KULIAH          ||\n");
    printf("++===========================++===============================++\n");

    // Print the courses currently taken by the user
    Course *currentCourse = user->courses_head;
    int courseIndex = 1;
    while (currentCourse != NULL) {
        printf("|| %d. %-50s %d SKS (%s) ||\n", courseIndex, currentCourse->courseName, currentCourse->credits, currentCourse->status == 0 ? "Belum disetujui" : "Sudah disetujui");
        currentCourse = currentCourse->next;
        courseIndex++;
    }

    printf("++============================================================++\n\n");
    printf("Pilih mata kuliah yang akan dibatalkan (masukkan nomor): ");
    scanf("%d", &choice);
    choice--; // To match array index (0-based)

    if (choice >= 0 && choice < user->totalCourses) {
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

void searchCourse(char searchTerm []) {
    int found = 0;
    printf("++============================================================================++\n");
    printf("|| No | Kode MK |          Nama Mata Kuliah          | SKS | Status           ||\n");
    printf("++============================================================================++\n");

    for (int i = 0; i < sizeof(availableCourses) / sizeof(availableCourses[0]); ++i) {
        // Menggunakan strstr untuk mencari kata kunci tanpa memperhatikan case sensitive
        if (strstr(availableCourses[i].courseCode, searchTerm) != NULL || 
            strstr(availableCourses[i].courseName, searchTerm) != NULL) {
            printf("|| %-2d | %-7s | %-34s | %-3d | %-1s ||\n", i + 1, availableCourses[i].courseCode, 
                   availableCourses[i].courseName, availableCourses[i].credits, 
                   availableCourses[i].status == 0 ? "Belum disetujui" : "Sudah disetujui");
            found = 1;
        }
    }

    if (!found) {
        printf("|| Tidak ada matakuliah yang cocok dengan pencarian Anda                      ||\n");
    }
    printf("++============================================================================++\n");
}

void getAccess(AcademicUser user) {
	int i, ch;
	char buffer[50];

	do {
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
			system("cls");
			printf("Nama atau PASSWORD yang dimasukkan salah\n\n");
			printf("Press ANY key to continue!");
			getch();
			system("cls");
		} else if (strcmp(user.password, buffer) == 0) {
			system("cls");
			return;
		}
	} while (strcmp != 0);
}

void getAccessDosen(Dosen user) {
	int i, ch;
	char buffer[50];

	do {
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
			system("cls");
			printf("Nama atau PASSWORD yang dimasukkan salah\n\n");
			printf("Press ANY key to continue!");
			getch();
			system("cls");
		} else if (strcmp(user.password, buffer) == 0) {
			system("cls");
			return;
		}
	} while (strcmp != 0);
}