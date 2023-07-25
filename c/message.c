#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <dos.h>
#include <dir.h>

#define FRAME 16
#define PIECE_SYMBOL 178
#define BOARD_SYMBOL 219
#define CHEATS 0




typedef struct piece_nd
{
    COORD squares[4];
    char symbol;
    char name;
    int orientation;
    int color;
}  Piece;



HANDLE _output_handle;


Piece * piece;
char board[12][22];
char board_colors[12][22];
int score=0;
int level=0;
int lines;
int next_piece=-1;
int shapes_counter[7];
int alive=1;



char get_input();
void hidecursor();
void print_at_xy(COORD coord, char ch);
void init_board();
void print_board();
void create_piece();
void update_board(char input);
void print_piece(char ch);
void death_screen();
void update_ui();

void move_right();
void move_left();
void move_down();
void rotate();

void rotate_I();
void rotate_J();
void rotate_L();
void rotate_T();
void rotate_S();
void rotate_Z();

void create_O();
void create_I();
void create_J();
void create_L();
void create_T();
void create_S();
void create_Z();
void SetColor(int ForgC);

void hidecursor()
{
    CONSOLE_CURSOR_INFO info;
    _output_handle = GetStdHandle(STD_OUTPUT_HANDLE);

    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(_output_handle, &info);
}

int main()
{

    int frames=0, frames_per_update=16;
    int speeds[]= {48,43,38,33,28,23,18,13,8,6,5,5,5,4,4,4,3,3,3,2,2,2,2,2,2,2,2,2,2,1};

    hidecursor();
    srand(time(0));
    piece=malloc(sizeof(Piece));
    init_board();
    if(CHEATS)
    {
        int i,j;
        for(i=1; i<10; i++)
        {
            for(j=13; j<21; j++)
            {
                board[i][j]=219;
                board_colors[i][j]=12;
            }
        }

    }
    print_board();
    create_piece();

    while(1)
    {
        if(!alive)
        {
            break;
        }
        frames_per_update=(level<29)?(speeds[level]):1;
        if(frames%frames_per_update)
        {
            char input;
            input=get_input();
            update_board(input);
        }
        else
        {
            update_board('s');
        }

        Sleep(FRAME);
        frames++;
    }
    Sleep(3000);

    return 0;
}


char get_input()
{
    char ch = 0;
    if(kbhit())
    {
        ch = getch();
    }
    return ch;
}


void print_at_xy(COORD coord, char ch)
{
    SetConsoleCursorPosition(_output_handle, coord);
    printf("%c", ch);
}

void init_board()
{
    int i;
    memset(board, ' ', 12*22);
    memset(board_colors, 7, 12*22);
    for(i=0; i<12; i++)
    {
        board[0][0] = 201;
        board[i-1][0] = 205;
        board[11][0] = 187;
    }
    for(i=1; i<21; i++)
    {
        board[0][i]= 186;
        board[11][i]= 186;
    }
    for(i=0; i <12; i++)
    {
        board[0][21] = 200;
        board[i-1][21] = 205;
        board[11][21] = 188;
    }
}

void print_board()
{
    COORD coord;
    hidecursor();
    for(coord.X=0; coord.X<12; (coord.X)++)
    {
        for(coord.Y=0; coord.Y<22; (coord.Y)++)
        {
            SetColor(board_colors[coord.X][coord.Y]);
            print_at_xy(coord, board[coord.X][coord.Y]);

        }
    }
    SetColor(7);
}

void update_ui()
{
    char shapes_names[]= {'O','I','J','L','T', 'Z', 'S'};
    COORD coord;
    int i;

    coord.X=13;
    coord.Y=2;
    print_at_xy(coord, ' ');
    printf("LEVEL: %d", level);
    coord.Y++;
    print_at_xy(coord, ' ');
    printf("SCORE: %d", score);
    coord.Y++;
    print_at_xy(coord, ' ');
    printf("LINES: %d", lines);
    coord.Y+=5;
    print_at_xy(coord, ' ');
    printf("NEXT: %c", (next_piece+1)?(shapes_names[next_piece]):('-'));

    coord.Y+=4;
    print_at_xy(coord, ' ');
    for(i=0; i<7; i++)
    {
        printf("%c's: %d", shapes_names[i], shapes_counter[i]);
        coord.Y++;
        print_at_xy(coord, ' ');
    }
}

