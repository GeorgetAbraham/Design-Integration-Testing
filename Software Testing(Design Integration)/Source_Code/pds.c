#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
// #include<iostream>
#include "pds.h"
#include "bst.h"
// Define the global variable
struct PDS_RepoInfo repo_handle;
struct PDS_NdxInfo *ndx_handle;
char temp2[50];
//while fread()!=EOF
static void bst_write(struct BST_Node* root);
static void bst_write(struct BST_Node* root)
{
	// if(repo_handle.pds_ndx_fp==NULL)
	// printf("HERE\n")
	// struct PDS_NdxInfo *ndx_handle=(struct PDS_NdxInfo *)malloc(sizeof(struct PDS_NdxInfo *));
	if(root==NULL) return;
	else
	{
		struct PDS_NdxInfo* t;
		t=(struct PDS_NdxInfo*)(root->data);
		if(t->is_deleted==0)
		fwrite(root->data,sizeof(struct PDS_NdxInfo),1,repo_handle.pds_ndx_fp);
		// printf("putting %d %d\n",((struct PDS_NdxInfo *)root->data)->key,((struct PDS_NdxInfo *)root->data)->offset);
		// t->key=root->key;
		// t->offset=(struct PDS_NdxInfo*)((root->data)->offset);
		// free(t);
		bst_write(root->left_child);
		// printf("%d\n",t->key);
		// if(root->left_child==NULL) printf("LEFt\n");
		// else if(root->right_child==NULL) printf("RIGHT\n");
		bst_write(root->right_child);
	}
}
int pds_load_ndx()
{
  struct PDS_NdxInfo *index_info;
  if(repo_handle.pds_ndx_fp==NULL) return PDS_FILE_ERROR;
  else
  {
    while(!feof(repo_handle.pds_ndx_fp)){
      index_info=malloc(sizeof(struct PDS_NdxInfo));
      if(!fread(index_info,sizeof(struct PDS_NdxInfo),1,repo_handle.pds_ndx_fp))
      break;
      // printf("getting %d %d\n",index_info->key,index_info->offset);
      bst_add_node(&(repo_handle.pds_bst),index_info->key,index_info);
    }
    return PDS_SUCCESS;
  }
}
int pds_open( char *repo_name,int rec_size)
{
  char temp1[50];
  strcpy(temp1,repo_name);
  strcat(temp1,".dat");
  strcpy(temp2,repo_name);
  strcat(temp2,"_ndx.dat");
  strcpy(repo_handle.pds_name,repo_name);
  if(repo_handle.pds_data_fp==(FILE*) fopen(temp1,"ab+"))
  {
    // printf("HERE\n");
    return PDS_REPO_ALREADY_OPEN;
  }
  else if(repo_handle.pds_ndx_fp==(FILE*) fopen(temp2,"ab+"))
  {
    return PDS_REPO_ALREADY_OPEN;
  }
  else
  {
    repo_handle.repo_status=PDS_REPO_OPEN;
    repo_handle.pds_data_fp=(FILE*) fopen(temp1,"ab+");
    repo_handle.pds_ndx_fp=(FILE*) fopen(temp2,"ab+");
    repo_handle.rec_size=rec_size;
    if(repo_handle.pds_data_fp==NULL || repo_handle.pds_ndx_fp==NULL) return PDS_FILE_ERROR;
    if(pds_load_ndx()==PDS_FILE_ERROR) return PDS_FILE_ERROR;
    fclose(repo_handle.pds_ndx_fp);
  }
  return PDS_SUCCESS;
}

