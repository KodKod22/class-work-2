#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"prog2_ex1.h"
#define max_name 100
typedef struct track
{
    char *name_track;
    int legth;
    int position;
}track;
typedef struct records
{
    char *name;
    int year;
    int num_of_traks;
    enum record_category_e ct;
    track *own_track;
}records;
int i=0,j=0;
int find_record(char* name_record){
    records *rc = (records *)malloc(MAX_RECORDS * sizeof(records));
    memset(rc, 0, MAX_RECORDS * sizeof(records));

    for (int a = 0; a < i; a++)
    {
        
        if (strcmp(rc[a].name, name_record) == 0)
        {
            free(rc);
            return 1;
        }
    }
    free(rc);
    return 0;
}
void Add_Record(FILE *fp,char *buffer){
    records **rc = (records **)malloc(MAX_RECORDS * sizeof(records *));
    rc[i] = (records*)malloc(sizeof(records));
    if (rc[i]==NULL)
    {
        prog2_report_error_message(OUT_OF_MEMORY);
        return;
    }
    
    char *token=strtok(buffer," \n\r");
    token=strtok(NULL," \n\r");
    token=strtok(NULL," \n\r");
    rc[i]->name=(char *)malloc(strlen(token)+1);
    if (rc[i]->name==NULL)
    {
        prog2_report_error_message(OUT_OF_MEMORY);
        free(rc[i]->name);
        return;
    }
    int rez=find_record(token);
    if (rez == 1)
    {
        prog2_report_error_message(RECORD_ALREADY_EXISTS);
        return;
    }
    strcpy(rc[i]->name,token);

    token=strtok(NULL," \n\r");
    rc[i]->year=atoi(token);
    if (rc[i]->year<1900)
    {
        prog2_report_error_message(INVALID_YEAR);
        return;
    }
    
    token=strtok(NULL," \n\r");
    rc[i]->num_of_traks=atoi(token);
    if (rc[i]->num_of_traks<0)
    {
        prog2_report_error_message(INVALID_NUM_OF_TRACKS);
        return;
    }
    enum record_category_e cr;
        token = strtok(NULL," \n\r");
        if (strcmp(token, "ROCK") == 0)
        {
                cr= ROCK;
        } else if (strcmp(token, "POP") == 0) {
                cr = POP;
        } else if (strcmp(token, "JAZZ") == 0) {
                cr = JAZZ;
        }else if (strcmp(token, "BLUES")==0)
        {
                cr = BLUES;
        }else if (strcmp(token, "HIP_HOP")==0)
        {
                cr =HIP_HOP;
        }else if (strcmp(token, "COUNTRY")==0)
        {
                cr =COUNTRY;
        }else if (strcmp(token, "CLASSIC")==0)
        {
                cr = CLASSIC;
        }else {
            prog2_report_error_message(INVALID_CATEGORY);
            return;
        }
        rc[i]->ct = cr;
    i++;
    free(rc);
}

int chack_track(char *name_track)
{
    records *rc=(records*)malloc(sizeof(records));
    int a, b;
    for (a = 0; a <MAX_RECORDS; a++){
        for (b = 0; b < rc->num_of_traks; b++) {
            if (strcmp(rc->own_track[b].name_track, name_track) == 0)
            {
                free(rc);
                return 1;
            }
        }
    }
    free(rc);
    return 0;
}
void Remove_Record(FILE *fp, char *buffer)
{
    char *token = strtok(buffer, " \n\r");
    token = strtok(NULL, " \n\r");
    token = strtok(NULL, " \n\r");
    int record_to_delete = find_record(token);
    if (record_to_delete == 0) {
        prog2_report_error_message(RECORD_DOESNT_EXIST);
        return;
    }
    FILE *temp_file;
    char temp_FileName[max_name];
    strcpy(temp_FileName, "temp___");
    strcat(temp_FileName, "rb.text");
    temp_file = fopen(temp_FileName, "wb");
    if (temp_file == NULL) {
        prog2_report_error_message(CANNOT_OPEN_FILE);
        return;
    }
    
    int record_count = 0;
    records record;
    while (fread(&record, sizeof(records), 1, fp) == 1) {
        record_count++;
        if (record_count == record_to_delete) {
            continue; 
        }
        fwrite(&record, sizeof(records), 1, temp_file);
    }
    fclose(fp);
    fclose(temp_file);
    
    remove("rb.text");
    rename(temp_FileName, "rb.text");
}

