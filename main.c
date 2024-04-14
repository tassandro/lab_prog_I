/*

SISTEMA ACADÊMICO

Disciplina: Laboratório de Programação
Professor: Cel Duarte
Linguagem: C

Alunos:
Tassandro Cavalcante Leitão (TASSANDRO), nº 22044
Vitor Luis Petralanda Alexandrino (PETRALANDA), nº 22059

*/

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defines
#define STUDENT_CODE_SIZE 6
#define DISCIPLINE_CODE_SIZE 5
#define NAME_SIZE 101
#define CPF_SIZE 14
#define PERIOD_SIZE 7
#define LINE_SIZE 241
#define endl printf("\n")

// Structs

// Student struct
typedef struct Student {
    char code[STUDENT_CODE_SIZE];
    char name[NAME_SIZE];
    char cpf[CPF_SIZE];
    int disciplinesLength; // How many disciplines this student is registered in
    struct DisciplineNode *currentDisciplines; // Linked list of disciplines this student is registered in
} Student;

// Student linked list node struct
typedef struct StudentNode {
    struct Student info;
    struct StudentNode *next;    
} StudentNode;

// Discipline struct
typedef struct Discipline {
    char code[DISCIPLINE_CODE_SIZE];
    char name[NAME_SIZE];
    char teacher[NAME_SIZE];
    int credits;
    char period[PERIOD_SIZE];
    int studentsLength; // How many students are registered in this discipline
    struct StudentNode *currentStudents; // Linked list of students registered in this discipline
} Discipline;

// Discipline linked list node struct
typedef struct DisciplineNode {
    struct Discipline info;
    struct DisciplineNode *next;
} DisciplineNode;

// Functions Prototypes

// Student general functions
Student createStudent();
void showStudents(StudentNode *head);
void appendStudent(StudentNode **head);
void pushStudent(StudentNode **head, Student student);
int findStudentByCode(StudentNode *head);
int deleteStudentByCode(StudentNode **head, DisciplineNode **headDiscipline);
void showDisciplinesFromStudentCode(StudentNode *head);
void showStudentsFromPeriod(StudentNode *head);

// Updates students current disciplines and also updates discipline's current students
int updateDisciplines(StudentNode *headStudent, DisciplineNode *headDiscipline);

// Discipline general functions
Discipline createDiscipline();
void showDisciplines(DisciplineNode *head);
void appendDiscipline(DisciplineNode **head);
void pushDiscipline(DisciplineNode **head, Discipline discipline);
int findDisciplineByCode(DisciplineNode *head);
int deleteDisciplineByCode(DisciplineNode **head, StudentNode **headStudent);
void showStudentsFromDisciplineCode(DisciplineNode *head);
void showDisciplinesFromPeriod(StudentNode *head);


// Sessions functions
void initializeSession(StudentNode **headStudent, DisciplineNode **headDiscipline);
void writeStudentsFile(StudentNode *head);
void writeDisciplinesFile(DisciplineNode *head);

// Other functions
void spacingLine(int length, int spacingBefore, int spacingAfter);

int main() {
    int option;
    StudentNode *headStudent = NULL;
    DisciplineNode *headDiscipline = NULL;
    initializeSession(&headStudent, &headDiscipline);
    spacingLine(35, 1, 2);
    printf("Bem-vindo ao SISTEMA ACADEMICO\n\n");
    do {
        spacingLine(35, 0, 2);
        printf("Menu\n\n");
        printf("1.\tVer lista de alunos\n2.\tVer lista de disciplinas\n3.\tAdicionar aluno\n4.\tAdicionar disciplina\n5.\tProcurar aluno\n6.\tProcurar disciplina\n7.\tDeletar aluno\n8.\tDeletar disciplina\n9.\tAdicionar disciplina a aluno\n10.\tDisciplinas de um aluno\n11.\tAlunos de uma disciplina\n12.\tDisciplinas de um periodo\n13.\tAlunos de um periodo\n14.\tSair (para salvar)\n\n");
        spacingLine(35, 0, 2);
        printf("Opcao: ");
        scanf("%d", &option);
        switch(option) {
            case 1:
                showStudents(headStudent);
                break;
            case 2:
                showDisciplines(headDiscipline);
                break;
            case 3:
                appendStudent(&headStudent);
                break;
            case 4:
                appendDiscipline(&headDiscipline);
                break;
            case 5: 
                findStudentByCode(headStudent);
                break;
            case 6: 
                findDisciplineByCode(headDiscipline);
                break;
            case 7: 
                deleteStudentByCode(&headStudent, &headDiscipline);
                break;
            case 8:
                deleteDisciplineByCode(&headDiscipline, &headStudent);
                break;
            case 9:
                updateDisciplines(headStudent, headDiscipline);
                break;
            case 10:
                showDisciplinesFromStudentCode(headStudent);
                break;
            case 11:
                showStudentsFromDisciplineCode(headDiscipline);
                break;
            case 12:
                showDisciplinesFromPeriod(headStudent);
                break;
            case 13:
                showStudentsFromPeriod(headStudent);
                break;
            case 14:
                writeStudentsFile(headStudent);
                writeDisciplinesFile(headDiscipline);
                break;
            default:
                printf("Opcao invalida\n\n");
                break;
        }
    } while(option != 14);
    return 0;
}

