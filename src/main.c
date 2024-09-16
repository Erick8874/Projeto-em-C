#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <time.h>
#include <pthread.h>

#define FILENAME "funcionarios.txt"
#define TRAINING_FILE "treinamentos.txt"
#define MAX_NAME_LEN 50
#define MAX_PHONE_LEN 15
#define MAX_EMAIL_LEN 50
#define MAX_TRAINING_LEN 100
#define MAX_DATE_LEN 11

typedef struct {
    char name[MAX_NAME_LEN];
    char phone[MAX_PHONE_LEN];
    char email[MAX_EMAIL_LEN];
} Funcionario;

typedef struct {
    char training[MAX_TRAINING_LEN];
    char date[MAX_DATE_LEN];
} Treinamento;

// Funções de validação
int isValidName(const char *name) {
    for (size_t i = 0; i < strlen(name); i++)
        if (!isalpha(name[i]) && !isspace(name[i])) return 0;
    return 1;
}

int isValidPhone(const char *phone) {
    return strlen(phone) == 14 &&
           phone[0] == '(' && phone[3] == ')' &&
           phone[9] == '-' &&
           strspn(phone + 1, "0123456789") == 2 &&
           strspn(phone + 4, "0123456789") == 5 &&
           strspn(phone + 10, "0123456789") == 4;
}

int isValidEmail(const char *email) {
    return strchr(email, '@') != NULL;
}

int isValidDate(const char *date, struct tm *tm_date) {
    return sscanf(date, "%4d-%2d-%2d", &tm_date->tm_year, &tm_date->tm_mon, &tm_date->tm_mday) == 3 &&
           (tm_date->tm_year -= 1900, tm_date->tm_mon -= 1, mktime(tm_date) != -1);
}

// Adicionar ou listar funcionários
void addFuncionario() {
    FILE *file = fopen(FILENAME, "a");
    if (!file) { perror("Erro ao abrir o arquivo de funcionários"); return; }

    Funcionario f;
    printf("Digite o nome do funcionário: ");
    fgets(f.name, MAX_NAME_LEN, stdin);
    f.name[strcspn(f.name, "\n")] = '\0';
    if (!isValidName(f.name)) { printf("Nome inválido!\n"); fclose(file); return; }

    printf("Digite o telefone do funcionário: ");
    fgets(f.phone, MAX_PHONE_LEN, stdin);
    f.phone[strcspn(f.phone, "\n")] = '\0';
    if (!isValidPhone(f.phone)) { printf("Telefone inválido!\n"); fclose(file); return; }

    printf("Digite o e-mail do funcionário: ");
    fgets(f.email, MAX_EMAIL_LEN, stdin);
    f.email[strcspn(f.email, "\n")] = '\0';
    if (!isValidEmail(f.email)) { printf("E-mail inválido!\n"); fclose(file); return; }

    fprintf(file, "%s;%s;%s\n", f.name, f.phone, f.email);
    printf("Funcionário adicionado com sucesso!\n");
    fclose(file);
}

void listFuncionarios() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) { perror("Erro ao abrir o arquivo de funcionários"); return; }

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        char *name = strtok(line, ";");
        char *phone = strtok(NULL, ";");
        char *email = strtok(NULL, ";");
        if (name && phone && email) {
            printf("Nome: %s\nTelefone: %s\nE-mail: %s\n", name, phone, email);
        } else {
            printf("Formato de dados inválido.\n");
        }
    }
    fclose(file);
}

