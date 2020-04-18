#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DLZSl 100

typedef struct name{
    char meno[DLZSl];
    char surrname[DLZSl];
}NAME;
typedef struct herec{
    NAME meno_her;
    int rok_narod;
    struct herec *dalsi;
}HEREC;

typedef struct film{
    char nazov_filmu[DLZSl];
    int vyroba;
    NAME meno_rez;
    HEREC herec;
    struct film *dalsifilm;

}FILM;
int main() {
    FILM *zac, *akt;

    zac=(FILM *)malloc(sizeof(FILM));
    scanf("%s %d %s %s %s %s %d",zac->nazov_filmu,&zac->vyroba,zac->meno_rez.meno,zac->meno_rez.surrname,zac->herec.meno_her.meno,zac->herec.meno_her.surrname,&zac->herec.rok_narod);
    zac->dalsifilm=NULL;
    printf("%s %d %s %s %s %s %d",zac->nazov_filmu,zac->vyroba,zac->meno_rez.meno,zac->meno_rez.surrname,zac->herec.meno_her.meno,zac->herec.meno_her.surrname,zac->herec.rok_narod);
    return 0;
}
