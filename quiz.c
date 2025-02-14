#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#define MAX_LINE_LENGTH 300

void loadQuestions(const char *filename);
void playQuiz();

typedef struct
{
    char question[MAX_LINE_LENGTH];
    char options[4][MAX_LINE_LENGTH];
    char correctOption;
} Question;
Question *questions = NULL;
const int totalSubjects = 4;
int questionCount = 0;
int answeredQuestions = 0;
int score = 0;
char subjects[totalSubjects + 1][70] = {"Operating Sysytem", "Computer Network", "Database Management", "C Programming", "Exit"};
char subjectsFile[totalSubjects][70] = {"operating.txt", "networking.txt", "database.txt", "programming.txt"};
int main()
{

    printf("%s\n", "Which Subject you want to play quiz on?");
    for (int i = 0; i < totalSubjects + 1; i++)
    {
        printf("%d. %s\n", i + 1, subjects[i]);
    }

    int input;
    printf("Enter your choice: ");
    scanf("%d", &input);
    if (input >= 1 && input <= totalSubjects)
    {
        printf("\n(IF YOU WANT TO OPEN MENU PRESS m)\n");

        loadQuestions(subjectsFile[input - 1]);

        playQuiz();
    }
    else
    {
        if (input == totalSubjects + 1)
        {

            exit(0);
        }

        printf("Invalid Input. Please Enter Number Between 1-%d\n", totalSubjects);
        return main();
    }

    return 0;
}

void loadQuestions(const char *filename)
{
    questionCount = 0;
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    questions = (Question *)malloc(sizeof(Question) * 1);
    char line[MAX_LINE_LENGTH];

    while (fscanf(file, " %[^---]", questions[questionCount].question) != EOF)
    {
        fscanf(file, " %[^\n]", line);

        for (int i = 0; i < 4; i++)
        {
            fscanf(file, " %[^\n]", questions[questionCount].options[i]);
        }
        fscanf(file, " %c", &questions[questionCount].correctOption);
        questionCount++;
        questions = (Question *)realloc(questions, sizeof(Question) * (questionCount + 1));
    }

    fclose(file);
}
bool checkAnswer(char answer, char correctOption)
{
    return answer == correctOption;
}
void displayQuestion(Question q)
{
    printf("\nQ: %s\n", q.question);
    for (int i = 0; i < 4; i++)
    {
        printf("%c) %s\n", 'a' + i, q.options[i]);
    }
}
void displayResult()
{
    if (score <= answeredQuestions / 2)
    {
        printf("\nYOU NEED TO WORK HARD\n");
    }
    else if (score > answeredQuestions / 2 && score <= ceil(answeredQuestions / 1.5))
    {
        printf("\nYOU ARE DOING GOOD\n");
    }
    else
    {
        printf("\nYOU ARE A CHAMP\n");
    }
    printf("Your Final Score Is %d/%d\n", score, answeredQuestions);
    free(questions);
}
void menu()
{
    printf("1. Go to Subjects\n");
    printf("2. Exit\n");
    printf("3. Continue\n");
    int input;
    printf("Enter your choice: ");
    scanf("%d", &input);
    if (input == 1)
    {
        displayResult();

        main();
    }
    else if (input == 2)
    {
        displayResult();

        exit(0);
    }
    else if (input == 3)
    {
        return;
    }
    else
    {
        printf("Invalid Input. Please Enter Number Between 1-3\n");
        return menu();
    }
}

void playQuiz()
{
    score = 0;
    answeredQuestions = 0;

    char answer;

    for (int i = 0; i < questionCount; i++)
    {
        displayQuestion(questions[i]);
        printf("Enter your answer (a/b/c/d/m): ");

        scanf(" %c", &answer);
        if (answer >= 'a' && answer <= 'd')
        {
            if (checkAnswer(answer, questions[i].correctOption))
            {
                score++;
                printf("Correct!\n");
            }
            else
            {
                printf("Wrong! Correct answer is %c. %s\n", questions[i].correctOption, questions[i].options[questions[i].correctOption - 'a']);
            }
        }
        else
        {
            if (answer == 'm')
            {
                menu();
            }
            else
            {
                printf("Invalid answer. Please enter a/b/c/d\n");
            }
            i--;
            printf("\n");
            continue;
        }
        answeredQuestions++;

        printf("\n");
    }

    displayResult();
    main();
}