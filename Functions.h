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
    int courseIndex = 1; // Used for displaying course index
    Course *currentCourse = user->courses_head;

    printf("++===========================++===============================++\n");
    printf("||   UNIVERSITAS PROGLAN 2   ||   DAFTAR MATA KULIAH          ||\n");
    printf("++===========================++===============================++\n");

    // Print available courses
    while (currentCourse != NULL) {
        printf("|| %d. %-50s %d SKS ||\n", courseIndex, currentCourse->courseName, currentCourse->credits);
        currentCourse = currentCourse->next;
        courseIndex++;
    }

    printf("++============================================================++\n\n");
    printf("Pilih mata kuliah (masukkan nomor): ");
    scanf("%d", &choice);
    choice--; // To match array index (0-based)

    // Find the chosen course
    currentCourse = user->courses_head;
    for (int i = 0; i < choice && currentCourse != NULL; i++) {
        currentCourse = currentCourse->next;
    }

    if (currentCourse != NULL) {
        // Check if the course is already in the user's course list
        Course *tempCourse = user->courses_head;
        while (tempCourse != NULL) {
            if (strcmp(tempCourse->courseCode, currentCourse->courseCode) == 0) {
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
            *newCourse = *currentCourse; // Copy course details
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