void print_piece(char ch)
{
    int i;
    if(ch==0)
    {
        ch=piece->symbol;
    }
    SetColor(piece->color);
    for(i=0; i<4; i++)
    {
        print_at_xy((piece->squares)[i], ch);
    }
    SetColor(7);
}

void create_piece()
{
    int piece_select, i;


    piece_select = (1+next_piece)?(next_piece):(rand()%7);
    next_piece = rand()%7;
    if(CHEATS)
    {
        next_piece = (rand()%2)?(1):(rand()%7);
    }
    shapes_counter[piece_select]++;

    switch(piece_select)
    {
    case 0:
        create_O();
        break;
    case 1:
        create_I();
        break;
    case 2:
        create_J();
        break;
    case 3:
        create_L();
        break;
    case 4:
        create_T();
        break;
    case 5:
        create_Z();
        break;
    case 6:
        create_S();
        break;
    }
    for(i=0; i<4; i++)
    {
        if(board[((piece->squares)[i]).X][((piece->squares)[i]).Y]!=' ')
        {
            death_screen();
            break;
        }
    }
    print_piece(0);


    return ;
}

void death_screen()
{
    COORD coord;
    alive=0;
    coord.X=15;
    coord.Y=22;
    print_at_xy(coord, ' ');
    system("color 04");
    printf("%c You lost!  Good game!\n\t\t Final score: %d, with cheats O%s.\n\n\n", 26,score, (CHEATS)?("N"):("FF"));
    Sleep(5000);
    exit(420);

}

void update_board(char input)
{
    static int updates=0;
    int i, j;
    int lines_cleared=0;
    updates++;
    /*if(!(updates%(FRAME)))
    {
        print_board();
        print_piece(0);
    }*/

    for(i=1; i<21; i++)
    {
        int cleared=1;
        for(j=1; j<11; j++)
        {
            if(board[j][i]==' ')
            {
                cleared=0;
            }
        }
        if(cleared)
        {
            lines_cleared++;
            for(j=1; j<11; j++)
            {
                memmove(&(board[j][2]), &(board[j][1]), (i-1)*sizeof(char));
                memmove(&(board_colors[j][2]), &(board_colors[j][1]), (i-1)*sizeof(char));
                board[j][1]=' ';
                board_colors[j][1]=7;
            }
            print_board();
            print_piece(0);
        }
    }
    if(lines%10 > (lines+lines_cleared)%10)
    {
        level++;
    }
    lines+=lines_cleared;
    switch(lines_cleared)
    {
    case 0:
        break;
    case 1:
        score+=40*(level+1);
        break;
    case 2:
        score+=100*(level+1);
        break;
    case 3:
        score+=300*(level+1);
        break;
    case 4:
        for(i=0; i<FRAME/2; i++)
        {
            sleep(1/2);
            system("color 02");
            sleep(1/2);
            system("color 07");
        }
        print_board();

        score+=1200*(level+1);
    }

    update_ui();

    switch(input)
    {
    case 'a':
        move_left();
        break;
    case 'd':
        move_right();
        break;
    case 's':
        move_down();
        break;
    case 'r':
        rotate();
        break;
    }

}

void move_down()
{
    int i, touchdown=0;
    for(i=0; i<4; i++)
    {
        if(board[((piece->squares)[i]).X][(((piece->squares)[i]).Y)+1]!=' ')
        {
            /*touchdown*/
            touchdown=1;
            break;
        }
    }
    if(touchdown)
    {
        for(i=0; i<4; i++)
        {
            board[((piece->squares)[i]).X][((piece->squares)[i]).Y]= BOARD_SYMBOL;
            board_colors[((piece->squares)[i]).X][((piece->squares)[i]).Y]= piece->color;
        }
        print_board();
        create_piece();
        return;
    }
    print_piece(' ');
    for(i=0; i<4; i++)
    {
        (((piece->squares)[i]).Y)++;
    }
    print_piece(0);

}

