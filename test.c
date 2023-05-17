#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
// #include<stdio_ext.h>
    // __fpurge(stdin);


typedef struct {
  char ma_yc[100];
  int so_nguoi;
  int so_phong;
  char ma_ks[5];
  int day;
  int m;
  int year;
  int kid;
}data_t;

//LIST STRUCTURE =============================================
typedef struct list_s {
  data_t data;
  struct list_s *next;
} list_t, *root_t;

void showData(data_t data) { printf("%s %d %d %s %02d-%02d-%d %d\n",data.ma_yc,data.so_nguoi,data.so_phong,data.ma_ks,data.day,data.m,data.year,data.kid); }

list_t* createNewNode(const data_t data) {
  list_t* newNode = (list_t*)malloc(sizeof(list_t));
  if (newNode == NULL) return NULL;

  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}


// Traversing a list and show
root_t llPrint(root_t root) {
  for (list_t* p = root; p != NULL; p = p->next) showData(p->data);
  printf("\n");
  return root;
}

root_t llInit() { return NULL; }

list_t* llSeek(root_t root, int index) {
  list_t* p = NULL;
  for (p = root; index > 0 && (p != NULL); index--) p = p->next;
  return p;
}

/* === Insert ============================================== */

root_t llInsertHead(root_t root, const data_t data) {
  list_t* pNewNode = createNewNode(data);
  pNewNode->next = root;
  return (root_t)pNewNode;
}

root_t llInsertTail(root_t root, const data_t data) {
  list_t* pNewNode = createNewNode(data);

  if (root == NULL) return (root_t)pNewNode;

  list_t* p = NULL;
  for (p = root; p->next != NULL; p = p->next)
    ;
  p->next = pNewNode;
  return root;
}

root_t llInsertAfter(root_t root, list_t* pAElem, const data_t data) {
  if (pAElem == NULL) return root;

  list_t* pNewNode = createNewNode(data);
  pNewNode->next = pAElem->next;
  pAElem->next = pNewNode;

  return root;
}

/* === Delete ============================================== */

root_t llDeleteHead(root_t root) {
  if (root == NULL) return NULL;

  list_t* p = root->next;
  free(root);
  return (root_t)p;
}

root_t llDeleteTail(root_t root) {
  if (root == NULL) return NULL;
  if (root->next == NULL) {
    free(root);
    return NULL;
  }

  list_t* p;
  // Find previous node of Tail
  for (p = root; p->next->next != NULL; p = p->next)
    ;

  free(p->next);
  p->next = NULL;
  return (root_t)root;
}

root_t llDeleteAfter(root_t root, list_t* pA) {
  if ((pA == NULL) || (pA->next == NULL)) return root;

  list_t* pToDelElem = pA->next;
  pA->next = pA->next->next;

  free(pToDelElem);
  return root;
}



root_t llDeleteExcally(root_t root, data_t data){
  list_t*p=root;
  if(strcmp(p->data.ma_yc,data.ma_yc)==0){
    root=llDeleteHead(root);
  }
  else for(p;p!=NULL;p=p->next){
    if(strcmp(p->next->data.ma_yc,data.ma_yc)==0){
      root=llDeleteAfter(root,p);
    }
    return root;
  }
  return root;
}


root_t llDeleteAll(root_t root) {
  list_t* p = NULL;
  for (; root != NULL; root = p) {
    p = root->next;
    free(root);
  }
  return NULL;
}


//BST STRUCTURE =======================================================

typedef data_t key_t;
typedef struct node_s {
  key_t key;
  struct node_s *left;
  struct node_s *right;
} node_t;

typedef node_t *tree_t;

tree_t Search(char x[], tree_t Root) {
  if (Root == NULL)
    return NULL;           
  else if (strcmp(Root->key.ma_yc, x)==0) 
    return Root;
  else if (strcmp(Root->key.ma_yc, x)<0)

    return Search(x, Root->right); 
  else {

    return Search(x, Root->left);
  }
}

void Insertnode_t(key_t x, tree_t *pRoot) {
  if (*pRoot == NULL) {

    *pRoot = (node_t *)malloc(sizeof(node_t));
    (*pRoot)->key = x;
    (*pRoot)->left = NULL;
    (*pRoot)->right = NULL;
  } else if (strcmp(x.ma_yc,(*pRoot)->key.ma_yc)<0)
    Insertnode_t(x, &((*pRoot)->left));
  else if (strcmp(x.ma_yc,(*pRoot)->key.ma_yc)>0)
    Insertnode_t(x, &((*pRoot)->right));
}

