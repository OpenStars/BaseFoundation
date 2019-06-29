/* 
 * File:   TServiceThriftHandlerBaseT.h
 * Author: trungthanh
 *
 * Created on February 26, 2011, 10:59 PM
 */

#ifndef TServiceThriftHandlerBaseT_H
#define	TServiceThriftHandlerBaseT_H

#include <Poco/RefCountedObject.h>
#include <thriftutil/TThriftServer.h>

template <class ModelType, class TServiceHandlerBaseType
        , class TServiceProcessorType
        , class TProtocolFactoryType = apache::thrift::protocol::TCompactProtocolFactory
        >
class TServiceThriftHandlerBaseT: virtual public TServiceHandlerBaseType{
public:
    TServiceThriftHandlerBaseT(Poco::SharedPtr<ModelType> aModel):m_model(aModel){
        m_pmodel = m_model.get();
    };
    virtual ~TServiceThriftHandlerBaseT(){};
   
    typedef openstars::base::transport::TThriftServer<TServiceHandlerBaseType , TServiceProcessorType, TProtocolFactoryType > TServiceThriftServer;
    typedef openstars::base::transport::TThriftServer<TServiceHandlerBaseType , TServiceProcessorType, apache::thrift::protocol::TCompactProtocolFactory > TCompactServiceThriftServer;
    typedef openstars::base::transport::TThriftServer<TServiceHandlerBaseType , TServiceProcessorType, apache::thrift::protocol::TBinaryProtocolFactory > TBinaryServiceThriftServer;
    
public:

protected:
    Poco::SharedPtr<ModelType> m_model;
    ModelType* m_pmodel;
public:

};


#endif	/* TServiceThriftHandlerBaseT_H */

