/* 
 * File:   CacheBase.h
 * Author: trungthanh
 *
 * Created on October 18, 2012, 10:29 AM
 */

#ifndef UP_CACHING_CACHEBASE_H
#define	UP_CACHING_CACHEBASE_H

namespace openstars { namespace caching {
    
    //interface for caching monitoring operations
    
    class CacheBase{
        public:
            CacheBase():_enableMemTracking(true){}
            virtual ~CacheBase(){}
            
        public:
            virtual size_t getMemSize() = 0;

            void enableTracking(bool enable){ _enableMemTracking = enable ; }
            
            virtual size_t size()const = 0;

            virtual size_t maxSize()const = 0;

            virtual void setMaxSize(size_t aSize) = 0;
            
        protected:
            bool _enableMemTracking;
        };
        
}}
#endif	/* CACHEBASE_H */

