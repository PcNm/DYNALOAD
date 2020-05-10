#define DYNALOAD_IMPLEMENTATION
#include "DYNALOAD.H"

#include <stdio.h> // printf

typedef int( * fun_foo )( void );
int main ( int argc, char ** argv )
{
	s_dynaload * dl = dynaload_create( "foo.dll", 0 ); // load DLL named "foo.dll"
	if ( dl )
	{
		if ( dynaload_is_loaded( dl ) ) // check if "foo.dll" could be loaded
		{
			fun_foo foo = (fun_foo) dynaload_procload( dl, "foo", 0 ); // load function "foo"
			
			if ( foo ) // check if function "foo" could be loaded
			{
				int bar = foo(); // call function "foo"
				
				printf( "foo.dll -> foo() returned bar %d", bar );
			}
		}
		dynaload_destroy( dl ); // also calls dynaload_exitlibrary( dl );
	}
};
