#include <cheat.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "pds.h"
#include "HorseRecord.h"
#include "application.h"

// All use coverage between pds.c module modify_rec_by_key and bst.c module bst_search

CHEAT_TEST(MODIFY,

  int competition_id = 30;
  struct HorseRecord test;
  create_record(&test,competition_id);
  int modify_status = modify_rec_by_key( competition_id, &test);
  cheat_assert((modify_status==PDS_FILE_ERROR));
)

CHEAT_TEST(OPEN_CLOSE_MODIFY,

  int rec_size = sizeof(struct HorseRecord);
  char repo_name[50];
  strcpy(repo_name, "OPEN");
  int open_status = pds_open(repo_name,rec_size);

  int close_status = pds_close();

  int competition_id = 30;
  struct HorseRecord test;
  create_record(&test,competition_id);
  int modify_status = modify_rec_by_key( competition_id, &test);

  cheat_assert((modify_status==PDS_ADD_FAILED));

)

CHEAT_TEST(OPEN_MODIFY_CLOSE,

  int rec_size = sizeof(struct HorseRecord);
  char repo_name[50];
  strcpy(repo_name, "OPEN");
  int open_status = pds_open(repo_name,rec_size);

  int competition_id = 30;
  struct HorseRecord test;
  create_record(&test,competition_id);
  int modify_status = modify_rec_by_key( competition_id, &test);

  int close_status = pds_close();

  cheat_assert((modify_status==PDS_SUCCESS && open_status == PDS_SUCCESS && close_status==PDS_SUCCESS));

)

CHEAT_TEST(OPEN_MODIFY_CLOSE_MISSING,

  int rec_size = sizeof(struct HorseRecord);
  char repo_name[50];
  strcpy(repo_name, "OPEN");
  int open_status = pds_open(repo_name,rec_size);

  int competition_id = 31;
  struct HorseRecord test;
  create_record(&test,competition_id);
  int modify_status = modify_rec_by_key( competition_id, &test);

  int close_status = pds_close();

  cheat_assert((modify_status==PDS_REC_NOT_FOUND && open_status == PDS_SUCCESS && close_status==PDS_SUCCESS));
)

CHEAT_TEST(OPEN_DELETE_MODIFY_CLOSE,

  int rec_size = sizeof(struct HorseRecord);
  char repo_name[50];
  strcpy(repo_name, "OPEN");
  int open_status = pds_open(repo_name,rec_size);

  int competition_id = 30;

  int delete_status = delete_rec_by_ndx_key( competition_id );

  struct HorseRecord test;
  create_record(&test,competition_id);
  int modify_status = modify_rec_by_key( competition_id, &test);

  int close_status = pds_close();

  cheat_assert((modify_status==PDS_MODIFY_FAILED && open_status == PDS_SUCCESS && close_status==PDS_SUCCESS && delete_status==PDS_SUCCESS));

)
