#include "student.h"
#include "exam.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int number;
    char name[20];
    int midterm;
    int final;
} Exam;

typedef struct {
    int number;
    char name[20];
    char phone[15];
    char birth[10]; // 앞으로 정수형으로 바꿔야함
    char gender;
    int height;
    char email[40];
} Student;


void exam()
{
    FILE *main_file;
    FILE *sub_file;
    char line[256];
    char line2[256];
    Exam exams[40];
    Student students[40];
    int exam_count = 0;
    int student_count = 0;

    main_file = fopen("exam.txt", "w+");
    sub_file = fopen("student.txt", "r+");

    if (main_file == NULL || sub_file == NULL) {
        printf("파일 여는중 오류 발생;;\n");
        return;
    }
    else if (main_file != NULL && sub_file != NULL){
        while (fgets(line, sizeof(line), main_file)) {
            if (line[0]=='\0'){
                printf("시험 정보가 없습니다.\n");
            }
            sscanf(line, "%d\t%19[^\t]\t%d\t%d\n",
                &exams[exam_count].number,
                exams[exam_count].name,
                &exams[exam_count].midterm,
                &exams[exam_count].final
                );
            exam_count++;
        }
        
        while (fgets(line2, sizeof(line2), sub_file)){
            if (line2[0]=='\0'){
                printf("학생 정보가 없습니다.\n");
            }
            sscanf(line2, "%d\t%19[^\t]\t%14[^\t]\t%9[^\t]\t%c\t%d\t%39[^\n]",
                &students[exam_count].number,
                students[exam_count].name,
                students[exam_count].phone,
                students[exam_count].birth,
                &students[exam_count].gender,
                &students[exam_count].height,
                students[exam_count].email
                );
            student_count++;

        }
        int save[40];
        int save_count = 0;
        for (int i = 0; i < exam_count; i++) {
            for (int j = 0; j < student_count; j++) {
                if (exams[i].number == students[j].number) {
 
                    save[save_count] = j;
                    save_count++;
                }
            }
        }
        if(exam_count == 0) {
            printf("시험 정보가 없습니다.\n");
            return;
        }

        int test_avg[exam_count];
        char test_grade[exam_count][3];

        printf("학생 수: %d\n", exam_count);
        printf("   학번   \t 이름 \t    중간   \t 기말 \t 평균 \t 학점\n");   
        for (int i = 0; i < exam_count; i++) {
            test_avg[i] = (exams[i].midterm + exams[i].final) / 2;
            if (100>= test_avg[i] && test_avg[i] >= 95)
                strcpy(test_grade[i], "A+");
            else if (test_avg[i] >= 90)
                strcpy(test_grade[i], "A");
            else if (test_avg[i] >= 85)
                strcpy(test_grade[i], "B+");
            else if (test_avg[i] >= 80)
                strcpy(test_grade[i], "B");
            else if (test_avg[i] >= 75)
                strcpy(test_grade[i], "C+");
            else if (test_avg[i] >= 70)
                strcpy(test_grade[i], "C");
            else if (test_avg[i] >= 65)
                strcpy(test_grade[i], "D+");
            else if (test_avg[i] >= 60)
                strcpy(test_grade[i], "D");
            else
                strcpy(test_grade[i], "F");
            printf("%d\t%s\t%d\t%d\t%d\t%s\n",
                exams[i].number,
                exams[i].name,
                exams[i].midterm,
                exams[i].final,
                test_avg[i],
                test_grade[i]
                );
        } 
        int count = 0;
        for (int i = 0; i<student_count;i++){
            if (i == save[count]){
                count++;
                continue;
            }
            printf("%d\t%s\t0\t0\t0\t0\tF\n",
                students[i].number,
                students[i].name
                );
        }
    }
    fclose(main_file);
    fclose(sub_file);
}