key_t DeleteMin(tree_t *pRoot) {
  key_t k;
  if ((*pRoot)->left == NULL) {
    k = (*pRoot)->key;
    (*pRoot) = (*pRoot)->right;
    return k;
  } else
    return DeleteMin(&(*pRoot)->left);
}

void Deletenode_t(char x[], tree_t *pRoot) {
  if (*pRoot != NULL)
    if (strcmp(x,(*pRoot)->key.ma_yc)<0)
      Deletenode_t(x, &(*pRoot)->left);
    else if (strcmp(x,(*pRoot)->key.ma_yc)>0)
      Deletenode_t(x, &(*pRoot)->right);
    else if (((*pRoot)->left == NULL) && ((*pRoot)->right == NULL))
      *pRoot = NULL;
    else if ((*pRoot)->left == NULL)
      *pRoot = (*pRoot)->right;
    else if ((*pRoot)->right == NULL)
      *pRoot = (*pRoot)->left;
    else
      (*pRoot)->key = DeleteMin(&(*pRoot)->right);
}

void freetree(tree_t tree) {
  if (tree != NULL) {
    freetree(tree->left);
    freetree(tree->right);
    free((void *)tree);
  }
}

void inOrderPrint(tree_t tree) {
  if (tree != NULL) {
    inOrderPrint(tree->left);
    showData(tree->key);
    inOrderPrint(tree->right);
  }
}

void postOrderPrint(tree_t tree) {
  if (tree != NULL) {
    postOrderPrint(tree->left);
    postOrderPrint(tree->right);
    showData(tree->key);
  }
}

void preOrderPrint(tree_t tree) {
  if (tree != NULL) {
    showData(tree->key);
    preOrderPrint(tree->left);
    preOrderPrint(tree->right);
  }
}







//Test Funcion
root_t read_file(FILE* fr,root_t root){
    char buffer[256];
    data_t tmp;
    fgets(buffer, sizeof(buffer), fr);
    int N;
    sscanf(buffer, "%d", &N);
    for(int i=0; i<N; i++){
      fgets(buffer, sizeof(buffer), fr);
      sscanf(buffer,"%s %d %d %s %d-%d-%d %d",tmp.ma_yc,&tmp.so_nguoi,&tmp.so_phong,tmp.ma_ks,&tmp.day,&tmp.m,&tmp.year,&tmp.kid);
      root=llInsertTail(root,tmp);
    }
    printf("So luong yeu cau doc duoc la %d\n",N);
    // llPrint(root);
    return root;
}

root_t cau_2(root_t root){
  root_t p=root;
  int k_hop_le=0;
  for(p;p!=NULL;p=p->next){
    if(p->data.kid!=0){
      if((p->data.so_nguoi-p->data.kid)<1){
        k_hop_le++;
        // root=llDeleteExcally(root,p->data);
      }
    }
  }
  printf("So yeu cau khong hop le la %d\n", k_hop_le);
  return root;
}

void tree_convert(tree_t *ptree,root_t root){
  root_t p=root;
  int slg=0;
  for(p;p!=NULL;p=p->next){
    Insertnode_t(p->data,ptree);
    slg++;
  }
}

void tra_cuu(tree_t tree){
  char buffer[256];
  char key[100];
  fgets(buffer,sizeof(buffer),stdin);
  sscanf(buffer,"%s",key);
  tree_t Search_key=Search(key,tree);
  if(Search_key!=NULL)  showData(Search_key->key);
  else printf("Not found\n");
}

