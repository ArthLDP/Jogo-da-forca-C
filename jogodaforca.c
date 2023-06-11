#include <windows.h>
#include <stdio.h>
#include <string.h>

void text_upper(char *text, char *text_upper)
{
    int i;
    strcpy(text_upper, text);
    for(i = 0; text_upper[i] != '\0'; i++)
    {
        if(text_upper[i] >= 97 && text_upper[i] <= 122) // se for minúsculo no ascii
        {
            text_upper[i] -= 32; // vai receber ascii maiúsculo
        }
    }
}

void draw_man(int **lives_draw)
{
    switch(**lives_draw)
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

void guess_letter(char *secret, char *secret_cpy, int *lives, int word_sz, char *secret_upper)
{
    int i;
    char guess_letter;
    char guess_letter_upper;
    char sub_menu;
    int hit;
    int error_count = 0;
    char error_letters[7] = {'\0'};

    do
    {
        hit = 0;
        system("cls");
        printf("Palavra secreta(possui %d letras): %s          Vidas: %d", word_sz, secret_cpy, *lives);
        printf("          Letras erradas: ");

        for(i = 0; i <= error_count; i++)
        {
            printf("%c ", error_letters[i]);
        }

        printf("\n\n");
        draw_man(&lives);
        printf("\n\nTente adivinhar alguma letra na palavra: ");
        scanf(" %1c", &guess_letter);
        guess_letter_upper = guess_letter;
        if(guess_letter_upper >= 97 && guess_letter_upper <= 122)
        {
            guess_letter_upper -= 32;
        }

        for(i = 0; i < word_sz; i++)
        {
            if(secret_upper[i] == guess_letter_upper)
            {
                secret_cpy[i] = secret[i];
                hit++;
            }
        }

        system("cls");

        if(!strcmp(secret_cpy, secret)) // retorna 0 se forem iguais por isso "!"
        {
            printf("\nParabens voce ganhou\n\nPalavra secreta: %s\n\n", secret);
            system("pause");
            exit(1);
        }

        if(hit == 0)
        {
            *lives = *lives - 1;
            error_letters[error_count] = guess_letter;
            printf("Palavra secreta(possui %d letras): %s          Vidas: %d", word_sz, secret_cpy, *lives);
            printf("          Letras erradas: ");

            for(i = 0; i <= error_count; i++)
            {
                printf("%c ", error_letters[i]);
            }

            error_count++;
            printf("\n\n");
            draw_man(&lives);
            printf("\nVoce errou, Letra: '%c' nao encontrada\n\n", guess_letter);
        }
        else
        {
            printf("Palavra secreta(possui %d letras): %s          Vidas: %d", strlen(secret_cpy), secret_cpy, *lives);
            printf("          Letras erradas: ");

            for(i = 0; i <= error_count; i++)
            {
                printf("%c ", error_letters[i]);
            }

            printf("\n\n");
            draw_man(&lives);
            printf("\nLetra: '%c' encontrada\n\n", guess_letter);
        }

        if (*lives > 0)
        {
            printf("Deseja continuar adivinhando as letras? Escolha a opcao (nao) caso saiba a palavra\n(1) - Sim\n(2) - Nao\n:");
            scanf(" %1c", &sub_menu);
            if(sub_menu == '2')
            {
                break;
            }
        }
    } while (*lives > 0);
}

void guess_word(char *secret, char *secret_cpy, int *lives, char *secret_upper)
{
    char secret_cpy_upper[20];
    system("cls");
    printf("Palavra secreta(possui %d letras): %s\n\n", strlen(secret_cpy), secret_cpy);
    printf("Tente adivinhar a palavra, se errar perde todas as vidas: ");
    scanf("%19s", secret_cpy);
    text_upper(secret_cpy, secret_cpy_upper);

    if(!strcmp(secret_cpy_upper, secret_upper)) // comparar a entrada maiúscula com palavra secreta maiúscula
    {
        printf("\nParabens voce ganhou\n\nPalavra secreta: %s\n\n", secret);
        system("pause");
        exit(1);
    }
    else
    {
        *lives = 0;
        draw_man(&lives);
    }
}

int main()
{
    int i;
    int word_size;
    char secret_word[20];
    char secret_word_cpy[20];
    char secret_word_upper[20];
    int lives = 7;
    char menu;

    printf("Digite a palavra secreta: ");
    scanf("%19s", secret_word); //19 pois têm que sobrar 1 para: delimitador de string '\0'
    text_upper(secret_word, secret_word_upper);
    strcpy(secret_word_cpy, secret_word);
    word_size = strlen(secret_word_cpy);

    for(i = 0; i < word_size; i++)
    {
        secret_word_cpy[i] = '*';
    }

    do
    {
        system("cls");
        printf("//// ESCOLHA UMA DAS OPCOES ABAIXO //// \n\n");
        printf("1 - Adivinhar letras na palavra\n2 - Adivinhar a palavra(UMA CHANCE)\n\n: ");
        scanf(" %1c", &menu);
        switch(menu)
        {
            case '1':
                guess_letter(secret_word, secret_word_cpy, &lives, word_size, secret_word_upper);
                if(lives > 0)
                {
                    guess_word(secret_word, secret_word_cpy, &lives, secret_word_upper);
                }
                break;
            case '2':
                guess_word(secret_word, secret_word_cpy, &lives, secret_word_upper);
                break;
            default:
                printf("\nEssa opcao nao existe\n\n");
                system("pause");
        }
    } while (lives > 0);

    printf("\nVoce perdeu todas as vidas, a palavra correta era: %s\n\n", secret_word);
    system("pause");

    return 0;
}