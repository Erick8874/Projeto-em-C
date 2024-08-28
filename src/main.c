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

// Funções de validação (como antes)...
int isValidName(const char *name) { /*...*/ }
int isValidPhone(const char *phone) { /*...*/ }
int isValidEmail(const char *email) { /*...*/ }
int isValidInput(const char *input) { /*...*/ }
int isValidTraining(const char *training) { /*...*/ }
int isValidDate(const char *date) { /*...*/ }
int parseDate(const char *date, struct tm *tm_date) { /*...*/ }

// Adicionar funcionário
void addFuncionario() {
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo de funcionários");
        return;
    }

    Funcionario funcionario;

    printf("Digite o nome do funcionário: ");
    if (fgets(funcionario.name, MAX_NAME_LEN, stdin) == NULL) {
        perror("Erro ao ler o nome do funcionário");
        fclose(file);
        return;
    }
    funcionario.name[strcspn(funcionario.name, "\n")] = '\0';

    if (!isValidInput(funcionario.name) || !isValidName(funcionario.name)) {
        printf("Nome inválido! Apenas letras e espaços são permitidos.\n");
        fclose(file);
        return;
    }

    printf("Digite o telefone do funcionário: ");
    if (fgets(funcionario.phone, MAX_PHONE_LEN, stdin) == NULL) {
        perror("Erro ao ler o telefone do funcionário");
        fclose(file);
        return;
    }
    funcionario.phone[strcspn(funcionario.phone, "\n")] = '\0';

    if (!isValidInput(funcionario.phone) || !isValidPhone(funcionario.phone)) {
        printf("Telefone inválido!\n");
        fclose(file);
        return;
    }

    printf("Digite o e-mail do funcionário: ");
    if (fgets(funcionario.email, MAX_EMAIL_LEN, stdin) == NULL) {
        perror("Erro ao ler o e-mail do funcionário");
        fclose(file);
        return;
    }
    funcionario.email[strcspn(funcionario.email, "\n")] = '\0';

    if (!isValidInput(funcionario.email) || !isValidEmail(funcionario.email)) {
        printf("E-mail inválido!\n");
        fclose(file);
        return;
    }

    if (fprintf(file, "%s;%s;%s\n", funcionario.name, funcionario.phone, funcionario.email) < 0) {
        perror("Erro ao escrever no arquivo de funcionários");
    } else {
        printf("Funcionário adicionado com sucesso!\n");
    }

    fclose(file);
}

// Listar funcionários
void listFuncionarios() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo de funcionários");
        return;
    }

    char line[200];
    printf("Lista de funcionários:\n");
    while (fgets(line, sizeof(line), file)) {
        char *name = strtok(line, ";");
        char *phone = strtok(NULL, ";");
        char *email = strtok(NULL, ";");

        if (name && phone && email) {
            printf("Nome: %s\nTelefone: %s\nE-mail: %s\n", name, phone, email);
        } else {
            printf("Formato de dados inválido no arquivo.\n");
        }
    }

    if (ferror(file)) {
        perror("Erro ao ler o arquivo de funcionários");
    }

    fclose(file);
}

// Adicionar treinamento
void addTreinamento() {
    FILE *file = fopen(TRAINING_FILE, "a");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo de treinamentos");
        return;
    }

    Treinamento treinamento;

    printf("Digite o nome do treinamento: ");
    if (fgets(treinamento.training, MAX_TRAINING_LEN, stdin) == NULL) {
        perror("Erro ao ler o nome do treinamento");
        fclose(file);
        return;
    }
    treinamento.training[strcspn(treinamento.training, "\n")] = '\0';

    if (!isValidTraining(treinamento.training)) {
        printf("Nome do treinamento inválido! Não pode ser vazio.\n");
        fclose(file);
        return;
    }

    printf("Digite a data do treinamento (YYYY-MM-DD): ");
    if (fgets(treinamento.date, MAX_DATE_LEN, stdin) == NULL) {
        perror("Erro ao ler a data do treinamento");
        fclose(file);
        return;
    }
    treinamento.date[strcspn(treinamento.date, "\n")] = '\0';

    if (!isValidDate(treinamento.date)) {
        printf("Data inválida! Use o formato YYYY-MM-DD.\n");
        fclose(file);
        return;
    }

    if (fprintf(file, "%s;%s\n", treinamento.training, treinamento.date) < 0) {
        perror("Erro ao escrever no arquivo de treinamentos");
    } else {
        printf("Treinamento adicionado com sucesso!\n");
    }

    fclose(file);
}

// Listar treinamentos
void listTreinamentos() {
    FILE *file = fopen(TRAINING_FILE, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo de treinamentos");
        return;
    }

    char line[200];
    printf("Lista de treinamentos:\n");
    while (fgets(line, sizeof(line), file)) {
        char *training = strtok(line, ";");
        char *date = strtok(NULL, ";");

        if (training && date) {
            printf("Treinamento: %s\nData: %s\n", training, date);
        } else {
            printf("Formato de dados inválido no arquivo de treinamentos.\n");
        }
    }

    if (ferror(file)) {
        perror("Erro ao ler o arquivo de treinamentos");
    }

    fclose(file);
}

