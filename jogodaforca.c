#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>

#define LIMIT 20

void draw_man(int **lives)
{
    switch(**lives)
    {
        case 7:
            break;
        case 6:
            printf("                                                                                        O\n");
            break;
        case 5:
            printf("                                                                                        O\n");
            printf("                                                                                        |\n");
            break;
        case 4:
            printf("                                                                                        O\n");
            printf("                                                                                        |\n");
            printf("                                                                                       /\n");
            break;
        case 3:
            printf("                                                                                        O\n");
            printf("                                                                                        |\n");
            printf("                                                                                       / \\\n");
            break;
        case 2:
            printf("                                                                                        O\n");
            printf("                                                                                       \\\n");
            printf("                                                                                        |\n");
            printf("                                                                                       / \\\n");
            break;
        case 1:
            printf("                                                                                        O\n");
            printf("                                                                                       \\ /\n");
            printf("                                                                                        |\n");
            printf("                                                                                       / \\\n");
            break;
        default:
            printf("                                                                                        X\n");
            printf("                                                                                       \\ /\n");
            printf("                                                                                        |\n");
            printf("                                                                                       / \\\n");
    }
}

void guess(char *secret_word, char *secret_word_hidden, int *lives)
{
    char guess_letter;
    boolean hit;

    while (*lives > 0) 
    {
        hit = false;
        system("cls");
        printf("Palavra secreta: %s\nVidas: %d\n", secret_word_hidden, *lives);
        draw_man(&lives);
        printf("\n\nAdivinhe uma letra: ");
        guess_letter = getchar();
        while (getchar() != '\n'); //limpar o buffer de entrada até encontrar '\n' gerado pelo getchar()
        guess_letter = toupper(guess_letter);

        for (int i = 0; secret_word[i] != '\0'; i++) 
        {
            if (guess_letter == toupper(secret_word[i])) 
            {
                hit = true;
                secret_word_hidden[i] = secret_word[i];
            }
        }

        if (!hit) 
        {
            *lives -= 1;
        }

        system("cls");
        printf("Palavra secreta: %s\nVidas: %d\n", secret_word_hidden, *lives);
        draw_man(&lives);

        if (!strcmp(secret_word, secret_word_hidden)) 
        {
            printf("\n\nParabens voce venceu!, a palavra secreta era: %s\n", secret_word);
            break;
        }

        if (*lives <= 0) 
        {
            printf("\n\nVoce perdeu todas as vidas, a palavra secreta era: %s\n", secret_word);
        }
    }
}

int main() 
{
    int lives = 7;
    int secret_word_size;
    char secret_word[LIMIT];
    char secret_word_hidden[LIMIT];
    char try_again = 's';

    while (try_again == 's' || try_again == 'S') 
    {
        lives = 7;
        printf("Digite a palavra para ser adivinhada: ");
        fgets(secret_word, LIMIT, stdin); //fgets lê espaços e \n, se chegar no LIMIT coloca um '\0' no lugar do \n
        secret_word[strlen(secret_word) - 1] = '\0'; //tirar o \n e colocar '\0' na última pos
        secret_word_size = strlen(secret_word);
        strncpy(secret_word_hidden, secret_word, secret_word_size + 1); //secret_word_size + 1 por causa do '\0'

        for (int i = 0; secret_word_hidden[i] != '\0'; i++) 
        {
            if (secret_word_hidden[i] != ' ') 
            {
                secret_word_hidden[i] = '?';
            }
        }

        guess(secret_word, secret_word_hidden, &lives);

        printf("\n\nDeseja jogar novamente? sim(s) ou nao(n): ");
        try_again = getchar();
        while (getchar() != '\n');
        system("cls");
    }

    return 0;
}
