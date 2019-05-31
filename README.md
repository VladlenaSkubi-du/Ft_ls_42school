# Ft_ls_42school
Ft_ls recodes (but not fully) the original ls-program.

Unable and reable: vim ~/.zshrc

ls -l/Library/Scripts/42/munki
ls /Library/Scripts/42/munki
ls -1 /Library/Scripts/42/munki

touch TEST
chmod 7000 TEST
ls -l TEST
chmod 7777 TEST
ls -l TEST

ls -l /dev
ls -l /

ls changes upper and lower letters:

	touch TEST
	ls TEST
	TEST
	ls test
	test
	ls TeSt
	TeSt
	ls w
	ls: w: No such file or directory

Function: issaty(1) - if the output is redirected
ls -1 = ls | cat

for check: ls /usr/sbin

For speed testing: ls /usr/share/man/man3 | wc -l
Flags to do: -1, -d, -ut (time), -x, -ul (time is changed)
Flag -G depends on the access rights

symbolic links are pink
folders are blue
files .c, .h, author .md, Makefile are no color

files like programs or without extraction are red BUT depend on the access rights:
if the following - red - letters
010, 030, 050, 070, 100, 300, 500, 700, 001, 003, 005, 007
if the following lower - no color
020, 040, 060, 200, 400, 600, 002, 004, 006
if both are odd (нечетные) - red letters
if all  are even (четные) - no color
If there is just one odd - red color - odd is stronger

SUID is 4---
SGID is 2---
Sticky-bit is 1---

Upper letters: if there were no x-right for user or group:

	touch t ; chmod +w t
	ls -la
	-rw-r--r--   1 sschmele  2018     0 Apr 26 19:12 t
	chmod u+s t
	ls -la
	-rwSr--r--   1 sschmele  2018     0 Apr 26 19:12 t

	BUT

	touch to ; chmod g+s,u=rwx,g+x,o+x to
	ls -la
	-rwxr-sr-x   1 sschmele  2018     0 Apr 26 19:15 to

if 2--- or 3--- and just one odd - blue background and black letters
if 2--- or 3--- and only even - no color
if 4--- or 5--- or 6--- or 7--- and just one odd - red color and black letters
if 4--- or 5--- or 6--- or 7--- and only even - no color
if 1--- or 0--- and just one odd - red letters
if 1--- or 0--- and only even - no color

In /dev
all the devices are blue letters
if symbolic - yellow background
if block - blue background

in /
if goinfre - blue letter and green background

AND DIFFERENT STDOUT!!

If we use colors:
write(1, "\33[1;31mHello World\33[m\n", 22) will show:
	^[[1;31mHello World^[[m$

write(1, "\33[1;31mHello World\33[m\n", 18);
	Hello World% or
	^[[1;31mHello World%

Коды атрибутов: 00=none 01=bold 04=underscore 05=blink 07=reverse 08=concealed
Текстовые цветовые коды: 30=black 31=red 32=green 33=yellow 34=blue 35=magenta 36=cyan 37=white
Фоновые цветовые коды: 40=black 41=red 42=green 43=yellow 44=blue 45=magenta 46=cyan 47=white



The allowed functions:
1) opendir

DIR *
     opendir(const char *filename);
2) readdir

struct dirent *
     readdir(DIR *dirp);
3) closedir

int
     closedir(DIR *dirp);
4) stat

int
     stat(const char *restrict path, struct stat *restrict buf);

5) lstat

int
     lstat(const char *restrict path, struct stat *restrict buf);
6) getpwuid

struct passwd *
     getpwuid(uid_t uid);

7) getgrgid

 struct group *
      getgrgid(gid_t gid);

8) listxattr

ssize_t
     listxattr(const char *path, char *namebuf, size_t size, int options);

9) getxattr

ssize_t
     getxattr(const char *path, const char *name, void *value, size_t size,
	          u_int32_t position, int options);

10) time

time_t
     time(time_t *tloc);

11) ctime

char *
     ctime(const time_t *clock);

12) readlink

ssize_t
     readlink(const char *restrict path, char *restrict buf, size_t bufsize)

13) perror

void
     perror(const char *s);

14) strerror

char *
     strerror(int errnum);



struct dirent {
  ino_t          d_ino;       /* inode number */
  off_t          d_off;       /* offset to the next dirent *//* смещение на dirent */
  unsigned short d_reclen;    /* length of this record */ /* длина d_name */
  unsigned char  d_type;      /* type of file; not supported
                                 by all file system types */
  char           d_name[256]; /* filename *//* имя файла (оканчивающееся нулем) */
};


stat(2)
считывает состояние файла
Данные системные вызовы возвращают информацию о файле в буфер, на который указывает buf. Для этого не требуется иметь права доступа к самому файлу, но — в случае stat(), fstatat() и lstat() — потребуются права выполнения (поиска) на все каталоги, указанные в полном имени файла pathname.

