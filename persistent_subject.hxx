
namespace om636
{
#pragma mark peristent_subject 
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    persistent_subject<T>::persistent_subject()
    : base_type()
    , m_name()
    {}
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    persistent_subject<T>::persistent_subject( const char * path )
    : base_type()
    , m_name( path )
    {
        singleton_type::instance().open( path );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    persistent_subject<T>::~persistent_subject()
    {}

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    template<class U, class V> 
    auto persistent_subject<T>::on_init(U & lhs, const V & init)->value_type
    {
        using std::string;
        using std::stringstream;

        if (lhs.m_name.empty()) 
        {
            lhs.m_local.reset( new value_type() );
            stringstream( init ) >> * lhs.m_local;
            return * lhs.m_local;
        }
        
        string & value ( singleton_type::instance().storage()[ lhs.name() = init ] );
        value_type result;
        stringstream( value ) >> result;
        return result;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    void persistent_subject<T>::on_swap(context_type & lhs, context_type & rhs)
    {
        using namespace std;

        if (rhs.m_local)
        {
            ASSERT( !name().empty() ); 

            string & value ( singleton_type::instance().storage()[ name() ] );
            value = * rhs.m_local;
        }
        else
        {
            lhs.name() = rhs.name(); 
        }
        
        base_type::on_swap( lhs, rhs );
    }
        
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    std::string & persistent_subject<T>::name()
    {
        return m_name;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    std::string persistent_subject<T>::name() const
    {
        return m_name;
    }

}   // om636