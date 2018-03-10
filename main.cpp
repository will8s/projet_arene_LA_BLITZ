#ifdef __cplusplus
    #include <cstdlib>
    #include <cstdio>
#else
    #include <stdlib.h>
    #include <stdio.h>
#endif

#include <SDL/SDL.h>


#include <time.h>

#define X 34
#define Y 27

int first_joueur(int nb_joueur);
int *tour_joueur(int nb_joueur);
void tab_base(int init_tab[Y][X]);
void position_init(int init_tab[Y][X],int nb_joueur,int **joueur_pos,int *ordre_joueur);
void verification_new_pos_ia(int **joueur_pos,int nb_joueur,int init_tab[Y][X],int *ordre_joueur);
void new_pos_ia(int **joueur_pos,int nb_joueur,int *ordre_joueur,int init_tab[Y][X]);
int *Daisy_Drate(int init_tab[Y][X],int y,int x);
int *switch_pos_ia(int joueur,int init_tab[Y][X]);
void tab_sdl(int init_tab_sdl[Y][X][2]);
void tab_avec_new_pos(int init_tab[Y][X],int nb_joueur,int **joueur_pos,int *ordre_joueur);


int main( int argc, char** argv )
{
    int nb_joueur=0,i=0;
    printf("il y a combien de joueur : ");
    scanf("%d",&nb_joueur);

    int *ordre_joueur=NULL, init_tab[Y][X],j=0,**joueur_pos=NULL;
    int continuer = 1;
    int init_tab_sdl[Y][X][2];
    tab_sdl(init_tab_sdl);

    if(nb_joueur>0){
        joueur_pos=(int**)malloc(nb_joueur*sizeof(int));
        if(joueur_pos==NULL){
            exit(0);
        }
        for(i=0;i<nb_joueur;i++){
            joueur_pos[i]=(int*)malloc(2*sizeof(int));
            if(joueur_pos[i]==NULL){
                exit(0);
            }
        }
    }

    ordre_joueur=tour_joueur(nb_joueur);//liste des joueur dans l'ordre en fonction du premier joueur
    tab_base(init_tab);// initialisation du tableau
    position_init(init_tab,nb_joueur,joueur_pos,ordre_joueur);// pos depart alea

    ///// sdl init securisation ///////
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        fprintf(stderr,"erreur d'initia de la sdl");
        exit(EXIT_FAILURE);// ouverture sécurisée
    }
    ////////////////////////////////////

    //////// init var SDL //////////////
    SDL_Surface *ecran = NULL;
    SDL_Surface *imagefond=NULL;
    SDL_Surface *perso1=NULL;
    SDL_Surface *perso2=NULL;
    SDL_Surface *perso3=NULL;
    SDL_Event event;

    SDL_Rect position_perso3;
    SDL_Rect position_perso2;
    SDL_Rect position_perso1;
    SDL_Rect position_imagefond;
    ////////////////////////////////////

    /////////// image ////////////
    imagefond=SDL_LoadBMP("map2.bmp");
    perso1=SDL_LoadBMP("perso_bleu/perso1.bmp");
    perso2=SDL_LoadBMP("perso_vert/perso2_1.bmp");
    perso3=SDL_LoadBMP("perso_rouge/perso3_1.bmp");
    //////////////////////////////

    ///// séurisation ecran /////
    ecran = SDL_SetVideoMode(839,720,32,SDL_HWSURFACE | SDL_DOUBLEBUF );// | SDL_FULLSCREEN);
    if(ecran == NULL){
        fprintf(stderr,"impossible de charger le mode video : %s\n",SDL_GetError());
        exit(EXIT_FAILURE);// ecran securisé
    }
    //////////////////////

    ///////////// barre du haut /////////:
    SDL_WM_SetCaption("LA BLITZ",NULL);
    SDL_WM_SetIcon(SDL_LoadBMP("BLITZ_image.bmp"),NULL);
    /////////////////////////////////////

    ///// collage de l'arene /////
    position_imagefond.x=0;
    position_imagefond.y=0;
    SDL_BlitSurface(imagefond,NULL,ecran,&position_imagefond);
    //////////////////////////////

    //////////test position SDL //////////
    //position_perso1.x=129;//+17 = +1 case vers la droite
    //position_perso1.y=131;//+17 = +1 vers le bas
    SDL_SetColorKey(perso1,SDL_SRCCOLORKEY,SDL_MapRGB(perso1->format,255,255,255));
    SDL_SetColorKey(perso2,SDL_SRCCOLORKEY,SDL_MapRGB(perso2->format,255,255,255));
    SDL_SetColorKey(perso3,SDL_SRCCOLORKEY,SDL_MapRGB(perso3->format,255,255,255));
    //////////////////////////////////////


    //////// boucle jeu /////////////
    while (continuer)
    {
        SDL_PollEvent(&event);// permet de demander une action sans faire de pose
        //SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
        //////// clavier interruption /////
        switch(event.key.keysym.sym){
            case SDLK_SPACE:
                continuer=0;
        }
        ///////////////////////////////////
        int tempsa=0,tempsb=0,h=0;
        tempsa=SDL_GetTicks();

        //// code ////
        for(i=0;i<Y;i++){
            for(j=0;j<X;j++){
                if(init_tab[i][j]==ordre_joueur[0]){
                    position_perso1.x=init_tab_sdl[i][j][0];
                    position_perso1.y=init_tab_sdl[i][j][1];
                }
                else if(init_tab[i][j]==ordre_joueur[1]){
                    position_perso2.x=init_tab_sdl[i][j][0];
                    position_perso2.y=init_tab_sdl[i][j][1];
                }
                else if(init_tab[i][j]==ordre_joueur[2]){
                    position_perso3.x=init_tab_sdl[i][j][0];
                    position_perso3.y=init_tab_sdl[i][j][1];
                }
            }
        }
        SDL_BlitSurface(perso1,NULL,ecran,&position_perso1);
        SDL_BlitSurface(perso2,NULL,ecran,&position_perso2);
        SDL_BlitSurface(perso3,NULL,ecran,&position_perso3);

        int x=0;
        //for(x=0;x<0;x++){
            new_pos_ia(joueur_pos,nb_joueur,ordre_joueur,init_tab);
            tab_avec_new_pos(init_tab, nb_joueur,joueur_pos,ordre_joueur);

            //////////////

            if((tempsa-tempsb)>500){
                for(i=0;i<Y;i++){
                    for(j=0;j<X;j++){
                        if(init_tab[i][j]==ordre_joueur[0]){
                            position_perso1.x=init_tab_sdl[i][j][0];
                            position_perso1.y=init_tab_sdl[i][j][1];
                        }
                        else if(init_tab[i][j]==ordre_joueur[1]){
                            position_perso2.x=init_tab_sdl[i][j][0];
                            position_perso2.y=init_tab_sdl[i][j][1];
                        }
                        else if(init_tab[i][j]==ordre_joueur[2]){
                            position_perso3.x=init_tab_sdl[i][j][0];
                            position_perso3.y=init_tab_sdl[i][j][1];
                        }
                    }
                }
                //position_perso1.y=position_perso1.y+1;
                tempsb=tempsa;
            }
            else{
                SDL_Delay(1000-(tempsa-tempsb));
            }
            SDL_BlitSurface(imagefond,NULL,ecran,&position_imagefond);
            SDL_BlitSurface(perso1,NULL,ecran,&position_perso1);
            SDL_BlitSurface(perso2,NULL,ecran,&position_perso2);
            SDL_BlitSurface(perso3,NULL,ecran,&position_perso3);
            SDL_Flip(ecran);
        //}
    }
    ///////////////////////////////



    ///// fin SDL ////////
    SDL_Flip(ecran);
    //pause();
    SDL_FreeSurface(imagefond);
    SDL_FreeSurface(perso1);
    SDL_FreeSurface(perso2);
    SDL_FreeSurface(perso3);
    SDL_Quit();
    free(ordre_joueur);
    free(joueur_pos);
    return 0;
}


