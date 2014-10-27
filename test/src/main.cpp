#include "test.h"

#include <lib/context/context.h>

#include <persistent_subject.h>

// hacky way not to dupe basic_subject and safe_policy
#include <lib/context/test/src/observer_test.h> /* basic_subject, safe_policy */ 

template< template<class> class T >
void test_persistence()
{
    typedef om636::context< int, T > context_type;
    
    const char * path( "persistent_storage.dat" );
    
    if (1)
    {
        context_type a( std::string("test_persistence_var"), path );
        a = 1230;
    }
    
    if (1)
    {
        context_type a( std::string("test_persistence_var"), path );
        
        ASSERT( a.value_ref() == 1230 );
    
        a = 1239;
    }

    if (1)
    {
        context_type a( std::string("test_persistence_var"), path );
    
        ASSERT( a.value_ref() == 1239 );
    }
}

template<class T>
using persistent_policy = om636::persistent_subject< safe_policy< T > >;

int main(int argc, const char * argv[])
{
	
    test_persistence< persistent_policy >();
    
    return 0;
}