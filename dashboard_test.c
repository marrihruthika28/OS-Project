#include "../include/dashboard.h"

int main(void)
{
    int choice;

    init_dashboard();

    while (1)
    {
        draw_dashboard();

        choice = dashboard_menu();

        if (choice == 0)
            break;
    }

    close_dashboard();

    return 0;
}