void add_trck(FILE *fp,char *buffer)
{
    track *tr[MAX_LEN];
    tr[j]= (track*)malloc(sizeof(track));
    char *token=strtok(buffer," \n\r");
    token=strtok(NULL," \n\r");
    token=strtok(NULL," \n\r");
    int b=find_record(token);
    if(b == 0){
        prog2_report_error_message(RECORD_DOESNT_EXIST);
        return;
    }

    tr[j]->name_track = (char*)malloc(strlen(token) + 1);
    strcpy(tr[j]->name_track, token);
    if (tr[j]->name_track == NULL)
        {
            prog2_report_error_message(OUT_OF_MEMORY);
            free(tr[j]->name_track);
            return;
        }
    int c=chack_track(tr[j]->name_track);
    if (c == 0)
    {
        prog2_report_error_message(TRACK_ALREADY_EXISTS);
        return;
    }
    
    
    token=strtok(NULL," \n\r");
    tr[j]->legth=atoi(token);
    if (tr[j]->legth<0)
    {
        prog2_report_error_message(INVALID_TRACK_LENGTH);
    }
    
    
    token=strtok(NULL," \n\r");
    tr[j]->position=atoi(token);
    if (tr[j]->position>10||tr[j]->position<0)
    {
        prog2_report_error_message(INVALID_TRACK_POSITION);
    }
    free(tr[j]);
    j++;
}
record_category get_category_from_string(char *category)
{
    if (strcmp(category, "ROCK") == 0) {
        return ROCK;
    } else if (strcmp(category, "POP") == 0) {
        return POP;
    } else if (strcmp(category, "JAZZ") == 0) {
        return JAZZ;
    }else if (strcmp(category,"BLUES")==0)
    {
        return BLUES;
    }else if (strcmp(category,"HIP_HOP")==0)
    {
        return HIP_HOP;
    }else if (strcmp(category,"COUNTRY")==0)
    {
        return COUNTRY;
    }else if (strcmp(category,"CLASSIC")==0)
    {
        return CLASSIC;
    }
    else {
       return ALL_CATEGORIES;
    }
}
int cmpfunc(const void *a, const void *b) {
    const records *ra = *(const records**)a;
    const records *rb = *(const records**)b;
    return strcmp(ra->name, rb->name);
}

