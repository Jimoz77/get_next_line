/* #include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
    int fd;
    char *line;

    // Ouvrir le fichier en lecture seule
    fd = open("invalid fd", O_RDONLY);
     if (fd == -1)
    {
        perror("Erreur lors de l'ouverture du fichier");
        return (1);
    }

    Lire et afficher chaque ligne du fichier
    while ((line = get_next_line(100)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

Fermer le fichier
    close(fd);
    return (0);
}*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h" // Assurez-vous d'inclure votre propre fichier header

int next_read_error = 0;
int res = 1; // Suppose que res est une variable globale dans votre programme
FILE *errors_file;

void test_gnl(int fd, const char *expected)
{
    char *line = get_next_line(fd);
    if ((line == NULL && expected != NULL) || (line != NULL && expected == NULL) || (line && strcmp(line, expected) != 0)) {
        fprintf(errors_file, "Expected: %s, but got: %s\n", expected, line);
    }
    free(line);
}

int main()
{
    errors_file = fopen("errors.log", "w"); // Fichier où vous enregistrez les erreurs
    if (errors_file == NULL) {
        perror("Failed to open errors.log");
        return 1;
    }

    char *name = "read_error.txt";
    int fd = open(name, O_RDONLY);

    if (fd < 0) {
        perror("Failed to open file");
        return 1;
    }

    test_gnl(fd, "aaaaaaaaaa\n"); // Test 1
    test_gnl(fd, "bbbbbbbbbb\n"); // Test 2

    // Simuler une erreur de lecture
    next_read_error = 1;
    if (BUFFER_SIZE > 100) {
        char *temp;
        do {
            temp = get_next_line(fd);
            free(temp);
        } while (temp != NULL);
    }
    test_gnl(fd, NULL); // Test 3
    next_read_error = 0;

    close(fd);
    fd = open(name, O_RDONLY);

    if (fd < 0) {
        perror("Failed to reopen file");
        return 1;
    }

    test_gnl(fd, "aaaaaaaaaa\n"); // Test 4
    test_gnl(fd, "bbbbbbbbbb\n"); // Test 5
    test_gnl(fd, "cccccccccc\n"); // Test 6
    test_gnl(fd, "dddddddddd\n"); // Test 7
    test_gnl(fd, NULL); // Test 8

    if (res != 1) {
        fprintf(errors_file, "Probable reason" ": You should clear the static buffer when a call to read returns -1\n");
    }

    fclose(errors_file);
    close(fd);

    return 0;
}
