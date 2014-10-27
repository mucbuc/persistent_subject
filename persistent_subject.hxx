
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
    template<class U>
    auto persistent_subject<T>::on_init(U & lhs, const std::string & name)->value_type
    {
        using std::string;
        using std::stringstream;
        
        base_type::on_init( lhs );
        
        string & value ( singleton_type::instance().storage()[ lhs.name() = name ] );
        
        stringstream strm( value );
        
        value_type result;
        strm >> result;
        return result;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    void persistent_subject<T>::on_swap(context_type & lhs, context_type & rhs)
    {
        using namespace std;
        
        string & value ( singleton_type::instance().storage()[ name() ] );
        
        stringstream strm2;
        strm2 << rhs.value_ref();
        value = strm2.str();
        
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