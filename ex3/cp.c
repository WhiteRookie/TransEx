#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>

#define BUFFER_SIZE 1024

void copy_file(const char *source, const char *object) {
    int source_fd, obj_fd;
    ssize_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];

    source_fd = open(source, O_RDONLY);
    if (source_fd == -1) {
        perror("open source file");
        exit(EXIT_FAILURE);
    }

    obj_fd = open(object, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (obj_fd == -1) {
        perror("open destination file");
        exit(EXIT_FAILURE);
    }

    while ((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(obj_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("write error");
            exit(EXIT_FAILURE);
        }
    }

    close(source_fd);
    close(obj_fd);
}

void copy_directory(const char *source, const char *destination) {
    DIR *dir;
    struct dirent *entry;
    char source_path[PATH_MAX];
    char dest_path[PATH_MAX];

    dir = opendir(source);
    if (dir == NULL) {
        perror("opendir faild");
        exit(-1);
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            snprintf(source_path, sizeof(source_path), "%s/%s", source, entry->d_name);
            snprintf(dest_path, sizeof(dest_path), "%s/%s", destination, entry->d_name);

            struct stat statbuf;
            if (lstat(source_path, &statbuf) == -1) {
                perror("lstat");
                closedir(dir);
                exit(EXIT_FAILURE);
            }

            if (S_ISDIR(statbuf.st_mode)) {
                if (mkdir(dest_path, statbuf.st_mode) == -1) {
                    perror("mkdir");
                    closedir(dir);
                    exit(EXIT_FAILURE);
                }
                copy_directory(source_path, dest_path);
            } else {
                copy_file(source_path, dest_path);
            }
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) 
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return EXIT_FAILURE;
    } 

    struct stat source_stat;
    if (lstat(argv[1], &source_stat) == -1) { // 获取源文件/目录状态
        perror("can't get the state of source file/dir");
        return -1;
    }

    // 如果源文件为目录，执行复制目录，否则执行复制文件
    if (S_ISDIR(statbuf.st_mode)) { 
        if (mkdir(argv[2], statbuf.st_mode) == -1) { // 
            perror("mkdir failed");
            return -1;
        }
        copy_directory(argv[1], argv[2]);
    } else {
        copy_file(argv[1], argv[2]);
    }

    return 0;
}