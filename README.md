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
