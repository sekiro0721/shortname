#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_TASKS 100
#define MAX_TITLE_LEN 50
#define MAX_DESC_LEN 200
#define LOW_PRIORITY 1
#define MEDIUM_PRIORITY 2
#define HIGH_PRIORITY 3

typedef struct {
    int id;
    char title[MAX_TITLE_LEN + 1];  // +1 for null terminator
    char description[MAX_DESC_LEN + 1];
    int priority;
    bool completed;
} Task;

Task tasks[MAX_TASKS];
int taskCount = 0;

// ��ȫ���뺯������ֹ���������
void safeInput(char* buffer, int maxLen) {
    fgets(buffer, maxLen, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    else {
        // ������뻺����ʣ������
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
    }
}

// ���������
bool addTask() {
    if (taskCount >= MAX_TASKS) {
        printf("���������б�������\n");
        return false;
    }

    Task newTask;
    newTask.id = taskCount + 1;
    newTask.completed = false;

    printf("\n--- ��������� ---\n");

    // �����������
    printf("������������� (���%d�ַ�): ", MAX_TITLE_LEN);
    safeInput(newTask.title, sizeof(newTask.title));

    // ������������
    printf("�������������� (���%d�ַ�): ", MAX_DESC_LEN);
    safeInput(newTask.description, sizeof(newTask.description));

    // �����������ȼ�
    do {
        printf("�������������ȼ� (%d-��, %d-��, %d-��): ",
            LOW_PRIORITY, MEDIUM_PRIORITY, HIGH_PRIORITY);
        scanf_s("%d", &newTask.priority);
        while (getchar() != '\n'); // ������뻺����
    } while (newTask.priority < LOW_PRIORITY || newTask.priority > HIGH_PRIORITY);

    tasks[taskCount++] = newTask;
    printf("������ӳɹ���ID: %d\n", newTask.id);
    return true;
}

// ��ʾ��������
void displayTasks() {
    if (taskCount == 0) {
        printf("\n��ǰû������\n");
        return;
    }

    printf("\n--- �����б� (��%d������) ---\n", taskCount);
    printf("ID\t״̬\t���ȼ�\t����\t\t����\n");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < taskCount; i++) {
        const char* status = tasks[i].completed ? "�����" : "δ���";
        const char* priority;

        switch (tasks[i].priority) {
        case LOW_PRIORITY: priority = "��"; break;
        case MEDIUM_PRIORITY: priority = "��"; break;
        case HIGH_PRIORITY: priority = "��"; break;
        default: priority = "δ֪"; break;
        }

        printf("%d\t%s\t%s\t%.20s\t%.30s%s\n",
            tasks[i].id,
            status,
            priority,
            tasks[i].title,
            tasks[i].description,
            strlen(tasks[i].description) > 30 ? "..." : "");
    }
}

// ���˵�
void showMenu() {
    printf("\n=== �����������ϵͳ ===\n");
    printf("1. �������\n");
    printf("2. ��ʾ�����б�\n");
    printf("0. �˳�\n");
    printf("��ѡ�����: ");
}

int main() {
    int choice;

    do {
        showMenu();
        if (scanf_s("%d", &choice) != 1) {
            printf("������Ч�����������룡\n");
            while (getchar() != '\n'); // �����Ч����
            continue;
        }
        while (getchar() != '\n'); // ������뻺����

        switch (choice) {
        case 1:
            addTask();
            break;
        case 2:
            displayTasks();
            break;
        case 0:
            printf("�˳�ϵͳ...\n");
            break;
        default:
            printf("��Чѡ�����������룡\n");
        }
    } while (choice != 0);

    return 0;
}