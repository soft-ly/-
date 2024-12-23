#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//고쳐야할 오류들
//1. add: 한꺼번에 학생정보 입력받기
//2. add: 특정학생 정보의 조건들을 세부화 시키기.(ex. 학번은 8자리로 제한, 전화번호는 11자리로 해도 -추가하기, 전번 11자리로 제한, 생년월일 6자리로 입력하면 8자리로 바꿔서 저장,
//                                               성별 입력시 남자, 여자로도 입력가능하게 만들기)
//3. del: 학생정보 삭제시 학생정보가 없을때의 예외처리
//4. del: 학생정보 삭제시 정수형 값이 0으로 출력되서 텍스트 파일에 0이 저장됨. -> 평소에는 string 형태로 저장하고 필요할때만 정수형으로 쓰기

typedef struct {
    int number;
    char name[20];
    char phone[15];
    char birth[10]; // 앞으로 정수형으로 바꿔야함
    char gender;
    int height;
    char email[40];
} Student;


void show()
{
    FILE *file;
    char line[256];
    Student students[40];
    int student_count = 0;

    file = fopen("student.txt", "r+");

    if (file == NULL) {
        printf("파일 여는 중에 오류가 있었거나, 파일이 없음.\n");
        printf("파일을 새로 생성하겠음\n");
        file = fopen("student.txt", "w+");    
    }
    if (file != NULL){
        while (fgets(line, sizeof(line), file)) {
            if (line[0]=='\0'){
                printf("학생 정보가 없습니다.\nadd를 통해 학생 정보를 추가하세요.\n");
            }
            sscanf(line, "%d\t%19[^\t]\t%14[^\t]\t%9[^\t]\t%c\t%d\t%39[^\n]",
                &students[student_count].number,
                students[student_count].name,
                students[student_count].phone,
                students[student_count].birth,
                &students[student_count].gender,
                &students[student_count].height,
                students[student_count].email
                );
            student_count++;
        }
        if(student_count == 0) {
            printf("학생 정보가 없습니다.\n");
            return;
        }
        printf("학생 수: %d\n", student_count);
        printf("   학번   \t 이름 \t    전화번호   \t 생년월일 \t성별\t 키 \t    이메일    \n");   
        for (int i = 0; i < student_count; i++) {
            printf("%d\t%s\t%s\t%s\t%c\t%d\t%s\n",
                students[i].number,
                students[i].name,
                students[i].phone,
                students[i].birth,
                students[i].gender,
                students[i].height,
                students[i].email
                );
        }
    }
    fclose(file);
}

void add()
{
    FILE *file;
    char line[256];
    Student students[40];
    int student_count = 0;

    file = fopen("student.txt", "a+");

    if (file == NULL) {
        printf("파일 여는 중에 오류가 있었거나, 파일이 없음.\n");
        printf("파일을 새로 생성하겠음\n");
        file = fopen("student.txt", "w+");    
    }
    printf("학생 정보를 입력하세요.\n");
    printf("학번: "); //이번주 안에 학생정보 한번에 입력받는것 완료하기
    scanf("%d", &students[student_count].number);
    printf("이름: ");
    scanf("%s", students[student_count].name);
    printf("전화번호: ");
    scanf("%s", students[student_count].phone);
    printf("생년월일: ");
    scanf("%s", students[student_count].birth);
    printf("성별: ");
    scanf(" %c", &students[student_count].gender);
    printf("키: ");
    scanf("%d", &students[student_count].height);
    printf("이메일: ");
    scanf("%s", students[student_count].email);

    fprintf(file, "%d\t%s\t%s\t%s\t%c\t%d\t%s\n",
        students[student_count].number,
        students[student_count].name,
        students[student_count].phone,
        students[student_count].birth,
        students[student_count].gender,
        students[student_count].height,
        students[student_count].email
        );
    student_count++;

    fclose(file);
}

void del()
{
    FILE *file;
    char line[256];
    Student students[40];
    int student_count = 0;

    file = fopen("student.txt", "r+");

    if (file == NULL) {
        printf("파일 여는중 오류 발생;;\n");
        return;
    }
    else if (file != NULL){
        while (fgets(line, sizeof(line), file)) {
            if (line[0]=='\0'){
                printf("학생 정보가 없습니다.\n");
            }
            sscanf(line, "%d\t%19[^\t]\t%14[^\t]\t%9[^\t]\t%c\t%d\t%39[^\n]",
                &students[student_count].number,
                students[student_count].name,
                students[student_count].phone,
                students[student_count].birth,
                &students[student_count].gender,
                &students[student_count].height,
                students[student_count].email
                );
            student_count++;
        }
        if(student_count == 0) {
            printf("학생 정보가 없습니다.\n");
            return;
        }
        printf("학번: ");
        int num_del;
        scanf("%d", &num_del);
        for (int i = 0; i < student_count; i++) {
            if (students[i].number == num_del) {
                for (int j = i; j < student_count; j++) {
                    students[j] = students[j+1];
                }
                student_count--;
            }
        }
    }
    fclose(file);
    file = fopen("student.txt", "w");
    for (int i = 0; i < student_count; i++) {
        fprintf(file, "%d\t%s\t%s\t%s\t%c\t%d\t%s\n",
            students[i].number,
            students[i].name,
            students[i].phone,
            students[i].birth, 
            students[i].gender,
            students[i].height,
            students[i].email
            );
    }
    fclose(file);
}

void sort()
{
    FILE *file;
    char line[256];
    Student students[40];
    int student_count = 0;

    file = fopen("student.txt", "r+");

    if (file == NULL) {
        printf("파일 여는중 오류 발생;;\n");
        return;
    }
    else if (file != NULL){
        while (fgets(line, sizeof(line), file)) {
            if (line[0]=='\0'){
                printf("학생 정보가 없습니다.\n");
            }
            sscanf(line, "%d\t%19[^\t]\t%14[^\t]\t%9[^\t]\t%c\t%d\t%39[^\n]",
                &students[student_count].number,
                students[student_count].name,
                students[student_count].phone,
                students[student_count].birth,
                &students[student_count].gender,
                &students[student_count].height,
                students[student_count].email
                );
            student_count++;
        }
        if(student_count == 0) {
            printf("학생 정보가 없습니다.\n");
            return;
        }
        Student temp;
        for (int i = 0; i < student_count; i++) {
            for (int j = i+1; j < student_count; j++) {
                if (students[i].height > students[j].height) {
                    temp = students[i];
                    students[i] = students[j];
                    students[j] = temp;
                }
            }
        }
        for (int i = 0; i < student_count; i++) {
            printf("%d\t%s\t%s\t%s\t%c\t%d\t%s\n",
                students[i].number,
                students[i].name,
                students[i].phone,
                students[i].birth,
                students[i].gender,
                students[i].height,
                students[i].email
                );
        }
    }
    fclose(file);
}

void quit()
{
    printf("프로그램을 종료합니다.\n");
    exit(0);
}