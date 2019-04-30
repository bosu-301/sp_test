#include <sys/types.h> 
#include <sys/stat.h> 
#include <dirent.h> 
#include <pwd.h> 
#include <grp.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
void printStat(char*, char*, struct stat*);

int main(int argc, char **argv)
{
    DIR *dp;
    char *dir;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ + 1];
    if (argc == 1)
        dir = ".";
    else dir = argv[1];
    if ((dp = opendir(dir)) == NULL)
        perror(dir);
    while ((d = readdir(dp)) != NULL) {
        sprintf(path, "%s/%s", dir, d->d_name);
        if (lstat(path, &st) < 0) 
            exit(1);
        printStat(path, d->d_name, &st);
        putchar('\n');
    }
    closedir(dp);
    exit(0);
}

void printStat(char *pathname, char *file, struct stat *st) {
    printf("%s %s ", getpwuid(st->st_uid)->pw_name, getgrgid(st->st_gid)->gr_name);
    printf("%.12s ", ctime(&st->st_mtime) + 4); // 수정시간
    printf("%s", file); // 파일명 
}
