#include <errno.h>

#include "s21_string.h"

#define ERRSTR(v, s)                   \
    do {                               \
        if (errnum == (v)) return (s); \
    } while (0)

#ifdef __linux__
#define UNKNOWN_PREFIX "Unknown error "
#else
#define UNKNOWN_PREFIX "Unknown error: "
#endif  // __linux__

#define UNKNOW_MESSAGE_MAX_SIZE 1000

static void write_unknown_error_in_buffer(int errnum, char *buffer);

char *s21_strerror(int errnum) {
    // Error desriptions may be differerent based on OS.

    static char unknown_message_buffer[UNKNOW_MESSAGE_MAX_SIZE] = "";

#ifdef __linux__
    ERRSTR(0, "Success");
    ERRSTR(E2BIG, "Argument list too long");
    ERRSTR(EACCES, "Permission denied");
    ERRSTR(EADDRINUSE, "Address already in use");
    ERRSTR(EADDRNOTAVAIL, "Cannot assign requested address");
    ERRSTR(EAFNOSUPPORT, "Address family not supported by protocol");
    ERRSTR(EAGAIN, "Resource temporarily unavailable");
    ERRSTR(EALREADY, "Operation already in progress");
    ERRSTR(EBADF, "Bad file descriptor");
    ERRSTR(EBADMSG, "Bad message");
    ERRSTR(EBUSY, "Device or resource busy");
    ERRSTR(ECANCELED, "Operation canceled");
    ERRSTR(ECHILD, "No child processes");
    ERRSTR(ECONNABORTED, "Software caused connection abort");
    ERRSTR(ECONNREFUSED, "Connection refused");
    ERRSTR(ECONNRESET, "Connection reset by peer");
    ERRSTR(EDEADLK, "Resource deadlock avoided");
    ERRSTR(EDESTADDRREQ, "Destination address required");
    ERRSTR(EDOM, "Numerical argument out of domain");
    ERRSTR(EDQUOT, "Disk quota exceeded");
    ERRSTR(EEXIST, "File exists");
    ERRSTR(EFAULT, "Bad address");
    ERRSTR(EFBIG, "File too large");
    ERRSTR(EHOSTDOWN, "Host is down");
    ERRSTR(EHOSTUNREACH, "No route to host");
    ERRSTR(EIDRM, "Identifier removed");
    ERRSTR(EILSEQ, "Invalid or incomplete multibyte or wide character");
    ERRSTR(EINPROGRESS, "Operation now in progress");
    ERRSTR(EINTR, "Interrupted system call");
    ERRSTR(EINVAL, "Invalid argument");
    ERRSTR(EIO, "Input/output error");
    ERRSTR(EISCONN, "Transport endpoint is already connected");
    ERRSTR(EISDIR, "Is a directory");
    ERRSTR(ELOOP, "Too many levels of symbolic links");
    ERRSTR(EMFILE, "Too many open files");
    ERRSTR(EMLINK, "Too many links");
    ERRSTR(EMSGSIZE, "Message too long");
    ERRSTR(EMULTIHOP, "Multihop attempted");
    ERRSTR(ENAMETOOLONG, "File name too long");
    ERRSTR(ENETDOWN, "Network is down");
    ERRSTR(ENETRESET, "Network dropped connection on reset");
    ERRSTR(ENETUNREACH, "Network is unreachable");
    ERRSTR(ENFILE, "Too many open files in system");
    ERRSTR(ENOBUFS, "No buffer space available");
    ERRSTR(ENODATA, "No data available");
    ERRSTR(ENODEV, "No such device");
    ERRSTR(ENOENT, "No such file or directory");
    ERRSTR(ENOEXEC, "Exec format error");
    ERRSTR(ENOLCK, "No locks available");
    ERRSTR(ENOLINK, "Link has been severed");
    ERRSTR(ENOMEM, "Cannot allocate memory");
    ERRSTR(ENOMSG, "No message of desired type");
    ERRSTR(ENOPROTOOPT, "Protocol not available");
    ERRSTR(ENOSPC, "No space left on device");
    ERRSTR(ENOSR, "Out of streams resources");
    ERRSTR(ENOSTR, "Device not a stream");
    ERRSTR(ENOSYS, "Function not implemented");
    ERRSTR(ENOTBLK, "Block device required");
    ERRSTR(ENOTCONN, "Transport endpoint is not connected");
    ERRSTR(ENOTDIR, "Not a directory");
    ERRSTR(ENOTEMPTY, "Directory not empty");
    ERRSTR(ENOTRECOVERABLE, "State not recoverable");
    ERRSTR(ENOTSOCK, "Socket operation on non-socket");
    ERRSTR(ENOTSUP, "Operation not supported");
    ERRSTR(ENOTTY, "Inappropriate ioctl for device");
    ERRSTR(ENXIO, "No such device or address");
    ERRSTR(EOPNOTSUPP, "Operation not supported");
    ERRSTR(EOVERFLOW, "Value too large for defined data type");
    ERRSTR(EOWNERDEAD, "Owner died");
    ERRSTR(EPERM, "Operation not permitted");
    ERRSTR(EPFNOSUPPORT, "Protocol family not supported");
    ERRSTR(EPIPE, "Broken pipe");
    ERRSTR(EPROTO, "Protocol error");
    ERRSTR(EPROTONOSUPPORT, "Protocol not supported");
    ERRSTR(EPROTOTYPE, "Protocol wrong type for socket");
    ERRSTR(ERANGE, "Numerical result out of range");
    ERRSTR(EREMOTE, "Object is remote");
    ERRSTR(EROFS, "Read-only file system");
    ERRSTR(ESHUTDOWN, "Cannot send after transport endpoint shutdown");
    ERRSTR(ESOCKTNOSUPPORT, "Socket type not supported");
    ERRSTR(ESPIPE, "Illegal seek");
    ERRSTR(ESRCH, "No such process");
    ERRSTR(ESTALE, "Stale file handle");
    ERRSTR(ETIME, "Timer expired");
    ERRSTR(ETIMEDOUT, "Connection timed out");
    ERRSTR(ETOOMANYREFS, "Too many references: cannot splice");
    ERRSTR(ETXTBSY, "Text file busy");
    ERRSTR(EUSERS, "Too many users");
    ERRSTR(EWOULDBLOCK, "Resource temporarily unavailable");
    ERRSTR(EXDEV, "Invalid cross-device link");
#else   // Error definition for not linux systems. For macOS for example.
    ERRSTR(0, "Undefined error: 0");
    ERRSTR(E2BIG, "Argument list too long");
    ERRSTR(EACCES, "Permission denied");
    ERRSTR(EADDRINUSE, "Address already in use");
    ERRSTR(EADDRNOTAVAIL, "Can't assign requested address");
    ERRSTR(EAFNOSUPPORT, "Address family not supported by protocol family");
    ERRSTR(EAGAIN, "Resource temporarily unavailable");
    ERRSTR(EALREADY, "Operation already in progress");
    ERRSTR(EAUTH, "Authentication error");
    ERRSTR(EBADARCH, "Bad CPU type in executable");
    ERRSTR(EBADEXEC, "Bad executable (or shared library)");
    ERRSTR(EBADF, "Bad file descriptor");
    ERRSTR(EBADMACHO, "Malformed Mach-o file");
    ERRSTR(EBADMSG, "Bad message");
    ERRSTR(EBADRPC, "RPC struct is bad");
    ERRSTR(EBUSY, "Resource busy");
    ERRSTR(ECANCELED, "Operation canceled");
    ERRSTR(ECHILD, "No child processes");
    ERRSTR(ECONNABORTED, "Software caused connection abort");
    ERRSTR(ECONNREFUSED, "Connection refused");
    ERRSTR(ECONNRESET, "Connection reset by peer");
    ERRSTR(EDEADLK, "Resource deadlock avoided");
    ERRSTR(EDESTADDRREQ, "Destination address required");
    ERRSTR(EDEVERR, "Device error");
    ERRSTR(EDOM, "Numerical argument out of domain");
    ERRSTR(EDQUOT, "Disc quota exceeded");
    ERRSTR(EEXIST, "File exists");
    ERRSTR(EFAULT, "Bad address");
    ERRSTR(EFBIG, "File too large");
    ERRSTR(EFTYPE, "Inappropriate file type or format");
    ERRSTR(EHOSTDOWN, "Host is down");
    ERRSTR(EHOSTUNREACH, "No route to host");
    ERRSTR(EIDRM, "Identifier removed");
    ERRSTR(EILSEQ, "Illegal byte sequence");
    ERRSTR(EINPROGRESS, "Operation now in progress");
    ERRSTR(EINTR, "Interrupted system call");
    ERRSTR(EINVAL, "Invalid argument");
    ERRSTR(EIO, "Input/output error");
    ERRSTR(EISCONN, "Socket is already connected");
    ERRSTR(EISDIR, "Is a directory");
    ERRSTR(ELOOP, "Too many levels of symbolic links");
    ERRSTR(EMFILE, "Too many open files");
    ERRSTR(EMLINK, "Too many links");
    ERRSTR(EMSGSIZE, "Message too long");
    ERRSTR(EMULTIHOP, "EMULTIHOP (Reserved)");
    ERRSTR(ENAMETOOLONG, "File name too long");
    ERRSTR(ENEEDAUTH, "Need authenticator");
    ERRSTR(ENETDOWN, "Network is down");
    ERRSTR(ENETRESET, "Network dropped connection on reset");
    ERRSTR(ENETUNREACH, "Network is unreachable");
    ERRSTR(ENFILE, "Too many open files in system");
    ERRSTR(ENOATTR, "Attribute not found");
    ERRSTR(ENOBUFS, "No buffer space available");
    ERRSTR(ENODATA, "No message available on STREAM");
    ERRSTR(ENODEV, "Operation not supported by device");
    ERRSTR(ENOENT, "No such file or directory");
    ERRSTR(ENOEXEC, "Exec format error");
    ERRSTR(ENOLCK, "No locks available");
    ERRSTR(ENOLINK, "ENOLINK (Reserved)");
    ERRSTR(ENOMEM, "Cannot allocate memory");
    ERRSTR(ENOMSG, "No message of desired type");
    ERRSTR(ENOPOLICY, "Policy not found");
    ERRSTR(ENOPROTOOPT, "Protocol not available");
    ERRSTR(ENOSPC, "No space left on device");
    ERRSTR(ENOSR, "No STREAM resources");
    ERRSTR(ENOSTR, "Not a STREAM");
    ERRSTR(ENOSYS, "Function not implemented");
    ERRSTR(ENOTBLK, "Block device required");
    ERRSTR(ENOTCONN, "Socket is not connected");
    ERRSTR(ENOTDIR, "Not a directory");
    ERRSTR(ENOTEMPTY, "Directory not empty");
    ERRSTR(ENOTRECOVERABLE, "State not recoverable");
    ERRSTR(ENOTSOCK, "Socket operation on non-socket");
    ERRSTR(ENOTSUP, "Operation not supported");
    ERRSTR(ENOTTY, "Inappropriate ioctl for device");
    ERRSTR(ENXIO, "Device not configured");
    ERRSTR(EOPNOTSUPP, "Operation not supported on socket");
    ERRSTR(EOVERFLOW, "Value too large to be stored in data type");
    ERRSTR(EOWNERDEAD, "Previous owner died");
    ERRSTR(EPERM, "Operation not permitted");
    ERRSTR(EPFNOSUPPORT, "Protocol family not supported");
    ERRSTR(EPIPE, "Broken pipe");
    ERRSTR(EPROCLIM, "Too many processes");
    ERRSTR(EPROCUNAVAIL, "Bad procedure for program");
    ERRSTR(EPROGUNAVAIL, "RPC prog. not avail");
    ERRSTR(EPROGMISMATCH, "Program version wrong");
    ERRSTR(EPROTO, "Protocol error");
    ERRSTR(EPROTONOSUPPORT, "Protocol not supported");
    ERRSTR(EPROTOTYPE, "Protocol wrong type for socket");
    ERRSTR(EPWROFF, "Device power is off");
    ERRSTR(EQFULL, "Interface output queue is full");
    ERRSTR(ERANGE, "Result too large");
    ERRSTR(EREMOTE, "Too many levels of remote in path");
    ERRSTR(EROFS, "Read-only file system");
    ERRSTR(ERPCMISMATCH, "RPC version wrong");
    ERRSTR(ESHLIBVERS, "Shared library version mismatch");
    ERRSTR(ESHUTDOWN, "Can't send after socket shutdown");
    ERRSTR(ESOCKTNOSUPPORT, "Socket type not supported");
    ERRSTR(ESPIPE, "Illegal seek");
    ERRSTR(ESRCH, "No such process");
    ERRSTR(ESTALE, "Stale NFS file handle");
    ERRSTR(ETIME, "STREAM ioctl timeout");
    ERRSTR(ETIMEDOUT, "Operation timed out");
    ERRSTR(ETOOMANYREFS, "Too many references: can't splice");
    ERRSTR(ETXTBSY, "Text file busy");
    ERRSTR(EUSERS, "Too many users");
    ERRSTR(EWOULDBLOCK, "Resource temporarily unavailable");
    ERRSTR(EXDEV, "Cross-device link");
#endif  // defined(__APPLE__) && defined(__MACH__)

    write_unknown_error_in_buffer(errnum, unknown_message_buffer);
    return (char *)unknown_message_buffer;
}

static void write_unknown_error_in_buffer(int errnum, char *buffer) {
    int prefix_len;

    s21_memset(buffer, '\0', sizeof(char) * UNKNOW_MESSAGE_MAX_SIZE);

    prefix_len = s21_strlen(UNKNOWN_PREFIX);

    s21_strcat(buffer, UNKNOWN_PREFIX);
    s21_itoa(buffer + prefix_len, errnum, 10);
}
