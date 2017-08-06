
#if defined(__sun)
#undef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif


#include "PocoEx/SharedMemoryEx.h"
#include <Poco/RefCountedObject.h>
#include <Poco/Exception.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

class OSSharedMemoryImpl : public Poco::RefCountedObject
/// Shared memory implementation for POSIX platforms.
{
public:
	OSSharedMemoryImpl(const std::string& name, std::size_t size, SharedMemoryEx::AccessMode mode, const void* addrHint, bool server);
	/// Creates or connects to a shared memory object with the given name.
	///
	/// For maximum portability, name should be a valid Unix filename and not
	/// contain any slashes or backslashes.
	///
	/// An address hint can be passed to the system, specifying the desired
	/// start address of the shared memory area. Whether the hint
	/// is actually honored is, however, up to the system. Windows platform
	/// will generally ignore the hint.
	///
	/// If server is set to false, the shared memory region will be unlinked
	/// by calling shm_unlink when the UPSharedMemory object is destroyed.

	OSSharedMemoryImpl(const Poco::File& file, SharedMemoryEx::AccessMode mode, const void* addrHint);
	/// Maps the entire contents of file into a shared memory segment.
	///
	/// An address hint can be passed to the system, specifying the desired
	/// start address of the shared memory area. Whether the hint
	/// is actually honored is, however, up to the system. Windows platform
	/// will generally ignore the hint.

	char* begin() const;
	/// Returns the start address of the shared memory segment.

	char* end() const;
	/// Returns the one-past-end end address of the shared memory segment. 

	void setAutoUnlink(bool autoUnlink);
	///unlink mapped file on closing

protected:
	void map(const void* addrHint);
	/// Maps the shared memory object.

	void unmap();
	/// Unmaps the shared memory object.

	void close();
	/// Releases the handle for the shared memory segment.

	~OSSharedMemoryImpl();
	/// Destroys the UPSharedMemoryImpl.

private:
	OSSharedMemoryImpl();
	OSSharedMemoryImpl(const OSSharedMemoryImpl&);
	OSSharedMemoryImpl& operator =(const OSSharedMemoryImpl&);

	std::size_t _size;
	int _fd;
	char* _address;
	SharedMemoryEx::AccessMode _access;
	std::string _name;
	bool _fileMapped;
	bool _server;
	bool _autoUnlink;
};

inline char* OSSharedMemoryImpl::begin() const {
	return _address;
}

inline char* OSSharedMemoryImpl::end() const {
	return _address + _size;
}

inline void OSSharedMemoryImpl::setAutoUnlink(bool autoUnlink) {
	_autoUnlink = autoUnlink;
}

OSSharedMemoryImpl::OSSharedMemoryImpl(const std::string& name, std::size_t size, SharedMemoryEx::AccessMode mode, const void* addrHint, bool server) :
_size(size),
_fd(-1),
_address(0),
_access(mode),
_name("/"),
_fileMapped(false),
_server(server),
_autoUnlink(true) {
	_name.append(name);

	int flags = _server ? O_CREAT : 0;
	if (_access == SharedMemoryEx::AM_WRITE)
		flags |= O_RDWR;
	else
		flags |= O_RDONLY;

	// open the shared memory segment
	_fd = ::shm_open(_name.c_str(), flags, S_IRUSR | S_IWUSR);
	if (_fd == -1)
		throw Poco::SystemException("Cannot create shared memory object", _name);

	// now set the correct size for the segment
	if (_server && -1 == ::ftruncate(_fd, size)) {
		::close(_fd);
		_fd = -1;
		::shm_unlink(_name.c_str());
		throw Poco::SystemException("Cannot resize shared memory object", _name);
	}
	map(addrHint);
}

OSSharedMemoryImpl::OSSharedMemoryImpl(const Poco::File& file, SharedMemoryEx::AccessMode mode, const void* addrHint) :
_size(0),
_fd(-1),
_address(0),
_access(mode),
_name(file.path()),
_fileMapped(true),
_server(false),
_autoUnlink(true) {
	if (!file.exists() || !file.isFile())
		throw Poco::FileNotFoundException(file.path());

	_size = file.getSize();
	int flag = O_RDONLY;
	if (mode == SharedMemoryEx::AM_WRITE)
		flag = O_RDWR;
	_fd = ::open(_name.c_str(), flag);
	if (-1 == _fd)
		throw Poco::OpenFileException("Cannot open memory mapped file", _name);

	map(addrHint);
}

OSSharedMemoryImpl::~OSSharedMemoryImpl() {
	unmap();
	close();
}

void OSSharedMemoryImpl::map(const void* addrHint) {
	int access = PROT_READ;
	if (_access == SharedMemoryEx::AM_WRITE)
		access |= PROT_WRITE;

	void* addr = ::mmap(const_cast<void*> (addrHint), _size, access, MAP_SHARED, _fd, 0);
	if (addr == MAP_FAILED)
		throw Poco::SystemException("Cannot map file into shared memory", _name);

	_address = static_cast<char*> (addr);
}

void OSSharedMemoryImpl::unmap() {
	if (_address) {
		::munmap(_address, _size);
	}
}

void OSSharedMemoryImpl::close() {
	if (_fd != -1) {
		::close(_fd);
		_fd = -1;
	}
	if (!_fileMapped && _server && _autoUnlink) {
		::shm_unlink(_name.c_str());
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// UPSharedMemory implementation

SharedMemoryEx::SharedMemoryEx() :
_pImpl(0) {
}

SharedMemoryEx::SharedMemoryEx(const std::string& name, std::size_t size, AccessMode mode, const void* addrHint, bool server) :
_pImpl(new OSSharedMemoryImpl(name, size, mode, addrHint, server)) {
}

SharedMemoryEx::SharedMemoryEx(const Poco::File& file, AccessMode mode, const void* addrHint) :
_pImpl(new OSSharedMemoryImpl(file, mode, addrHint)) {
}

SharedMemoryEx::SharedMemoryEx(const SharedMemoryEx& other) :
_pImpl(other._pImpl) {
	if (_pImpl)
		_pImpl->duplicate();
}

SharedMemoryEx::~SharedMemoryEx() {
	if (_pImpl)
		_pImpl->release();
}

SharedMemoryEx& SharedMemoryEx::operator =(const SharedMemoryEx& other) {
	SharedMemoryEx tmp(other);
	swap(tmp);
	return *this;
}

char* SharedMemoryEx::begin() const {
	if (_pImpl)
		return _pImpl->begin();
	else
		return 0;
}

char* SharedMemoryEx::end() const {
	if (_pImpl)
		return _pImpl->end();
	else
		return 0;
}

void SharedMemoryEx::setAutoUnlink(bool autoUnlink) {
	if (_pImpl)
		_pImpl->setAutoUnlink(autoUnlink);
}

