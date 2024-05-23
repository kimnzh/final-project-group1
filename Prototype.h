//MODE MAHASISWA
// MAIN MENU
void mainMenuMahasiswa(AcademicUser user, int *size, char sourceMa[], char sourceAk[]);
// OPTIONS
void TampilkanPilihanMataKuliah(AcademicUser *user);
void addCourse(AcademicUser *user);
void deleteCourse(AcademicUser *user);
void showGrades(AcademicUser user);
void searchCourse(char searchTerm []);
void tampilkanTagihan(AcademicUser *user);
void programGuide();
void updateProfile(AcademicUser *user);
// FILE HANDLING
void loadStudentData(AcademicUser *student, const char *filename, int *stat);
void loadCourses(AcademicUser *student, const char *filename);
void writeStudentData(AcademicUser *student, const char *filename);
void writeCourses(AcademicUser *student, const char *filename);
// MISCELLANEOUS
Course* createCourseNode();
void printHistogram(float *grade, int size);
void getAccessMahasiswa(AcademicUser user, int *pass);

//MODE DOSEN
// MAIN MENU
void mainMenuDosen(AcademicUser user, Dosen advisor, int *size);
// OPTIONS
void pilihMahasiswa(AcademicUser user);
void beriNilai(AcademicUser *user);
void setujuiMatakuliah(AcademicUser *user);
// FILE HANDLING
void loadAdvisorData(Dosen *advisor, const char *filename);
void writeAdvisorData(Dosen *advisor, const char *filename);
// MISCELLANEOUS
void getAccessDosen(Dosen user, int *pass);