// utile pour le comttage des points (joueur_pos[i][0]!=joueur_pos[j][0] && joueur_pos[i][1]!=joueur_pos[j][1])||(joueur_pos[i][0]!=joueur_pos[j][0]+1 && joueur_pos[i][1]!=joueur_pos[j][1]) || (joueur_pos[i][0]!=joueur_pos[j][0]-1 && joueur_pos[i][1]!=joueur_pos[j][1] ) || (joueur_pos[i][0]!=joueur_pos[j][0] && joueur_pos[i][1]!=joueur_pos[j][1]+1) || (joueur_pos[i][0]!=joueur_pos[j][0] && joueur_pos[i][1]!=joueur_pos[j][1]-1 )

void tab_sdl(int tab_for_sdl[Y][X][2]){//init tab sdl : fonction qui permet de reference la pos des joueurs
    int i=0,j=0;
    for(i=0;i<Y;i++){
        for(j=0;j<X;j++){
            tab_for_sdl[i][j][0]=129+j*17;//x
            tab_for_sdl[i][j][1]=131+i*17;//y
        }
    }
}


void tab_avec_new_pos(int init_tab[Y][X],int nb_joueur,int **joueur_pos,int *ordre_joueur){//tab avec les new pos validée
    int i=0,j=0;
    int n=0;
    for(j=0;j<Y;j++){
        for(i=0;i<X;i++){
            init_tab[j][i]=0;
            for(n=0;n<nb_joueur;n++){
                //if(i==joueur_pos[(ordre_joueur[n]-1)][0] && j==joueur_pos[(ordre_joueur[n]-1)][1]){
                if(i==joueur_pos[n][0] && j==joueur_pos[n][1]){// possible erreure avec la ligne precedente
                    //printf("joueur=%d(%d,%d)\n",ordre_joueur[n],i,j);
                    init_tab[j][i]=ordre_joueur[n];
                }
            }
        }
    }
}

