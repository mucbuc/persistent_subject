#include "test.h"

#include <lib/context/src/interface.h>
#include <lib/persistent_subject/persistent_subject.h>
#include <lib/sense/src/observer.h>
#include <lib/sense/src/subject.h>

template< template<class> class T, class U>
void test_persistence(U u, U v, std::string name)
{
    typedef om636::context< U, T > context_type;
    
    const char * path( "persistent_storage.dat" );
    
    if (1)
    {
        context_type a( name, path );
        a = u;
    }
    
    if (1)
    {
        context_type a( name, path );
        
        ASSERT( a.value_ref() == u );
    
        a = v;
    }

    if (1)
    {
     context_type a( name, path );

     ASSERT( a.value_ref() == v );
    }

    if (1)
    {
        context_type a( name, path );

        a = v = u;

        ASSERT( a.value_ref() == u )( a.value_ref() );
    }


    FOOTER;
}

template<class T>
using basic_subject = om636::basic_subject< T, om636::observer >;

template<class T>
using safe_policy = om636::safe_subject< basic_subject< T > >;

template<class T>
using persistent_policy = om636::persistent_subject< safe_policy< T > >;

int main(int argc, const char * argv[])
{
    test_persistence< persistent_policy, int >( 1230, 1239, "test_persistence_int" );
    test_persistence< persistent_policy, std::string >( "hello", "bye", "test_persistence_string" );
    
    return 0;
}