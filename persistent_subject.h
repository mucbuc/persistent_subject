#ifndef persistent_subject_3lk34jtrljlkj344343 
#define persistent_subject_3lk34jtrljlkj344343

#include <map>

#include <lib/om636/src/core/persistent.h>
#include <lib/om636/src/create/singleton.h>

namespace om636
{
    template<class T>
    struct persistent_subject
    : public T
    {
        typedef T base_type;
        using typename base_type::context_type;
        using typename base_type::value_type;
        using base_type::on_init;

        persistent_subject();
        persistent_subject(const char *);
        virtual ~persistent_subject();
        
        template<class U>
        static value_type on_init(U &, const std::string &);
    
        virtual void on_swap(context_type &, context_type &);
        
        std::string & name();
        std::string name() const;
        
    private:
        
        typedef om636::persistent< std::map< std::string, std::string > > persistent_type;
        typedef singleton< persistent_type, default_lifetime< persistent_type >, create_new< persistent_type > > singleton_type;
        
        std::string m_name;
    };
}   //om636

#include "persistent_subject.hxx"

#endif // persistent_subject_3lk34jtrljlkj344343