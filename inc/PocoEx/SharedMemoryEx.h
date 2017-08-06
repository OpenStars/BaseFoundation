
#ifndef UPSharedMEMORY_H
#define UPSharedMEMORY_H


#include <Poco/File.h>
#include <algorithm>
#include <cstddef>


class OSSharedMemoryImpl;

class SharedMemoryEx
/// Create and manage a shared memory object.
///
/// A UPSharedMemory object has value semantics, but
/// is implemented using a handle/implementation idiom.
/// Therefore, multiple UPSharedMemory objects can share
/// a single, reference counted UPSharedMemoryImpl object.
{
public:

	enum AccessMode {
		AM_READ = 0,
		AM_WRITE
	};

	SharedMemoryEx();
	/// Default constructor creates an unmapped UPSharedMemory object. 
	/// No clients can connect to an unmapped UPSharedMemory object.

	SharedMemoryEx(const std::string& name, std::size_t size, AccessMode mode, const void* addrHint = 0, bool server = true);
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
	/// If server is set to true, the shared memory region will be unlinked
	/// by calling shm_unlink() (on POSIX platforms) when the UPSharedMemory object is destroyed.
	/// The server parameter is ignored on Windows platforms.

	SharedMemoryEx(const Poco::File& file, AccessMode mode, const void* addrHint = 0);
	/// Maps the entire contents of file into a shared memory segment.
	///
	/// An address hint can be passed to the system, specifying the desired
	/// start address of the shared memory area. Whether the hint
	/// is actually honored is, however, up to the system. Windows platform
	/// will generally ignore the hint.

	SharedMemoryEx(const SharedMemoryEx& other);
	/// Creates a UPSharedMemory object by copying another one.

	~SharedMemoryEx();
	/// Destroys the UPSharedMemory.

	SharedMemoryEx& operator =(const SharedMemoryEx& other);
	/// Assigns another UPSharedMemory object.

	void swap(SharedMemoryEx& other);
	/// Swaps the UPSharedMemory object with another one.

	char* begin() const;
	/// Returns the start address of the shared memory segment.
	/// Will be NULL for illegal segments.

	char* end() const;
	/// Returns the one-past-end end address of the shared memory segment. 
	/// Will be NULL for illegal segments.

	void setAutoUnlink(bool autoUnlink);
	///unlink mapped file on closing

private:
	OSSharedMemoryImpl* _pImpl;
};


//
// inlines
//

inline void SharedMemoryEx::swap(SharedMemoryEx& other) {
	using std::swap;
	swap(_pImpl, other._pImpl);
}


#endif // UPSharedMEMORY_H
