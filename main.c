#include "mini_lib.h"
#include <stdlib.h>
#include <sys/stat.h>

//exo 41
void execute_command(char* line) {
    mini_printf("Executing command: ");
    mini_printf(line);
    mini_printf("\n");
}

//exo 41
void load_config() {
    char* home = getenv("HOME");
    if (home == NULL) {
        return; 
    }

    char config_path[512];
    mini_strcpy(home, config_path, sizeof(config_path));
    mini_strcat(config_path, "/.mini_bashrc", sizeof(config_path));

    struct stat st;
    if (stat(config_path, &st) != 0) {
        return;
    }

    MYFILE* config_file = mini_fopen(config_path, 'r');
    if (config_file == NULL) {
        mini_printf("Erreur: Impossible d'ouvrir ~/.mini_bashrc.\n");
        return;
    }

    char line[BUF_SIZE];
    int ch;
    int index = 0;

    while ((ch = mini_fgetc(config_file)) != EOF) {
        if (ch != '\n' && index < BUF_SIZE - 1) {
            line[index++] = (char)ch;
        } else {
            line[index] = '\0';
            execute_command(line);
            index = 0;
        }
    }

    if (index > 0) {
        line[index] = '\0';
        execute_command(line);
    }

    mini_fclose(config_file);
}

//exo 41
int main() {
    initialize_mini_io();

    load_config();

    //exo 12
    mini_printf("Allocation de 3 blocs de mémoire.\n");
    void* ptr1 = mini_calloc(10, sizeof(int));
    if (ptr1 == NULL) {
        mini_printf("Erreur: Échec de l'allocation de ptr1.\n");
        mini_exit();
    }
    mini_printf("ptr1 alloué.\n");

    void* ptr2 = mini_calloc(20, sizeof(int));
    if (ptr2 == NULL) {
        mini_printf("Erreur: Échec de l'allocation de ptr2.\n");
        mini_exit();
    }
    mini_printf("ptr2 alloué.\n");

    void* ptr3 = mini_calloc(30, sizeof(int));
    if (ptr3 == NULL) {
        mini_printf("Erreur: Échec de l'allocation de ptr3.\n");
        mini_exit();
    }
    mini_printf("ptr3 alloué.\n");

    mini_printf("Libération de ptr2.\n");
    mini_free(ptr2);

    mini_printf("Allocation de ptr4 avec une taille égale à ptr2.\n");
    void* ptr4 = mini_calloc(20, sizeof(int));
    if (ptr4 == NULL) {
        mini_printf("Erreur: Échec de l'allocation de ptr4.\n");
        mini_exit();
    }
    mini_printf("ptr4 alloué.\n");

    //exo 16
    mini_printf("Test de mini_printf avec des messages.\n");
    mini_printf("Bonjour, Monde!\n");
    mini_printf("Ceci est un test de mini_printf.\n");

    //exo 19
    char input_buffer[50];
    mini_printf("Veuillez saisir une chaîne de caractères (max 49) : ");
    int chars_read = mini_scanf(input_buffer, 50);
    if (chars_read >= 0) {
        if (chars_read > 0 && input_buffer[chars_read - 1] == '\n') {
            input_buffer[chars_read - 1] = '\0';
            chars_read--;
        }
        mini_printf("Vous avez saisi : ");
        mini_printf(input_buffer);
        mini_printf("\n");
    } else {
        mini_printf("Erreur lors de la saisie.\n");
    }

    /:exo 21
    mini_printf("Test des fonctions de manipulation de chaînes.\n");
    char test_str1[] = "Bonjour, Monde!";
    mini_printf("La longueur de \"");
    mini_printf(test_str1);
    mini_printf("\" est calculée.\n");

    char source[] = "Copier cette chaîne.";
    char destination[50];
    int copied = mini_strcpy(source, destination, sizeof(destination));
    if (copied >= 0) {
        mini_printf("Destination après copie : \"");
        mini_printf(destination);
        mini_printf("\"\n");
    } else {
        mini_printf("Erreur lors de la copie de la chaîne.\n");
    }

    char str_a[] = "ChaineTest";
    char str_b[] = "ChaineTest";
    char str_c[] = "AutreChaine";

    int cmp_result = mini_strcmp(str_a, str_b);
    if (cmp_result == 0) {
        mini_printf("Les chaînes \"");
        mini_printf(str_a);
        mini_printf("\" et \"");
        mini_printf(str_b);
        mini_printf("\" sont identiques.\n");
    } else {
        mini_printf("Les chaînes ne sont pas identiques.\n");
    }

    cmp_result = mini_strcmp(str_a, str_c);
    if (cmp_result != 0) {
        mini_printf("Les chaînes \"");
        mini_printf(str_a);
        mini_printf("\" et \"");
        mini_printf(str_c);
        mini_printf("\" sont différentes.\n");
    } else {
        mini_printf("Les chaînes sont identiques.\n");
    }

    //exo 30
    mini_printf("Test de mini_fread.\n");
    MYFILE* file = mini_fopen("test_file.txt", 'r');
    if (file != NULL) {
        char read_buffer[50];
        int items_read = mini_fread(read_buffer, sizeof(char), 49, file);
        if (items_read != -1) {
            read_buffer[items_read] = '\0';
            mini_printf("Contenu lu du fichier : ");
            mini_printf(read_buffer);
            mini_printf("\n");
        } else {
            mini_printf("Erreur lors de la lecture du fichier.\n");
        }
        mini_fclose(file);
    } else {
        mini_printf("Erreur lors de l'ouverture du fichier.\n");
    }

    //exo 32
    mini_printf("Test de mini_fwrite.\n");
    MYFILE* outFile = mini_fopen("output_test.txt", 'w');
    if (outFile != NULL) {
        char write_buffer[] = "Ceci est un test de mini_fwrite.\n";
        int items_to_write = mini_strlen(write_buffer);
        int items_written = mini_fwrite(write_buffer, sizeof(char), items_to_write, outFile);
        if (items_written == items_to_write) {
            mini_printf("Écriture réussie dans output_test.txt.\n");
        } else {
            mini_printf("Erreur lors de l'écriture dans le fichier.\n");
        }
        mini_fclose(outFile);
    } else {
        mini_printf("Erreur lors de l'ouverture du fichier en écriture.\n");
    }

    //exo 38
    mini_printf("Test de mini_fgetc et mini_fputc.\n");

    MYFILE* inFile = mini_fopen("test_file.txt", 'r');
    if (inFile != NULL) {
        int ch;
        mini_printf("Contenu de test_file.txt :\n");
        while ((ch = mini_fgetc(inFile)) != -1) {
            char c = (char)ch;
            mini_fputc(mini_stdout, c);  
        }
        mini_fflush(mini_stdout); 
        mini_fclose(inFile);
    } else {
        mini_printf("Erreur lors de l'ouverture du fichier en lecture.\n");
    }
    outFile = mini_fopen("fputc_output.txt", 'w');
    if (outFile != NULL) {
        char text[] = "Ceci est un test de mini_fputc.\n";
        for (int i = 0; text[i] != '\0'; i++) {
            if (mini_fputc(outFile, text[i]) == -1) {
                mini_printf("Erreur lors de l'écriture du caractère.\n");
                break;
            }
        }
        mini_fclose(outFile);
        mini_printf("Écriture terminée dans fputc_output.txt.\n");
    } else {
        mini_printf("Erreur lors de l'ouverture du fichier en écriture.\n");
    }

    //exo 18
    mini_printf("Fin du programme, appel de mini_exit.\n");
    mini_exit();
    return 0; 
}
