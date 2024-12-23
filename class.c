#include <stdio.h>
#include <string.h>
#include "exam.h"
#include "student.h"

//하고 싶은 것들:
// 1. 특정 명령 뒤에 //?를 입력하면 설명을 출력해주기
// 2. 학생정보를 동적 메모리를 사용해서 저장하기


int main() {
    printf("version 1.0\n");
    printf("<<학사관리 시스템>>\n");
    printf(">>> show\n");
    printf(">>> add\n");
    printf(">>> del\n");
    printf(">>> sort\n");
    printf(">>> exam\n");
    printf(">>> quit\n");
    printf("\\?를 치시면 명령들에 대하여 설명드립니다.\n");

    while(1) {
            char command[12];
            printf(">>> ");
            scanf("%s", command);
            if (strcmp(command, "show") == 0)
                show();
            else if (strcmp(command, "add") == 0)
                add();
            else if (strcmp(command, "del") == 0)
                del();
            else if (strcmp(command, "sort") == 0)
                sort();
            else if (strcmp(command, "exam") == 0)
                exam();
            else if (strcmp(command, "quit") == 0)
                quit();
            else if (strcmp(command, "\\?") == 0) {
                printf(">>> show: 학생 정보를 출력합니다.\n");
                printf(">>> add: 학생 정보를 추가합니다.\n");
                printf(">>> del: 학생 정보를 삭제합니다.\n");
                printf(">>> sort: 학생 정보를 정렬합니다.\n");
                printf(">>> exam: 시험 점수를 입력합니다.\n");
                printf(">>> quit: 프로그램을 종료합니다.\n");
            }
            else
                printf("잘못된 명령어입니다.\n");

            printf("다음 명령을 입력하세요!\n");

    }



}