// ***** Student functions *****

// Creates new student asking user for inputs and returns it as struct
Student createStudent() {
    char code[STUDENT_CODE_SIZE];
    char name[NAME_SIZE];
    char cpf[CPF_SIZE];
    Student *student = (Student*)malloc(sizeof(Student)); // Dynamic allocation
    spacingLine(35, 1, 2);
    printf("Insira o codigo do aluno (5 digitos): ");
    fflush(stdin);
    scanf(" %s", code);
    printf("Insira o nome do aluno: ");
    fflush(stdin);
    scanf(" %[^\n]s", name);
    printf("Insira o CPF do aluno (somente numeros): ");
    fflush(stdin);
    scanf(" %s", cpf);
    strcpy(student->code, code);
    strcpy(student->name, name);
    strcpy(student->cpf, cpf);
    student->disciplinesLength = 0;
    student->currentDisciplines = NULL;
    return (*student);
}

// Appends student at the end of the list
void appendStudent(StudentNode **head) {
    StudentNode *newStudent = (StudentNode*)malloc(sizeof(StudentNode)); // Node dynamic allocation
    Student *student = (Student*)malloc(sizeof(Student)); // Student dynamic allocation
    (*student) = createStudent();
    newStudent->info = (*student);
    newStudent->next = NULL;
    if(*head == NULL) { // Empty student list
        *head = newStudent;
        printf("\nAluno criado com sucesso!\n\n");
        return;
    }
    StudentNode *lastNode = (StudentNode*)malloc(sizeof(StudentNode)); // Student dynamic allocation
    lastNode = *head;
    while(lastNode->next != NULL) {
        lastNode = lastNode->next;
    }
    lastNode->next = newStudent;
    printf("\nAluno criado com sucesso!\n\n");
}

// Pushes student at the end of the list (student as parameter and prints nothing)
void pushStudent(StudentNode **head, Student student) {
    StudentNode *newStudent = (StudentNode*)malloc(sizeof(StudentNode)); // Dynamic allocation
    newStudent->info = student;
    newStudent->next = NULL;
    if(*head == NULL) { // Empty student list
        *head = newStudent;
        return;
    }
    StudentNode *lastNode = (StudentNode*)malloc(sizeof(StudentNode)); // Student dynamic allocation
    lastNode = *head;
    while(lastNode->next != NULL) {
        lastNode = lastNode->next;
    }
    lastNode->next = newStudent;
}

// Displays every registered student
void showStudents(StudentNode *head) {
    if(head == NULL) { // Empty student list
        spacingLine(35, 1, 2);
        printf("Nao ha alunos cadastrados\n\n");
        return;
    }
    printf("\nAlunos cadastrados:\n\n");
    printf("%-20s%-40s%-30s%-20s\n", "Codigo", "Nome", "CPF", "Disciplinas");
    while(head != NULL) {
        printf("%-20s%-40s%-30s%-20d\n", head->info.code, head->info.name, head->info.cpf, head->info.disciplinesLength);
        head = head->next;
    }
    printf("\n");
}

