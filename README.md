MEMBRE DE L'EQUIPE :

William Le Moal
jerry Nde Tchinda Styve
Yorane Doare
Anthea Latrubesse
Rayan Edjekouane
Nylda Dadjio Djuka
Fhevry Cazal


Règles du jeu :

La configuration initiale du jeu est une maps de dimension 27x34. 
Les joueurs sont places aleatoirement sur la maps, avec un ecart entre chaque joueur de 1 case minimum.
Le premier joueur est tire au hasard.
Chaque IA possède 5-15 pv ( nous n'avons pas encore definis ).

les IA peuvent se deplacer dans une des 4 directions (haut, bas, gauche, droite), rester sur place, ou en diagonale. Attention, le maximum de deplacement possible est 1 case.
Les IA perdent 1 pv quand elles sont ‡ cotes d'une autre IA. Elles perdent 2 vp quand les IA sont sur la meême case l'une sur l'autre.


Deès qu'une IA ne respecte pas les reègles, elle retourne ‡ sa position precedente.

La partie se termine lorsqu'il ne reste qu'une IA en vie. Si il y a egalite, on compte le nombre d'IA tuees par chaque IA ex eaquo.

En cours de developpement : 
-le retraisissement de map.
-objets de boosts et d'attaques sur la map.


Documentation du code :

-la fonction first_joueur(int nb_joueur):
Determine le premier joueur aleatoirement parmis un certain nombre de joueurs. Elle renvoie le premier joueur. 


-la fonction *tour_joueur(int nb_joueur): 
Elle renvoie un pointeur contenant la liste des joueurs dans l'ordre que la fonction definie, en fonction du premier joueur.


-la fonction tab_base(int init_tab[Y][X]):
Elle remplie notre tableau principal de zero. Cette fonction est un void.
Nous utilisons au debut un tableau ‡ deux dimensions, ‡ la place d'un pointeur de pointeur pour avancer plus vite sur notre projet.
Nous le remplacerons en pointeur de pointeur par la suite.


-la fonction void position_init(int init_tab[Y][X],int nb_joueur,int **joueur_pos,int *ordre_joueur):
Elle permet de placer aleatoirement chaque joueur dans notre arène ( init_tab[Y][X] ) avec 1 case d'intervalle minimum.
elle va ensuite enregistrer les positions de chaque joueur dans un second pointeur de pointeur.


-la fonction int *switch_pos_ia(int joueur,int init_tab[Y][X]):
Elle permet de selectionner une IA en fonction l'ordre que nous avons defini avec la fonction *tour_joueur, avec le paramètre joueur.
Une fois que une IA est selectionnee la fonction *switch_pos_ia retourne la position que l'IA choisit.

-les fonctions int *autre_ia2(int init_tab[Y][X],int y,int x);int *autre_ia(int init_tab[Y][X],int y,int x);int *Daisy_Drate(int init_tab[Y][X],int y,int x):                    
Ces fonctions sont des IA de test, qui renvoient des positions aleatoires.


-la fonction void new_pos_ia(int **joueur_pos,int nb_joueur,int *ordre_joueur,int init_tab[Y][X]):
Elle permet d'ajouter ‡ un tableau contenant les positions des joueurs, les nouvelles positions de chaque joueur.


-la fonction void verification_new_pos_ia(int **joueur_pos,int nb_joueur,int init_tab[Y][X],int *ordre_joueur):
elle permet de verifier si la position choisie par une IA est valide, selon les reègles du jeu.
elle a pour but de comparer la nouvelle position et l'ancienne pour savoir si l'IA ‡ respecte la distance maximale pour un mouvement.
Cette fonction est en cours de developpement.


-la fonction void tab_avec_new_pos(int init_tab[Y][X],int nb_joueur,int **joueur_pos,int *ordre_joueur):
Elle permet de reinitialiser le tableau ( remettre chaque case du tableau a zero ),et de placer les nouvelles positions dans le tableau principale.


-la fonction void tab_sdl(int tab_for_sdl[Y][X][2]):
Elle permet d'indiquer la position de chaque case de notre arène dans un tableau.


-nous utilisons la librairie time.h pour ameliorer la fonction rand(). rand retournera une valeur en fonction d'un date grace ‡ la fonction srand(time(NULL)).


-nous avons utilise la SDL, qui est une bibliothèque du langage C.
nous l'utilisons dans notre "main" principalement.
la SDL nous a permis de donner plus de texture ‡ notre jeu 2D, et d'eêtre ainsi plus attractif.
	-SDL_Init( SDL_INIT_VIDEO ): initialise le mode video
	-SDL_Surface *nom_variable : permet d'avoir une variable de type SDL_Surface
	-SDL_event event : variable qui va permettre de gérer les evènements (touches du clavier ...)
	-SDL_Rect position : permet de faire se deplacer une image selon un abscisse et un ordonne (position.x et position.y)
	-SDL_LoadBMP("image.bmp") : permet de charger une image et de l'affecter ‡ une variable
	-SDL_SetVideoMode : permet de configurer l'ecran de la SDL selon nos envies
	-SDL_BlitSurface : permet de coller une image sur l'ecran de la SDL
	-SDL_SetColorKey : permet d'appliquer un filtre alpha ‡ notre image
	-SDL_Flip : permet de mettre ‡ jour l'affichage
	-SDL_FreeSurface(variable) : permet de liberer l'espace utilise par les variables de la SDL
	-SDL_Quit() : permet de quitter la SDL
                                          

-Le "main" :
	-notre main utilise les fonctions precedentes pour faire se deplacer les IA sur notre arène, dans l'ecran de la SDL.
pour cela je regarde si chaque position de notre tableau 2D contient un nombre superieur ‡ Zero. 
si c'est le cas, j'attribue aux IA leurs positions en fonction d'un axe (X,Y) donne par la fonction tab_sdl().
	- je le place dans un timer pour faire bouger les AI en fonction d'un certaine duree.
	-pour faire bouger les IA je colle des images sur des images grace ‡ la SDL.
                            