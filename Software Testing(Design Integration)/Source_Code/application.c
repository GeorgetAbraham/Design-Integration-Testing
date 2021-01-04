#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "pds.h"
#include "HorseRecord.h"
#include "application.h"

#define TREPORT(a1,a2) printf("Status %s: %s\n\n",a1,a2); fflush(stdout);

void view_instructions()
{
	printf("Add 0 at the end of every command except NON_NDX_SEARCH\n");
	printf("1. OPEN <repo_name> \n2. CLOSE\n3. STORE <key>\n4.NDX_SEARCH <key>\n5. NDX_MODIFY <key>\n6. NON_NDX_SEARCH Name-of-horse-<key> <Record No> \n7.NDX_DELETE <key> \n");
	printf("\n");
}
/*
int main(int argc, char *argv[])
{
	printf("Welcome to Horse Riding Management System\n");
	printf("Instructions\n1. Type HELP to view necessary commands\n2. Press Exit to leave the system\n");
	while(1)
	{
		// printf("HERE\n");
		char c;
		char *test_case=malloc(sizeof(char)*50);
		scanf("%[^\n]",test_case);
		scanf("%c",&c);
		// fflush(stdout);
		if(!strcmp(test_case,"Exit"))
		{
			printf("You have exited the system\n");
			printf("\n");
			break;
		}
		else if(!strcmp(test_case,"HELP"))
		{
			printf("Here are the instructions.\n");
			view_instructions();
		}
		else if(strcmp(test_case,""))
		{
			process_line(test_case);
			printf("\n");
		}
	}
}*/
int check(struct HorseRecord *a,struct HorseRecord *b)
{
	if(a->competition_id!=b->competition_id) return 0;
	if(strcmp(a->competition_name,b->competition_name)) return 0;
	if(strcmp(a->horse_name,b->horse_name)) return 0;
	if(strcmp(a->time,b->time)) return 0;
	if(strcmp(a->date,b->date)) return 0;
	if(strcmp(a->track,b->track)) return 0;
	if(strcmp(a->distance,b->distance)) return 0;
	if(a->age!=b->age) return 0;
	if(a->lucky_no!=b->lucky_no) return 0;
	if(a->weight!=b->weight) return 0;
 	return 1;
}
void create_record(struct HorseRecord* h,int competition_id)
{
	h->competition_id=competition_id;
	sprintf(h->competition_name,"Name-of-competition-%d",competition_id);
	sprintf(h->horse_name,"Name-of-horse-%d",competition_id);
	sprintf(h->time,"Finish-time-of-horse-%d",competition_id);
	sprintf(h->date,"Date-%d",competition_id);
	sprintf(h->track,"Track-Name-%d",competition_id);
	if(competition_id/300<2) h->age=2;
	else h->age=competition_id/300;
	h->lucky_no=competition_id%10;
	h->weight=70*(h->age);
	sprintf(h->distance,"Distance-%d",competition_id);
}
void process_line( char *test_case )
{
	// printf("HERE\n");
	char repo_name[30];
	char command[50], param1[50], param2[50], info[1000];
	char horse_name[30];
	int competition_id, status, rec_size, expected_status, expected_io, actual_io;
	char expected_name[50], expected_phone[50];
	struct HorseRecord test;
	// printf("HERE\n");
	rec_size = sizeof(struct HorseRecord);
	// strcpy(command,test_case[0]);
	// strcpy(param1,test_case[1]);
	// strcpy(param2,test_case[2]);
	sscanf(test_case, "%s%s%s", command, param1, param2);
	// printf("Test case: %s", test_case);
	fflush(stdout);
	if( !strcmp(command,"OPEN") ){
		strcpy(repo_name, param1);
		if( !strcmp(param2,"0") )
			expected_status = HORSERECORD_SUCCESS;
		else
			expected_status = HORSERECORD_FAILURE;

		status = pds_open( repo_name, rec_size );
		if(status == PDS_SUCCESS)
			status = HORSERECORD_SUCCESS;
		else
			status = HORSERECORD_FAILURE;
		if( status == expected_status ){
			TREPORT("PASS", "");
		}
		else{
			sprintf(info,"pds_open returned status %d",status);
			TREPORT("FAIL", info);
		}
	}
	else if( !strcmp(command,"STORE") ){
		if( !strcmp(param2,"0") )
			expected_status = HORSERECORD_SUCCESS;
		else
			expected_status = HORSERECORD_FAILURE;

		sscanf(param1, "%d", &competition_id);
		create_record(&test,competition_id);
		status = add_horse_record_by_competition_id(&test);
		if(status == PDS_SUCCESS)
			status = HORSERECORD_SUCCESS;
		else
			status = HORSERECORD_FAILURE;
		if( status == expected_status ){
			TREPORT("PASS", "");
		}
		else{
			sprintf(info,"add_contact returned status %d",status);
			TREPORT("FAIL", info);
		}
	}
	else if( !strcmp(command,"NDX_MODIFY") ){
		if( !strcmp(param2,"0") )
			expected_status = HORSERECORD_SUCCESS;
		else
			expected_status = HORSERECORD_FAILURE;

		sscanf(param1, "%d", &competition_id);
		create_record(&test,competition_id);
		status = modify_rec_by_key( competition_id, &test);
		if(status == PDS_SUCCESS)
			status = HORSERECORD_SUCCESS;
		else
			status = HORSERECORD_FAILURE;
		if( status == expected_status ){
			TREPORT("PASS", "");
		}
		else{
			sprintf(info,"modify_rec_by_key returned status %d",status);
			TREPORT("FAIL", info);
		}
	}
	else if( !strcmp(command,"NDX_SEARCH") ){
		// printf("%s\n",param2);
		if( !strcmp(param2,"0") )
			expected_status = HORSERECORD_SUCCESS;
		else
			expected_status = HORSERECORD_FAILURE;
		// printf("%d\n",expected_status);
		sscanf(param1, "%d", &competition_id);
		// create_record(&test,competition_id);
		status = search_horse_record_by_competition_id(competition_id,&test);
		// print_horse_record(&test);
		// printf("%d\n",status);
		if(status == PDS_SUCCESS)
			status = HORSERECORD_SUCCESS;
		else
			status = HORSERECORD_FAILURE;
		if( status != expected_status ){
			sprintf(info,"search key: %d; Got status %d",competition_id, status);
			TREPORT("FAIL", info);
		}
		else{
			// Check if the retrieved values match
			if( expected_status == 0 ){
				struct HorseRecord test1;
				create_record(&test1,competition_id);
				if(check(&test,&test1))
				{
					TREPORT("PASS", "");
				}
				else{
					TREPORT("FAIL", info);
				}
			}
			else
				TREPORT("PASS", "");
		}
	}
	else if( !strcmp(command,"NON_NDX_SEARCH") ){
		// printf("HERE\n");
		if( strcmp(param2,"-1") )
			expected_status = HORSERECORD_SUCCESS;
		else
			expected_status = HORSERECORD_FAILURE;

		// create_record(&test,competition_id);
		sscanf(param1, "%s", horse_name);
		sscanf(param2, "%d", &expected_io);
		int actual_io = 0;
		// printf("%s\n",horse_name);
		status = search_horse_record_by_horse_name( horse_name, &test, &actual_io );
		// printf("%d %d\n",status,actual_io);
		if(status == PDS_SUCCESS)
			status = HORSERECORD_SUCCESS;
		else
			status = HORSERECORD_FAILURE;
		if( status != expected_status ){
			sprintf(info,"search key: %d; Got status %d",competition_id,status);
			TREPORT("FAIL", info);
		}
		else{
			// Check if the retrieved values match
			// Check if num block accesses match too
			// Extract the expected contact_id from the phone number
			struct HorseRecord test1;
			sscanf(horse_name+sizeof("Name-of-horse"), "%d", &competition_id);
			// printf("%d\n",competition_id);
			create_record(&test1,competition_id);
			if( expected_status == 0 ){
				// print_horse_record(&test);
				// print_horse_record(&test1);
				if(check(&test,&test1))
				{

					if( expected_io == actual_io ){
						TREPORT("PASS", "");}
					else{
						sprintf(info,"Num I/O not matching for %d... Expected:%d Got:%d\n",
							competition_id, expected_io, actual_io
						);
						TREPORT("FAIL", info);
					}
				}
				else{
					TREPORT("FAIL", info);
				}
			}
			else
				TREPORT("PASS", "");
		}
	}
	else if( !strcmp(command,"NDX_DELETE") ){
		if( strcmp(param2,"1") )
			expected_status = HORSERECORD_SUCCESS;
		else
			expected_status = HORSERECORD_FAILURE;

		sscanf(param1, "%d", &competition_id);
		test.competition_id = -1;
		status = delete_rec_by_ndx_key( competition_id );
		if(status == PDS_SUCCESS)
			status = HORSERECORD_SUCCESS;
		else
			status = HORSERECORD_FAILURE;
		if( status != expected_status ){
			sprintf(info,"delete key: %d; Got status %d",competition_id, status);
			TREPORT("FAIL", info);
		}
		else{
			TREPORT("PASS", "");
		}
	}
	else if( !strcmp(command,"CLOSE") ){
		if( !strcmp(param1,"0") )
			expected_status = HORSERECORD_SUCCESS;
		else
			expected_status = HORSERECORD_FAILURE;

		status = pds_close();
		// printf("%d %d\n",status,expected_status);
		if(status == PDS_SUCCESS)
			status = HORSERECORD_SUCCESS;
		else
			status = HORSERECORD_FAILURE;
		if( status == expected_status ){
			TREPORT("PASS", "");
		}
		else{
			sprintf(info,"pds_close returned status %d",status);
			TREPORT("FAIL", info);
		}
	}
}
