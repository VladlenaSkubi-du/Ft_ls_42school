# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>
# include <stdlib.h>
# include <stdio.h>
# include <termios.h>

int		main(void)
{
//	write(1, "\33[1;31mHello World\33[m\n", 18);
	DIR *dir;
	struct dirent *entry;

	dir = opendir(".");
	if (!dir) {
		perror("diropen");
		exit(1);
	};

	while ( (entry = readdir(dir)) != NULL) {
		printf("%lld - %s [%d] %d\n",
		entry->d_ino, entry->d_name, entry->d_type, entry->d_reclen);
	};

	closedir(dir);
	return (0);
}