void move_left()
{
    int i;
    for(i=0; i<4; i++)
    {
        if((((piece->squares)[i]).X)<=1)
        {
            return;
        }
    }
    for(i=0; i<4; i++)
    {

        for(i=0; i<4; i++)
        {
            if(board[(((piece->squares)[i]).X)-1][((piece->squares)[i]).Y]!=' ')
            {
                return ;
            }
        }

    }
    print_piece(' ');
    for(i=0; i<4; i++)
    {
        (((piece->squares)[i]).X)--;
    }
    print_piece(0);

}

void move_right()
{
    int i;
    for(i=0; i<4; i++)
    {
        if((((piece->squares)[i]).X)==10)
        {
            return;
        }
    }
    for(i=0; i<4; i++)
    {


        for(i=0; i<4; i++)
        {
            if(board[(((piece->squares)[i]).X)+1][((piece->squares)[i]).Y]!=' ')
            {
                return ;
            }
        }

    }
    print_piece(' ');
    for(i=0; i<4; i++)
    {
        (((piece->squares)[i]).X)++;
    }
    print_piece(0);
}

void rotate()
{
    switch(piece->name)
    {
    case 'O':
        break;
    case 'I':
        rotate_I();
        break;
    case 'J':
        rotate_J();
        break;
    case 'L':
        rotate_L();
        break;
    case 'T':
        rotate_T();
        break;
    case 'Z':
        rotate_Z();
        break;
    case 'S':
        rotate_S();
        break;
    }
}


void rotate_I()
{
    int i;

    if(piece->orientation==0)
    {
        for(i=0; i<4; i++)
        {
            if(((piece->squares)[0]).Y  <3)
            {
                return;
            }
            if (board[((piece->squares)[2]).X][((piece->squares)[0]).Y+i-2]!=' ')
            {
                return;
            }
        }
        print_piece(' ');
        ((piece->squares)[0]).X+=2;
        ((piece->squares)[0]).Y-=2;
        ((piece->squares)[1]).X+=1;
        ((piece->squares)[1]).Y-=1;
        ((piece->squares)[3]).X-=1;
        ((piece->squares)[3]).Y+=1;
        print_piece(0);
        piece->orientation=1;
    }
    else
    {
        for(i=0; i<4; i++)
        {
            if(((piece->squares)[0]).X  <3)
            {
                return;
            }
            if (board[((piece->squares)[0]).X+i-2][((piece->squares)[2]).Y]!=' ')
            {
                return;
            }
        }
        print_piece(' ');
        ((piece->squares)[0]).X-=2;
        ((piece->squares)[0]).Y+=2;
        ((piece->squares)[1]).X-=1;
        ((piece->squares)[1]).Y+=1;
        ((piece->squares)[3]).X+=1;
        ((piece->squares)[3]).Y-=1;
        print_piece(0);
        piece->orientation=0;
    }

}

