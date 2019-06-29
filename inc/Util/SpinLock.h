/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SpinLock.h
 * Author: trungthanh
 *
 * Created on June 30, 2016, 1:58 PM
 */

#ifndef Util_SPINLOCK_H
#define Util_SPINLOCK_H

#include "boost/atomic.hpp"
#include <boost/smart_ptr/detail/spinlock.hpp>

namespace Util {

    class SpinLock {
    private:

        typedef enum {
            Locked, Unlocked
        } LockState;
        boost::atomic<LockState> state_;

    public:

        SpinLock() : state_(Unlocked) {
        }

        void lock() {
            unsigned k = 0;
            while (state_.exchange(Locked, boost::memory_order_acquire) == Locked) {
                /* wait */
                boost::detail::yield(k);
                k++;
            }
        }

        void unlock() {
            state_.store(Unlocked, boost::memory_order_release);
        }
    public:

        class ScopedLock
        /// A class that simplifies thread synchronization
        /// with a mutex.
        /// The constructor accepts a Mutex (and optionally
        /// a timeout value in milliseconds) and locks it.
        /// The destructor unlocks the mutex.
        {
        public:

            explicit ScopedLock(SpinLock& mutex) : _mutex(mutex) {
                _mutex.lock();
            }


            ~ScopedLock() {
                _mutex.unlock();
            }

        private:
            SpinLock& _mutex;

            ScopedLock();
            ScopedLock(const ScopedLock&);
            ScopedLock& operator=(const ScopedLock&);
        };
    };
}
#endif /* SPINLOCK_H */

