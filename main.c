#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_STUDENTS 250

typedef struct
{
    char name[100];
    int class;
    // забележка! char не работи за български символи за това във students.txt паралеката се отличава с "a" или "b" ot anglijski ezik
    char par;
    int ots;
}
student;

student students[MAX_STUDENTS];

// променливата option е string за да не дава грешка при въвеждане на букви защото при променлива int програмата се затваря дори ако има условие с do while цикъл
string option;
int grade;
char parr;
// bool error ще се използва главно и само за проверки (мисля че ще е само необходим за main където не може да се върнем с return и да напуснем действието)
bool error;
bool back;

void students_update(void);
void menu_1(void);
void menu_2(void);
void option_1(void);
void students_display(int grade, char par, string datanames[], int dataots[]);
void change_ots(string namesave);
void menu_3(int class, char par, string namesave, int otssave);
int ots_sum(void);
int class_ots_sum(int grade, char par);

int main(int argc, string argv[])
{

    // while цикъл за да не се затваря програмата след първа употреба или извеждане на клас до волно напускане на програмата
    while(true){
        // for cikul za vmukvaneto na dannite ot TXT faila ili funkciq
        students_update();
        do{
            // Main menu
            int sumots = ots_sum();
            printf("\n\nИнформация:");
            printf("\nОбщ брой отсъствия - %i", sumots);
            printf("\nОпции:");
            printf("\n1) Класове");
            printf("\n2) Изход");
            option = get_string("\nОпция - ");

            if (strcmp(option, "1") != 0 && strcmp(option, "2") != 0)
            {
                printf("\nМоля въведете цифрата на една от зададените опции!");
                option = get_string("\nНатисни Enter за да продължиш...");
                error = true;
            }
            else
            {
                switch (option[0])
                {
                    case '1':
                    error = false;
                    break;

                    case '2':
                    error = false;
                    return 0;
                    break;

                    default:
                    return 1;
                }
            }
        } while(error);
        //

        option_1();

    }
}

// !!!        ||
// Under main \/

void students_update(void)
{
    FILE *fp = fopen("students.txt", "r");
    if (!fp){option = get_string("\nНатисни Enter за да продължиш...");return;}
    // брой символи за 1 ред
    char line[256];
    // fgets помага за четенето на файла ред по ред във for цикъла
    // fgets(чете по ред, големина на реда като лимит, от кой файл)
    // след прочитане на ред минава на следващия и дори фор цикъла да спре fp е стигнало до информацията на (примерно 34 ртед) съответно fgets извършва същата функция която и i++ за for цикъла
    for (int i = 0; i < MAX_STUDENTS && fgets(line, sizeof(line), fp); i++)
    {
        int class;
        char par;
        int ots;

        // sscanf помага да разделя един ред от txt файла на 4 различни променливи които съм обявил над if аргумента :D
        if (sscanf(line, " %99[^,],%i,%c,%i", students[i].name, &class, &par, &ots) == 4)
        {
            students[i].class = class;
            students[i].par = par;
            students[i].ots = ots;
        }
    }

    fclose(fp);
}

void menu_1(void)
{
    while(true){
        back = false;
        printf("\n\nКласове: ");
        printf("\n1) 8-ми клас");
        printf("\n2) 9-ми клас");
        printf("\n3) 10-ми клас");
        printf("\n4) 11-ми клас");
        printf("\n5) 12-ми клас");
        printf("\n6) Връщане");
        option = get_string("\nОпция - ");

        if (strcmp(option, "1") != 0 && strcmp(option, "2") != 0 && strcmp(option, "3") != 0 && strcmp(option, "4") != 0 && strcmp(option, "5") != 0 && strcmp(option, "6") != 0)
        {
            printf("\nМоля въведете цифрата на една от зададените опции!");
            option = get_string("\nНатисни Enter за да продължиш...");
        }
        else
        {
            switch (option[0])
            {
                case '1':
                grade = 8;
                return;

                case '2':
                grade = 9;
                return;

                case '3':
                grade = 10;
                return;

                case '4':
                grade = 11;
                return;

                case '5':
                grade = 12;
                return;

                case '6':
                back = true;
                return;

                default:
                return;
            }
        }
    }
}

void menu_2(void)
{
    while(true){
        back = false;
        printf("\n\nПаралелки: ");
        printf("\n1) А паралелка");
        printf("\n2) Б паралелка");
        printf("\n3) Връщане");
        option = get_string("\nОпция - ");

        if (strcmp(option, "1") != 0 && strcmp(option, "2") != 0 && strcmp(option, "3") != 0)
        {
            printf("\nМоля въведете цифрата на една от зададените опции!");
            option = get_string("\nНатисни Enter за да продължиш...");
        }
        else
        {
            switch (option[0])
            {
                case '1':
                parr = 'a';
                return;

                case '2':
                parr = 'b';
                return;

                case '3':
                back = true;
                return;

                default:
                return;
            }
        }
    }
}

