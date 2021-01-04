#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "pds.h"
#include "HorseRecord.h"

// Load all the horserecords from a CSV file
int store_horse_records( char *horse_record_file )
{
	FILE *cfptr;
	char HorseRecord_line[500], token;
	struct HorseRecord h;
	cfptr = (FILE *) fopen(horse_record_file, "r");
	while(fgets(HorseRecord_line, sizeof(HorseRecord_line)-1, cfptr)){
		//printf("line:%s",contact_line);
		sscanf(HorseRecord_line, "%d%s%s%s%s%s%d%d%d%s", &(h.competition_id),h.competition_name,h.horse_name,h.time,h.date,h.track,&(h.age),&(h.lucky_no),&(h.weight),h.distance);
		print_horse_record(&h);
		add_horse_record_by_competition_id(&h);
	}
}

void print_horse_record(struct HorseRecord *h)
{
	printf("%d,%s,%s,%s,%s,%s,%d,%d,%d,%s\n",h->competition_id,h->competition_name,h->horse_name,h->time,h->date,h->track,h->age,h->lucky_no,h->weight,h->distance);
}

// Use get_rec_by_key function to retrieve horserecord
int search_horse_record_by_competition_id(int competition_id,struct HorseRecord *h)
{
	int status=get_rec_by_ndx_key(competition_id,h);
	// printf("%s %s %d",c->contact_name,c->phone,c->contact_id);
	return status;
}

// Add the given horserecord into the repository by calling put_rec_by_key
int add_horse_record_by_competition_id(struct HorseRecord *h)
{
	int status;
	status=put_rec_by_key(h->competition_id,h);
	/*if(status!=PDS_SUCCESS){
		fprintf(stderr,"Unable to add contact with key %d. Error %d",h->competition_id,status);
		return HORSERECORD_FAILURE;
	}*/
	return status;
}
int match_horse_name(struct HorseRecord *h,char *horse_name)
{
	// printf("%s %s %d\n",c->phone,c->contact_name,c->contact_id);
	return strcmp(h->horse_name,horse_name);
}
int search_horse_record_by_horse_name(char *horse_name, struct HorseRecord *h, int *io_count )
{
	int status=get_rec_by_non_ndx_key(horse_name,h,match_horse_name,io_count);
	// printf("%s %s %d",c->contact_name,c->phone,c->contact_id);
	return status;
}
