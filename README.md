#Ft_ls_42school
Ft_ls recodes (but not fully) the Unix command that lists files in the directories given as arguments. Original ls suggests the following flags that influence the list output:

    original: -ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1

This ft_ls-program deals with the following flags:

    ft_ls: -1CFGRSacdfglprstu

#Usage
You need to compile the program and then use it according to the usage the original ls-command has.

So, your steps -

Clone the repository:

    git clone https://github.com/VladlenaSkubi-du/Ft_ls_42school.git

Get into it and compile the ft_ls-program:

    cd [folder's name you want]
    make

After you make:

    ./ft_ls [flag] [directory-name or file-name or any staff you want]

For example:

    ./ft_ls -l .. or 
    ./ft_ls -GC /usr / ~/Downloads Makefile aaa

Paralelly you can check the output using the same arguments for original ls-command and ft_ls-program. I hope it will show the same results.

Go and try. Good luck!

#The program returns
The same output as the original ls-command with all the flags described in the first part of README. If you input a directory (".", "..", "/", "~/Applications") as an argument, ft_ls program returns a list of files lying within this directory (or to say it in a more "scientific" way - listed in the catalogue with the same name and path as the argument you input).
If you input a file name or link name or program name and so on as an argument, ft_ls program returns the names you input if they exist in the directory you work from or put as an argument. If you input some staff that does not exist, ft_ls outputs: "./ft_ls: 1: No such file or directory".
It can also answer as: "./ft_ls: Permission denied" if the files or directories you input as arguments are non-readable for you as user (your group of users).

You can also try special commands that this ft_ls reproduces as the original ls-command:

    ./ft_ls -aC / > test_file.txt

    mkdir l
    mv l -l
    ./ft_ls -a -- -u

Where flag "--" gives stop to ./ft_ls and says that further it will see only arguments but not flags. The following command will be long because it will show all the files under the root-user (all the files in the system):

	./ft_ls -RG ~/

The last command will be beautiful and list all the files lying in the home-directoty and its sub-directories.

#Grade
/100
