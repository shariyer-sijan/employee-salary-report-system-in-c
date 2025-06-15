#include <stdio.h>
int read_data(FILE *input_file, int *e_id, float *basic_salary, float *percentage){
    return fscanf(input_file, "%d %f %f", e_id, basic_salary, percentage);
}
float calculation(float basic_salary, float percentage){
    return basic_salary + (basic_salary * percentage / 100);
}
void write_id_salary(FILE *output_file, int e_id, float total_salary){
    fprintf(output_file, "Employee ID: %d, Total Salary: %.2f\n", e_id, total_salary);
}
int main(){
char input_file_name[100], output_file_name[100];
printf("Please provide the name of the input file: ");
scanf("%s", input_file_name);
printf("Please provide the name of the output file: ");
scanf("%s", output_file_name);
FILE *input_file = fopen(input_file_name, "r");
FILE *output_file = fopen(output_file_name, "w");
if(input_file == NULL){
    printf("Error: Could not open the input file '%s'!\n", input_file_name);
    return 1;
}
if(output_file == NULL){
    printf("Error: Could not open the output file '%s'!\n", output_file_name);
    fclose(input_file);
    return 1;
}
int num_emp, processed = 0, skipped = 0;
if(fscanf(input_file, "%d", &num_emp) != 1 || num_emp <= 0) {
    printf("Error: Invalid number of employees in the input file.\n");
    fclose(input_file);
    fclose(output_file);
    return 1;
}
for(int i = 0; i < num_emp; i++){
    int e_id;
    float basic_salary, percentage, total_salary;
    if(read_data(input_file, &e_id, &basic_salary, &percentage) != 3){
        printf("Warning: Skipping invalid entry at line %d.\n", i + 2);
        skipped++;
        continue;
    }
    total_salary = calculation(basic_salary, percentage);
    write_id_salary(output_file, e_id, total_salary);
    processed++;
}
fclose(input_file);
fclose(output_file);
printf("Salary report successfully generated in '%s'.\n", output_file_name);
printf("Processed: %d employees, Skipped: %d invalid entries.\n", processed, skipped);
    return 0;
}


