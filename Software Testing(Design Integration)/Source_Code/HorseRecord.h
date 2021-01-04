#ifndef HORSERECORD_H
#define HORSERECORD_H
#define HORSERECORD_SUCCESS 0
#define HORSERECORD_FAILURE 1

struct HorseRecord{
  int competition_id;
  char competition_name[30];
	char horse_name[30];
	char time[15];
  char date[15];
  char track[30];
  int age;
  int lucky_no;
  int weight;
  char distance[30];
};
extern struct PDS_RepoInfo *repoHandle;
// Add the given HorseRecord into the repository by calling add_horse_record_by_competition_id
int add_horse_record_by_competition_id( struct HorseRecord *h );
// Display HorseRecord info in a single line as a CSV without any spaces
void print_horse_record(struct HorseRecord *h);
// Use search_horse_record_by_key function to retrieve HorseRecord
int search_horse_record_by_competition_id(int competition_id,struct HorseRecord *h );
// Use search_horse_record_by_name function to retrieve HorseRecord
int search_horse_record_by_horse_name( char *horse_name, struct HorseRecord *h, int *io_count );
// Load all the HorseRecords from a CSV file
int store_horse_records( char *horse_record_file );
/* Return 0 if name of the HorseRecord matches with horse name*/
/* Return 1 if name of the HorseRecord does NOT match */
/* Return > 1 in case of any other error */
int match_horse_name(struct HorseRecord *h, char *horse_name );
#endif
