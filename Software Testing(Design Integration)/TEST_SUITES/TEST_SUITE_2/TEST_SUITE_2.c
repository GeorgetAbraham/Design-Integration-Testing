#include <cheat.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "pds.h"
#include "HorseRecord.h"
#include "application.h"

//All use coverage between HorseRecord.c module add_horse_record_by_competition_id and pds.c module put_rec_by_key


CHEAT_TEST(OPEN_STORE_CLOSE,

  int rec_size = sizeof(struct HorseRecord);
  char repo_name[50];
  strcpy(repo_name, "OPEN");
  int open_status = pds_open(repo_name,rec_size);

  int competition_id  = 1;
  struct HorseRecord test;
  create_record(&test,competition_id);
  int store_status = add_horse_record_by_competition_id(&test);
  // printf("id %d, flag %d\n",competition_id, store_status);
  int close_status = pds_close();

  cheat_assert((open_status==PDS_SUCCESS && store_status==PDS_SUCCESS && close_status==PDS_SUCCESS));
)

CHEAT_TEST(OPEN_STORE_CLOSE_1,

  int rec_size = sizeof(struct HorseRecord);
  char repo_name[50];
  strcpy(repo_name, "OPEN");
  int open_status = pds_open(repo_name,rec_size);

  int competition_id  = 30;
  struct HorseRecord test;
  create_record(&test,competition_id);
  int store_status = add_horse_record_by_competition_id(&test);
  // printf("id %d, flag %d\n",competition_id, store_status);
  int close_status = pds_close();

  cheat_assert((open_status==PDS_SUCCESS && store_status==PDS_SUCCESS && close_status==PDS_SUCCESS));
)

CHEAT_TEST(OPEN_STORE_CLOSE_2,

  int rec_size = sizeof(struct HorseRecord);
  char repo_name[50];
  strcpy(repo_name, "OPEN");
  int open_status = pds_open(repo_name,rec_size);

  int competition_id  = 300;
  struct HorseRecord test;
  create_record(&test,competition_id);
  int store_status = add_horse_record_by_competition_id(&test);
  // printf("id %d, flag %d\n",competition_id, store_status);
  int close_status = pds_close();

  cheat_assert((open_status==PDS_SUCCESS && store_status==PDS_SUCCESS && close_status==PDS_SUCCESS));
)

// file_error
CHEAT_TEST(STORE,
  int competition_id  = 3;
  struct HorseRecord test;
  create_record(&test,competition_id);
  int store_status = add_horse_record_by_competition_id(&test);
  // printf("%d\n",store_status);
  // printf("%d\n",store_status);

  cheat_assert((store_status==PDS_FILE_ERROR));
)

// add_failed after closing file
CHEAT_TEST(OPEN_STORE_CLOSE_DUPLICATE,

  int rec_size = sizeof(struct HorseRecord);
  char repo_name[50];
  strcpy(repo_name, "OPEN");
  int open_status = pds_open(repo_name,rec_size);

  int competition_id  = 1;
  struct HorseRecord test;
  create_record(&test,competition_id);
  int store_status = add_horse_record_by_competition_id(&test);

  // printf("%d\n",store_status);

  int close_status = pds_close();

  cheat_assert((open_status==PDS_SUCCESS && store_status==PDS_ADD_FAILED && close_status==PDS_SUCCESS));
)

CHEAT_TEST(OPEN_CLOSE_STORE,

  int rec_size = sizeof(struct HorseRecord);
  char repo_name[50];
  strcpy(repo_name, "OPEN");
  int open_status = pds_open(repo_name,rec_size);

  int close_status = pds_close();

  int competition_id  = 20;
  struct HorseRecord test;
  create_record(&test,competition_id);
  int store_status = add_horse_record_by_competition_id(&test);
  // printf("id %d, flag %d\n",competition_id, store_status);

  cheat_assert((open_status==PDS_SUCCESS && store_status==PDS_ADD_FAILED && close_status==PDS_SUCCESS));
)
