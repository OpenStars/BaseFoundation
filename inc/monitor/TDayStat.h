#ifndef TDAYSTAT_H
#define	TDAYSTAT_H

#include "boost/atomic.hpp"
#include <limits>
#include <vector>
#include "Poco/LocalDateTime.h"

#define TSECOND (60*60*24)

template<class itemType = boost::atomic_uint32_t, class ioType = uint32_t>
class TDayStat {
private:
    itemType _data[TSECOND];

public:
    ioType get(int pos) {
        if (pos < 0 || pos > TSECOND)
            return -1;

        return (ioType) _data[pos];
    }

    int set(int pos, ioType value) {
        if (pos < 0 || pos > TSECOND)
            return -1;

        _data[pos].store(value);
        return value;
    }

    int inc(int pos) {
        if (pos < 0 || pos > TSECOND)
            return -1;

        _data[pos]++;
        return 0;
    }

    int dec(int pos) {
        if (pos < 0 || pos > TSECOND)
            return -1;

        _data[pos]--;
        return 0;
    }

    int add(int pos, ioType value) {
        if (pos < 0 || pos > TSECOND)
            return -1;

        _data[pos] += value;
        return 0;
    }

    int sub(int pos, ioType value) {
        if (pos < 0 || pos > TSECOND)
            return -1;

        _data[pos] -= value;
        return 0;
    }

    ioType operator[] (int pos) {
        return get(pos);
    }

    void clear() {
        for (int i=0; i< TSECOND; i++) {
            _data[i].store(0);
        }
    }

    ioType maxDataFromDate(int from, int to) {
        /* validate */
        if (from < 0 || from > TSECOND) return -2;
        if (to < 0 || to > TSECOND) return -2;

        int current_mv = (int) std::numeric_limits<int>::max(); /* or MAX_INT */

        for (int i=from; i<=to; i++) {
            if (this->_data[i] > current_mv) {
                current_mv = this->_data[i];
            }
        }

        return current_mv;

    }

    int minDataFromDate(int from, int to) {
        /* validate */
        if (from < 0 || from > TSECOND) return -2;
        if (to < 0 || to > TSECOND) return -2;

        int current_mv = (int) std::numeric_limits<ioType>::max(); /* or MAX_INT */

        for (int i=from; i<=to; i++) {
            if (this->_data[i] < current_mv) {
                current_mv = this->_data[i];
            }
        }

        return current_mv;
    }

    int avgDataFromDate(int from, int to) {
        /* validate */
        if (from < 0 || from > TSECOND) return -2;
        if (to < 0 || to > TSECOND) return -2;

        int current_mv = (int) std::numeric_limits<int>::max(); /* or MAX_INT */

        for (int i=from; i<=to; i++) {
            if (this->_data[i] < current_mv) {
                current_mv = this->_data[i];
            }
        }

        return current_mv;
    }

    int getDataFromDate(int from, int to, std::vector<ioType> & rpsData) {
        if (to - from == 0) return -1;
        if (from < 0 || from > TSECOND) return -2;
        if (to < 0 || to > TSECOND) return -2;
        if (to - from > 3600) return -3;

        for (int i=from; i<=to; i++) {
            rpsData.push_back((ioType)this->_data[i]);
        }

        return (to-from);
    }

    static int getCurrentSecond() {
        Poco::LocalDateTime current;        

        return current.hour() * 60 * 60 + current.minute() * 60 + current.second();        
    }

};

#endif	/* TDAYSTAT_H */

