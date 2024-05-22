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

// Function to write student data to a file
void writeStudentData(AcademicUser *student, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open student data file for writing");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s\n", student->npm);
    fprintf(file, "%s\n", student->name);
    fprintf(file, "%d\n", student->batch);
    fprintf(file, "%s\n", student->advisorNumber);
    fprintf(file, "%s\n", student->advisorName);
    fprintf(file, "%s\n", student->password);
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

    fclose(file);
}

// Function to write advisor data to a file
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

// Function to write courses to a file
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
        fprintf(file, "%.2f\n", currentCourse->tugas);
        fprintf(file, "%.2f\n", currentCourse->uas);
        fprintf(file, "%.2f\n", currentCourse->uts);
        fprintf(file, "%.2f\n", currentCourse->kuis);
        fprintf(file, "%.2f\n", currentCourse->score);
        fprintf(file, "%d\n", currentCourse->credits);
        fprintf(file, "%s\n", currentCourse->grade);
        fprintf(file, "%d\n", currentCourse->status);
        currentCourse = currentCourse->next;
    }
	
    fclose(file);
}