struct stat {
    dev_t     st_dev;         /* ID устройства с файлом */ dev_t is a 32-bit quantity with 12 bits set aside for the major number and 20 for the minor number
    ino_t     st_ino;         /* номер inode */
    mode_t    st_mode;        /* права доступа */
    nlink_t   st_nlink;       /* кол-во жёстких ссылок */
    uid_t     st_uid;         /* ID пользователя-владельца */
    gid_t     st_gid;         /* ID группы-владельца */
    dev_t     st_rdev;        /* ID устройства (если это спец. файл) */
    off_t     st_size;        /* полный размер в байтах */ 
Когда указана опция -l, то перед каждым списком выводится итоговая строка с общим размером всех файлов в списке, который измеряется в полу-килобайтах (512 байт).
    blksize_t st_blksize;     /* размер блока ввода-вывода
                                 файловой системы */
    blkcnt_t  st_blocks;      /* кол-во выделенных блоков по 512Б */
    /* Начиная с Linux 2.6, ядро поддерживает точность до
       наносекунд в следующих полям меток времени.
       Подробней о версиях до Linux 2.6, смотрите ЗАМЕЧАНИЯ. */
    struct timespec st_atime;  /* время доступа - time of last access (ls -lu)*/
    struct timespec st_mtime;  /* время изменения - time of last modification (ls -l)*/
    struct timespec st_ctime;  /* время смены состояния - time of last status change (ls -lc) */
#define st_atime st_atim.tv_sec      /* для обратной совместимости */
#define st_mtime st_mtim.tv_sec
#define st_ctime st_ctim.tv_sec
};

struct passwd {
	char    *pw_name;       /* имя пользователя */
	char    *pw_passwd;     /* пароль пользователя */
	uid_t   pw_uid;         /* id пользователя */
	gid_t   pw_gid;         /* id группы */
	char    *pw_gecos;      /* настоящее имя */
	char    *pw_dir;        /* домашний каталог */
	char    *pw_shell;      /* программа-оболочка */
};

struct timespec {
	time_t          tv_sec;
	long            tv_nsec;
};

time_t
Имя	Описание
int tm_sec;	Секунды от начала минуты - [0,60][1]
int tm_min;	Минуты от начала часа - [0,59]
int tm_hour;	Часы от полуночи - [0,23]
int tm_mday;	День месяца - [1,31]
int tm_mon;	Месяцы после января - [0,11]
int tm_year;	Года с 1900
int tm_wday;	Дни с воскресенья - [0,6]
int tm_yday;	Дни с первого января - [0,365]
int tm_isdst;	Признак летнего времени

Замечание: Для простоты и производительности различные поля структуры stat могут содержать информацию о состоянии из различных моментов работы системного вызова. Например, если st_mode или st_uid изменились другим процессом с помощью вызова chmod(2) или chown(2), то stat() может вернуть старое значение st_mode вместе с новым st_uid, или старое значение st_uid вместе с новым st_mode.
Поле st_dev описывает устройство, на котором расположен файл (для разбора идентификатора этого поля могут пригодиться макросы major(3) и minor(3)).
Поле st_rdev описывает устройство, который этот файл (inode) представляет.

#Time

Так как atime должно меняться при каждом доступе к файлу, это заметно снижает производительность, поэтому при монтировании можно использовать некоторые опции, позволяющие изменить поведение системы в этом вопросе:
noatime – вообще не менять этот атрибут.
relatime – (relative atime) немного смухлевать, и менять только когда оно становится раньше mtime или ctime. С версии 2.6.29 используется в Linux по-умолчанию.
strictatime – менять atime строго как положено, при каждом обращении к файлу.



Так как в POSIX.1 не определён размер поля d_name и других нестандартных полей, которые могут находиться перед этим полем в структуре dirent, переносимые приложения, использующие readdir_r(), должны выделять буфер, адрес которого передаётся в entry, следующим образом:


If the file or directory has extended attributes, you'll see an @ in the permissions field. For extended security information (ACLs), you'll see a +.

The @ is displayed with a extended attribute is set
The + is displayed for an ACL.
IF you have both an attribute and a ACL then you see @.
Run the command ls -le filename to see if it has any ACLs set.




Особенный вывод по цветам и проверке d_type:
1) ls -Gl /private/tmp/com.apple.launchd.hGWIvg6zhB
ls -Gl /private/tmp/com.apple.launchd.3qWNd4CUHB
ls -Gl /private/tmp/com.apple.launchd.GGiEA8N7Ie

./a.out /private/tmp/com.apple.launchd.hGWIvg6zhB/

	Domain socket: Render - 12

2) ./a.out /usr/libexec/

	File: authopen - 8

3)ls -aGl /Library/Caches - there is plus in mode: drwxr-xr-x+
4)  
