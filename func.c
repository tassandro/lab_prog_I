#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "func.h"

struct Student createStudent()
{
    char code[5];
    char name[101];
    char cpf[21];
    struct Student student;
    spacingLine(35, 1, 2);
    printf("Insira o codigo do aluno: ");
    fflush(stdin);
    scanf(" %s", code);
    printf("Insira o nome do aluno: ");
    fflush(stdin);
    scanf(" %[^\n]s", name);
    printf("Insira o CPF do aluno (somente numeros): ");
    fflush(stdin);
    scanf(" %s", cpf);
    strcpy(student.code, code);
    strcpy(student.name, name);
    strcpy(student.cpf, cpf);
    return student;
}

struct Discipline createDiscipline()
{
    char code[5];
    char name[101];
    char teacher[101];
    int credits;
    struct Discipline discipline;
    printf("\nInsira o codigo da disciplina: ");
    fflush(stdin);
    scanf(" %s", code);
    printf("Insira o nome da disciplina: ");
    fflush(stdin);
    scanf(" %[^\n]s", name);
    printf("Insira o professor da disciplina: ");
    fflush(stdin);
    scanf(" %s", teacher);
    printf("Insira a quantidade de creditos da disciplina: ");
    fflush(stdin);
    scanf(" %d", &credits);
    strcpy(discipline.code, code);
    strcpy(discipline.name, name);
    strcpy(discipline.teacher, teacher);
    discipline.credits = credits;
    return discipline;
}

void appendStudent(struct StudentNode **head)
{
    struct StudentNode *newStudent = (struct StudentNode *)malloc(sizeof(struct StudentNode));
    struct Student student = createStudent();
    newStudent->info = student;
    newStudent->next = NULL;
    if (*head == NULL)
    {
        *head = newStudent;
        printf("\nAluno criado com sucesso!\n\n");
        return;
    }
    struct StudentNode *lastNode = *head;
    while (lastNode->next != NULL)
    {
        lastNode = lastNode->next;
    }
    lastNode->next = newStudent;
    printf("\nAluno criado com sucesso!\n\n");
}

void appendDiscipline(struct DisciplineNode **head)
{
    struct DisciplineNode *newDiscipline = (struct DisciplineNode *)malloc(sizeof(struct DisciplineNode));
    struct Discipline discipline = createDiscipline();
    newDiscipline->info = discipline;
    newDiscipline->next = NULL;
    if (*head == NULL)
    {
        *head = newDiscipline;
        printf("\nDisciplina criada com sucesso!\n\n");
        return;
    }
    struct DisciplineNode *lastNode = *head;
    while (lastNode->next != NULL)
    {
        lastNode = lastNode->next;
    }
    lastNode->next = newDiscipline;
    printf("\nDisciplina criada com sucesso!\n\n");
}

void showStudents(struct StudentNode *head)
{
    if (head == NULL)
    {
        spacingLine(35, 1, 2);
        printf("Nao ha alunos cadastrados\n\n");
    }
    while (head != NULL)
    {
        printf("\nCodigo: %s\nNome: %s\nCPF: %s\n\n", head->info.code, head->info.name, head->info.cpf);
        head = head->next;
    }
}

void showDisciplines(struct DisciplineNode *head)
{
    if (head == NULL)
    {
        spacingLine(35, 1, 2);
        printf("Nao ha disciplinas cadastradas\n\n");
    }
    while (head != NULL)
    {
        printf("\nCodigo: %s\nNome: %s\nProfessor: %s\nCreditos: %d\n\n", head->info.code, head->info.name, head->info.teacher, head->info.credits);
        head = head->next;
    }
}


int findStudentByCode(struct StudentNode *head)
{
    struct StudentNode *aux = head;
    char code[5];
    spacingLine(35, 1, 2);
    printf("Insira o codigo do aluno a procurar: ");
    fflush(stdin);
    scanf(" %s", code);
    if (head == NULL)
    {
        printf("\nLista vazia\n");
    }
    while (head != NULL)
    {
        if (strcmp(head->info.code, code) == 0)
        {
            printf("\nAluno encontrado:\n");
            printf("Codigo: %s\nNome: %s\nCPF: %s\n\n", head->info.code, head->info.name, head->info.cpf);
            head = aux;
            return 1;
            break;
        }
        else
        {
            head = head->next;
        }
    }
    if (head == NULL)
    {
        printf("\nAluno nao encontrado");
        head = aux;
        return 0;
    }
}


int findDisciplineByCode(struct DisciplineNode *head)
{
    struct DisciplineNode *aux = head;
    char code[5];
    spacingLine(35, 1, 2);
    printf("Insira o codigo da disciplina a procurar: ");
    fflush(stdin);
    scanf(" %s", code);
    if (head == NULL)
    {
        printf("\nLista vazia\n");
    }
    while (head != NULL)
    {
        if (strcmp(head->info.code, code) == 0)
        {
            printf("\nDisciplina encontrada:\n");
            printf("Codigo: %s\nNome: %s\nProfessor: %s\n\n", head->info.code, head->info.name, head->info.teacher);
            head = aux;
            return 1;
            break;
        }
        else
        {
            head = head->next;
        }
    }
    if (head == NULL)
    {
        printf("\nDisciplina nao encontrada");
        head = aux;
        return 0;
    }
}


void spacingLine(int quantity, int spacingBefore, int spacingAfter)
{
    int i = 0, j = 0, k = 0;
    while (i < spacingBefore)
    {
        printf("\n");
        i++;
    }
    while (j < quantity)
    {
        printf("-");
        j++;
    }
    while (k < spacingAfter)
    {
        printf("\n");
        k++;
    }
}
