#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// find seed for random
int find_seed(int len, int seed, char *account, char *key)
{
    for (int i = 0; i < len; i++)
        for (int j = 0; j < 63; j++)
            if (account[i] == key[j])
                seed += j;
    return seed;
}

int main(void)
{
    char web_key[] =
        "PwFeSiV2cCh7Ju8AnEsDaXd0HoTm9LrWtBb3Q5fUgRyKvZkI1xYl4MzNjOqG6p ";
    // 63 -> this is provided from a special string

    char account[100000];          // the web name you want to submit
    char general_password[100000]; // the password which you usually used

    // scanf your web name and password
    printf("Please enter your web's name : ");
    fgets(account, sizeof(account), stdin);
    printf("Please enter your general password : ");
    fgets(general_password, sizeof(general_password), stdin);

    int acc_len = strlen(account), password_len = strlen(general_password);

    // generate random number w -> used for deciding row numbers for matrix A and
    // generating matrix A
    int seed = 0;
    seed = find_seed(acc_len, seed, account, web_key);
    srand(seed);
    int w = rand() % 999 + 2;

    int A_row = (w % password_len) + password_len; // row numbers for matrix A

    // allocate memory for matrix A -> is used for encode our passwords
    int **matrix = (int **)calloc(A_row, sizeof(int *));
    for (int i = 0; i < A_row; i++)
        matrix[i] = (int *)calloc(password_len, sizeof(int));

    // generate matrix A using web_key
    int tmp = 0, tempcount = 0;
    for (int i = 0; i < A_row; i++)
    {
        for (int j = 0; j < password_len; j++)
        {
            matrix[i][j] = ((int)web_key[tmp]) + (2 * w + 5) + (tempcount / 63);
            tmp++;
            tempcount++;
            tmp %= 63;
        }
    }

    //
    for (int i = 0; i < A_row; i++)
    {
        for (int j = 0; j < password_len; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // transpose general password
    int number_general_password[password_len][1];
    for (int i = 0; i < password_len; i++)
        number_general_password[i][0] = (int)general_password[i];

    int new_password[A_row][1];

    // encoding
    for (int i = 0; i < A_row; i++)
        new_password[i][0] = 0;
    for (int i = 0; i < A_row; i++)
    {
        for (int j = 0; j < password_len; j++)
            new_password[i][0] +=
                (matrix[i][j] % 10000) * (number_general_password[j][0] % 10000);
    }

    int number[10000];
    int numberfornew[10000];

    // combine every three numbers in a group and transport it to an ASCII code
    int j = 0;
    for (int i = 0; i < A_row; i++)
    {
        while (new_password[i][0] > 0)
        {
            number[j] = new_password[i][0] % 10;
            new_password[i][0] /= 10;
            j++;
        }
    }
    if (j % 3 == 1)
    {
        number[j] = 0;
        j++;
    }
    else if (j % 3 == 2)
    {
        number[j] = 0;
        number[j + 1] = 0;
        j += 2;
    }
    int numcase = 0;
    for (int i = 0; i < j; i += 3)
    {
        numberfornew[numcase] =
            number[i] * 100 + number[i + 1] * 10 + number[i + 2];
        numberfornew[numcase] = (numberfornew[numcase] % 89) + 33;
        numcase++;
    }

    // eliminate characters that can't be used in password
    // characters can be used in password: 33 35~37 47~57(number) 64~90(capital)
    // 97~122(lower case)
    int index[] = {
        33, 35, 36, 37,
        64}; // ASCII cade of special characters that can be used in password
    for (int i = 0; i < j; i++)
    {
        for (int k = 0; k < 5; k++)
        {
            if (numberfornew[i] == 34)
                numberfornew[i] = index[numberfornew[i] % 5];
            else if (numberfornew[i] > 37 && numberfornew[i] < 47)
                numberfornew[i] = index[numberfornew[i] % 5];
            else if (numberfornew[i] > 57 && numberfornew[i] < 64)
                numberfornew[i] = index[numberfornew[i] % 5];
            else if (numberfornew[i] > 90 && numberfornew[i] < 97)
                numberfornew[i] = index[numberfornew[i] % 5];
        }
    }

    // transport ASCII code into corresponded character
    char lastpassword[10000];
    for (int i = 0; i < numcase; i++)
    {
        lastpassword[i] = (char)numberfornew[i];
    }

    // printf encoded password
    printf("New password : ");
    if (strlen(lastpassword) < 10)
        printf("%10s", lastpassword);
    else
        for (int i = 0; i < password_len; i++)
            printf("%c", lastpassword[i]);
    printf("\n");
    return 0;
}