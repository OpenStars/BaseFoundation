/* 
 * File:   NQueueCenterWorker.cpp
 * Author: trungthanh
 * 
 * Created on January 14, 2010, 3:26 PM
 */

#include <NQueueCenterWorker.h>

NQueueCenterWorker::NQueueCenterWorker(Poco::NotificationCenter& aNc, Poco::NotificationQueue& aNQ)
: m_NotificationCenter(aNc)
, m_NotificationQueue(aNQ)
, m_pause(false) {
}

NQueueCenterWorker::~NQueueCenterWorker() {
}

void NQueueCenterWorker::run() {
    Poco::Notification* aNf = m_NotificationQueue.waitDequeueNotification();
    while (aNf) {
        while (m_pause)
            Poco::Thread::sleep(10);
        m_NotificationCenter.postNotification(aNf);
        aNf = m_NotificationQueue.waitDequeueNotification();
    }
}

void NQueueCenterWorker::Start() {
    if (!m_thread.isRunning())
        m_thread.start(*this);
}

void NQueueCenterWorker::Stop() {

    while (!m_NotificationQueue.empty()) Poco::Thread::sleep(100);

    do {
        m_NotificationQueue.wakeUpAll();
    } while (!m_thread.tryJoin(100));
}
/////////////////

NQueueCenterWorkers::NQueueCenterWorkers(Poco::NotificationCenter& aNc, Poco::NotificationQueue& aNQ, int aWorkerCount)
: m_NotificationCenter(aNc)
, m_NotificationQueue(aNQ)
, m_countWorkers(aWorkerCount) {

}

void NQueueCenterWorkers::startWorkers() {
    for (int index = 0; index < m_countWorkers; index++) {
        NQueueCenterWorker::Ptr aWorker = new NQueueCenterWorker(m_NotificationCenter, m_NotificationQueue);
        aWorker->Start();
        m_workers.push_back(aWorker);
    }
}

void NQueueCenterWorkers::stopWorkers() {
    for (std::vector<NQueueCenterWorker::Ptr> ::iterator aIt = m_workers.begin(); aIt != m_workers.end(); aIt++) {
        (*aIt)->Stop();
    }
    m_workers.clear();
}