void students_display(int class, char par, string datanames[], int dataots[])
{
    int classotssum = class_ots_sum(class, par);
    int count = 0;
    printf("\nОбщ брой отсъствия - %i\n%i%c клас:", classotssum, class, par);
    for(int i = 0; i < MAX_STUDENTS; i++)
    {
        if(students[i].class == class && students[i].par == par)
        {
            // променлива която няма приложение във функцията, но помага извън нея и е тука като паразит въпреки че мога да променя printf да показва данните от datanames и dataots реших да ги оставя така
            datanames[count] = students[i].name;
            dataots[count] = students[i].ots;
            printf("\n%i. %s - %i отс.", ++count, students[i].name, students[i].ots);
        }
    }
}

void change_ots(string namesave)
{
    while (true)
    {
        int new_ots = 0;
        new_ots = get_int("\nВъведи нов брой отсъствия - ");
        if(new_ots < 0 ){
            printf("Ученик не може да има по-малко от 0 отс.");
            option = get_string("\nНатисни Enter за да продължиш...");
        }
        else{
            for (int i = 0; i < MAX_STUDENTS; i++)
            {
                if (strcmp(students[i].name, namesave) == 0 && students[i].class == grade && students[i].par == parr)
                {
                    students[i].ots = new_ots;
                    printf("\n%s има променени отсъствия - %i отс.", students[i].name, students[i].ots);
                    break;
                }
            }

            // "w" вместо "а" за да пренапишем цялата информация тъй като сме я копирали в програмата и всички данни съществуват в приложението и можем спокойно да пренапишем целият файл
            FILE *fp = fopen("students.txt", "w");
            if (!fp)
            {
                printf("\nГрешка при записване на файла!");
                option = get_string("\nНатисни Enter за да продължиш...");
                return;
            }
            for (int i = 0; i < MAX_STUDENTS; i++)
            {
                //fprintf служи за добавяне на иформация линия по линия
                fprintf(fp, "%s,%i,%c,%i\n", students[i].name, students[i].class, students[i].par, students[i].ots);
            }
            fclose(fp);

            printf("\nПромените са записани във файла.");
            option = get_string("\nНатисни Enter за да продължиш...");
            return;
        }
    }
}

void menu_3(int class, char par, string namesave, int otssave)
{
    while(true){
        printf("%s от %i%c клас - %i отс.", namesave, class, par, otssave);
        printf("\n1) Промени");
        printf("\n2) Връщане");
        option = get_string("\nОпция - ");
        if (strcmp(option, "1") != 0 && strcmp(option, "2") != 0)
        {
            printf("\nМоля въведете цифрата на една от зададените опции!");
            option = get_string("\nНатисни Enter за да продължиш...");
        }
        else
        {
            switch(option[0])
            {
                case '1':
                change_ots(namesave);
                return;

                case '2':
                back = true;
                return;

                default:
                return;
            }
        }
    }
}

// вместо да вкарам тази част от кода в main съм направил отделна функция за да мога при натистакне на опация назад да се връща на предходна функция вместо да затваря програмата или да пропуска предна функция като вече сме избрали опция за 3та функция
void option_1(void)
{
    if(strcmp(option, "1") == 0)
    {
        do{
            menu_1();
            if(back)return;
            menu_2();
        } while(back);

        do{
            back = false;
            string datanames[25];
            int dataots[25];
            students_display(grade, parr, datanames, dataots);
            printf("\nВъведи номер на ученик за промяна на отсъствията или натисни Enter за връщане назад:");
            option = get_string("\nВъведи номер или Enter - ");
            if(option[0] == '\0') return;
            else if(atoi(option) > 0 && atoi(option) < 26)
            {
                string namesave = datanames[atoi(option)-1];
                int otssave = dataots[atoi(option)-1];
                menu_3(grade, parr, namesave, otssave);
            }
            else{
                back = true;
                printf("\nМоля въведете цифрата на една от зададените опции!");
                option = get_string("\nНатисни Enter за да продължиш...");
            }
        }while(back);
    }
}

int ots_sum(void)
{
    int ots = 0;
    for(int i = 0; i < MAX_STUDENTS; i++)
    {
        ots += students[i].ots;
    }
    return ots;
}

int class_ots_sum(int group, char subgroup)
{
    int sum = 0;
    for (int i = 0; i < MAX_STUDENTS; i++)
    {
        if (students[i].class == group && students[i].par == subgroup)
        {
            sum += students[i].ots;
        }
    }
    return sum;
}