void thay_doi(tree_t tree){
  char buffer[256];
  int choose;
  char ma[100];
  printf("Nhap ma yeu cau: ");
  fgets(buffer,sizeof(buffer),stdin);
  sscanf(buffer,"%s",ma);
  tree_t pSearch=Search(ma,tree);
  if(pSearch==NULL) {
    printf("Not Found\n");
    return;
  }
  else {
    printf("Thay doi loai nao\n1. Thoi gian\n2. So nguoi\n3. So luong tre em\nChon: ");
    fgets(buffer,sizeof(buffer),stdin);
    sscanf(buffer,"%d",&choose);
  }
  printf("Nhap du lieu: ");

  int day;
  int m;
  int year;
  int so_nguoi;
  char c;
  int kid;
  switch (choose)
  {
  case 1:
    fgets(buffer,sizeof(buffer),stdin);
    sscanf(buffer,"%d-%d-%d",&day,&m,&year);
    pSearch->key.day=day;
    pSearch->key.m=m;
    pSearch->key.year=year;
    break;
  case 2:
    fgets(buffer,sizeof(buffer),stdin);
    sscanf(buffer,"%c",&c);
    if(isdigit(c)){
      sscanf(buffer,"%d",&so_nguoi);
      if((so_nguoi-pSearch->key.kid)<1){
        printf("Invalid\n");
        return;
      }
      pSearch->key.so_nguoi=so_nguoi;
    }
    else{
      printf("Invalid\n");
      return;
    }
    break;
  case 3:
    fgets(buffer,sizeof(buffer),stdin);
    sscanf(buffer,"%c",&c);
    if(isdigit(c)){
      sscanf(buffer,"%d",&kid);
      if((pSearch->key.so_nguoi-kid)<1){
        printf("Invalid\n");
        return;
      }
      pSearch->key.kid=kid;
    }
    else{
      printf("Invalid\n");
      return;
    }
    break;
  default:
    break;
  }
  printf("Update\n");
  // preOrderPrint(tree);
}

void huy_yc(tree_t* ptree){
  char buffer[256];
  fgets(buffer,sizeof(buffer),stdin);
  char ma[100];
  sscanf(buffer,"%s",ma);

  tree_t pSearch=Search(ma,(*ptree));
  if(pSearch==NULL){
    printf("Not found\n");
    return;
  }
  else{
    Deletenode_t(ma,ptree);
    printf("Deleted\n");
  }
  // preOrderPrint(*ptree);
}

void showData_file(data_t data,FILE*fw) { fprintf(fw,"%s %d %d %s %02d-%02d-%d %d\n",data.ma_yc,data.so_nguoi,data.so_phong,data.ma_ks,data.day,data.m,data.year,data.kid); }

int slg_file=0;

void preOrder_file(tree_t tree,FILE*fw) {
  if (tree != NULL) {
    showData_file(tree->key,fw);
    slg_file++;
    preOrder_file(tree->left,fw);
    preOrder_file(tree->right,fw);
  }
}

void in_file(FILE *fw,tree_t tree){
  preOrder_file(tree,fw);
  printf("Da in %d ma yeu cau ra file\n",slg_file);
  slg_file=0;
}


int main(){
    FILE *fr=NULL;
    if((fr=fopen("booking_orders.txt","r"))==NULL){
        printf("Can not open input file\n");
        exit(1);
    }
    FILE *fw=NULL;
    if((fw=fopen("booking_output.txt","w"))==NULL){
        printf("Can not open output file\n");
        exit(1);
    }

    root_t list=llInit();
    tree_t tree=NULL;
    //menu
    int otp=-1;
    while(otp!=0){
        printf("===== Menu Option =====\n");
        printf("1. Doc du lieu tu log file\n");
        printf("2. Kiem tra so luong yeu cau khong hop le\n");
        printf("3. Tra cuu theo ma yeu cau\n");
        printf("4. Thay doi yeu cau\n");
        printf("5. Huy yeu cau\n");
        printf("6. Luu danh sach yeu cau ra file\n");
        printf("7. Quit\n");

        printf("Lua chon: ");
        scanf("%d",&otp);
        char c;
        do{
            c=getchar();
        }while(c!='\n');
        switch (otp) {
            case 1: 
              list=read_file(fr,list);
              tree_convert(&tree,list);
                break;
            case 2: 
              list=cau_2(list);
                break;
            case 3: 
              tra_cuu(tree);
                break;
            case 4: 
              thay_doi(tree);
                break;
            case 5: 
              huy_yc(&tree);
                break;
            case 6: 
              in_file(fw,tree);
              fclose(fw);
                break;
            case 7:
              fclose(fr);
              llDeleteAll(list);
              freetree(tree);
              otp=0;
                break;
            default: 
              printf("Khong co lua chon nay\n");
              otp=-1;
                break;
        }

    }
    return 0;
}