int main()
{
    /***Variables***/

    FILE *dictionary = NULL;
    char guess;
    char hideWord[10] = {0};
    char secretWord[10] = {0};
    int charRead = 0;
    int numberWord = 0;
    int wordChoosed = 0;
    int try = 10;
    int game = 0;


    /***Génération du mot aléatoire***/
    dictionary = fopen("mots_pendu.txt","r");

    if (dictionary != NULL)
    {
        do
        {
            charRead = fgetc(dictionary);
            if(charRead == '\n')//A chaque saut de ligne on compte un nouveau mot
                numberWord++;
        }while(charRead != EOF);

        //récupère a ligne du mot aléatoire
        srand(time(NULL));
        wordChoosed = rand()%numberWord;

        // On recommence à lire le fichier depuis le début.
        rewind(dictionary);

        //Etant donné qu'on a le numero de la ligne du mot desiré, on va parcourir chaque ligne et la sauter jusqu'à qu'on arrive au numéro de la ligne que l'on a obtenu plus haut
        while (wordChoosed > 0)
        {
            charRead = fgetc(dictionary);
            if (charRead == '\n')
                wordChoosed--;
        }

        //Une fois que le curseur dans le fichier est bien placé on récupère le mot
        fgets(secretWord, 100, dictionary);

        //On remplace le saut de ligne par une fin de chaine de caracteres
        secretWord[strlen(secretWord) - 1] = '\0';

    }
    fclose(dictionary);


    /***Lancement du Pendu***/

    //On cache le mot secret avec des *
    for(int i = 0; i < strlen(secretWord); i++)
    {
        hideWord[i] = '*';;
    }

    printf("Bienvenue au jeu du Pendu ! \n\n");

    while(try > 0 && game == 0)
    {
        printf("%s\n",hideWord);
        printf("Vous avez encore %d essais\n",try);
        printf("Quel est le mot secret ?\n");
        scanf("%s",&guess);

        guess = toupper(guess);//Met les lettres saisis en majuscule

        for(int i = 0; i < 6; i++)
        {
            //Empeche de perdre un essai en remettant une bonne lettre
            if (guess == hideWord[i])
            {
                printf("Vous avez deja trouve cette lettre !\n");
                break;
            }

            //Devoile la lettre si elle est correcte
            if(guess == secretWord[i])
            {
                hideWord[i] = guess;
                break;
            }

            //Perd un essai si la lettre est incorrecte
            if(guess != secretWord[i] && secretWord[i] == '\0')
                try--;
        }
        if (strcmp(hideWord,secretWord) == 0)
        {
            printf("Gagne, le mot secret etait bien %s !\n",secretWord);
            game = 1;
        }

        if (try == 0)
        {
            printf("Perdu, le mot secret etait %s !\n",secretWord);
            game = 1;
        }
    }
}