void rotate_J()
{
    switch(piece->orientation)
    {
    case 0:
        if (board[((piece->squares)[1]).X][((piece->squares)[1]).Y+1]!=' ') return;
        if (board[((piece->squares)[1]).X-1][((piece->squares)[1]).Y+1]!=' ') return;
        if (board[((piece->squares)[1]).X][((piece->squares)[1]).Y-1]!=' ') return;
        print_piece(' ');
        ((piece->squares)[0]).X+=1;
        ((piece->squares)[0]).Y-=1;
        ((piece->squares)[2]).X-=1;
        ((piece->squares)[2]).Y+=1;
        ((piece->squares)[3]).X-=2;
        print_piece(0);
        piece->orientation=1;
        return;
    case 1:
        if (board[((piece->squares)[1]).X+1][((piece->squares)[1]).Y]!=' ') return;
        if (board[((piece->squares)[1]).X-1][((piece->squares)[1]).Y]!=' ') return;
        if (board[((piece->squares)[1]).X-1][((piece->squares)[1]).Y-1]!=' ') return;
        print_piece(' ');
        ((piece->squares)[0]).X+=1;
        ((piece->squares)[0]).Y+=1;
        ((piece->squares)[2]).X-=1;
        ((piece->squares)[2]).Y-=1;
        ((piece->squares)[3]).Y-=2;
        print_piece(0);
        piece->orientation=2;
        return;
    case 2:
        if (board[((piece->squares)[1]).X][((piece->squares)[1]).Y-1]!=' ') return;
        if (board[((piece->squares)[1]).X][((piece->squares)[1]).Y+1]!=' ') return;
        if (board[((piece->squares)[1]).X-1][((piece->squares)[1]).Y-1]!=' ') return;
        print_piece(' ');
        ((piece->squares)[0]).X-=1;
        ((piece->squares)[0]).Y+=1;
        ((piece->squares)[2]).X+=1;
        ((piece->squares)[2]).Y-=1;
        ((piece->squares)[3]).X+=2;
        print_piece(0);
        piece->orientation=3;
        return;
    case 3:
        if (board[((piece->squares)[1]).X+1][((piece->squares)[1]).Y]!=' ') return;
        if (board[((piece->squares)[1]).X-1][((piece->squares)[1]).Y]!=' ') return;
        if (board[((piece->squares)[1]).X+1][((piece->squares)[1]).Y+1]!=' ') return;
        print_piece(' ');
        ((piece->squares)[0]).X-=1;
        ((piece->squares)[0]).Y-=1;
        ((piece->squares)[2]).X+=1;
        ((piece->squares)[2]).Y+=1;
        ((piece->squares)[3]).Y+=2;
        print_piece(0);
        piece->orientation=0;
        return;




    }
}

void rotate_L()
{
    switch(piece->orientation)
    {
    case 0:
        if (board[((piece->squares)[1]).X][((piece->squares)[1]).Y-1]!=' ') return;
        if (board[((piece->squares)[1]).X][((piece->squares)[1]).Y+1]!=' ') return;
        if (board[((piece->squares)[1]).X-1][((piece->squares)[1]).Y-1]!=' ') return;
        print_piece(' ');
        ((piece->squares)[0]).X+=1;
        ((piece->squares)[0]).Y-=1;
        ((piece->squares)[2]).X-=1;
        ((piece->squares)[2]).Y+=1;
        ((piece->squares)[3]).Y-=2;
        print_piece(0);
        piece->orientation=1;
        return;
    case 1:
        if (board[((piece->squares)[1]).X+1][((piece->squares)[1]).Y]!=' ') return;
        if (board[((piece->squares)[1]).X-1][((piece->squares)[1]).Y]!=' ') return;
        if (board[((piece->squares)[1]).X+1][((piece->squares)[1]).Y-1]!=' ') return;
        print_piece(' ');
        ((piece->squares)[0]).X+=1;
        ((piece->squares)[0]).Y+=1;
        ((piece->squares)[2]).X-=1;
        ((piece->squares)[2]).Y-=1;
        ((piece->squares)[3]).X+=2;
        print_piece(0);
        piece->orientation=2;
        return;
    case 2:
        if (board[((piece->squares)[1]).X][((piece->squares)[1]).Y-1]!=' ') return;
        if (board[((piece->squares)[1]).X][((piece->squares)[1]).Y+1]!=' ') return;
        if (board[((piece->squares)[1]).X+1][((piece->squares)[1]).Y-1]!=' ') return;
        print_piece(' ');
        ((piece->squares)[0]).X-=1;
        ((piece->squares)[0]).Y+=1;
        ((piece->squares)[2]).X+=1;
        ((piece->squares)[2]).Y-=1;
        ((piece->squares)[3]).Y+=2;
        print_piece(0);
        piece->orientation=3;
        return;
    case 3:
        if (board[((piece->squares)[1]).X+1][((piece->squares)[1]).Y]!=' ') return;
        if (board[((piece->squares)[1]).X-1][((piece->squares)[1]).Y]!=' ') return;
        if (board[((piece->squares)[1]).X-1][((piece->squares)[1]).Y+1]!=' ') return;
        print_piece(' ');
        ((piece->squares)[0]).X-=1;
        ((piece->squares)[0]).Y-=1;
        ((piece->squares)[2]).X+=1;
        ((piece->squares)[2]).Y+=1;
        ((piece->squares)[3]).X-=2;
        print_piece(0);
        piece->orientation=0;
        return;
    }
}

