#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DLZSl 101
#define SUBOR "film.txt"

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
    HEREC *her;
    struct film *dalsi;
}FILM;

HEREC *vymaz_herca(HEREC *zac){
    HEREC *akt=zac;
    if(akt!=NULL){
        vymaz_herca(akt->dalsi);
    }
    free(akt);
}

FILM *uvolnenie(FILM *zac){
    FILM *akt=zac,*pred=NULL;
    while(akt!=NULL){
        pred=akt;
        vymaz_herca(pred->her);
        free(pred);
        akt=akt->dalsi;
    }
    free(zac);
    return zac=NULL;
}

void podla_roku(FILM *zac){
    FILM *akt=zac;
    FILM *herci;
    int pocet_hercov=1,rok=0,posun=0,allocovane=1,something=0;
    scanf("%d",&rok);
    herci = (FILM *) malloc(pocet_hercov * sizeof(FILM));
    while(akt!=NULL){
        if(akt->vyroba==rok){
            while (akt->her!=NULL){
                int true=0;
                posun=0;
                if(something++==0) {
                    herci[pocet_hercov - 1].her = akt->her;
                    pocet_hercov++;
                }
                while(posun!=pocet_hercov-1) {
                    if (!(strcmp(akt->her->meno_her.meno, herci[posun].her->meno_her.meno)) &&!(strcmp(akt->her->meno_her.surrname, herci[posun].her->meno_her.surrname)) &&akt->her->rok_narod == herci[posun].her->rok_narod) {
                        true = 1;
                        break;
                    }
                    posun++;
                }
                if(true==0) {
                    if (pocet_hercov >= allocovane) {
                        herci = (FILM *) realloc(herci, (allocovane + 1) * sizeof(FILM));
                        allocovane++;
                    }
                    herci[pocet_hercov - 1].her = akt->her;
                    pocet_hercov++;
                }
                akt->her=akt->her->dalsi;
            }

        }
        akt=akt->dalsi;
    }

    for (int i = 0; i < pocet_hercov-1; i++) {
        for (int j = i + 1; j < pocet_hercov-1; j++) {
            if((strcmp(herci[i].her->meno_her.surrname,herci[j].her->meno_her.surrname))!=0) {
                if (strcmp(herci[i].her->meno_her.surrname, herci[j].her->meno_her.surrname) > 0) {
                    FILM temp = herci[i];
                    herci[i] = herci[j];
                    herci[j] = temp;
                }
            }
            else if((strcmp(herci[i].her->meno_her.meno,herci[j].her->meno_her.meno))!=0){
                if (strcmp(herci[i].her->meno_her.meno,herci[j].her->meno_her.meno) > 0) {
                    FILM temp = herci[i];
                    herci[i] = herci[j];
                    herci[j] = temp;
                }
            }
            else{
                if (herci[i].her->rok_narod>herci[j].her->rok_narod) {
                    FILM temp = herci[i];
                    herci[i] = herci[j];
                    herci[j] = temp;
                }
            }

        }
    }

    for (int i = 0; i < pocet_hercov-1; ++i) {
        printf("%s %s (%d)",herci[i].her->meno_her.meno,herci[i].her->meno_her.surrname,herci[i].her->rok_narod);
        if(i!=pocet_hercov-2)
            printf(", ");
    }
    putchar('\n');


}

