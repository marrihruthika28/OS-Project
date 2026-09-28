#include <ncurses.h>
#include <stdio.h>

#include "../include/dashboard.h"

void init_dashboard(void)
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    if (has_colors())
    {
        start_color();

        init_pair(1, COLOR_CYAN, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);
        init_pair(4, COLOR_RED, COLOR_BLACK);
        init_pair(5, COLOR_WHITE, COLOR_BLUE);
    }
}

void close_dashboard(void)
{
    endwin();
}

void draw_header(void)
{
    attron(A_BOLD);
    attron(COLOR_PAIR(1));

    mvprintw(1, 25, "PROCESSPULSE");
    mvprintw(2, 17, "Linux Process Termination Monitor");

    attroff(COLOR_PAIR(1));
    attroff(A_BOLD);

    mvhline(3, 2, ACS_HLINE, 72);
}

void draw_dashboard(void)
{
    clear();

    draw_header();

    attron(A_BOLD);
    mvprintw(5, 5, "SYSTEM STATUS");
    mvprintw(5, 42, "PROCESS STATISTICS");
    attroff(A_BOLD);

    mvhline(6, 3, ACS_HLINE, 72);

    attron(COLOR_PAIR(2));
    mvprintw(8, 5, "● READY");
    attroff(COLOR_PAIR(2));

    mvprintw(10, 5, "Parent PID       : --");

    mvprintw(8, 42, "Created          : 0");
    mvprintw(9, 42, "Currently Running: 0");
    mvprintw(10, 42, "Terminated       : 0");
    mvprintw(11, 42, "Successful Exits : 0");

    mvhline(13, 3, ACS_HLINE, 72);

    attron(A_BOLD);
    mvprintw(15, 5, "[1] Dashboard");
    mvprintw(15, 30, "[2] Create Processes");
    mvprintw(16, 5, "[3] Live Monitor");
    mvprintw(16, 30, "[4] Process Tree");
    mvprintw(17, 5, "[5] Termination History");
    mvprintw(17, 30, "[6] Statistics");
    mvprintw(18, 5, "[7] Process Laboratory");
    mvprintw(18, 30, "[8] Demo Mode");
    mvprintw(19, 5, "[9] Explain Mode");
    mvprintw(19, 30, "[10] About Project");
    mvprintw(21, 5, "[0] Exit");
    attroff(A_BOLD);

    mvhline(23, 3, ACS_HLINE, 72);

    attron(COLOR_PAIR(3));
    mvprintw(25, 5, "Select an option:");
    attroff(COLOR_PAIR(3));

    refresh();
}

int dashboard_menu(void)
{
    int choice;

    echo();
    mvscanw(25, 25, "%d", &choice);
    noecho();

    return choice;
}