void rotate_T()
{
    switch(piece->orientation)
    {
    case 0:
        if (board[((piece->squares)[1]).X][((piece->squares)[1]).Y-1]!=' ') return;
        print_piece(' ');
        ((piece->squares)[2]).X-=1;
        ((piece->squares)[2]).Y-=1;
        print_piece(0);
        piece->orientation=1;
        return;
    case 1:
        if (board[((piece->squares)[1]).X+1][((piece->squares)[1]).Y]!=' ') return;
        print_piece(' ');
        ((piece->squares)[3]).X+=1;
        ((piece->squares)[3]).Y-=1;
        print_piece(0);
        piece->orientation=2;
        return;
    case 2:
        if (board[((piece->squares)[1]).X][((piece->squares)[1]).Y+1]!=' ') return;
        print_piece(' ');
        ((piece->squares)[0]).X+=1;
        ((piece->squares)[0]).Y+=1;
        print_piece(0);
        piece->orientation=3;
        return;
    case 3:
        if (board[((piece->squares)[1]).X-1][((piece->squares)[1]).Y]!=' ') return;
        print_piece(' ');
        ((piece->squares)[0]).X-=1;
        ((piece->squares)[0]).Y-=1;
        ((piece->squares)[2]).X+=1;
        ((piece->squares)[2]).Y+=1;
        ((piece->squares)[3]).X-=1;
        ((piece->squares)[3]).Y+=1;
        print_piece(0);
        piece->orientation=0;
        return;
    }
}

void rotate_Z()
{
    switch(piece->orientation)
    {
    case 0:
        if (board[((piece->squares)[1]).X+1][((piece->squares)[1]).Y-1]!=' ') return;
        if (board[((piece->squares)[1]).X+1][((piece->squares)[1]).Y]!=' ') return;
        print_piece(' ');
        ((piece->squares)[0]).X+=2;
        ((piece->squares)[0]).Y-=1;
        ((piece->squares)[3]).Y-=1;
        print_piece(0);
        piece->orientation=1;
        return;
    case 1:
        if (board[((piece->squares)[1]).X-1][((piece->squares)[1]).Y]!=' ') return;
        if (board[((piece->squares)[1]).X+1][((piece->squares)[1]).Y+1]!=' ') return;
        print_piece(' ');
        ((piece->squares)[0]).X-=2;
        ((piece->squares)[0]).Y+=1;
        ((piece->squares)[3]).Y+=1;
        print_piece(0);
        piece->orientation=0;
        return;

    }

}

void rotate_S()
{
    switch(piece->orientation)
    {
    case 0:
        if (board[((piece->squares)[0]).X-1][((piece->squares)[0]).Y-1]!=' ') return;
        if (board[((piece->squares)[0]).X-1][((piece->squares)[0]).Y]!=' ') return;
        print_piece(' ');
        ((piece->squares)[1]).X-=2;
        ((piece->squares)[1]).Y-=1;
        ((piece->squares)[2]).Y-=1;
        print_piece(0);
        piece->orientation=1;
        return;
    case 1:
        if (board[((piece->squares)[0]).X-1][((piece->squares)[0]).Y+1]!=' ') return;
        if (board[((piece->squares)[0]).X+1][((piece->squares)[0]).Y+1]!=' ') return;
        print_piece(' ');
        ((piece->squares)[1]).X+=2;
        ((piece->squares)[1]).Y+=1;
        ((piece->squares)[2]).Y+=1;
        print_piece(0);
        piece->orientation=0;
        return;

    }
}

