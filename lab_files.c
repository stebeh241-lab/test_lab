#include <stdio.h>
#include <stdbool.h>

typedef struct mat_size // a struct storing only the size of a matrix. This should just have been in the matrix struct.
{
    int n_rows;
    int n_columns;
} mat_size;

typedef struct row
{
    float numbers[100];
} row;

typedef struct column
{
    float numbers[100];
} column;

typedef struct matrix // This should just have had members float matrix[100][100], int n_rows, int n_columns
{
    row rows[100];
    column columns[100];
} matrix;

mat_size read_matrix_size(char *filename) // Takes a file and reads the size of the matrix it contains from the first row
{
    mat_size size;
    FILE *fp;
    fp = fopen(filename, "r");
    size.n_rows = 0;
    size.n_columns = 0;
    fscanf(fp, "%d %d", &size.n_rows, &size.n_columns);
    fclose(fp);
    printf("Rows: %d\nColumns: %d\n", size.n_rows, size.n_columns);
    return size;
}

bool multiplication_possible(mat_size size_of_first, mat_size size_of_second) // just checking if multiplication is possible using a mat_size struct for each matrix as input.
{
    if (size_of_first.n_columns == size_of_second.n_rows)
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

matrix file_to_struct_mat_1(char *mat_file_in, mat_size size_of_mat_in) // Reads first matrix and puts its data into rows :P
{
    int n_rows = size_of_mat_in.n_rows;
    int n_columns = size_of_mat_in.n_columns;
    matrix mat_out;
    FILE *fp;

    fp = fopen(mat_file_in, "r");
    char scrap[10];
    fgets(scrap, sizeof(scrap), fp);
    printf("Reading first matrix from file.\nScrapping first row: %s\n", scrap); // printing scrap to see if it scraps
    for (int n = 0; n < n_rows; n++)                                             // en iteration av nästa loop för varje rad.
    {

        for (int i = 0; i < n_columns; i++) // för varje column läser vi ett element och lägger på plats i structen.
        {
            fscanf(fp, "%f", &mat_out.rows[n].numbers[i]);
            printf("mat_1: row %d number %d is %f\n", n, i, mat_out.rows[n].numbers[i]);
        }
    }
    fclose(fp);
    return mat_out;
}

matrix file_to_struct_mat_2(char *mat_file_in, mat_size size_of_mat_in) // Reads second matrix and puts its data into columns :P
{
    int n_rows = size_of_mat_in.n_rows;
    int n_columns = size_of_mat_in.n_columns;
    matrix mat_out;
    FILE *fp;

    fp = fopen(mat_file_in, "r");
    char scrap[10];
    fgets(scrap, sizeof(scrap), fp);
    printf("Reading second matrix from file.\nScrapping first row: %s\n", scrap); // printing scrap to see if it scraps
    for (int n = 0; n < n_rows; n++)                                              // en iteration av nästa loop för varje rad.
    {

        for (int i = 0; i < n_columns; i++) // för varje column läser vi ett element och lägger på plats i structen.
        {
            fscanf(fp, "%f", &mat_out.columns[i].numbers[n]);
            printf("mat_1: column %d number %d is %f\n", i, n, mat_out.columns[i].numbers[n]);
        }
    }
    fclose(fp);
    return mat_out;
}

matrix matrix_multiplier(matrix input_1, matrix input_2, mat_size size_of_1, mat_size size_of_2) // takes two "matrices" and their sizes and returns a matrix with new size.
{
    matrix output;
    for (int i = 0; i < size_of_1.n_rows; i++)
    {
        for (int j = 0; j < size_of_2.n_columns; j++)
        {
            output.rows[i].numbers[j] = 0;
            for (int n = 0; n < size_of_1.n_columns; n++)
            {
                float product = input_1.rows[i].numbers[n] * input_2.columns[j].numbers[n];
                output.rows[i].numbers[j] = output.rows[i].numbers[j] + product;
            }
        }
    }
    return output;
}

void write_result_file(char *filename, matrix result, int rows_of_A, int columns_of_B) // takes a result matrix struc, and indirectly sizes of it, plus a filenamn and writes to file. Not a beautiful solution.
{
    printf("Resulting matrix will be %d rows and %d columnes\n", rows_of_A, columns_of_B);
    FILE *fp;
    fp = fopen(filename, "w");
    fprintf(fp, "%d %d\n", rows_of_A, columns_of_B);
    for (int n = 0; n < rows_of_A; n++) // en iteration av nästa loop för varje rad.
    {

        for (int i = 0; i < columns_of_B; i++) // för varje column skriver vi ett element.
        {
            printf("out: rad %d column %d = %f,\n", n, i, result.rows[n].numbers[i]);
            fprintf(fp, "%f ", result.rows[n].numbers[i]);
        }
        fprintf(fp, "\n");
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
            mat_size size_of_A = read_matrix_size(path_to_A);
            mat_size size_of_B = read_matrix_size(path_to_B);
            if (multiplication_possible(size_of_A, size_of_B))
            {
                matrix A = file_to_struct_mat_1("A.mat", size_of_A);
                matrix B = file_to_struct_mat_2("B.mat", size_of_B);
                matrix result = matrix_multiplier(A, B, size_of_A, size_of_B);
                write_result_file(result_name, result, size_of_A.n_rows, size_of_B.n_columns);
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
}