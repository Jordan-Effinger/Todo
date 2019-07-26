#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/file.h>

#define BUFF 80

int
main( void )
{
    char homedir[BUFF], temp[BUFF], filename[BUFF], cmd[BUFF];
    int res, fd = 0;
    
    strcpy( homedir, getenv("HOME") );
    sprintf( temp, "%s/.todo", homedir);
    realpath( temp, filename );
    
    fd = open(filename, O_RDWR | O_CREAT );
    if( fd == -1 )
    {
        fprintf( stderr, "Errno %d; Error %s; Opening %s for read-write.\n", errno, strerror(errno), filename );
        return(errno);
    }
    
    sprintf( cmd, "vi %s", filename );
    
    res = system(cmd);
    if( res == 127 )
    {
        fprintf( stderr, "Error 127; Error shell execution failed; Running %s.\n", cmd );
    }
    else if( res == -1 )
    {
        fprintf( stderr, "Error %d; Error %s; Calling fork or exec while running %s.\n", errno, strerror(errno), cmd );
    }
    else{
        res = 0;
    }

    close(fd);
    return(0);
}
