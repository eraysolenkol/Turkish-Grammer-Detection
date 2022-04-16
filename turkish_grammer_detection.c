#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int checkSoftConsonant(char *word);
int checkStrongConsonant(char *word);
int checkConnexion(char *firstWord, char *secondWord);
int checkPalatalHarmony(char *word);
int checkLabialHarmony(char *word);
int checkPlural(char *word);

int main()
{
    char sentence[10000];
    printf("Please enter your sentence.\n");
    fgets(sentence, 10000, stdin);
    int wordCount = 0;
    int sentenceCount = 0;
    int letterCount = 0;
    /* A variable to store the punct locations with word indexes.It helps the connexions rule,
    checkConnexion function checks the every single 2 words back to back but with punctOrNot
    array if there is a punct between that 2 words it will not count as a connexion.
    Example: If there is a punction between 0. index word and 1. index word ,
    punctOrNot[0] will be equal to 1  (Meaning there is a punct after the 0. word) */
    int punctOrNot[1000] = {0};
    int j = 0;
    while (*(sentence + j) != '\0')
    {
        if ((*(sentence + j) == '.') || (*(sentence + j) == '!') || (*(sentence + j) == '?'))
        {
            sentenceCount++;
        }

        if (isspace(*(sentence + j)))
        {
            wordCount++;
        }
        else if (ispunct(*(sentence + j)))
        {
            sentence[j] = ' ';
            punctOrNot[wordCount - 1]++;
        }
        else
        {
            letterCount++;
            /* Turkish letters causing a problem in letter counting , it counts 2 times so
            if Turkish letter has found decreasing the letter count by 1 */
            char turkish[6] = {'ğ', 'ş', 'ı', 'ö', 'ü', 'ç'};
            for (int i = 0; i < 6; i++)
            {
                if (*(sentence + j) == *(turkish + i))
                {
                    letterCount--;
                    break;
                }
            }
        }
        sentence[j] = tolower(sentence[j]);
        j++;
    }

    int i = 0;
    char *p = strtok(sentence, " ");
    char *wordsArray[wordCount + 1];

    while (p != NULL)
    {
        wordsArray[i++] = p;
        p = strtok(NULL, " ");
    }

    char *plural[wordCount];
    char *palatalWords[wordCount];
    char *connexions[wordCount];
    char *labialWords[wordCount];
    int pluralCount = 0;
    int palatalCount = 0;
    int connexionCount = 0;
    int labialCount = 0;
    int softConsonantCount = 0;
    int strongConsonantCount = 0;

    for (int i = 0; i < wordCount; i++)
    {

        if (checkPlural(wordsArray[i]) == 0)
        {
            plural[pluralCount++] = wordsArray[i];
        }
        if (checkPalatalHarmony(wordsArray[i]) == 0)
        {
            palatalWords[palatalCount++] = wordsArray[i];
        }
        if (checkLabialHarmony(wordsArray[i]) == 0)
        {
            labialWords[labialCount++] = wordsArray[i];
        }
        if (checkSoftConsonant(wordsArray[i]) == 0)
        {
            softConsonantCount++;
        }
        if (checkStrongConsonant(wordsArray[i]) == 0)
        {
            strongConsonantCount++;
        }
    }
    printf("[+] %d sentences were found.\n", sentenceCount);
    printf("[+] %d words were found.\n", wordCount);
    printf("[+] %d letters were found.\n", letterCount);
    printf("[+] %d plural words were found. Words: ", pluralCount);
    for (int i = 0; i < pluralCount; i++)
    {
        if (i != pluralCount - 1)
            printf("%s, ", *(plural + i));
        else
            printf("%s.", *(plural + i));
    }
    printf("\n");
    char connexions_str[500][100] = {""}; // Stores the two words together for the connexions
    for (int i = 0; i < wordCount - 1; i++)
    {
        if ((checkConnexion(wordsArray[i], wordsArray[i + 1]) == 0) && punctOrNot[i] == 0)
        {
            sprintf(connexions_str[connexionCount], "%s %s", wordsArray[i], wordsArray[i + 1]);
            connexions[connexionCount] = connexions_str[connexionCount];
            connexionCount++;
        }
    }
    printf("[+] %d connexion were found. Connexions: ", connexionCount);
    for (int i = 0; i < connexionCount; i++)
    {
        if (i != connexionCount - 1)
            printf("%s, ", *(connexions + i));
        else
            printf("%s.", *(connexions + i));
    }

    printf("\n");
    printf("[+] %d labial harmony words were found. Words: ", labialCount);
    for (int i = 0; i < labialCount; i++)
    {
        if (i != labialCount - 1)
            printf("%s, ", *(labialWords + i));
        else
            printf("%s.", *(labialWords + i));
    }
    printf("\n");
    printf("[+] %d palatal harmony words were found. Words: ", palatalCount);
    for (int i = 0; i < palatalCount; i++)
    {
        if (i != palatalCount - 1)
            printf("%s, ", *(palatalWords + i));
        else
            printf("%s.", *(palatalWords + i));
    }
    printf("\n");
    printf("[+] %d soft consonant words were found.\n", softConsonantCount);
    printf("[+] %d strong consonant words were found.\n\n", strongConsonantCount);
    int pick;

    while (1)
    {
        printf("Is there a rule you want checked?\n");
        printf("0.Exit\n1.Sentence Count\n2.Word Count\n3.Letter Count\n4.Connexions\n5.Plurals\n6.Labial Harmony\n7.Palatal Harmony\n8.Search a word\n9.Soft Consonant Count\n10.Strong Consonant Count\n=");
        scanf("%d", &pick);
        printf("\n");
        switch (pick)
        {
        case 0:
            printf("Successfully exited\n");
            return 0;
        case 1:
            printf("%d sentences were found.\n", sentenceCount);
            break;
        case 2:
            printf("%d words were found.\n", wordCount);
            break;
        case 3:
            printf("%d letters were found.\n", letterCount);
            break;
        case 4:
            printf("%d connexion were found. Connexions: ", connexionCount);
            for (int i = 0; i < connexionCount; i++)
            {
                if (i != connexionCount - 1)
                    printf("%s, ", *(connexions + i));
                else
                    printf("%s.", *(connexions + i));
            }
            printf("\n");
            break;
        case 5:
            printf("%d plural words were found. Words: ", pluralCount);
            for (int i = 0; i < pluralCount; i++)
            {
                if (i != pluralCount - 1)
                    printf("%s, ", *(plural + i));
                else
                    printf("%s.", *(plural + i));
            }
            printf("\n");
            break;
        case 6:
            printf("%d labial harmony words were found. Words: ", labialCount);
            for (int i = 0; i < labialCount; i++)
            {
                if (i != labialCount - 1)
                    printf("%s, ", *(labialWords + i));
                else
                    printf("%s.", *(labialWords + i));
            }
            printf("\n");
            break;
        case 7:
            printf("%d palatal harmony words were found. Words: ", palatalCount);
            for (int i = 0; i < palatalCount; i++)
            {
                if (i != palatalCount - 1)
                    printf("%s, ", *(palatalWords + i));
                else
                    printf("%s.", *(palatalWords + i));
            }
            printf("\n\n");
            break;
        case 8:
            __fpurge(stdin);
            char search[100];
            printf("Enter the word that you want to search = ");
            gets(search);
            for (int i = 0; i < strlen(search); i++)
            {
                search[i] = tolower(search[i]);
            }
            int searchCount = 0;
            for (int i = 0; i < wordCount; i++)
            {
                if (strcmp(wordsArray[i], search) == 0)
                {
                    searchCount++;
                }
            }
            if (searchCount == 0)
            {
                printf("%s not found in the sentence.\n", search);
            }
            else
            {
                printf("%s found %d times in the sentence.\n", search, searchCount);
            }
            break;
        case 9:
            printf("%d soft consonant words were found.\n", softConsonantCount);
            break;
        case 10:
            printf("%d strong consonant words were found.\n", strongConsonantCount);
            break;
        default:
            printf("Please enter a number between 0-10 including\n");
            break;
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}

int checkSoftConsonant(char *word)
{
    char softConsonants[13] = {'b', 'c', 'd', 'g', 'ğ', 'j', 'l', 'm', 'n', 'r', 'v', 'y', 'z'};
    int i = 0;
    while (*(word + i) != '\0')
    {
        for (int j = 0; j < 13; j++)
        {
            if (softConsonants[j] == *(word + i))
            {
                return 0;
            }
        }
        i++;
    }
    return 1;
}

int checkStrongConsonant(char *word)
{
    char strongConsonants[8] = {'ç', 'f', 'h', 'k', 's', 'ş', 't', 'p'};
    int i = 0;
    while (*(word + i) != '\0')
    {
        for (int j = 0; j < 8; j++)
        {
            if (strongConsonants[j] == *(word + i))
            {
                return 0;
            }
        }
        i++;
    }
    return 1;
}

int checkConnexion(char *firstWord, char *secondWord)
{
    char vowels[8] = {'a', 'e', 'i', 'ı', 'u', 'ü', 'o', 'ö'};
    char consonants[21] = {'b', 'c', 'ç', 'd', 'f', 'g', 'ğ', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'r', 's', 'ş', 't', 'v', 'y', 'z'};
    int length = strlen(firstWord);
    char end = firstWord[length - 1];
    char start = secondWord[0];
    int flagEnd = 0;
    int flagStart = 0;
    // Checking if second word's first character is a vowel or not
    for (int i = 0; i < 8; i++)
    {
        if (vowels[i] == start)
        {
            flagStart = 1;
        }
    }
    // Checking if first word's last character is a consonant or not
    for (int i = 0; i < 21; i++)
    {
        if (consonants[i] == end)
        {
            flagEnd = 1;
        }
    }
    // If both flags triggered returning 0 as the rule provided.
    if (flagStart == 1 && flagEnd == 1)
    {
        return 0;
    }
    return 1;
}

int checkPalatalHarmony(char *word)
{
    char frontVowels[4] = {'e', 'i', 'ü', 'ö'};
    char backVowels[4] = {'a', 'ı', 'u', 'o'};
    int flagFrontVowel = 0, flagBackVowel = 0;
    int i = 0;

    // Checking the letters in the word if they are in the frontVowels and backVowels arrays.
    while (*(word + i) != '\0')
    {
        for (int j = 0; j < 4; j++)
        {
            if (frontVowels[j] == *(word + i))
            {
                flagFrontVowel = 1;
            }
            else if (backVowels[j] == *(word + i))
            {
                flagBackVowel = 1;
            }
        }
        i++;
    }
    // Return 1 if both flagBackVowel and flagFrontVowel triggered.
    if ((flagBackVowel == 1) && (flagFrontVowel == 1))
    {
        return 1;
    }

    return 0;
}

int checkLabialHarmony(char *word)
{
    char unroundedVowels[4] = {'a', 'e', 'ı', 'i'};
    char roundedVowels[4] = {'o', 'ö', 'u', 'ü'};
    char roundedWideAndUnroundedNarrowVowels[4] = {'o', 'ö', 'ı', 'i'};

    int flagUnroundedVowel = 0, flagRoundedVowel = 0;
    int i = 0;
    int indexRoundedVowel = -1; // Variable to store the index of first vowel in the word if it is a rounded vowel.

    // Checking the letters in the word if they are in the unroundedVowels and roundedVowels arrays.
    while (*(word + i) != '\0')
    {
        for (int j = 0; j < 4; j++)
        {
            // If flagRoundedVowel triggered don't check for the flagUnroundedVowel
            if ((unroundedVowels[j] == *(word + i)) && flagRoundedVowel == 0)
            {
                flagUnroundedVowel = 1;
            }
            // If flagUnroundedVowel triggered don't check for the flagRoundedVowel
            // Also if first vowel already found as rounded vowel don't trigger again for the indexRoundedVowel
            else if ((roundedVowels[j] == *(word + i)) && (flagUnroundedVowel == 0) && (indexRoundedVowel == -1))
            {
                flagRoundedVowel = 1;
                indexRoundedVowel = i;
            }

            if (flagUnroundedVowel == 1)
            {
                if (roundedVowels[j] == *(word + i))
                {
                    return 1;
                }
            }
            /* Don't trigger for the first vowel (indexRoundedVowel != i) because grammatically
            we need to check the vowels after the first syllable */
            else if ((flagRoundedVowel == 1) && (indexRoundedVowel != i))
            {
                if (roundedWideAndUnroundedNarrowVowels[j] == *(word + i))
                {
                    return 1;
                }
            }
        }
        i++;
    }

    return 0;
}

int checkPlural(char *word)
{
    int length = strlen(word);
    char threeChar[4];
    char plural[4] = "ler";
    char plural2[4] = "lar";

    // Checking the every single 3 character substring in the word
    for (int i = 0; i < length - 2; i++)
    {
        strncpy(threeChar, &word[i], 3);
        /* Assigning the last index of character array to null ,
        if it is not assigned, the computer can fill it with any character in its own memory */
        threeChar[3] = '\0';
        if ((strcmp(plural, threeChar) == 0) || (strcmp(plural2, threeChar) == 0))
        {
            return 0;
        }
    }
    return 1;
}