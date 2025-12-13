#include <stdio.h>
#include <stdbool.h>

typedef struct matrix
{
    int n_rows;
    int n_columns;
    float mat[100][100];
} matrix;

matrix read_file(char *filenamn)
{
    matrix mat_out;
    FILE *fp;
    fp = fopen(filenamn, "r");
    if (fp == NULL)
    {
        perror("Error opening file in read_file");
        return mat_out;
    }
    mat_out.n_rows = 0;
    mat_out.n_columns = 0;
    fscanf(fp, "%d %d", &mat_out.n_rows, &mat_out.n_columns);
    printf("Rows: %d\nColumns: %d\n", mat_out.n_rows, mat_out.n_columns);
    for (int n = 0; n < mat_out.n_rows; n++) // en iteration av nästa loop för varje rad.
    {
        for (int i = 0; i < mat_out.n_columns; i++) // för varje column läser vi ett element och lägger på plats i structen.
        {
            fscanf(fp, "%f", &mat_out.mat[n][i]);
            printf("row %d column %d is %f\n", n, i, mat_out.mat[n][i]);
        }
    }
    fclose(fp);
    return mat_out;
}

bool multiplicable(matrix input_1, matrix input_2)
{
    if (input_1.n_columns == input_2.n_rows)
    {
        printf("Compatible sizes so multi is possible!\n");
        return true;
    }
    else
    {
        printf("Incompatible sizes so multi is NOT possible!\nOrder matters with matrices!\n");
        return false;
    }
}

matrix multiply(matrix input_1, matrix input_2)
{
    matrix output;
    output.n_rows = input_1.n_rows;
    output.n_columns = input_2.n_columns;
    for (int i = 0; i < input_1.n_rows; i++)
    {
        for (int j = 0; j < input_2.n_columns; j++)
        {
            output.mat[i][j] = 0;
            for (int n = 0; n < input_1.n_columns; n++)
            {
                float product = input_1.mat[i][n] * input_2.mat[n][j];
                output.mat[i][j] = output.mat[i][j] + product;
            }
        }
    }
    return output;
}

void write_result_file(char *filename, matrix result) // takes a result matrix struc and a filenamn and writes to file.
{
    printf("Resulting matrix will be %d rows and %d columnes\n", result.n_rows, result.n_columns);
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        perror("Error opening file in read_file");
        return;
    }
    fprintf(fp, "%d %d\n", result.n_rows, result.n_columns); // prints the size of result to file
    for (int n = 0; n < result.n_rows; n++)                  // One iteration for each row of result matrix
    {
        for (int i = 0; i < result.n_columns; i++) // One iteration for each column of result matrix
        {
            printf("out: rad %d column %d = %f,\n", n, i, result.mat[n][i]);
            fprintf(fp, "%f ", result.mat[n][i]);
        }
        fprintf(fp, "\n"); // linebreak after each row has been printed to file.
    }
    fclose(fp);
}

int main()
{
    int run = 1;
    while (run == 1)
    {
        printf("* This is a simple matrix multiplication tool\n* Input is two files with format pascalmatrix\n* Press 1 to start or 0 to exit.\n");
        printf("\n");
        scanf("%d", &run);
        if (run == 1)
        {
            printf("Choose name of first file, it needs to be in current folder\n");
            char path_to_A[256];
            scanf("%s", path_to_A);
            printf("Choose second file, it needs to be in current folder\n");
            char path_to_B[256];
            scanf("%s", path_to_B);
            printf("Choose name of output file, it will be saved in current folder\n");
            char result_name[256];
            scanf("%s", result_name);
            matrix A = read_file(path_to_A);
            matrix B = read_file(path_to_B);
            if (multiplicable(A, B))
            {
                matrix result = multiply(A, B);
                write_result_file(result_name, result);
            }
            printf("********************************************************\n");
            printf("MULTIPLICATION COMPLETE, RESULT IS STORED IN %s\n", result_name);
            printf("********************************************************\n");
        }
        else
        {
            run = 0;
        }
    }
    return 0;
}