void create_O()
{
    piece->name='O';
    piece->symbol = PIECE_SYMBOL;
    /*piece->symbol = 'O';*/
    piece->color=13;
    piece->orientation=0;
    ((piece->squares)[0]).X=5;
    ((piece->squares)[0]).Y=1;
    ((piece->squares)[1]).X=6;
    ((piece->squares)[1]).Y=1;
    ((piece->squares)[2]).X=5;
    ((piece->squares)[2]).Y=2;
    ((piece->squares)[3]).X=6;
    ((piece->squares)[3]).Y=2;

}

void create_I()
{
    piece->name='I';
    piece->symbol = PIECE_SYMBOL;
    /*piece->symbol = 'O';*/
    piece->color=12;
    piece->orientation=0;
    ((piece->squares)[0]).X=5;
    ((piece->squares)[0]).Y=1;
    ((piece->squares)[1]).X=6;
    ((piece->squares)[1]).Y=1;
    ((piece->squares)[2]).X=7;
    ((piece->squares)[2]).Y=1;
    ((piece->squares)[3]).X=8;
    ((piece->squares)[3]).Y=1;
}

void create_J()
{
    piece->name='J';
    piece->symbol = PIECE_SYMBOL;
    /*piece->symbol = 'O';*/
    piece->color=10;
    piece->orientation=0;
    ((piece->squares)[0]).X=5;
    ((piece->squares)[0]).Y=1;
    ((piece->squares)[1]).X=6;
    ((piece->squares)[1]).Y=1;
    ((piece->squares)[2]).X=7;
    ((piece->squares)[2]).Y=1;
    ((piece->squares)[3]).X=7;
    ((piece->squares)[3]).Y=2;
}

void create_L()
{
    piece->name='L';
    piece->symbol = PIECE_SYMBOL;
    /*piece->symbol = 'O';*/
    piece->color=6;
    piece->orientation=0;
    ((piece->squares)[0]).X=5;
    ((piece->squares)[0]).Y=1;
    ((piece->squares)[1]).X=6;
    ((piece->squares)[1]).Y=1;
    ((piece->squares)[2]).X=7;
    ((piece->squares)[2]).Y=1;
    ((piece->squares)[3]).X=5;
    ((piece->squares)[3]).Y=2;
}

void create_T()
{
    piece->name='T';
    piece->symbol = PIECE_SYMBOL;
    /*piece->symbol = 'O';*/
    piece->color=9;
    piece->orientation=0;
    ((piece->squares)[0]).X=5;
    ((piece->squares)[0]).Y=1;
    ((piece->squares)[1]).X=6;
    ((piece->squares)[1]).Y=1;
    ((piece->squares)[2]).X=7;
    ((piece->squares)[2]).Y=1;
    ((piece->squares)[3]).X=6;
    ((piece->squares)[3]).Y=2;
}

void create_Z()
{
    piece->name='Z';
    piece->symbol = PIECE_SYMBOL;
    /*piece->symbol = 'O';*/
    piece->color=4;
    piece->orientation=0;
    ((piece->squares)[0]).X=5;
    ((piece->squares)[0]).Y=1;
    ((piece->squares)[1]).X=6;
    ((piece->squares)[1]).Y=1;
    ((piece->squares)[2]).X=6;
    ((piece->squares)[2]).Y=2;
    ((piece->squares)[3]).X=7;
    ((piece->squares)[3]).Y=2;
}

void create_S()
{
    piece->name='S';
    piece->symbol = PIECE_SYMBOL;
    /*piece->symbol = 'O';*/
    piece->color=1;
    piece->orientation=0;
    ((piece->squares)[0]).X=6;
    ((piece->squares)[0]).Y=1;
    ((piece->squares)[1]).X=7;
    ((piece->squares)[1]).Y=1;
    ((piece->squares)[2]).X=5;
    ((piece->squares)[2]).Y=2;
    ((piece->squares)[3]).X=6;
    ((piece->squares)[3]).Y=2;
}


void SetColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}