// Notificar novos treinamentos
void* notifyNewTrainings(void* arg) {
    FILE *file = fopen(TRAINING_FILE, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo de treinamentos");
        return NULL;
    }

    printf("Notificação de novos treinamentos:\n");
    char line[200];
    while (fgets(line, sizeof(line), file)) {
        char *training = strtok(line, ";");
        char *date = strtok(NULL, ";");

        if (training && date) {
            printf("Novo treinamento: %s na data %s\n", training, date);
        }
    }

    if (ferror(file)) {
        perror("Erro ao ler o arquivo de treinamentos");
    }

    fclose(file);
    return NULL;
}

// Atualizar status de treinamentos
void* updateTrainingStatus(void* arg) {
    FILE *file = fopen(TRAINING_FILE, "r+");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo de treinamentos");
        return NULL;
    }

    FILE *tempFile = fopen("temp_treinamentos.txt", "w");
    if (tempFile == NULL) {
        perror("Erro ao abrir o arquivo temporário");
        fclose(file);
        return NULL;
    }

    char line[200];
    time_t now = time(NULL);
    struct tm *current_time = localtime(&now); // Usa localtime em vez de localtime_r

    while (fgets(line, sizeof(line), file)) {
        char *training = strtok(line, ";");
        char *date = strtok(NULL, ";");

        if (training && date) {
            struct tm tm_date = {0};
            if (parseDate(date, &tm_date)) {
                double difference = difftime(now, mktime(&tm_date)) / (60 * 60 * 24);

                if (difference > 30) { // Exemplo: considera treinamento como atrasado se mais de 30 dias passaram
                    fprintf(tempFile, "%s;%s (ATRAZADO)\n", training, date);
                } else {
                    fprintf(tempFile, "%s;%s\n", training, date);
                }
            } else {
                fprintf(tempFile, "%s;%s\n", training, date); // Escreve a linha como está se a data for inválida
            }
        }
    }

    if (ferror(file)) {
        perror("Erro ao ler o arquivo de treinamentos");
    }

    fclose(file);
    fclose(tempFile);

    remove(TRAINING_FILE);
    rename("temp_treinamentos.txt", TRAINING_FILE);
    return NULL;
}

// Listar funcionários de um treinamento
void listFuncionariosPorTreinamento(const char* treinamentoNome) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo de funcionários");
        return;
    }

    char line[200];
    printf("Funcionários associados ao treinamento '%s':\n", treinamentoNome);
    while (fgets(line, sizeof(line), file)) {
        char *name = strtok(line, ";");
        char *phone = strtok(NULL, ";");
        char *email = strtok(NULL, ";");

        if (name && phone && email) {
            // Aqui você deve verificar se o funcionário está associado ao treinamento
            // Isso exigiria que a associação seja armazenada em algum lugar
            // Como o código não implementa isso, apenas listamos todos os funcionários
            printf("Nome: %s\nTelefone: %s\nE-mail: %s\n", name, phone, email);
        } else {
            printf("Formato de dados inválido no arquivo.\n");
        }
    }

    if (ferror(file)) {
        perror("Erro ao ler o arquivo de funcionários");
    }

    fclose(file);
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    pthread_t notify_thread, update_thread;
    int choice;
    while (1) {
        printf("\n1. Adicionar funcionário\n2. Listar funcionários\n3. Adicionar treinamento\n4. Listar treinamentos\n5. Notificar novos treinamentos\n6. Atualizar status de treinamentos\n7. Listar funcionários por treinamento\n8. Sair\n");
        printf("Escolha uma opção: ");
        if (scanf("%d", &choice) != 1) {
            printf("Entrada inválida!\n");
            while (getchar() != '\n'); // Limpa o buffer
            continue;
        }
        getchar(); // Consome newline character

        switch (choice) {
            case 1:
                addFuncionario();
                break;
            case 2:
                listFuncionarios();
                break;
            case 3:
                addTreinamento();
                break;
            case 4:
                listTreinamentos();
                break;
            case 5:
                pthread_create(&notify_thread, NULL, notifyNewTrainings, NULL);
                pthread_join(notify_thread, NULL);
                break;
            case 6:
                pthread_create(&update_thread, NULL, updateTrainingStatus, NULL);
                pthread_join(update_thread, NULL);
                break;
            case 7: {
                char treinamentoNome[MAX_TRAINING_LEN];
                printf("Digite o nome do treinamento para listar os funcionários: ");
                fgets(treinamentoNome, MAX_TRAINING_LEN, stdin);
                treinamentoNome[strcspn(treinamentoNome, "\n")] = '\0';
                listFuncionariosPorTreinamento(treinamentoNome);
                break;
            }
            case 8:
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opção inválida!\n");
        }
    }

    return 0;
}

