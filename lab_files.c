#include <stdio.h>
#include <stdbool.h>

typedef struct mat_size
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

typedef struct matrix
{
    row rows[100];
    column columns[100];
} matrix;

void create_file(char *filename)
{
    FILE *fp;                  // create pointer pointing to a FILE
    fp = fopen(filename, "w"); // creates the result file
    fclose(fp);
}

void write_to_file(char *file, char *input)
{
    FILE *fp;
    fp = fopen(file, "w");
    fprintf(fp, "%s\n", input);
    fclose(fp);
}

char read_from_file(char *filename)
{
    FILE *fp;
    fp = fopen(filename, "r");
    char red_content[100];
    fgets(red_content, 100, fp);
}

mat_size read_matrix_size(char *filename)
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

bool multiplication_possible(mat_size size_of_first, mat_size size_of_second) // här ska vi börja jobba
{
    if (size_of_first.n_rows == size_of_second.n_columns)
    {
        printf("Compatible sizes so multi is possible!\n");
        return true;
    }
    else
    {
        printf("Incompatible sizes so multi is NOT possible!\n Order matters with matrices!\n");
        return false;
    }
}

matrix file_to_struct(char *mat_file_in, mat_size size_of_mat_in) // nu blev det matrix_read_data av den här ändå?
{
    int n_rows = size_of_mat_in.n_rows;
    int n_columns = size_of_mat_in.n_columns;
    matrix mat_out;
    FILE *fp;

    fp = fopen(mat_file_in, "r");
    char scrap[3];
    fgets(scrap, sizeof(scrap), fp);
    for (int n = 0; n < n_rows; n++) // en iteration av nästa loop för varje rad.
    {

        for (int i = 0; i < n_columns; i++) // för varje column läser vi ett element och lägger på plats i structen.
        {
            fscanf(fp, "%f", &mat_out.rows[n].numbers[i]);
        }
    }
    fclose(fp);
    return mat_out;
}

matrix matrix_multiplier(matrix input_1, matrix input_2, mat_size size_of_1, mat_size size_of_2)
// behöver nog bara ha en av deras size som input? Behöver sätta alla element till 0?
{
    matrix output;
    for (int i = 0; i < size_of_1.n_rows; i++)
    {
        float row_1_sum = 0;
        for (int n = 0; n < size_of_1.n_columns; n++)
        {
            output.rows[i].numbers[i] = 0;
            float product = input_1.rows[i].numbers[i] * input_2.columns[i].numbers[i];
            output.rows[i].numbers[i] = output.rows[i].numbers[i] + product;
        }
    }
    return output;
}

void write_result_file(matrix result)
{
}

int main()
{
    // create_file("mat1.txt");
    // write_to_file("mat1.txt", "3 4");
    mat_size size_of_A = read_matrix_size("A.mat");
    mat_size size_of_B = read_matrix_size("B.mat");
    multiplication_possible(size_of_A, size_of_B);
    matrix A = file_to_struct("A.mat", size_of_A);
    matrix B = file_to_struct("B.mat", size_of_B);
    matrix_multiplier(A, B, size_of_A, size_of_B);
}