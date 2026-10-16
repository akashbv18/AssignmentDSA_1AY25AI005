
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    FULL_TIME,
    CONTRACT
} EmployeeType;

typedef struct {
    char name[20];
    int emp_id;
    EmployeeType type;

    union {
        float salary;

        struct {
            float hourly_rate;
            int hours_worked;
        } contract_info;

    } pay;

} Employee;

int main(void) {
    int n, i;
    float total_bill = 0.0f, pay;
    Employee *e;

    printf("Enter number of employees: ");

    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of employees!\n");
        return 1;
    }

    e = malloc((size_t)n * sizeof(Employee));

    if (e == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("\nEnter employee name: ");
        if (scanf("%19s", e[i].name) != 1)
            goto input_error;

        printf("Enter employee ID: ");
        if (scanf("%d", &e[i].emp_id) != 1)
            goto input_error;

        printf("Enter type (0-Full-time, 1-Contract): ");
        if (scanf("%d", &e[i].type) != 1 ||
            (e[i].type != FULL_TIME &&
             e[i].type != CONTRACT))
            goto input_error;

        if (e[i].type == FULL_TIME) {
            printf("Enter monthly salary: ");
            if (scanf("%f", &e[i].pay.salary) != 1 ||
                e[i].pay.salary < 0)
                goto input_error;
        } else {
            printf("Enter hourly rate: ");
            if (scanf("%f",
                &e[i].pay.contract_info.hourly_rate) != 1 ||
                e[i].pay.contract_info.hourly_rate < 0)
                goto input_error;

            printf("Enter hours worked: ");
            if (scanf("%d",
                &e[i].pay.contract_info.hours_worked) != 1 ||
                e[i].pay.contract_info.hours_worked < 0)
                goto input_error;
        }
    }

    printf("\n--- Employee Payslips ---\n");

    for (i = 0; i < n; i++) {
        if (e[i].type == FULL_TIME) {
            pay = e[i].pay.salary;
        } else {
            pay = e[i].pay.contract_info.hourly_rate *
                  e[i].pay.contract_info.hours_worked;
        }

        printf("\nName: %s\n", e[i].name);
        printf("Employee ID: %d\n", e[i].emp_id);
        printf("Total Pay: %.2f\n", pay);

        total_bill += pay;
    }

    printf("\nTotal Salary Bill: %.2f\n", total_bill);

    free(e);
    return 0;

input_error:
    printf("Invalid input! Please run the program again.\n");
    free(e);
    return 1;
}

