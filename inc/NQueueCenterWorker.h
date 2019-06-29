/* 
 * File:   NQueueCenterWorker.h
 * Author: trungthanh
 *
 * Created on January 14, 2010, 3:26 PM
 * Class NQueueCenterWorker
 * Auto dequeue notifications from NotificationQueue and post it to observers of NotificationCenter
 * postNotification will be called in worker thread.
 *
 * Using this for async jobs.
 * Master thread will enqueue notification in a queue
 *  Workers will dequeue notification and post to observers.
 */

#ifndef _NQUEUECENTERWORKER_H
#define	_NQUEUECENTERWORKER_H

#include <Poco/NotificationCenter.h>
#include <Poco/NotificationQueue.h>
#include <Poco/Thread.h>
#include <Poco/Runnable.h>
#include <Poco/SharedPtr.h>
#include <Poco/NObserver.h>

// a change from Poco::NObserver
namespace openstars{
template <class C, class N>
class NObserver : public Poco::AbstractObserver
/// This template class implements an adapter that sits between
/// a NotificationCenter and an object receiving notifications
/// from it. It is quite similar in concept to the 
/// RunnableAdapter, but provides some NotificationCenter
/// specific additional methods.
/// See the NotificationCenter class for information on how
/// to use this template class.
///
/// This class template is quite similar to the Observer class
/// template. The only difference is that the NObserver
/// expects the callback function to accept a const AutoPtr& 
/// instead of a plain pointer as argument, thus simplifying memory
/// management.
{
public:
    typedef Poco::AutoPtr<N> NotificationPtr;
    typedef void (C::*Callback)(const NotificationPtr&);

    NObserver(C& object, Callback method) :
    _pObject(&object),
    _method(method) {
    }

    NObserver(const NObserver& observer) :
    Poco::AbstractObserver(observer),
    _pObject(observer._pObject),
    _method(observer._method) {
    }

    ~NObserver() {
    }

    NObserver& operator =(const NObserver& observer) {
        if (&observer != this) {
            _pObject = observer._pObject;
            _method = observer._method;
        }
        return *this;
    }

    void notify(Poco::Notification* pNf) const {
        C* pObject = _pObject;

        if (pObject) {
            N* pCastNf = dynamic_cast<N*> (pNf);
            if (pCastNf) {
                this->_mutex.lock();
                NotificationPtr ptr(pCastNf, true);
                this->_mutex.unlock();
                (pObject->*_method)(ptr);
            }
        }
    }

    bool equals(const Poco::AbstractObserver& abstractObserver) const {
        const NObserver* pObs = dynamic_cast<const NObserver*> (&abstractObserver);
        return pObs && pObs->_pObject == _pObject && pObs->_method == _method;
    }

    bool accepts(Poco::Notification* pNf) const {
        return dynamic_cast<N*> (pNf) != 0;
    }

    Poco::AbstractObserver* clone() const {
        return new NObserver(*this);
    }

    void disable() {

        _pObject = 0;
    }

private:
    NObserver();

    C* _pObject;
    Callback _method;
    mutable Poco::Mutex _mutex;
};

}

class NQueueCenterWorker : public Poco::Runnable {
public:
    typedef Poco::SharedPtr<NQueueCenterWorker> Ptr;
    NQueueCenterWorker(Poco::NotificationCenter& aNc, Poco::NotificationQueue& aNQ);
    virtual ~NQueueCenterWorker();
    void Start();
    void Stop(); // this can make other workers with the same NotificationQueue stop.

    void Pause() {
        m_pause = true;
    }

    void Resume() {
        m_pause = false;
    }

    virtual void run();
private:
    Poco::NotificationCenter& m_NotificationCenter;
    Poco::NotificationQueue& m_NotificationQueue;
    Poco::Thread m_thread;
    bool m_pause;
private:

};

class NQueueCenterWorkers {
public:
    NQueueCenterWorkers(Poco::NotificationCenter& aNc, Poco::NotificationQueue& aNQ, int aWorkerCount = 5);

    virtual ~NQueueCenterWorkers() {
    }
    void startWorkers();
    void stopWorkers();

    void startWorkers(int aCount) {
        m_countWorkers = aCount;
        stopWorkers();
        startWorkers();
    }
	
	inline Poco::NotificationCenter& getCenter() {
		return m_NotificationCenter;
	}
	
	inline Poco::NotificationQueue& getQueue() {
		return m_NotificationQueue;
	}

private:
    int m_countWorkers;
    Poco::NotificationCenter& m_NotificationCenter;
    Poco::NotificationQueue& m_NotificationQueue;
    std::vector<NQueueCenterWorker::Ptr> m_workers;

};

#endif	/* _NQUEUECENTERWORKER_H */

