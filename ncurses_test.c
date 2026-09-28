#include <ncurses.h>

int main(void)
{
    initscr();

    printw("PROCESSPULSE");
    printw("\n");
    printw("Linux Process Termination Monitor");
    printw("\n\n");
    printw("NCURSES UI TEST SUCCESSFUL");
    printw("\n\n");
    printw("Press any key to exit...");

    refresh();
    getch();

    endwin();

    return 0;
}
