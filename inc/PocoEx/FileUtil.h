/* 
 * File:   FileUtil.h
 * Author: trungthanh
 *
 * Created on November 7, 2010, 12:11 AM
 */

#ifndef _FILEUTIL_H
#define	_FILEUTIL_H
#include <Poco/File.h>
#include <Poco/Path.h>
#include <string>
#include <set>
class FileUtil{
public:
    // Copied from NamNQ's CommitlogReader
	static std::string FindNewestSubDir(const std::string &dir) {
		try {
			Poco::Path p;
			p.parseDirectory(dir);
			Poco::File d(p.toString());
			std::vector<Poco::File> listSubFiles;
			d.list(listSubFiles);
			std::set<std::string> listSubDir;
			for (std::vector<Poco::File>::iterator it = listSubFiles.begin()
					; it != listSubFiles.end()
					; ++it) {
				if ((*it).isDirectory()) {
					listSubDir.insert((*it).path());
					std::cout << (*it).path() << std::endl;
				}
			}

			if (listSubDir.empty()) {
				return "";
			}

			return *(--listSubDir.end());
		} catch (const std::exception &ex) {
			std::cerr << "CommitLogReaderMan::FindNewestSubDir: An error occurred: " << ex.what() << std::endl;
			return "";
		} catch (...) {
			std::cerr << "CommitLogReaderMan::FindNewestSubDir: Unknown error occurred" << std::endl;
			return "";
		}
	}


        static void findFiles(const std::string& dir, const std::string& preFileName
            ,const std::string& sufFileName
            ,long long unsigned int timestamp
            ,std::set<std::string>& outFileNames

        )
        {
		Poco::File d(dir);
		std::vector<std::string> vecNameFiles;
		d.list(vecNameFiles);
		int preLen = preFileName.length();
		int sufLen = sufFileName.length();

		std::string timestampStr;
		char buf[32];
		sprintf(buf, "%llu", timestamp);
		timestampStr = buf;

		std::string preName, sufName, midName;
		for (std::vector<std::string>::iterator it = vecNameFiles.begin()
				; it != vecNameFiles.end()
				; ++it) {
			preName = it->substr(0, preLen);
			sufName = it->substr((it->length() > sufLen) ? (it->length() - sufLen) : 0);
			midName = it->substr(preName.length(), it->length() - sufName.length() - preName.length());

			if (preName == preFileName
                                && sufName == sufFileName
                                && midName >= timestampStr)
                        {
                            Poco::File f(dir + "/" + *it);
                            outFileNames.insert(*it);
//                            std::cout << "FileUtil::findFiles: match: " << it->c_str() << std::endl;
			}
		}

        }
};


#endif	/* _FILEUTIL_H */

