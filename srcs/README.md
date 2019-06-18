#Ft_ls_42school
Ft_ls recodes (but not fully) the Unix command that lists files in the directories given as arguments. Originaloing flags that influence the list output:

    original: -ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1

This ft_ls-program deals with the following flags:

    ft_ls: -1CFGRSacdfglprstu

#Usage
You need to compile the program and then use it according to the usage the original ls-command has.

So, your steps -

Clone the repository:

    git clone https://github.com/VladlenaSkubi-du/Ft_ls_42school.git

Get into it and compile the ft_ls program:

    cd [folder's name you want]
    make

After you make:

    ./ft_ls [flag] [directory]

For example:

    ./ft_ls -l .. or 
    ./ft_ls -GC /usr / ~/Downloads Makefile aaa

Or other arguments you want. At the same time you are able to use the same arguments for original ls-command and check if ft_ls program shows the same results. I hope.

Go and try. Good luck!

#The program returns
The same output as the original ls-command with all the flags described in the first part of README. If you input a directory (".", "..", "/", "~/Applications") as an argument, ft_ls program returns a list of files lying within this directory.
If you input a file name or link name or program name and so on as an argument, ft_ls program returns the names you input if they exist in the directory you work from or put as an argument. If you input some staff that does not exist, ft_ls outputs: "./ft_ls: 1: No such file or directory".
It can also answer as: "./ft_ls: Permission denied" if the files or directories you input as arguments are non-readable for you as user (your group of users).

You can also try special commands that this ft_ls reproduces as the original ls-command:

    ./ft_ls -aC / > test_file.txt

    mkdir l
    mv l -l
    ./ft_ls -a -- -u

Where flag "--" gives stop to ./ft_ls and says that further it will see only arguments but not flags. The following command will be long because it will show all the files under the root-user (all the files in the system):

    ./ft_ls -R /

For the further check of the ft_ls program you can also find the testing script called test_ft_ls that recodes both ft_ls and ls output and compares it using diff-command.

#Grade
/100