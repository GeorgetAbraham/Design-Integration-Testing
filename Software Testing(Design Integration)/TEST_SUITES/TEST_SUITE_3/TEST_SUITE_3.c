#include <cheat.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "pds.h"
#include "HorseRecord.h"
#include "application.h"

// All use coverage between HorseRecord.c module search_horse_record_by_competition_id and pds.c module get_rec_by_ndx_key


CHEAT_TEST(SEARCH,
  struct HorseRecord test;
  int competition_id=1;
  int status = search_horse_record_by_competition_id(competition_id,&test);
  cheat_assert_not(status==PDS_SUCCESS);
)

// PDS_SUCCESS
CHEAT_TEST(OPEN_SEARCH_CLOSE,

  int rec_size = sizeof(struct HorseRecord);
  char repo_name[50];
  strcpy(repo_name, "OPEN");
  int open_status = pds_open(repo_name,rec_size);

  struct HorseRecord test,test1;
  int competition_id=1;
  create_record(&test1,competition_id);
  int search_status = search_horse_record_by_competition_id(competition_id,&test);

  int close_status = pds_close();

  // printf("%d\n",check(&test,&test1));

  cheat_assert((open_status==PDS_SUCCESS && search_status==PDS_SUCCESS && close_status==PDS_SUCCESS && check(&test,&test1)==1));

)
// PDS_REC_NOT_FOUND
CHEAT_TEST(OPEN_SEARCH_CLOSE_MISSING,

  int rec_size = sizeof(struct HorseRecord);
  char repo_name[50];
  strcpy(repo_name, "OPEN");
  int open_status = pds_open(repo_name,rec_size);

  struct HorseRecord test;
  int competition_id=2;
  int search_status = search_horse_record_by_competition_id(competition_id,&test);

  int close_status = pds_close();

  cheat_assert((open_status==PDS_SUCCESS && search_status==PDS_REC_NOT_FOUND && close_status==PDS_SUCCESS));

)
//PDS_ADD_FAILED
CHEAT_TEST(OPEN_CLOSE_SEARCH,

  int rec_size = sizeof(struct HorseRecord);
  char repo_name[50];
  strcpy(repo_name, "OPEN");
  int open_status = pds_open(repo_name,rec_size);

  int close_status = pds_close();

  struct HorseRecord test;
  int competition_id=1;
  int search_status = search_horse_record_by_competition_id(competition_id,&test);

  // printf("%d\n",check(&test,&test1));

  cheat_assert((open_status==PDS_SUCCESS && search_status==PDS_ADD_FAILED && close_status==PDS_SUCCESS ));

)

CHEAT_TEST(OPEN_STORE_SEARCH,

  int rec_size = sizeof(struct HorseRecord);
  char repo_name[50];
  strcpy(repo_name, "OPEN");
  int open_status = pds_open(repo_name,rec_size);

  int competition_id  = 2;
  struct HorseRecord test;
  create_record(&test,competition_id);
  int store_status = add_horse_record_by_competition_id(&test);

  struct HorseRecord test1;
  int search_status = search_horse_record_by_competition_id(competition_id,&test1);

  cheat_assert((open_status==PDS_SUCCESS && store_status==PDS_SUCCESS && search_status==PDS_SUCCESS && check(&test,&test1)==1));

)

CHEAT_TEST(OPEN_DELETE_SEARCH_CLOSE,

  int rec_size = sizeof(struct HorseRecord);
  char repo_name[50];
  strcpy(repo_name, "OPEN");
  int open_status = pds_open(repo_name,rec_size);

  struct HorseRecord test,test1;
  int competition_id=300;

  int delete_status = delete_rec_by_ndx_key( competition_id );

  create_record(&test1,competition_id);
  int search_status = search_horse_record_by_competition_id(competition_id,&test);

  int close_status = pds_close();

  // printf("%d\n",check(&test,&test1));

  cheat_assert((open_status==PDS_SUCCESS && search_status==PDS_REC_NOT_FOUND && close_status==PDS_SUCCESS  && delete_status==PDS_SUCCESS));

)