// Finds student by its code (all students)
int findStudentByCode(StudentNode *head) {
    StudentNode *auxStudent = (StudentNode*)malloc(sizeof(StudentNode)); // Node dynamic allocation
    auxStudent = head; // Keep track of original head
    char code[STUDENT_CODE_SIZE];
    spacingLine(35, 1, 2);
    printf("Insira o codigo do aluno a procurar: ");
    fflush(stdin);
    scanf(" %s", code);
    if(head == NULL) { // Empty list
        printf("\nLista vazia\n");
        return 0;
    } 
    int found = 0;
    while(head != NULL) {
        if(strcmp(head->info.code, code) == 0) {
            if(!found) {
                printf("\nAluno(s) encontrado(s):\n\n");
                printf("%-20s%-40s%-30s%-20s\n", "Codigo", "Nome", "CPF", "Disciplinas");
                found = 1;
            }
            printf("%-20s%-40s%-30s%-20d\n", head->info.code, head->info.name, head->info.cpf, head->info.disciplinesLength);
        }
        head = head->next;
    }
    head = auxStudent;
    if(found) {
        return 1;
    } else {
        printf("\nAluno nao encontrado");
        return 0;
    }
}


// Deletes student by code (all students)
int deleteStudentByCode(StudentNode **head, DisciplineNode **headDiscipline) {
    char code[STUDENT_CODE_SIZE];
    spacingLine(35, 1, 2);
    printf("Insira o codigo do aluno a deletar: ");
    fflush(stdin);
    scanf(" %s", code);
    if(*head == NULL) { // Empty list
        printf("\nLista vazia\n");
        return 0;
    } 
    int counter = 0;
    // Deleting student from students linked list
    StudentNode *prev = (StudentNode*)malloc(sizeof(StudentNode)); // Node dynamic allocation
    StudentNode *curr = (StudentNode*)malloc(sizeof(StudentNode)); // Node dynamic allocation
    prev = NULL;
    curr = *head;
    while(curr != NULL) {
        if(strcmp(curr->info.code, code) == 0) {
            if(prev == NULL) {
                *head = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            counter++;
        } else {
            prev = curr;
        }
        curr = curr->next;
    }
    // Deleting student from disciplines that this student is registered
    DisciplineNode *auxDiscipline = (DisciplineNode*)malloc(sizeof(DisciplineNode)); // Node dynamic allocation
    auxDiscipline = *headDiscipline;
    while(*headDiscipline != NULL) {
        StudentNode *auxStudent = (StudentNode*)malloc(sizeof(StudentNode)); // Node dynamic allocation
        StudentNode *currStudent = (StudentNode*)malloc(sizeof(StudentNode)); // Node dynamic allocation
        StudentNode *prevStudent = (StudentNode*)malloc(sizeof(StudentNode)); // Node dynamic allocation
        auxStudent = (*headDiscipline)->info.currentStudents;
        prevStudent = NULL;
        currStudent = (*headDiscipline)->info.currentStudents;
        while(currStudent != NULL) {
            if(strcmp(currStudent->info.code, code) == 0) {
                if(prevStudent == NULL) {
                    (*headDiscipline)->info.currentStudents = currStudent->next;
                    (*headDiscipline)->info.studentsLength--;
                } else {
                    prevStudent->next = currStudent->next;
                    (*headDiscipline)->info.studentsLength--;
                }
                free(currStudent);
            } else {
                prevStudent = currStudent;
            }
            currStudent = currStudent->next;
        }
        (*headDiscipline) = (*headDiscipline)->next;
    }
    (*headDiscipline) = auxDiscipline;
    if(counter) {
        printf("\nAlunos deletados: %d\n", counter);
        return 1;
    } else {
        printf("\nNenhum aluno foi deletado");
        return 0;
    }
}


// Shows every discipline a student is registered
void showDisciplinesFromStudentCode(StudentNode *head) {
    StudentNode *auxStudent = (StudentNode*)malloc(sizeof(StudentNode)); // Node dynamic allocation
    auxStudent = head; // Keep track of original head
    char code[STUDENT_CODE_SIZE];
    printf("Insira o codigo do aluno: ");
    fflush(stdin);
    scanf(" %s", code);
    if(head == NULL) { // Empty list
        printf("\nLista vazia\n");
        return;
    }
    int found = 0;
    while(head != NULL) {
        if(strcmp(head->info.code, code) == 0) {
            DisciplineNode *auxDiscipline = (DisciplineNode*)malloc(sizeof(DisciplineNode)); // Node dynamic allocation
            auxDiscipline = head->info.currentDisciplines; // Keep track of original head
            found = 1;
            printf("\n%s\tAluno: %s\n\n", head->info.code, head->info.name);
            printf("Disciplinas:\n");
            if(head->info.currentDisciplines == NULL) {
                printf("Nao ha disciplinas\n\n");
                return;
            }
            while(head->info.currentDisciplines != NULL) {
                printf("%s\t%s, Professor: %s, Periodo: %s\n", head->info.currentDisciplines->info.code, head->info.currentDisciplines->info.name, head->info.currentDisciplines->info.teacher, head->info.currentDisciplines->info.period);
                head->info.currentDisciplines = head->info.currentDisciplines->next;
            }
            head->info.currentDisciplines = auxDiscipline;
            printf("\n");
        }
        head = head->next;
    }
    head = auxStudent;
}

// Shows every student registered into a discipline in certain period
void showStudentsFromPeriod(StudentNode *head) {
    StudentNode *auxStudent = (StudentNode*)malloc(sizeof(StudentNode)); // Node dynamic allocation
    auxStudent = head; // Keep track of original head
    char period[PERIOD_SIZE];
    printf("Insira o periodo (ex.: 2024.1): ");
    fflush(stdin);
    scanf(" %s", period);
    if(head == NULL) { // Empty list
        printf("Nao ha alunos cadastradas em periodos");
        return;
    }
    int found = 0;
    while(head != NULL) {
        if(head->info.disciplinesLength != 0) {
            DisciplineNode *auxDiscipline = (DisciplineNode*)malloc(sizeof(DisciplineNode)); // Node dynamic allocation
            auxDiscipline = head->info.currentDisciplines; // Keep track of original head
            while(head->info.currentDisciplines != NULL) {
                if(strcmp(head->info.currentDisciplines->info.period, period) == 0) {
                    if(!found) {
                        printf("\nAlunos:\n\n");
                    }
                    printf("\n%s\tNome: %s", head->info.code, head->info.name);
                    found = 1;
                    break;
                }
                head->info.currentDisciplines = head->info.currentDisciplines->next;
            }
            head->info.currentDisciplines = auxDiscipline;
        }        
        head = head->next;
    }
    head = auxStudent;
    printf("\n\n");
    if(!found) {
        printf("Nao ha alunos no periodo selecionado\n\n");
    }
}


// ***** Discipline Functions *****

// Creates new discipline and returns it
Discipline createDiscipline() {
    char code[DISCIPLINE_CODE_SIZE];
    char name[NAME_SIZE];
    char teacher[NAME_SIZE];
    int credits;
    Discipline *discipline = (Discipline*)malloc(sizeof(Discipline)); // Dynamic allocation
    printf("\nInsira o codigo da disciplina (4 digitos): ");
    fflush(stdin);
    scanf(" %s", code);
    printf("Insira o nome da disciplina: ");
    fflush(stdin);
    scanf(" %[^\n]s", name);
    printf("Insira o professor da disciplina: ");
    fflush(stdin);
    scanf(" %[^\n]s", teacher);
    printf("Insira a quantidade de creditos da disciplina: ");
    fflush(stdin);
    scanf(" %d", &credits);
    strcpy(discipline->code, code);
    strcpy(discipline->name, name);
    strcpy(discipline->teacher, teacher);
    strcpy(discipline->period, "----.-");
    discipline->credits = credits;
    discipline->studentsLength = 0;
    discipline->currentStudents = NULL;
    return (*discipline);
}

// Appends discipline to the end of the list
void appendDiscipline(DisciplineNode **head) {
    DisciplineNode *newDiscipline = (DisciplineNode*)malloc(sizeof(DisciplineNode)); // Node dynamic allocation
    Discipline discipline = createDiscipline();
    newDiscipline->info = discipline;
    newDiscipline->next = NULL;
    if(*head == NULL) { // Empty discipline list
        *head = newDiscipline;
        printf("\nDisciplina criada com sucesso!\n\n");
        return;
    }
    DisciplineNode *lastNode = (DisciplineNode*)malloc(sizeof(DisciplineNode)); // Node dynamic allocation
    lastNode = *head;
    while (lastNode->next != NULL) {
        lastNode = lastNode->next;
    }
    lastNode->next = newDiscipline;
    printf("\nDisciplina criada com sucesso!\n\n");
}

// Pushes discipline to the end of the list (discipline as parameter and prints nothing)
void pushDiscipline(DisciplineNode **head, Discipline discipline) {
    DisciplineNode *newDiscipline = (DisciplineNode*)malloc(sizeof(DisciplineNode)); // Dynamic allocation
    newDiscipline->info = discipline;
    newDiscipline->next = NULL;
    if(*head == NULL) { // Empty discipline list
        *head = newDiscipline;
        return;
    }
    DisciplineNode *lastNode = (DisciplineNode*)malloc(sizeof(DisciplineNode)); // Node dynamic allocation
    lastNode = *head;
    while (lastNode->next != NULL) {
        lastNode = lastNode->next;
    }
    lastNode->next = newDiscipline;
}

// Displays every registered discipline
void showDisciplines(DisciplineNode *head) {
    if(head == NULL) { // Empty discipline list
        spacingLine(35, 1, 2);
        printf("Nao ha disciplinas cadastradas\n\n");
        return;
    }
    printf("\nDisciplinas cadastradas:\n\n");
    printf("%-20s%-30s%-30s%-20s%-20s\n", "Codigo", "Nome", "Professor", "Creditos", "Alunos");
    while(head != NULL) {
        printf("%-20s%-30s%-30s%-20d%-20d\n", head->info.code, head->info.name, head->info.teacher, head->info.credits, head->info.studentsLength);
        head = head->next;
    }
    printf("\n");
}

// Finds discipline by code
int findDisciplineByCode(DisciplineNode *head) {
    DisciplineNode *auxDiscipline = (DisciplineNode*)malloc(sizeof(DisciplineNode)); // Node dynamic allocation
    auxDiscipline = head;
    char code[DISCIPLINE_CODE_SIZE];
    spacingLine(35, 1, 2);
    printf("Insira o codigo da disciplina a procurar: ");
    fflush(stdin);
    scanf(" %s", code);
    if (head == NULL) { // Empty list
        printf("\nLista vazia\n");
    }
    int found = 0;
    while (head != NULL) {
        if (strcmp(head->info.code, code) == 0) {
            if(!found) {
                printf("\nDisciplina(s) encontrada(s):\n\n");
                printf("%-20s%-30s%-30s%-20s%-20s\n", "Codigo", "Nome", "Professor", "Creditos", "Alunos");
                found = 1;
            }
            printf("%-20s%-30s%-30s%-20d%-20d\n", head->info.code, head->info.name, head->info.teacher, head->info.credits, head->info.studentsLength);
        }
        printf("\n");
        head = head->next;
    }
    head = auxDiscipline;
    if(found) {
        return 1;
    } else {
        printf("\nDisciplina nao encontrada");
        return 0;
    }
}


// Deletes discipline by code
int deleteDisciplineByCode(DisciplineNode **head, StudentNode **headStudent) {
    char code[DISCIPLINE_CODE_SIZE];
    spacingLine(35, 1, 2);
    printf("Insira o codigo da disciplina a deletar: ");
    fflush(stdin);
    scanf(" %s", code);
    if(*head == NULL) { // Empty list
        printf("\nLista vazia\n");
        return 0;
    } 
    int counter = 0;
    // Deleting discipline from disciplines linked list
    DisciplineNode *prev = (DisciplineNode*)malloc(sizeof(DisciplineNode)); // Node dynamic allocation
    DisciplineNode *curr = (DisciplineNode*)malloc(sizeof(DisciplineNode)); // Node dynamic allocation
    prev = NULL;
    curr = *head;
    while(curr != NULL) {
        if(strcmp(curr->info.code, code) == 0) {
            if(prev == NULL) {
                *head = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            counter++;
        } else {
            prev = curr;
        }
        curr = curr->next;
    }
    // Deleting discipline from possible registrations of students
    StudentNode *auxStudent = (StudentNode*)malloc(sizeof(StudentNode)); // Node dynamic allocation
    auxStudent = *headStudent;
    while(*headStudent != NULL) {
        DisciplineNode *auxDiscipline = (DisciplineNode*)malloc(sizeof(DisciplineNode)); // Node dynamic allocation
        DisciplineNode *currDiscipline = (DisciplineNode*)malloc(sizeof(DisciplineNode)); // Node dynamic allocation
        DisciplineNode *prevDiscipline = (DisciplineNode*)malloc(sizeof(DisciplineNode)); // Node dynamic allocation
        auxDiscipline = (*headStudent)->info.currentDisciplines;
        prevDiscipline = NULL;
        currDiscipline = (*headStudent)->info.currentDisciplines;
        while(currDiscipline != NULL) {
            if(strcmp(currDiscipline->info.code, code) == 0) {
                if(prevDiscipline == NULL) {
                    (*headStudent)->info.currentDisciplines = currDiscipline->next;
                    (*headStudent)->info.disciplinesLength--;
                } else {
                    prevDiscipline->next = currDiscipline->next;
                    (*headStudent)->info.disciplinesLength--;
                }
                free(currDiscipline);
            } else {
                prevDiscipline = currDiscipline;
            }
            currDiscipline = currDiscipline->next;
        }
        (*headStudent) = (*headStudent)->next;
    }
    (*headStudent) = auxStudent;
    if(counter) {
        printf("\nDisciplinas deletadas: %d\n", counter);
        return 1;
    } else {
        printf("\nNenhuma disciplina foi deletada");
        return 0;
    }
}

// Shows every student registered in a discipline
void showStudentsFromDisciplineCode(DisciplineNode *head) {
    DisciplineNode *auxDiscipline = (DisciplineNode*)malloc(sizeof(DisciplineNode)); // Node dynamic allocation
    auxDiscipline = head;
    char code[DISCIPLINE_CODE_SIZE];
    printf("Insira o codigo da disciplina: ");
    fflush(stdin);
    scanf(" %s", code);
    if(head == NULL) { // Empty list
        printf("\nLista vazia\n");
        return;
    }
    int found = 0;
    while(head != NULL) {
        if(strcmp(head->info.code, code) == 0) {
            StudentNode *auxStudent = head->info.currentStudents;
            found = 1;
            printf("\n%s\tDisciplina: %s\n\n", head->info.code, head->info.name);
            printf("Alunos:\n");
            if(head->info.currentStudents == NULL) {
                printf("Nao ha alunos\n\n");
                return;
            }
            while(head->info.currentStudents != NULL) {
                printf("%s\t%s\n", head->info.currentStudents->info.code, head->info.currentStudents->info.name);
                head->info.currentStudents = head->info.currentStudents->next;
            }
            head->info.currentStudents = auxStudent;
            printf("\n");
        }
        head = head->next;
    }
    head = auxDiscipline;
}

// Shows every discipline from certain period
void showDisciplinesFromPeriod(StudentNode *head) {
    StudentNode *auxStudent = (StudentNode*)malloc(sizeof(StudentNode)); // Node dynamic allocation
    auxStudent = head;
    char period[PERIOD_SIZE];
    printf("Insira o periodo (ex.: 2024.1): ");
    fflush(stdin);
    scanf(" %s", period);
    if(head == NULL) { // Empty list
        printf("Nao ha disciplinas cadastradas em periodos\n\n");
        return;
    }
    int found = 0;
    while(head != NULL) {
        if(head->info.disciplinesLength != 0) {
            DisciplineNode *auxDiscipline = head->info.currentDisciplines;
            char seen[50][DISCIPLINE_CODE_SIZE]; // Just to avoid duplicates
            while(head->info.currentDisciplines != NULL) {
                if(strcmp(head->info.currentDisciplines->info.period, period) == 0) {
                    strcpy(seen[found], head->info.currentDisciplines->info.code);
                    if(!found) {
                        printf("\nDisciplinas:\n\n");
                    }
                    int haveSeen = 0;
                    for(int i = 0; i < found; i++) {
                        if(strcmp(seen[i], head->info.currentDisciplines->info.code) == 0) {
                            haveSeen = 1;
                        }
                    }
                    if(!haveSeen) {
                        printf("\n%s\tDisciplina: %s", head->info.currentDisciplines->info.code, head->info.currentDisciplines->info.name);
                    }
                    found++;
                }
                head->info.currentDisciplines = head->info.currentDisciplines->next;
            }
            head->info.currentDisciplines = auxDiscipline;
        }        
        head = head->next;
    }
    head = auxStudent;
    printf("\n\n");
    if(!found) {
        printf("\nNao ha disciplinas no periodo selecionado\n");
    }
}

// ***** Update funcions *****

// Updates students current disciplines and also discipline current students
int updateDisciplines(StudentNode *headStudent, DisciplineNode *headDiscipline) {
    char studentCode[STUDENT_CODE_SIZE];
    char disciplineCode[DISCIPLINE_CODE_SIZE];
    char period[PERIOD_SIZE];
    printf("Para cadastrar uma disciplina a um aluno, insira:\n1. Codigo do aluno: ");
    fflush(stdin);
    scanf(" %[^\n]s", studentCode);
    printf("2. Codigo da disciplina: ");
    fflush(stdin);
    scanf(" %[^\n]s", disciplineCode);
    printf("3. Periodo (ex.: 2024.1): ");
    fflush(stdin);
    scanf(" %[^\n]s", period);
    if(headStudent == NULL || headDiscipline == NULL) { // Empty list
        printf("\nAlguma das listas é vazia\n");
        return 0;
    }
    int updated = -1;
    while(headDiscipline != NULL) {
        if(strcmp(headDiscipline->info.code, disciplineCode) == 0) {
            updated = 0;
            while(headStudent != NULL) {
                if(strcmp(headStudent->info.code, studentCode) == 0) {
                    headStudent->info.disciplinesLength++;
                    DisciplineNode *newDiscipline = (DisciplineNode*)malloc(sizeof(DisciplineNode));
                    newDiscipline->info = headDiscipline->info;
                    strcpy(newDiscipline->info.period, period);
                    newDiscipline->next = NULL;
                    if(headStudent->info.currentDisciplines == NULL) {
                        headStudent->info.currentDisciplines = newDiscipline;
                    } else {
                        DisciplineNode *lastDisciplineNode = headStudent->info.currentDisciplines;
                        while(lastDisciplineNode->next != NULL) {
                            lastDisciplineNode = lastDisciplineNode->next;
                        }
                        lastDisciplineNode->next = newDiscipline;
                    }
                    headDiscipline->info.studentsLength++;
                    StudentNode *newStudent = (StudentNode*)malloc(sizeof(StudentNode));
                    newStudent->info = headStudent->info;
                    newStudent->next = NULL;
                    if(headDiscipline->info.currentStudents == NULL) {
                        headDiscipline->info.currentStudents = newStudent;
                    } else {
                        StudentNode *lastStudentNode = headDiscipline->info.currentStudents;
                        while(lastStudentNode->next != NULL) {
                            lastStudentNode = lastStudentNode->next;
                        }
                        lastStudentNode->next = newStudent;
                    }
                    updated = 1;
                }
                headStudent = headStudent->next;
            }
        }
        headDiscipline = headDiscipline->next;
    }
    if(updated == -1) {
        printf("\nA disciplina nao foi encontrada\n\n");
        return 0;
    } else if(updated == 0) {
        printf("\nO aluno nao foi encontrado\n\n");
        return 0;
    } else {
        printf("\nO aluno foi atualizado com sucesso\n\n");
        return 1;
    }
}

// ***** Session funcions *****
void writeStudentsFile(StudentNode *head) {
    StudentNode *auxStudent = (StudentNode*)malloc(sizeof(StudentNode)); // Node dynamic allocation
    auxStudent = head;
    FILE *fp;
    fp = fopen("Alunos.txt", "w");
    if(fp == NULL) {
        return;
    }
    if(head == NULL) { // Empty list
        fprintf(fp, "%s", "Nao ha alunos cadastrados\n");
        return;
    }
    while(head != NULL) {
        fprintf(fp, "%s,%s,%s,%d,\n", head->info.code, head->info.name, head->info.cpf, head->info.disciplinesLength);
        if(head->info.disciplinesLength == 0) {
            fprintf(fp, "%s,\n", "Sem disciplinas");
        } else {
            while(head->info.currentDisciplines != NULL) {
                fprintf(fp, "%s,%s,%s,%d,%s,\n", head->info.currentDisciplines->info.code, head->info.currentDisciplines->info.name, head->info.currentDisciplines->info.teacher, head->info.currentDisciplines->info.credits, head->info.currentDisciplines->info.period);
                head->info.currentDisciplines = head->info.currentDisciplines->next;
            }
        }
        head = head->next;
    }
    head = auxStudent;
    fclose(fp);
}

void writeDisciplinesFile(DisciplineNode *head) {
    DisciplineNode *auxDiscipline = (DisciplineNode*)malloc(sizeof(DisciplineNode)); // Node dynamic allocation
    auxDiscipline = head;
    FILE *fp;
    fp = fopen("Disciplinas.txt", "w");
    if(fp == NULL) {
        return;
    }
    if(head == NULL) {
        fprintf(fp, "%s", "Nao ha disciplinas cadastradas\n");
        return;
    }
    while(head != NULL) {
        fprintf(fp, "%s,%s,%s,%d,%d,\n", head->info.code, head->info.name, head->info.teacher, head->info.credits, head->info.studentsLength);
        if(head->info.studentsLength == 0) {
            fprintf(fp, "%s,\n", "Sem alunos") ;
        } else {
            while(head->info.currentStudents != NULL) {
                fprintf(fp, "%s,%s,%s,\n", head->info.currentStudents->info.code, head->info.currentStudents->info.name, head->info.currentStudents->info.cpf);
                head->info.currentStudents = head->info.currentStudents->next;
            }
        }
        head = head->next;
    }
    head = auxDiscipline;
    fclose(fp);
}

void initializeSession(StudentNode **headStudent, DisciplineNode **headDiscipline) {
    char line[LINE_SIZE];
    FILE *fpStudents;
    FILE *fpDisciplines;
    fpStudents = fopen("Alunos.txt", "r");
    fpDisciplines = fopen("Disciplinas.txt", "r");
    if(fpStudents == NULL || fpDisciplines == NULL) {
        return;
    }
    while(fgets(line, sizeof(line), fpStudents) != NULL) {
        char *token = strtok(line, ",");
        if(strlen(token) == 5) {
            Student student;
            strcpy(student.code, token);
            strcpy(student.name, strtok(NULL, ","));
            strcpy(student.cpf, strtok(NULL, ","));
            student.disciplinesLength = atoi(strtok(NULL, ","));
            student.currentDisciplines = NULL;
            char lineDiscipline[LINE_SIZE];
            int i = 0;
            while(i < student.disciplinesLength && fgets(lineDiscipline, sizeof(lineDiscipline), fpStudents) != NULL) {
                Discipline discipline;
                strcpy(discipline.code, strtok(lineDiscipline, ","));
                strcpy(discipline.name, strtok(NULL, ","));
                strcpy(discipline.teacher, strtok(NULL, ","));
                discipline.credits = atoi(strtok(NULL, ","));
                strcpy(discipline.period, strtok(NULL, ","));
                DisciplineNode *newDiscipline = (DisciplineNode*)malloc(sizeof(DisciplineNode));
                newDiscipline->info = discipline;
                newDiscipline->next = NULL;
                if(student.currentDisciplines == NULL) {
                    student.currentDisciplines = newDiscipline;
                } else {
                    DisciplineNode *lastDisciplineNode = student.currentDisciplines;
                    while(lastDisciplineNode->next != NULL) {
                        lastDisciplineNode = lastDisciplineNode->next;
                    }
                    lastDisciplineNode->next = newDiscipline;
                }
                i++;
            }
            pushStudent(&(*headStudent), student);
        }
    }
    while(fgets(line, sizeof(line), fpDisciplines) != NULL) {
        char *token = strtok(line, ",");
        if(strlen(token) == 4) {
            Discipline discipline;
            strcpy(discipline.code, token);
            strcpy(discipline.name, strtok(NULL, ","));
            strcpy(discipline.teacher, strtok(NULL, ","));
            discipline.credits = atoi(strtok(NULL, ","));
            discipline.studentsLength = atoi(strtok(NULL, ","));
            discipline.currentStudents = NULL;
            char lineStudent[LINE_SIZE];
            int i = 0;
            while(i < discipline.studentsLength && fgets(lineStudent, sizeof(lineStudent), fpDisciplines) != NULL) {
                Student student;
                strcpy(student.code, strtok(lineStudent, ","));
                strcpy(student.name, strtok(NULL, ","));
                strcpy(student.cpf, strtok(NULL, ","));
                StudentNode *newStudent = (StudentNode*)malloc(sizeof(StudentNode));
                newStudent->info = student;
                newStudent->next = NULL;
                if(discipline.currentStudents == NULL) {
                    discipline.currentStudents = newStudent;
                } else {
                    StudentNode *lastStudentNode = discipline.currentStudents;
                    while(lastStudentNode->next != NULL) {
                        lastStudentNode = lastStudentNode->next;
                    }
                    lastStudentNode->next = newStudent;
                }
                i++;
            }
            pushDiscipline(&(*headDiscipline), discipline);
        }
    }
}

// Other functions
void spacingLine(int length, int spacingBefore, int spacingAfter) {
    int i = 0, j = 0, k = 0;
    while (i < spacingBefore) {
        printf("\n");
        i++;
    }
    while (j < length) {
        printf("-");
        j++;
    }
    while (k < spacingAfter) {
        printf("\n");
        k++;
    }
}
