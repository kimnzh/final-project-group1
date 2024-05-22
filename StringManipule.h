void lowercase(char *string) {
    while (*string) {
        *string = tolower(*string);
        string++;
    }
}

void append(char *string, char append[]) {
    int sizeString = strlen(string);
    int sizeAppend = strlen(append);
    int i;

    for (i = 0; i < sizeAppend; i++) {
        string[sizeString + i] = append[i];
    }
}