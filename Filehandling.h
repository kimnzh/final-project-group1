// Function to create a new Course node
Course* createCourseNode() {
    Course* newCourse = (Course*)malloc(sizeof(Course));
    newCourse->next = NULL;
    return newCourse;
}

// Function to load student data from a file
void loadStudentData(AcademicUser *student, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open student data file");
        exit(EXIT_FAILURE);
    }
    
    fscanf(file, "%s", student->npm);
    fscanf(file, " %[^\n]", student->name);
    fscanf(file, "%d", &student->batch);
    fscanf(file, "%s", student->advisorNumber);
    fscanf(file, " %[^\n]", student->advisorName);
    fscanf(file, "%s", student->password);
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
    
    fclose(file);
}

// Function to load advisor data from a file
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

// Function to load courses from a file
void loadCourses(AcademicUser *student, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open courses file");
        exit(EXIT_FAILURE);
    }

    Course *currentCourse = NULL;
    while (!feof(file)) {
        Course *newCourse = createCourseNode();
        fscanf(file, "%s", newCourse->courseCode);
        fscanf(file, " %[^\n]", newCourse->courseName);
        fscanf(file, "%f", &newCourse->tugas);
        fscanf(file, "%f", &newCourse->uas);
        fscanf(file, "%f", &newCourse->uts);
        fscanf(file, "%f", &newCourse->kuis);
        fscanf(file, "%f", &newCourse->score);
        fscanf(file, "%d", &newCourse->credits);
        fscanf(file, "%s", newCourse->grade);
        fscanf(file, "%d", &newCourse->status);

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