void verification_new_pos_ia(int **joueur_pos,int nb_joueur,int init_tab[Y][X],int *ordre_joueur){
    int i=0,j=0,x=0,y=0,w=0;
    for(i=0;i<nb_joueur;i++){
        for(j=0;j<nb_joueur;j++){
            if((nb_joueur>1) && (joueur_pos[i][0]==joueur_pos[j][0] && joueur_pos[i][1]==joueur_pos[j][1]) && (i!=j)){
                //si plus d'un pas retour sur la case precedente ou ne bouge pas, les ia ont le droits de ne pas bouger
                //printf("\ni=x=%d,y=%d --- j=x=%d,y=%d",joueur_pos[i][0],joueur_pos[i][1],joueur_pos[j][0],joueur_pos[j][1]);
                for(y=0;y<Y;y++){
                    for(x=0;x<X;x++){
                        if((init_tab[y][x]==ordre_joueur[i])){
                            joueur_pos[i][0]=x;
                            joueur_pos[i][1]=y;
                            printf("meme pos\n");
                        }
                    }
                }

            }
        }
    }
    for(y=0;y<Y;y++){
        for(x=0;x<X;x++){
            for(i=0;i<nb_joueur;i++){
                w=ordre_joueur[i];
                if((init_tab[y][x]==w) && (!(joueur_pos[i][0]==x || joueur_pos[i][0]==x+1 || joueur_pos[i][0]==x-1) && !(joueur_pos[i][1]==y || joueur_pos[i][1]==y+1 || joueur_pos[i][1]==y-1)) ){
                    //printf("joueur (%d,%d) base new=(x%d,y%d) et x(%d,%d,%d)-y(%d,%d,%d)\n",init_tab[y][x],w,joueur_pos[i][0],joueur_pos[i][1],x+1,x,x-1,y+1,y,y-1);
                    //plus d'un pas alors ==>
                    joueur_pos[i][0]=x;
                    joueur_pos[i][1]=y;
                }
            }
        }
    }
}

