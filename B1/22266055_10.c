#include <stdio.h>
#include <string.h>

#define NUM_STUDENT 30
#define MAX_CLASS 15
#define MAX_ID_LENGTH 8

typedef struct {
  char ID[MAX_ID_LENGTH+1];
  int GPT;
  double GPA;
} student;

void read_data(student *s, char *fname) {
  int i,j,k=0;
  char studentID[MAX_ID_LENGTH + 1];
  char grade[MAX_CLASS];
  FILE *fp = fopen(fname, "r");

  for (i = 0; i < NUM_STUDENT; i++,k=0){
		fscanf(fp, "%[^,]", studentID);
    for (j = 0; j < MAX_CLASS; j++) {
      fscanf(fp, ",%c", &grade[j]);
    }
    fscanf(fp, "\n");

    strcpy(s[i].ID,studentID);
    s[i].GPT=0;
    for(j=0;j<MAX_CLASS;j++){
      if(grade[j]=='S'){
        s[i].GPT+=4; k++;
      }else if(grade[j]=='A'){
        s[i].GPT+=3; k++;
      }else if(grade[j]=='B'){
        s[i].GPT+=2; k++;
      }else if(grade[j]=='C'){
        s[i].GPT+=1; k++;
      }else if(grade[j]=='D')k++;
    }
    s[i].GPA=(double)s[i].GPT/k;
  }
  fclose(fp);
}

int main(int argc, char *argv[]){
  int i;
  student s[NUM_STUDENT];
  
  if (argc != 2) {
    printf("Usage: %s ScoreDataFile(*.csv)\n", argv[0]);
    return 1;
  }
  char *fname = argv[1];

  read_data(s, fname);

  for (i = 0; i < NUM_STUDENT; i++){
		printf("%s,GPT:%d,GPA:%.2f\n", s[i].ID, s[i].GPT, s[i].GPA);
  }
  return 0;
}