int put_rec_by_key( int key, void *rec )
{
  // struct Contact *c;
  // c=(struct Contact *)rec;
  if(repo_handle.repo_status==PDS_REPO_OPEN)
  {
    ndx_handle=(struct PDS_NdxInfo *)malloc(sizeof(struct PDS_NdxInfo));
    // if(repo_handle.pds_data_fp==NULL) printf("%s\n",repo_handle.pds_name);
    fseek(repo_handle.pds_data_fp,0,SEEK_END);
    ndx_handle->key=key;
    ndx_handle->offset=ftell(repo_handle.pds_data_fp);
		ndx_handle->is_deleted=0;
    fwrite(&key,sizeof(int),1,repo_handle.pds_data_fp);
    fwrite(rec,repo_handle.rec_size,1,repo_handle.pds_data_fp);
    // printf("putting into bst %d %d\n",ndx_handle->key,ndx_handle->offset);
		// printf("%s\n",*c->phone);
    int status=bst_add_node(&(repo_handle.pds_bst),ndx_handle->key,ndx_handle);
		// printf("%d\n",status);
    if(status == BST_NULL || status == BST_DUP_KEY) return PDS_ADD_FAILED;
    return PDS_SUCCESS;
  }
  else if(repo_handle.repo_status==PDS_REPO_CLOSED)
  {
    return PDS_ADD_FAILED;
  }
  else
  {
    return PDS_FILE_ERROR;
  }
}
int modify_rec_by_key(int key,void *rec)
{
	// struct Contact* c;
  struct PDS_NdxInfo* t;
  // rec=(struct Contact*)rec;
  if(repo_handle.repo_status==PDS_REPO_OPEN)
  {
    struct BST_Node *temp=bst_search(repo_handle.pds_bst,key);
    if(temp==NULL) return PDS_REC_NOT_FOUND;
    t=(struct PDS_NdxInfo*)(temp->data);
    fseek(repo_handle.pds_data_fp,t->offset,SEEK_SET);
    //free(t);
    if(repo_handle.pds_data_fp!=NULL)
    {
      // int k;
			struct BST_Node *temp=bst_search(repo_handle.pds_bst,key);
			struct PDS_NdxInfo* t=(struct PDS_NdxInfo*)(temp->data);
			if(t->is_deleted==1) return PDS_MODIFY_FAILED;
			fwrite(&key,sizeof(int),1,repo_handle.pds_data_fp);
	    fwrite(rec,repo_handle.rec_size,1,repo_handle.pds_data_fp);
      //fread(&k,sizeof(int),1,repo_handle.pds_data_fp);
      //fread(rec,repo_handle.rec_size,1,repo_handle.pds_data_fp);
      // printf("%d %d\n",k,rec.contact_id);
      // printf("%d\n",rec.contact_id);
			// printf("HERE\n");
      return PDS_SUCCESS;
    }
    else return PDS_MODIFY_FAILED;
  }
  else if(repo_handle.repo_status==PDS_REPO_CLOSED)
  {
    return PDS_ADD_FAILED;
  }
  else
  {
    return PDS_FILE_ERROR;
  }
}
int get_rec_by_ndx_key( int key, void *rec )
{
  // struct Contact* c;
  struct PDS_NdxInfo* t;
  // rec=(struct Contact*)rec;
  if(repo_handle.repo_status==PDS_REPO_OPEN)
  {
    struct BST_Node *temp=bst_search(repo_handle.pds_bst,key);
    if(temp==NULL) return PDS_REC_NOT_FOUND;
    t=(struct PDS_NdxInfo*)(temp->data);
		if(t->is_deleted==1) return PDS_REC_NOT_FOUND;
    fseek(repo_handle.pds_data_fp,t->offset,SEEK_SET);
    //free(t);
    if(repo_handle.pds_data_fp!=NULL)
    {
      int k;
      fread(&k,sizeof(int),1,repo_handle.pds_data_fp);
      fread(rec,repo_handle.rec_size,1,repo_handle.pds_data_fp);
      // printf("%d %d\n",k,rec.contact_id);
      // printf("%d\n",rec.contact_id);
      return PDS_SUCCESS;
    }
    else return PDS_FILE_ERROR;
  }
  else if(repo_handle.repo_status==PDS_REPO_CLOSED)
  {
    return PDS_ADD_FAILED;
  }
  else
  {
    return PDS_FILE_ERROR;
  }
}
int get_rec_by_non_ndx_key( void *key,void *rec,int (*matcher)(void *rec, void *key),int *io_count)
{
	// struct Contact* c;
  struct PDS_NdxInfo* t;
  // rec=(struct Contact*)rec;
	key=(char*)key;
	if(repo_handle.repo_status==PDS_REPO_OPEN)
  {
    // FILE *fstart=repo_handle.pds_data_fp;
    // FILE *fend=repo_handle.pds_data_fp;
    // fseek(fend,0,SEEK_END);
		// if(fstart==	fend) printf("HERE\n");
		// printf("HERE\n");
		fseek(repo_handle.pds_data_fp,0,SEEK_SET);
		int k,temp1=0;
    while(!feof(repo_handle.pds_data_fp))
    {
			// if(matcher(rec,key)==0) return PDS_SUCCESS;
			temp1++;
			// printf("HERE\n");
			fread(&k,sizeof(int),1,repo_handle.pds_data_fp);
			fread(rec,repo_handle.rec_size,1,repo_handle.pds_data_fp);
			if(matcher(rec,key)==0)
			{
				struct BST_Node *temp=bst_search(repo_handle.pds_bst,k);
				// printf("HERE\n");
				struct PDS_NdxInfo* t=(struct PDS_NdxInfo*)(temp->data);
				// printf("%d\n",t->is_deleted);
				if(t->is_deleted==1)
				{
					return PDS_REC_NOT_FOUND;
				}
				*io_count=temp1;
				// printf("%d\n",temp);
				return PDS_SUCCESS;
			}
      /*if(rec->contact_id==key)
      {
        return PDS_SUCCESS;
      }*/
			// if(feof(fstart)) break;
    }
    return PDS_REC_NOT_FOUND;
  }
  else if(repo_handle.repo_status==PDS_REPO_CLOSED)
  {
    return PDS_ADD_FAILED;
  }
  else
  {
    return PDS_FILE_ERROR;
  }
}

int delete_rec_by_ndx_key(int key)
{
	struct BST_Node *temp=bst_search(repo_handle.pds_bst,key);
	if(temp==NULL) return PDS_DELETE_FAILED;
	struct PDS_NdxInfo* t=(struct PDS_NdxInfo*)(temp->data);
	if(t->is_deleted==1) return PDS_DELETE_FAILED;
	else
	{
		t->is_deleted=1;
		return PDS_SUCCESS;
	}
}

int pds_close()
{
  if(repo_handle.repo_status==PDS_REPO_OPEN)
  {
    // printf("HERE\n");
    repo_handle.pds_ndx_fp=(FILE*)fopen(temp2,"wb+");
    // printf("%s\n",temp2);
    bst_write(repo_handle.pds_bst);
    bst_destroy(repo_handle.pds_bst);
    repo_handle.repo_status=PDS_REPO_CLOSED;
		repo_handle.pds_bst = NULL;
    fclose(repo_handle.pds_data_fp);
    fclose(repo_handle.pds_ndx_fp);
    return PDS_SUCCESS;
  }
  else return PDS_FILE_ERROR;
}
