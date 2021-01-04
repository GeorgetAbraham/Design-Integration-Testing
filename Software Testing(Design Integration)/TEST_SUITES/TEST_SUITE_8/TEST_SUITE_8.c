#include <cheat.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "pds.h"
#include "HorseRecord.h"
#include "application.h"

// All use coverage between pds.c module get_rec_by_ndx_key and bst.c module bst_search

CHEAT_TEST(OPEN_SEARCH_CLOSE,

  int rec_size = sizeof(struct HorseRecord);
  char repo_name[50];
  strcpy(repo_name, "OPEN");
  int open_status = pds_open(repo_name,rec_size);

  struct HorseRecord test,test1;
  int competition_id=1;
  create_record(&test1,competition_id);
  struct HorseRecord *h = &test;
  int search_status = get_rec_by_ndx_key(competition_id,h);

  int close_status = pds_close();

  // printf("%d\n",check(&test,&test1));

  cheat_assert((open_status==PDS_SUCCESS && search_status==PDS_SUCCESS && close_status==PDS_SUCCESS && check(&test,&test1)==1));

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
  struct HorseRecord *h = &test1;
  int search_status = get_rec_by_ndx_key(competition_id,h);

  cheat_assert((open_status==PDS_SUCCESS && store_status==PDS_SUCCESS && search_status==PDS_SUCCESS && check(&test,&test1)==1));

)
