#pragma once
char record = 0;
#define PRINT_RECORD printf("Record:\t%d\n", record)
#define NEW_RECORD(x) if (x > record) save_record()
void save_record() {
    FILE *fp = fopen("record.txt", "w");
    fprintf(fp, "%d", snake_length);
    fclose(fp);
}

void load_record() {
    FILE *fp = fopen("record.txt", "r");
    if (!fp) { return; }
    fscanf(fp, "%d", &record);
    fclose(fp);
}