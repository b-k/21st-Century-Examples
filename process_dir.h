/* See compilation notes in show_tree.c or charct.c*/
struct filestruct;
typedef void (*level_fn)(struct filestruct path);

typedef struct filestruct{
    char *name, *fullname;
    level_fn directory_action, file_action;
    int depth, error;
    void *data;
} filestruct;

/** I get the contents of the given directory, run \c file_action on each
    file, and for each directory run \c dir_action and recurse into the directory.
    Note that this makes the traversal `depth first'.

    Your functions will take in a \c filestruct, qv. Note that there is an \c error
    element, which you can set to one to indicate an error.

    Inputs are designated initializers, and may include:

    \li \c .name The current file or directory name
    \li \c .fullname The path of the current file or directory
    \li \c .directory_action A function that takes in a \c filestruct.
            I will call it with an appropriately-set \c filestruct
            for every directory (just before the files in the directory
            are processed).
    \li \c .file_action Like the \c directory_action, but the function
            I will call for every non-directory file.
    \li \c .data A void pointer to be passed in to your functions.

    \return 0=OK, otherwise the count of directories that failed + errors thrown by your scripts.
    Your functions may change the \c data element of the \c filestruct.

    Sample usage:
\code
    void dirp(filestruct in){ printf("Directory: <%s>\n", in.name); }
    void filep(filestruct in){ printf("File: %s\n", in.name); }

    //list files, but not directories, in current dir:
    process_dir(.file_action=filep);

    //show everything in my home directory:
    process_dir(.name="/home/b", .file_action=filep, .directory_action=dirp);
\endcode
*/
#define process_dir(...) process_dir_r((filestruct){__VA_ARGS__})

int process_dir_r(filestruct level);
