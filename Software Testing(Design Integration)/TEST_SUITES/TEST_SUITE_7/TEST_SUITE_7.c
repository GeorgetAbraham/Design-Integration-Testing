#include <cheat.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "pds.h"
#include "HorseRecord.h"
#include "application.h"

// All use coverage between pds.c module put_rec_by_key and bst.c module bst_add

CHEAT_TEST(OPEN_STORE_PDS_CLOSE,
  int rec_size = sizeof(struct HorseRecord);
  char repo_name[50];
  strcpy(repo_name, "OPEN");
  int open_status = pds_open(repo_name,rec_size);

  int competition_id  = 1;
  struct HorseRecord test;
  create_record(&test,competition_id);

  struct HorseRecord *h = &test;

  int store_status = put_rec_by_key(h->competition_id,h);
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

  struct HorseRecord *h = &test;

  int store_status = put_rec_by_key(h->competition_id,h);
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

  struct HorseRecord *h = &test;

  int store_status = put_rec_by_key(h->competition_id,h);
  // printf("id %d, flag %d\n",competition_id, store_status);
  int close_status = pds_close();

  cheat_assert((open_status==PDS_SUCCESS && store_status==PDS_SUCCESS && close_status==PDS_SUCCESS));
)

CHEAT_TEST(OPEN_STORE_CLOSE_DUPLICATE,

  int rec_size = sizeof(struct HorseRecord);
  char repo_name[50];
  strcpy(repo_name, "OPEN");
  int open_status = pds_open(repo_name,rec_size);

  int competition_id  = 1;
  struct HorseRecord test;
  create_record(&test,competition_id);

  struct HorseRecord *h = &test;

  int store_status = put_rec_by_key(h->competition_id,h);
  // printf("%d\n",store_status);

  int close_status = pds_close();

  cheat_assert((open_status==PDS_SUCCESS && store_status==PDS_ADD_FAILED && close_status==PDS_SUCCESS));
)
