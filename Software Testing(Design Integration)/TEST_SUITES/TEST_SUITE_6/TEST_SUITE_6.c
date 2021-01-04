#include <cheat.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "pds.h"
#include "HorseRecord.h"
#include "application.h"

// All use coverage between pds.c module delete_rec_by_ndx_key and bst.c module bst_search


CHEAT_SET_UP(

  int s_status = pds_open("OPEN",sizeof(struct HorseRecord));

  struct HorseRecord test,test1,test2;

  int competition_id  = 1;
  create_record(&test,competition_id);
  s_status = add_horse_record_by_competition_id(&test);

  competition_id  = 30;
  create_record(&test1,competition_id);
  s_status = add_horse_record_by_competition_id(&test1);

  competition_id  = 300;
  create_record(&test2,competition_id);
  s_status = add_horse_record_by_competition_id(&test2);

  s_status = pds_close();

)


CHEAT_TEST(OPEN_DELETE_MISSING_CLOSE,

  int rec_size = sizeof(struct HorseRecord);
  char repo_name[50];
  strcpy(repo_name, "OPEN");
  int open_status = pds_open(repo_name,rec_size);


  int competition_id = 100;
  int delete_status = delete_rec_by_ndx_key( competition_id );

  int close_status = pds_close();

  cheat_assert((open_status==PDS_SUCCESS && delete_status==PDS_DELETE_FAILED && close_status==PDS_SUCCESS));
)

CHEAT_TEST(OPEN_DOUBLE_DELETE_MISSING_CLOSE,

  int rec_size = sizeof(struct HorseRecord);
  char repo_name[50];
  strcpy(repo_name, "OPEN");
  int open_status = pds_open(repo_name,rec_size);


  int competition_id = 1;
  int delete_status = delete_rec_by_ndx_key( competition_id );
  delete_status = delete_rec_by_ndx_key( competition_id );
  int close_status = pds_close();

  cheat_assert((open_status==PDS_SUCCESS && delete_status==PDS_DELETE_FAILED && close_status==PDS_SUCCESS));
)

CHEAT_TEST(OPEN_DELETE_CLOSE,

  int rec_size = sizeof(struct HorseRecord);
  char repo_name[50];
  strcpy(repo_name, "OPEN");
  int open_status = pds_open(repo_name,rec_size);

  int competition_id = 30;
  int delete_status = delete_rec_by_ndx_key( competition_id );

  int close_status = pds_close();

  cheat_assert((open_status==PDS_SUCCESS && delete_status==PDS_SUCCESS && close_status==PDS_SUCCESS));
)