// Adicionar ou listar treinamentos
void addTreinamento() {
    FILE *file = fopen(TRAINING_FILE, "a");
    if (!file) { perror("Erro ao abrir o arquivo de treinamentos"); return; }

    Treinamento t;
    printf("Digite o nome do treinamento: ");
    fgets(t.training, MAX_TRAINING_LEN, stdin);
    t.training[strcspn(t.training, "\n")] = '\0';
    if (strlen(t.training) == 0) { printf("Nome do treinamento inválido!\n"); fclose(file); return; }

    printf("Digite a data do treinamento (YYYY-MM-DD): ");
    fgets(t.date, MAX_DATE_LEN, stdin);
    t.date[strcspn(t.date, "\n")] = '\0';

    struct tm tm_date = {0};
    if (!isValidDate(t.date, &tm_date)) { printf("Data inválida!\n"); fclose(file); return; }

    fprintf(file, "%s;%s\n", t.training, t.date);
    printf("Treinamento adicionado com sucesso!\n");
    fclose(file);
}

void listTreinamentos() {
    FILE *file = fopen(TRAINING_FILE, "r");
    if (!file) { perror("Erro ao abrir o arquivo de treinamentos"); return; }

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        char *training = strtok(line, ";");
        char *date = strtok(NULL, ";");
        if (training && date) {
            printf("Treinamento: %s\nData: %s\n", training, date);
        } else {
            printf("Formato de dados inválido.\n");
        }
    }
    fclose(file);
}

// Notificar e atualizar treinamentos
void* notifyNewTrainings(void* arg) {
    FILE *file = fopen(TRAINING_FILE, "r");
    if (!file) { perror("Erro ao abrir o arquivo de treinamentos"); return NULL; }

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        char *training = strtok(line, ";");
        char *date = strtok(NULL, ";");
        if (training && date) {
            printf("Novo treinamento: %s na data %s\n", training, date);
        }
    }
    fclose(file);
    return NULL;
}

void* updateTrainingStatus(void* arg) {
    FILE *file = fopen(TRAINING_FILE, "r");
    if (!file) { perror("Erro ao abrir o arquivo de treinamentos"); return NULL; }

    FILE *tempFile = fopen("temp_treinamentos.txt", "w");
    if (!tempFile) { perror("Erro ao abrir o arquivo temporário"); fclose(file); return NULL; }

    char line[200];
    time_t now = time(NULL);
    while (fgets(line, sizeof(line), file)) {
        char *training = strtok(line, ";");
        char *date = strtok(NULL, ";");
        if (training && date) {
            struct tm tm_date = {0};
            if (isValidDate(date, &tm_date)) {
                double days = difftime(now, mktime(&tm_date)) / (60 * 60 * 24);
                fprintf(tempFile, "%s;%s%s\n", training, date, days > 30 ? " (ATRAZADO)" : "");
            } else {
                fprintf(tempFile, "%s;%s\n", training, date);
            }
        }
    }
    fclose(file);
    fclose(tempFile);
    remove(TRAINING_FILE);
    rename("temp_treinamentos.txt", TRAINING_FILE);
    return NULL;
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    pthread_t notify_thread, update_thread;
    int choice;
    while (1) {
        printf("\n1. Adicionar funcionário\n2. Listar funcionários\n3. Adicionar treinamento\n4. Listar treinamentos\n5. Notificar novos treinamentos\n6. Atualizar status de treinamentos\n7. Sair\n");
        printf("Escolha uma opção: ");
        if (scanf("%d", &choice) != 1) {
            printf("Entrada inválida!\n");
            while (getchar() != '\n'); // Limpa o buffer
            continue;
        }
        getchar(); // Consome o caractere de nova linha

        switch (choice) {
            case 1: addFuncionario(); break;
            case 2: listFuncionarios(); break;
            case 3: addTreinamento(); break;
            case 4: listTreinamentos(); break;
            case 5: pthread_create(&notify_thread, NULL, notifyNewTrainings, NULL); pthread_join(notify_thread, NULL); break;
            case 6: pthread_create(&update_thread, NULL, updateTrainingStatus, NULL); pthread_join(update_thread, NULL); break;
            case 7: printf("Saindo...\n"); return 0;
            default: printf("Opção inválida!\n");
        }
    }
    return 0;
}
