#include <stdio.h>
#include <stdlib.h>

struct Student {
    int roll_no;
    char name[20];
    float marks;
};

int main() {
    int n, i;
    char ans;
    struct Student *s, *highest;

    printf("Enter number of students: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number!\n");
        return 1;
    }

    s = malloc(n * sizeof(struct Student));

    if (s == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("Enter roll, name, marks: ");
        scanf("%d %19s %f", &(s+i)->roll_no,
              (s+i)->name, &(s+i)->marks);
    }


    repeat:
    	;
        float total = 0;
        highest = s;

        for (i = 0; i < n; i++) {
            total += (s+i)->marks;

            if ((s+i)->marks > highest->marks)
                highest = s+i;
        }

        printf("\nUpdated average marks: %.2f\n", total/n);
        printf("Topper: %s (Roll %d, Marks %.2f)\n",
            highest->name, highest->roll_no, highest->marks);


        printf("\n\nDo you want to add 2 more students? (y/n): ");
        scanf(" %c", &ans);

        if (ans == 'y' || ans == 'Y') {
            struct Student *temp;
            temp = realloc(s, (n+2) * sizeof(struct Student));

            if (temp != NULL) {
                s = temp;

                for (i = n; i < n+2; i++) {
                    printf("Enter roll, name, marks: ");
                    scanf("%d %19s %f", &(s+i)->roll_no,
                        (s+i)->name, &(s+i)->marks);
                }
                n = n + 2;
                goto repeat;
            }
        }
    free(s);
    return 0;
}