void report_records(FILE *fp, char *buffer){
    records *NEW_RC[MAX_RECORDS];
    records *rec[MAX_RECORDS];
    records *rc[MAX_RECORDS];
    int num_records = 0;

    char *token1=strtok(buffer," \n\r");
    token1=strtok(NULL," \n\r");
    token1=strtok(NULL," \n\r");
    char *category=(char *)malloc(sizeof(token1));
    strcpy(category,token1);
   
    
    for (int j = 0; j < i; j++) {
        rec[j] = rc[j];
    }
    record_category cat_enum = get_category_from_string(category);
    if (cat_enum == ALL_CATEGORIES) {
        prog2_report_error_message(INVALID_CATEGORY);
        return;
    }
    for (int j = 0; j < i; j++) {
        if (rec[j] != NULL && (category == NULL || rec[j]->ct == get_category_from_string(category))) {
            NEW_RC[num_records++] = rec[j];
        }
    }
    if (num_records == 0) {
        prog2_report_error_message(RECORD_DOESNT_EXIST);
        return;
    }
    qsort(NEW_RC, num_records, sizeof(records*), cmpfunc);
    for (int j = 0; j < num_records && NEW_RC[j] != NULL; j++) {
        prog2_report_record(fp, NEW_RC[j]->name, NEW_RC[j]->year, NEW_RC[j]->num_of_traks, NEW_RC[j]->ct);
        for (int k = 0; k < NEW_RC[j]->num_of_traks; k++) {
            prog2_report_track(fp, NEW_RC[j]->own_track[k].name_track, NEW_RC[j]->own_track[k].legth,NEW_RC[j]->own_track[k].position);
        }
    }
    free(rc[i]);
    free(category);
    free(rec[i]);
    for ( i = 0; i < MAX_RECORDS; i++)
    {
        free(rc[i]->name);
        free(rc[i]->own_track);
    }
}
void report_Tracks(FILE *fp, char *buffer)
{
    records *rc=(records *)malloc(sizeof(records));
    char *token1=strtok(buffer," \n\r");
    token1=strtok(NULL," \n\r");
    token1=strtok(NULL," \n\r");
    int i;
    for (i = 0; i < MAX_RECORDS; i++) {
        if (strcmp(rc[i].name, token1) == 0) {
            break;
        }
    }
    if (i == MAX_RECORDS){
        
        prog2_report_error_message(RECORD_DOESNT_EXIST);
        return;
    }

    
    prog2_report_record(fp, rc[i].name, rc[i].year,rc[i].num_of_traks ,rc[i].ct);

    
    if (rc[i].num_of_traks == 0) {
        
        prog2_report_error_message(NO_TRACKS);
        return;
    }
    fprintf(fp, "Tracks:\n");
    for (int j = 0; j < rc[i].num_of_traks; j++) {
        prog2_report_track(fp, rc[i].own_track[i].name_track, j+1, rc[i].own_track[j].legth);
    }
    free(rc);
}
void report_containing(FILE *fp, char *buffr){
    int found_record = 0;
    int found_track = 0;
    records *rc=(records *)malloc(sizeof(records));
    char *token1=strtok(buffr," \n\r");
    token1=strtok(NULL," \n\r");
    token1=strtok(NULL," \n\r");
    token1=strtok(NULL," \n\r");

    for (int i = 0; i < MAX_RECORDS; i++){
        records current_record = rc[i];

        
        for (int j = 0; j < current_record.num_of_traks; j++) {
            track current_track = current_record.own_track[j];

            
            if (strstr(current_track.name_track, token1) != NULL) {
                
                if (!found_track) {
                    found_track = 1;
    
                }
                if (!found_record) {
                    found_record = 1;
                    prog2_report_record(fp, current_record.name, current_record.year,current_record.num_of_traks, current_record.ct);
                }

                
                prog2_report_track(fp, current_track.name_track, j+1, current_track.legth);
            }
        }
    }
    if (!found_record)
    {
        prog2_report_error_message(NO_RECORDS);
    } else if (!found_track)
    {
        prog2_report_error_message(NO_TRACKS);
    }
    free(rc);
}
void op_in_prog(FILE *fp){
    char buffr[MAX_LEN];
    char *token;
    char buffr2[MAX_LEN];
    fgets(buffr,MAX_LEN,stdin);
    while (!feof(fp))
    {
        strcpy(buffr2,buffr);
        token=strtok(buffr2," \n\r");
        if (strcmp(token,"#")==0)
        {
            fgets(buffr,MAX_RECORDS,stdin);
            continue;
        }
        if (strcmp(token,"Add") == 0)
        {
            token=strtok(NULL," \n\r");
            if (strcmp(token,"Record") == 0)
            {
                Add_Record(fp,buffr);
            }
            if (strcmp(token,"Track") == 0)
            {
                add_trck(fp,buffr);
            }
        }
        if (strcmp(token,"Remove")==0)
        {
            token=strtok(NULL," \n\r");
            if (strcmp(token,"Record")==0)
            {
                Remove_Record(fp,buffr);
            }
            
        }
        if (strcmp(token,"Report")==0)
        {
            token=strtok(NULL," \n\r");
            if (strcmp(token,"Records"))
            {
                report_records(fp,buffr);
            }
            if (strcmp(token,"Tracks")==0)
            {
                report_Tracks(fp,buffr);
            }
            if (strcmp(token,"Containing") == 0)
            {
                report_containing(fp,buffr);
            }
            
        }
        
        fgets(buffr,MAX_LEN,stdin);
        
    }
    
}
int main(int arc,char **arv){
    char flag[4];
    FILE *fp;
    fp=fopen("rb.text","w");
    if (fp==NULL)
    {
        prog2_report_error_message(CANNOT_OPEN_FILE);
    }
    if (arc<5 && arc!=4 && arc!=2 && arc!=0)
    {
        prog2_report_error_message(INVALID_ARGUMENTS);
    }
    for (int i = 1; i < arc; i++)
    {
        if (strcmp(arv[i],"-i")==0)
        {
            strcpy(flag,"-i");
            continue;
        }
        if (strcmp(arv[i],"-o")==0)
        {
            strcpy(flag,"-o");
            continue;
        }
        if (strcmp(flag,"-i")==0){
            op_in_prog(fp);
            fclose(fp);
        }
        if (strcmp(flag,"-o")==0)
        {
            fp=fopen("rb.text","r");
            op_in_prog(fp);
            fclose(fp);
            
        }       
    }
    fclose(fp);
    return 0;
}