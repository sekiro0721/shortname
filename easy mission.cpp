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

// 安全输入函数，防止缓冲区溢出
void safeInput(char* buffer, int maxLen) {
    fgets(buffer, maxLen, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    else {
        // 清除输入缓冲区剩余内容
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
    }
}

// 添加新任务
bool addTask() {
    if (taskCount >= MAX_TASKS) {
        printf("错误：任务列表已满！\n");
        return false;
    }

    Task newTask;
    newTask.id = taskCount + 1;
    newTask.completed = false;

    printf("\n--- 添加新任务 ---\n");

    // 输入任务标题
    printf("请输入任务标题 (最多%d字符): ", MAX_TITLE_LEN);
    safeInput(newTask.title, sizeof(newTask.title));

    // 输入任务描述
    printf("请输入任务描述 (最多%d字符): ", MAX_DESC_LEN);
    safeInput(newTask.description, sizeof(newTask.description));

    // 输入任务优先级
    do {
        printf("请输入任务优先级 (%d-低, %d-中, %d-高): ",
            LOW_PRIORITY, MEDIUM_PRIORITY, HIGH_PRIORITY);
        scanf_s("%d", &newTask.priority);
        while (getchar() != '\n'); // 清除输入缓冲区
    } while (newTask.priority < LOW_PRIORITY || newTask.priority > HIGH_PRIORITY);

    tasks[taskCount++] = newTask;
    printf("任务添加成功！ID: %d\n", newTask.id);
    return true;
}

// 显示所有任务
void displayTasks() {
    if (taskCount == 0) {
        printf("\n当前没有任务！\n");
        return;
    }

    printf("\n--- 任务列表 (共%d个任务) ---\n", taskCount);
    printf("ID\t状态\t优先级\t标题\t\t描述\n");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < taskCount; i++) {
        const char* status = tasks[i].completed ? "已完成" : "未完成";
        const char* priority;

        switch (tasks[i].priority) {
        case LOW_PRIORITY: priority = "低"; break;
        case MEDIUM_PRIORITY: priority = "中"; break;
        case HIGH_PRIORITY: priority = "高"; break;
        default: priority = "未知"; break;
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

// 主菜单
void showMenu() {
    printf("\n=== 简易任务管理系统 ===\n");
    printf("1. 添加任务\n");
    printf("2. 显示任务列表\n");
    printf("0. 退出\n");
    printf("请选择操作: ");
}

int main() {
    int choice;

    do {
        showMenu();
        if (scanf_s("%d", &choice) != 1) {
            printf("输入无效，请重新输入！\n");
            while (getchar() != '\n'); // 清除无效输入
            continue;
        }
        while (getchar() != '\n'); // 清除输入缓冲区

        switch (choice) {
        case 1:
            addTask();
            break;
        case 2:
            displayTasks();
            break;
        case 0:
            printf("退出系统...\n");
            break;
        default:
            printf("无效选择，请重新输入！\n");
        }
    } while (choice != 0);

    return 0;
}