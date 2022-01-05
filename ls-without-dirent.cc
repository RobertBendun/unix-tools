#include <array>
#include <cassert>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <limits>

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/syscall.h>

char const* program_name;

// https://elixir.bootlin.com/linux/v5.15.12/source/include/linux/dirent.h
struct dirent64
{
	enum Type : unsigned char
	{
		Block_Device = 6,
		Character_Device = 2,
		Directory = 4,
		Named_Pipe = 1,
		Regular_File = 8,
		Symbolic_Link = 10,
		Unix_Socket = 12,
		Unknown = 0
	};

	ino64_t inode; // Inode number
	off64_t offset; // Offset to next node
	unsigned short length; // Length of this struct
	Type type;
	char name[];
	// After name may be some padding, so end of struct != end of string

	dirent64* next()
	{
		// This behaviour was observed by me, it's not defined in the manpage
		// Maybe it's defined somewhere in here: https://elixir.bootlin.com/linux/v5.15.12/source/fs/readdir.c#L311
		if (offset == std::numeric_limits<decltype(offset)>::max())
			return nullptr;
		return reinterpret_cast<dirent64*>((char*)this + length);
	}

	char const* pretty_type()
	{
		switch (type) {
		case Block_Device:      return "block";
		case Character_Device:  return "char";
		case Directory:         return "dir";
		case Named_Pipe:        return "fifo";
		case Regular_File:      return "file";
		case Symbolic_Link:     return "link";
		case Unix_Socket:       return "socket";
		default:
		case Unknown:           return "unknown";
		}
	}
};

// Reads into dirent64 dirs[count] entries inside directory at fd.
// Returns number of bytes read.
// This syscall is not defined as function, so we need custom wrap.
long getdents64(unsigned int fd, dirent64 *dirs, unsigned int count)
{
	return syscall(SYS_getdents64, fd, dirs, count);
}

int ensure(int retval, char const* function_name)
{
	if (retval < 0) {
		std::cerr << basename(program_name) << ": " << function_name << ": " << std::strerror(errno) << std::endl;
		std::exit(1);
	}
	return retval;
}

#define TRY(function, ...) (ensure(function(__VA_ARGS__), #function))

int main(int, char **argv)
{
	assert(*argv);
	program_name = *argv++;
	char const* target = *argv ? *argv : ".";

	auto fd = TRY(openat, AT_FDCWD, target, O_RDONLY|O_NONBLOCK|O_CLOEXEC|O_DIRECTORY);

	// Number based on observation of syscalls made by dirent.h
	std::array<dirent64, 32768> dirs;
	while (TRY(getdents64, fd, dirs.data(), dirs.size())) {
		for (auto p = dirs.data(); p; p = p->next()) {
			std::cout << p->inode << '\t' << p->pretty_type() << '\t' << p->name << '\n';
		}
	}
}