void new_pos_ia(int **joueur_pos,int nb_joueur,int *ordre_joueur,int init_tab[Y][X]){
    int i=0;
    for(i=0;i<nb_joueur;i++){
        joueur_pos[i]=switch_pos_ia(ordre_joueur[i],init_tab);
    }
    //verification_new_pos_ia(joueur_pos,nb_joueur,init_tab,ordre_joueur);
}
//// placement des ia ////
int *Daisy_Drate(int init_tab[Y][X],int y,int x){
    int *pos=(int*)malloc(2*sizeof(int)),i=0,j=0;
    srand(time(NULL));
    int choose=((rand()+1)%4+1);
    printf("daisy ia choix:%d\n",choose);
    for(i=0;i<y;i++){
        for(j=0;j<x;j++){
            if(init_tab[i][j]==1){

                if(choose==1){
                    //devant
                    pos[0]=abs(j-1);//Y
                    pos[1]=i;//X
                    printf("%d-%d",j-1,i);
                    printf("<=pos\n");
                    return pos;
                }
                else if(choose==2){
                    //derriere
                    pos[0]=j+1;
                    pos[1]=i;
                    printf("%d-%d",j+1,i);
                    printf("<=pos\n");
                    return pos;
                }
                else if(choose==3){
                    //droite
                    pos[0]=j;
                    pos[1]=i+1;
                    printf("%d-%d",j,i+1);
                    printf("<=pos\n");
                    return pos;
                }
                else if(choose==4){
                    //gauche
                    pos[0]=j;
                    pos[1]=abs(i-1);
                    printf("%d-%d",j,i-1);
                    printf("<=pos\n");
                    return pos;
                }
            }
        }
    }
}

int *autre_ia(int init_tab[Y][X],int y,int x){
    int *pos=(int*)malloc(2*sizeof(int)),i=0,j=0;
    srand(time(NULL));
    int choose=((rand()+11)%4+1);
    printf("autre ia choix:%d\n",choose);
    for(i=0;i<y;i++){
        for(j=0;j<x;j++){
            if(init_tab[i][j]==2){

                if(choose==1){
                    //devant
                    pos[0]=abs(j-1);//Y
                    pos[1]=i;//X
                    printf("%d-%d",j-1,i);
                    printf("<=pos\n");
                    return pos;
                }
                else if(choose==2){
                    //derriere
                    pos[0]=j+1;
                    pos[1]=i;
                    printf("%d-%d",j+1,i);
                    printf("<=pos\n");
                    return pos;
                }
                else if(choose==3){
                    //droite
                    pos[0]=j;
                    pos[1]=i+1;
                    printf("%d-%d",j,i+1);
                    printf("<=pos\n");
                    return pos;
                }
                else if(choose==4){
                    //gauche
                    pos[0]=j;
                    pos[1]=abs(i-1);
                    printf("%d-%d",j,i-1);
                    printf("<=pos\n");
                    return pos;
                }
            }
        }
    }
}

int *autre_ia2(int init_tab[Y][X],int y,int x){
    int *pos=(int*)malloc(2*sizeof(int)),i=0,j=0;
    srand(time(NULL));
    int choose=((rand()+23)%4+1);
    printf("daisy ia choix:%d\n",choose);
    for(i=0;i<y;i++){
        for(j=0;j<x;j++){
            if(init_tab[i][j]==3){

                if(choose==1){
                    //devant
                    pos[0]=abs(j-1);//Y
                    pos[1]=i;//X
                    printf("%d-%d",j-1,i);
                    printf("<=pos\n");
                    return pos;
                }
                else if(choose==2){
                    //derriere
                    pos[0]=j+1;
                    pos[1]=i;
                    printf("%d-%d",j+1,i);
                    printf("<=pos\n");
                    return pos;
                }
                else if(choose==3){
                    //droite
                    pos[0]=j;
                    pos[1]=i+1;
                    printf("%d-%d",j,i+1);
                    printf("<=pos\n");
                    return pos;
                }
                else if(choose==4){
                    //gauche
                    pos[0]=j;
                    pos[1]=abs(i-1);
                    printf("%d-%d",j,i-1);
                    printf("<=pos\n");
                    return pos;
                }
            }
        }
    }
}
////////////////////////////

