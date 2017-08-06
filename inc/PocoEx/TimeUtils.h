#ifndef TIMEUTIL_H
#define	TIMEUTIL_H

#include <Poco/DateTime.h>
#include <Poco/Timezone.h>

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

class TimeUtils {
public:
        static int getCurrentSeconds() {
            Poco::LocalDateTime now;

            return now.hour()*60*60 + now.minute() * 60 + now.second();
        }
    
	static std::pair<int, int> HHMMFromString(const std::string&str) {
		std::string::size_type pos = str.find(':');
		if (pos != std::string::npos) {
			std::string str1 = str.substr(0, pos); //hour
			std::string str2 = str.substr(1 + pos); //minute
			return std::pair<int, int>(atoi(str1.c_str()), atoi(str2.c_str()));
		}
		return std::pair<int, int>(0, 0);
	}

	static Poco::DateTime LocalNowDttm() {
		Poco::DateTime now;
		MoveTimeZone(now, LocalTimezone());
		return now;
	}

	static Poco::Timestamp LocalNowTm() {
		Poco::Timestamp now;
		MoveTimeZone(now, LocalTimezone());
		return now;
	}

	static int LocalTimezone() {
		return Poco::Timezone::utcOffset() / 3600;
	}

	static int UtcOffset(int tz)
	///return seconds from the tz to UTC
	{
		return 3600 * tz;
	}

	static void MoveTimeZone(Poco::DateTime & dttm, int tz) {
		if (tz > 0) {
			dttm.makeLocal(UtcOffset(tz));
		} else if (tz < 0) {
			dttm.makeUTC(UtcOffset(tz));
		}
	}

	static void MoveTimeZone(Poco::Timestamp & tm, int tz) {
		tm += 1000000LL * UtcOffset(tz);
	}

	static void print(std::string &_result, const Poco::DateTime & dttm) {
		char buf[100];
		sprintf(buf, "%.4d-%.2d-%.2d %.2d:%.2d:%.2d %.3d:%.3d"
				, dttm.year()
				, dttm.month()
				, dttm.day()
				, dttm.hour()
				, dttm.minute()
				, dttm.second()
				, dttm.millisecond()
				, dttm.microsecond()
				);
		_result = buf;
	}

	static void print(std::ostream &os, const Poco::DateTime & dttm) {
		std::string message;
		print(message, dttm);
		os << message << std::endl;
	}

	static void print(std::string &_result, const Poco::Timestamp &tm) {
		Poco::DateTime dttm(tm);
		print(_result, dttm);
	}

	static void print(std::ostream &os, const Poco::Timestamp &tm) {
		Poco::DateTime dttm(tm);
		print(os, dttm);
	}

	static void print(std::string &_result, const Poco::Timespan & ts) {
		char buf[100];
		sprintf(buf, "0000-00-%.2d %.2d:%.2d:%.2d %.3d:%.3d"
				, ts.days()
				, ts.hours()
				, ts.minutes()
				, ts.seconds()
				, ts.milliseconds()
				, ts.microseconds()
				);
		_result = buf;
	}

	static void print(std::ostream &os, const Poco::Timespan & ts) {
		std::string message;
		print(message, ts);
		os << message << std::endl;
	}

	static void printNow(std::string &_result) {
		print(_result, LocalNowTm());
	}

        static std::string Time2String(const Poco::Timestamp &timestamp) {
                Poco::DateTime dttm(timestamp);
                char buf[32];
                sprintf(buf, "%.4d%.2d%.2d_%.2d%.2d%.2d_%.3d%.3d"
                                , dttm.year()
                                , dttm.month()
                                , dttm.day()
                                , dttm.hour()
                                , dttm.minute()
                                , dttm.second()
                                , dttm.millisecond()
                                , dttm.microsecond()
                                );
                return std::string(buf);
        }
};

#endif	/* TIMEUTIL_H */

