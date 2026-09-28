#include <stdio.h>
#include <stdlib.h>

#include "../include/ui.h"

void clear_screen(void)
{
    system("clear");
}

void pause_screen(void)
{
    printf("\nPress Enter to continue...");

    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
    }

    getchar();
}

void display_main_menu(void)
{
    printf("\n");
    printf("============================================================\n");
    printf("                    PROCESSPULSE                            \n");
    printf("             Linux Process Termination Monitor              \n");
    printf("============================================================\n");

    printf("\n");
    printf("  1. Dashboard\n");
    printf("  2. Create Processes\n");
    printf("  3. Live Process Monitor\n");
    printf("  4. Process Tree\n");
    printf("  5. Termination History\n");
    printf("  6. Statistics\n");
    printf("  7. Process Laboratory\n");
    printf("  8. Demo Mode\n");
    printf("  9. Explain Mode\n");
    printf(" 10. About Project\n");
    printf("  0. Exit\n");

    printf("\n============================================================\n");
}

int get_menu_choice(void)
{
    int choice;

    printf("Enter your choice: ");

    if (scanf("%d", &choice) != 1)
    {
        while (getchar() != '\n')
        {
        }

        return -1;
    }

    return choice;
}