int *switch_pos_ia(int joueur,int init_tab[Y][X]){///// on ajoute les ia ici
    /*switch(joueur){
        case 1 :
            return Daisy_Drate(init_tab,X,Y);
    }*/
    if (joueur==1){
        return Daisy_Drate(init_tab,X,Y);
    }
    else if (joueur==2){
        return autre_ia(init_tab,X,Y);
    }
    else if (joueur==3){
        return autre_ia2(init_tab,X,Y);
    }
}

void position_init(int init_tab[Y][X],int nb_joueur,int **joueur_pos,int *ordre_joueur){
    int i=0,j=0,joueur=0,joueur_coller=0;
    srand(time(NULL));
    printf("fonctionne ?");
    ///// placement alea des joueurs au debut ////////
    while(joueur_coller==0){
        printf("oui");
        joueur_coller=1;
        for(i=0;i<nb_joueur && joueur_coller==1;i++){
            joueur_pos[i][0]=rand()%(X);
            joueur_pos[i][1]=rand()%(Y);
            printf("\n%d(x=%d,y=%d)\n",ordre_joueur[i],joueur_pos[i][0],joueur_pos[i][1]);
            for(j=0;j<i;j++){
                if((joueur_pos[i][0]==joueur_pos[j][0] && joueur_pos[i][1]==joueur_pos[j][1])||(joueur_pos[i][0]==joueur_pos[j][0]+1 && joueur_pos[i][1]==joueur_pos[j][1] ) || (joueur_pos[i][0]==joueur_pos[j][0]-1 && joueur_pos[i][1]==joueur_pos[j][1] ) || (joueur_pos[i][0]==joueur_pos[j][0] && joueur_pos[i][1]==joueur_pos[j][1]+1) || (joueur_pos[i][0]==joueur_pos[j][0] && joueur_pos[i][1]==joueur_pos[j][1]-1 )){
                    joueur_coller=0;
                }
            }
        }
    }//////////////////////////////////////////////////
    for(i=0;i<Y;i++){
        for(j=0;j<X;j++){
            for(joueur=0;joueur<nb_joueur;joueur++){
                if(i==joueur_pos[joueur][1] && j==joueur_pos[joueur][0]){
                    init_tab[i][j]=ordre_joueur[joueur];
                }
            }
        }
    }
}

void tab_base(int init_tab[Y][X]){
    int i=0,j=0;
    for(i=0;i<Y;i++){
        for(j=0;j<X;j++){
            init_tab[i][j]=0;
        }
    }
}

int *tour_joueur(int nb_joueur){
    int i=0,*ordre_joueur=NULL,premier_joueur=first_joueur(nb_joueur);

    if(nb_joueur>0){
        ordre_joueur=(int*)malloc(nb_joueur*sizeof(int));
        if(ordre_joueur==NULL){
            exit(0);
        }
    }
    for(i=0;i<=(nb_joueur-premier_joueur);i++){
        ordre_joueur[i]=i+premier_joueur;
    }
    for(i=(nb_joueur-premier_joueur)+1;i<nb_joueur;i++){
        ordre_joueur[i]=i-(nb_joueur-premier_joueur);
    }

    for(i=0;i<nb_joueur;i++){
        printf("%d \t",ordre_joueur[i]);
    }
    return ordre_joueur;
}

int first_joueur(int nb_joueur){
    srand(time(NULL));
    int joueur=rand()%nb_joueur+1;
    printf("premier joueur : %d - %d\n",joueur,rand());
    return joueur;
}

