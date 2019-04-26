#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#define MAX_PATH 260
#define KEY 17
#define ENCRYPT 0
#define DECRYPT 1
//Key 17 untuk mengambil indeks ke 17 dalam

static const char dirpath[] = "/home/tieria21/modul4";
static const char charlist[] = "qE1~ YMUR2\"`hNIdPzi\%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0";

void caesar(char inp[], int len, int flag){
    int i, j, indeks;
    if (flag == ENCRYPT){
        for (i = 0; i < len; i++){

            if (inp[i] == '/')
                continue;
            else
            {
                for (j = 0; j < strlen(charlist); j++)
                {
                    if (charlist[j] == inp[i])
                        indeks = j;
                }
                indeks += KEY;
                indeks %= strlen(charlist);
                inp[i] = charlist[indeks];
            }
        }
    }

    else if (flag == DECRYPT){

        for (i = 0; i < len; i++){
            if (inp[i] == '/')
                continue;
            else{

                for (j = 0; j < strlen(charlist); j++){

                    if (charlist[j] == inp[i])
                        indeks = j;
                }
                indeks -= KEY;
                while (indeks < 0)
                    indeks += strlen(charlist);
                inp[i] = charlist[indeks];
            }
        }
    }
}

static int xmp_getattr(const char *path, struct stat *stbuf)
{
    int res;
    char name[MAX_PATH], fname[MAX_PATH];
    memset(fname, '\0', MAX_PATH);
    strcpy(name, path);
    caesar(name, strlen(name), ENCRYPT);
    strcat(fname, dirpath);
    strcat(fname, name);
    res = lstat(fname, stbuf);
    if (res == -1)
        return -errno;
    return 0;
}

static int xmp_readdir(const char *path,
                       void *buf,
                       fuse_fill_dir_t filler,
                       off_t offset,
                       struct fuse_file_info *fi)
{
    char name[MAX_PATH], fname[MAX_PATH], dec[MAX_PATH];
    memset(fname, '\0', MAX_PATH);
    if(strcmp(path,"/") == 0)
    {
        path = dirpath;
        sprintf(fname, "%s", path);
    }
    else
    {
        strcpy(name, path);
        caesar(name, strlen(name), ENCRYPT);
        memset(fname, '\0', MAX_PATH);
        strcat(fname, dirpath);
        strcat(fname, name);
    }
    int res = 0;

    DIR *dp;
    struct dirent *de;

    (void) offset;
    (void) fi;

    dp = opendir(fname);
    if (dp == NULL)
        return -errno;

    while ((de = readdir(dp)) != NULL)
    {
        if(strcmp(de->d_name,".")==0||strcmp(de->d_name,"..")==0)
            continue;
        if (strcmp(de->d_name, "@ZA>AXio") == 0)
        {
            system("touch /home/tieria/dapet");
        }
        struct stat st;
        memset(&st, 0, sizeof(st));
        st.st_ino = de->d_ino;
        st.st_mode = de->d_type << 12;
        memset(dec, '\0', MAX_PATH);
        strcpy(dec, de->d_name);
        caesar(dec, strlen(dec), DECRYPT);
        res = (filler(buf, dec, &st, 0));
        if(res != 0)
            break;
    }

    closedir(dp);
    return 0;
}

static int xmp_read(const char *path,
                    char *buf,
                    size_t size,
                    off_t offset,
                    struct fuse_file_info *fi)
{
    char name[MAX_PATH], fname[MAX_PATH];
    memset(fname, '\0', MAX_PATH);
    if(strcmp(path,"/") == 0)
    {
        path = dirpath;
        sprintf(fname, "%s", path);
    }
    else
    {
        strcpy(name, path);
        caesar(name, strlen(name), ENCRYPT);
        memset(fname, '\0', MAX_PATH);
        strcat(fname, dirpath);
        strcat(fname, name);
    }
    int res = 0;
    int fd = 0 ;

    (void) fi;
    fd = open(fname, O_RDONLY);
    if (fd == -1)
        return -errno;

    res = pread(fd, buf, size, offset);
    if (res == -1)
        res = -errno;

    close(fd);
    return res;
}

static struct fuse_operations xmp_oper =
{
    .getattr	= xmp_getattr,
    .readdir	= xmp_readdir,
    .read		= xmp_read,
};

int main(int argc, char *argv[])
{
    umask(0);
    argc = 2;
    argv[0] = "./sisop4";
    argv[1] = "/home/tieria21/soal4_mount";
    argv[2] = NULL;
    return fuse_main(argc, argv, &xmp_oper, NULL);
}
