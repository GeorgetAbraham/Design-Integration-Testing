#ifndef APPLICATION_H
#define APPLICATION_H
#include "HorseRecord.h"
void process_line( char *test_case );
void create_record(struct HorseRecord* h,int competition_id);
int check(struct HorseRecord *a,struct HorseRecord *b);
void view_instructions();


#endif
