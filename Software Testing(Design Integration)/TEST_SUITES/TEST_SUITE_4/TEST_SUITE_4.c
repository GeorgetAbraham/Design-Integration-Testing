#include <cheat.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "pds.h"
#include "HorseRecord.h"
#include "application.h"

// All use coverage between HorseRecord.c module search_horse_record_by_horse_name and pds.c module get_rec_by_non_ndx_key

CHEAT_TEST(NON_KEY_SEARCH,

  char horse_name[50];
  strcpy(horse_name, "Name-of-horse-1");
  struct HorseRecord test,test1;
  int actual_io = 0;
  int expected_io = 1;
  int competition_id = 1;
  int non_search_status = search_horse_record_by_horse_name( horse_name, &test, &actual_io );
  create_record(&test1,competition_id);
  // printf("%d %d %d\n",non_search_status,check(&test,&test1),actual_io);
  cheat_assert((non_search_status==PDS_FILE_ERROR));
)

CHEAT_TEST(OPEN_CLOSE_NON_KEY_SEARCH,

  int rec_size = sizeof(struct HorseRecord);
  char repo_name[50];
  strcpy(repo_name, "OPEN");
  int open_status = pds_open(repo_name,rec_size);

  int close_status = pds_close();

  char horse_name[50];
  strcpy(horse_name, "Name-of-horse-1");
  struct HorseRecord test,test1;
  int actual_io = 0;
  int expected_io = 1;
  int competition_id = 1;
  int non_search_status = search_horse_record_by_horse_name( horse_name, &test, &actual_io );

  cheat_assert((non_search_status==PDS_ADD_FAILED));
)

CHEAT_TEST(OPEN_NON_KEY_SEARCH_CLOSE,

  int rec_size = sizeof(struct HorseRecord);
  char repo_name[50];
  strcpy(repo_name, "OPEN");
  int open_status = pds_open(repo_name,rec_size);

  char horse_name[50];
  strcpy(horse_name, "Name-of-horse-1");
  struct HorseRecord test,test1;
  int actual_io = 0;
  int expected_io = 1;
  int competition_id = 1;
  int non_search_status = search_horse_record_by_horse_name( horse_name, &test, &actual_io );
  create_record(&test1,competition_id);

  int close_status = pds_close();


  cheat_assert((open_status==PDS_SUCCESS && non_search_status==PDS_SUCCESS && check(&test,&test1)==1 && expected_io==actual_io && close_status==PDS_SUCCESS));

)

CHEAT_TEST(OPEN_NON_KEY_SEARCH_CLOSE_MISSING,

  int rec_size = sizeof(struct HorseRecord);
  char repo_name[50];
  strcpy(repo_name, "OPEN");
  int open_status = pds_open(repo_name,rec_size);

  char horse_name[50];
  strcpy(horse_name, "Name-of-horse-25");
  struct HorseRecord test,test1;
  int actual_io = 0;
  int expected_io = 1;
  int competition_id = 1;
  int non_search_status = search_horse_record_by_horse_name( horse_name, &test, &actual_io );
  create_record(&test1,competition_id);

  int close_status = pds_close();

  cheat_assert((non_search_status==PDS_REC_NOT_FOUND));

)

CHEAT_TEST(OPEN_DELETE_NON_KEY_SEARCH_CLOSE,

  int rec_size = sizeof(struct HorseRecord);
  char repo_name[50];
  strcpy(repo_name, "OPEN");
  int open_status = pds_open(repo_name,rec_size);

  char horse_name[50];
  strcpy(horse_name, "Name-of-horse-1");
  struct HorseRecord test,test1;
  int actual_io = 0;
  int expected_io = 1;
  int competition_id = 1;
  int delete_status = delete_rec_by_ndx_key( competition_id );

  // printf("%d\n",delete_status);

  int non_search_status = search_horse_record_by_horse_name( horse_name, &test, &actual_io );
  create_record(&test1,competition_id);

  int close_status = pds_close();


  cheat_assert((open_status==PDS_SUCCESS && non_search_status==PDS_REC_NOT_FOUND && delete_status==PDS_SUCCESS && close_status==PDS_SUCCESS));

)
