//MODE MAHASISWA
// MAIN MENU
void mainMenuMahasiswa(AcademicUser user, int *size, char sourceMa[], char sourceAk[]);
// OPTIONS
void tambahMataKuliah(AcademicUser *user);
void hapusMataKuliah(AcademicUser *user);
void tampilkanMataKuliah(AcademicUser *user);
Course* sortCoursesByScore(Course *head, int ascending);
void tampilkanNilai(AcademicUser user);
void toLowerCase(char *str);
void searchMataKuliah();
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
void printHistogram(float grade[], int size);
void getAccessMahasiswa(AcademicUser user, int *pass);

//MODE DOSEN
// MAIN MENU
void mainMenuDosen(AcademicUser user, Dosen advisor, int *size);
// OPTIONS
void pilihMahasiswa(AcademicUser user, Dosen dosen);
void beriNilai(AcademicUser *user);
void setujuiMatakuliah(AcademicUser *user);
// FILE HANDLING
void loadAdvisorData(Dosen *advisor, const char *filename, int *stat);
void writeAdvisorData(Dosen *advisor, const char *filename);
// MISCELLANEOUS
void getAccessDosen(Dosen user, int *pass);

//MODE ADMIN
void tambahDataMahasiswa();
int generateNPM(int batch);
int generateAdvisorIndex(int idx);
void tambahDataDosen();
void generateNIP(char NIP[]);