void vypis_filmu(FILM *zac){
    FILM *akt=zac;
    if(zac==NULL){
        printf("Zoznam je prazdny\n");
    }
    while (akt!=NULL){
        HEREC *akther=akt->her;
        printf("%s (%d) %s %s\n",akt->nazov_filmu,akt->vyroba,akt->meno_rez.meno,akt->meno_rez.surrname);
        printf("\tHraju:");
        do {
            printf("%s %s (%d)",akt->her->meno_her.meno,akt->her->meno_her.surrname,akt->her->rok_narod);

            if(akt->her->dalsi!=NULL)
                printf(", ");

            akt->her= akt->her->dalsi;
        }while (akt->her!=NULL);

        putchar('\n');
        akt->her=akther;
        akt=akt->dalsi;
    }
}
FILM *herci_vo_filmoch(FILM *zac){
 FILM *akt=zac,*akt2=zac;
 char c1,c2,film1[DLZSl],film2[DLZSl];
 int i1=0,i2=0,vyskyt=0;

 while(c1!='\n'){
     c1=getchar();
     film1[i1++]=c1;
 }
 while(c2!='\n'){
     c2=getchar();
     film2[i2++]=c2;
 }
 film1[i1-1]='\0';
 film2[i2-1]='\0';
 while(akt!=NULL) {
     if (!(strcmp(akt->nazov_filmu, film1))) {
         while (akt2 != NULL) {
             if (!(strcmp(akt2->nazov_filmu, film2))) {
                 while (akt->her != NULL) {
                     HEREC *akther=akt->her;
                     HEREC *akther2=akt2->her;
                     while (akt2->her != NULL) {
                         if (!(strcmp(akt->her->meno_her.meno, akt2->her->meno_her.meno)) &&!(strcmp(akt->her->meno_her.surrname, akt2->her->meno_her.surrname))){
                             if (vyskyt!=0){
                                 printf(", ");
                             }
                             printf("%s %s (%d)", akt->her->meno_her.meno, akt->her->meno_her.surrname,akt->her->rok_narod);
                             vyskyt++;
                         }
                         akt2->her=akt2->her->dalsi;
                     }
                     akt->her=akther;
                     akt2->her=akther2;
                     akt->her = akt->her->dalsi;
                 }
                 putchar('\n');
                 return zac;
             }
             akt2=akt2->dalsi;
         }
     }
     akt = akt->dalsi;
 }
}
FILM *vyskyt_vo_filme(FILM *zac){
    FILM *akt=zac;

    char meno[DLZSl],priezvisko[DLZSl];
    int vyskyt=0;
    scanf("%s %s",meno,priezvisko);
    while(akt!=NULL){
        HEREC *akther=akt->her;
        while(akt->her!=NULL) {
            if((!(strcmp(akt->her->meno_her.meno,meno)))&&(!(strcmp(akt->her->meno_her.surrname,priezvisko)))){
                    printf("%s (%d)\n", akt->nazov_filmu, akt->vyroba);
                    vyskyt++;
            }
            akt->her=akt->her->dalsi;
        }
        akt->her=akther;
        akt=akt->dalsi;
    }
    if(vyskyt==0){
        printf("Herec sa nenachadza v ziadnom filme\n");
    }
    return zac;
}
FILM *vymazanie_zanamu(FILM *zac) {
    FILM *akt = zac, *pred = NULL,*delete=NULL;
    char vymaz[DLZSl],c;
    int i=0;

    while(c!='\n') {
        c=getchar();
        vymaz[i++] = c;
    }
    vymaz[i-1]='\0';
    if (zac == NULL) {
        printf("Zoznam je prazdny\n");
        return zac;
    }
    if (zac->dalsi == NULL && !(strcmp(zac->nazov_filmu, vymaz))) {
        free(zac);
        vymaz_herca(zac->her);
        return zac=NULL;
    }
    while(akt!=NULL){
        if(!(strcmp(akt->nazov_filmu,vymaz))){
            if(akt->dalsi==NULL) {
                pred->dalsi=NULL;
                vymaz_herca(akt->her);
                free(akt);
                return zac;
            }
            if(pred==NULL){
                zac=akt->dalsi;
                delete=akt;
                vymaz_herca(delete->her);
                free(delete);
                return zac;
            }
            pred->dalsi=akt->dalsi;
            delete=akt;
            vymaz_herca(delete->her);
            free(delete);
            return zac;
        }
        pred=akt;
        akt=akt->dalsi;
    }
    printf("%s sa nenechadza v zozname",vymaz);
}
FILM *pridaj_film(FILM *zac) {

    FILM *akt = zac, *vloz = NULL;
    HEREC *akther = NULL;
    vloz = (FILM *) malloc(sizeof(FILM));
    scanf("%[^\n]", vloz->nazov_filmu);
    scanf("%d", &vloz->vyroba);
    scanf("%s %s", vloz->meno_rez.meno, vloz->meno_rez.surrname);
    vloz->her = NULL;
    vloz->dalsi = NULL;
    if (zac == NULL)
        zac = vloz;
    else {
        while (akt->dalsi != NULL)
            akt = akt->dalsi;
        akt->dalsi = vloz;
    }
    while (1) {
        HEREC *vlozher = (HEREC *) malloc(sizeof(HEREC));
        scanf("%s", vlozher->meno_her.meno);
        if(!(strcmp(vlozher->meno_her.meno, "*")))
            break;
        scanf("%s %d", vlozher->meno_her.surrname, &vlozher->rok_narod);
        vlozher->dalsi = NULL;
        if (vloz->her == NULL)//vloz si vzdy pamata posledny vlozeny film
            vloz->her = vlozher;
        else {
            akther = vloz->her;
            while (akther->dalsi != NULL)
                akther = akther->dalsi;
            akther->dalsi = vlozher;
        }
    }
    return zac;
}
FILM *nacitaj_suborf(FILM *zac){
    FILE *fr;
    FILM *vloz=NULL, *akt = NULL;
    HEREC *akther=NULL;

    if((fr=fopen(SUBOR,"r"))==NULL){
        printf("Subor sa nepodarilo otvorit\n");
        exit(0);
    }
    if(zac!=NULL)
        zac=uvolnenie(zac);
    char c;
    while(c!=EOF) {
        c=getc(fr);
        if (c == '*') {
            while (1) {
                HEREC  *vlozher= (HEREC *) malloc(sizeof(HEREC));
                fscanf(fr, "%s %s %d", vlozher->meno_her.meno, vlozher->meno_her.surrname,&vlozher->rok_narod);getc(fr);
                vlozher->dalsi = NULL;
                if (vloz->her == NULL)//vloz si vzdy pamata posledny vlozeny film
                    vloz->her = vlozher;
                else {
                    akther = vloz->her;
                    while (akther->dalsi != NULL)
                        akther = akther->dalsi;
                    akther->dalsi = vlozher;
                }
                c = getc(fr);
                if (c != '*') {
                    ungetc(c,fr);
                    break;
                }
            }

        }
        else {
            ungetc(c,fr);
            vloz = (FILM *) malloc(sizeof(FILM));
            fscanf(fr, "%[^\n]", vloz->nazov_filmu);
            getc(fr);
            fscanf(fr, "%d", &vloz->vyroba);
            getc(fr);
            fscanf(fr, "%s %s", vloz->meno_rez.meno, vloz->meno_rez.surrname);
            getc(fr);
            vloz->her=NULL;
            vloz->dalsi=NULL;
            if(zac==NULL) {
                zac = vloz;
            }
            else{
                akt=zac;
                while(akt->dalsi != NULL)
                    akt = akt->dalsi;
                akt->dalsi = vloz;

            }
        }
    }
    return zac;
}

int main() {
    FILM *zac = NULL;
    char commands[10];
    while(1){
        scanf("%s",commands);
        if(!(strcmp(commands,"pridaj"))) {
            getchar();
            zac = pridaj_film(zac);
        }
        if(!(strcmp(commands,"nacitaj")))
            zac = nacitaj_suborf(zac);
        if(!(strcmp(commands,"filmy"))) {
            getchar();
            vyskyt_vo_filme(zac);
        }
        if(!(strcmp(commands,"vypis")))
            vypis_filmu(zac);
        if(!(strcmp(commands,"vymaz"))) {
            getchar();
            zac=vymazanie_zanamu(zac);
        }
        if(!(strcmp(commands,"herci"))) {
            getchar();
            herci_vo_filmoch(zac);
        }
        if(!(strcmp(commands,"rok")))
            podla_roku(zac);
        if((!strcmp(commands,"koniec"))) {
            zac=uvolnenie(zac);
            return 0;
        }
    }
}
