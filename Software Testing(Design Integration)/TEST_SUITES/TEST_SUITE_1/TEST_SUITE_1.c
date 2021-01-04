#include <cheat.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "pds.h"
#include "HorseRecord.h"
#include "application.h"

//All use coverage between pds.c module pds_open and bst.c module bst_add 


CHEAT_TEST(OPEN,
  int rec_size = sizeof(struct HorseRecord);
  char repo_name[50];
  strcpy(repo_name, "OPEN");
  int status = pds_open(repo_name,rec_size);
  cheat_assert((status==PDS_SUCCESS && (repo_handle.rec_size)==rec_size));
)

CHEAT_TEST(CLOSE,
  int status = pds_close();
  cheat_assert_not((status==PDS_SUCCESS));
)

CHEAT_TEST(OPEN_CLOSE,
  int rec_size = sizeof(struct HorseRecord);
  char repo_name[50];
  strcpy(repo_name, "OPEN");
  int open_status = pds_open(repo_name,rec_size);
  int close_status = pds_close();
  cheat_assert((open_status==PDS_SUCCESS && close_status==PDS_SUCCESS));
)
