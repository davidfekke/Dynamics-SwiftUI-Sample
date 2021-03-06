/*
 * (c) 2016 Good Technology Corporation. All rights reserved.
 */

#ifndef GD_C_FILESYSTEM_H
#define GD_C_FILESYSTEM_H

#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/stat.h>

/** \addtogroup capilist
 * @{
 */

/** C API file structure, for accessing secure storage.
 *
 */
typedef size_t GD_FILE;

/** C API directory structure, for accessing secure storage.
 *
 */
typedef size_t GD_DIR;

/** @}
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GD_C_API
#   if !defined(_WIN32)
#       define GD_C_API __attribute__((visibility("default")))
#   else
#       define GD_C_API
#   endif
#endif

#ifndef GD_C_API_EXT
#   define GD_C_API_EXT
#endif
    
#if defined(_WIN32)
#   define GD_ATTRIBUTE(ignore)
#else
#   define GD_ATTRIBUTE __attribute__
#endif

/** \addtogroup capilist
 * @{
 */

/** Open a file that is in the secure store, for reading or writing.
 * Call this function to open a file in the secure store for reading or writing.
 * Files in the secure store are encrypted on the device; this
 * function provides access to decrypted data.
 *
 * @param filename <tt>const char*</tt> pointer to a C string containing the
 *                 path, within the secure store, that represents the file to be
 *                 opened.
 *
 * @param mode <tt>const char*</tt> pointer to a C string of the mode. The
 *             values are analogous to the standard C call <tt>fopen</tt> and
 *             can be:
 *             - write <tt>"w"</tt>
 *             - read <tt>"r"</tt>
 *             - append <tt>"a"</tt>
 *             .
 *             Note that the "+" qualifier is supported for opening a file for
 *             both reading and writing.\n
 *             The "b" and "t" qualifiers aren't supported.
 *
 * @return <tt>GD_FILE*</tt> object pointer (analogous to the FILE* file pointer
 *                           returned from <tt>fopen</tt>) which can be used for
 *                           subsequent file access, or <tt>NULL</tt> if the
 *                           file could not be opened or created.
 */
GD_C_API GD_FILE* GD_fopen(const char* filename, const char* mode);

/** Close a file that was previously opened.
 * Call this function to close a file that was previously opened by a call to GD_fopen.
 *
 * @param filePointer <tt>GD_FILE*</tt> object which was returned by a previous call to <tt>GD_fopen</tt>.\n
 *
 * Note that this should always be called when file access is no longer required. It also forces a flush
 * of any uncommitted write operation.
 *
 * @return <tt>int</tt> 0 if successful, EOF otherwise
 *
 */
GD_C_API int GD_fclose(GD_FILE* filePointer);

/** Read from a file that is in the secure store, previously opened in read mode
 *  with <tt>GD_fopen</tt>.
 * Call this function to read a file in the secure store previously opened with
 * <tt>GD_open</tt> in a read mode such as "r" or "w+".
 *
 * @param ptr <tt>void*</tt> pointer to a buffer to receive the read data.
 *
 * @param size <tt>size_t</tt> size of the data block.
 *
 * @param count <tt>size_t</tt> number of data blocks.
 *
 * @param filePointer <tt>GD_FILE*</tt> a pointer to a valid GD_FILE* object.
 *
 * (Note that the underlying library simply reads size * count bytes from the
 * secure file system.)
 *
 * @return <tt>size_t</tt> The total number of elements successfully read is
 *                         returned. If this number differs from the count
 *                         parameter, either a reading error occurred or the
 *                         end-of-file was reached while reading. In both cases,
 *                         the proper indicator is set, which can be checked
 *                         with <tt>ferror</tt> and <tt>feof</tt>, respectively.
 *                         If either size or count is zero, the function returns
 *                         zero and both the stream state and the content
 *                         pointed by ptr remain unchanged.\n
 *                         <tt>size_t</tt> is an unsigned integral type.
 *
 */
GD_C_API size_t GD_fread(void* ptr, size_t size, size_t count, GD_FILE* filePointer);

/** Write to a file that is in the secure store, previously opened in write mode
 *  with <tt>GD_fopen</tt>.
 * Call this function to read a file in the secure store previously opened with
 * <tt>GD_open</tt> in a read mode such as "w" or "r+".
 *
 * @param ptr <tt>void*</tt> pointer to a buffer containing the data to be written
 *
 * @param size <tt>size_t</tt> size of the data block.
 *
 * @param count <tt>size_t</tt> number of data blocks
 *
 * @param filePointer <tt>GD_FILE*</tt> a pointer to a valid GD_FILE* object
 *
 * (Note that the underlying library simply writes size * count bytes to the
 * encrypted file system.)
 *
 * @return <tt>size_t</tt> The total number of elements successfully written is
 *                         returned. If this number differs from the count
 *                         parameter, a writing error prevented the function
 *                         from completing. In this case, the error indicator
 *                         (<tt>ferror</tt>) will be set for the stream. If
 *                         either size or count is zero, the function returns
 *                         zero and the error indicator remains unchanged.
 *                         <tt>size_t</tt> is an unsigned integral type.
 *
 */
GD_C_API size_t GD_fwrite(const void* ptr, size_t size, size_t count, GD_FILE* filePointer);

/** Delete a file.
 * Call this function to delete a file by path.
 *
 * @param filename <tt>const char*</tt> the path of the field to be deleted.
 *
 * @return <tt>int</tt> 0 if successful, -1 otherwise.
 */
GD_C_API int GD_remove(const char* filename);

/** Get the current position of the file pointer.
 * Call this function obtain the current file pointer position.
 *
 * @param filePointer <tt>GD_FILE*</tt> object which was returned by a previous call to <tt>GD_fopen</tt>.\n
 *
 * @return <tt>long int</tt> the position of the file pointer or -1 if an error has occurred.
 *
 */
GD_C_API long int GD_ftell(GD_FILE* filePointer);

/** Get the current position of the file pointer.
 * Call this function obtain the current file pointer position.
 *
 * @param filePointer <tt>GD_FILE*</tt> object which was returned by a previous call to <tt>GD_fopen</tt>.\n
 *
 * @return <tt>off_t</tt> the position of the file pointer or -1 if an error has occurred.
 *
*/
GD_C_API off_t GD_ftello(GD_FILE* filePointer);
    
/** Set the position of the file pointer.
 * Call this function to set the file pointer position.
 *
 * @param filePointer <tt>GD_FILE*</tt> object which was returned by a previous call to <tt>GD_fopen</tt>.\n
 *
 * @param offset <tt>long int</tt> offset relative to the origin parameter
 *
 * @param origin <tt>int</tt> one of SEEK_SET, SEEK_CUR, SEEK_END
 *
 * @return <tt>int</tt> 0 for success or -1 for failure
 *
 */
GD_C_API int GD_fseek(GD_FILE* filePointer, long int offset, int origin);
    
/** Set the position of the file pointer.
 * Call this function to set the file pointer position.
 *
 * @param filePointer <tt>GD_FILE*</tt> object which was returned by a previous call to <tt>GD_fopen</tt>.\n
 *
 * @param offset <tt>off_t</tt> offset relative to the origin parameter
 *
 * @param origin <tt>int</tt> one of SEEK_SET, SEEK_CUR, SEEK_END
 *
 * @return <tt>int</tt> 0 for success or -1 for failure
 *
 */
GD_C_API int GD_fseeko(GD_FILE* filePointer, off_t offset, int origin);
    
/** Read formatted data from stream.
 * Reads data from the stream and stores them according to the parameter format into the locations pointed by 
 * the additional arguments. The additional arguments should point to already allocated objects of the type specified 
 * by their corresponding format specifier (subsequences beginning with %) within the format string.
 *
 * @param filePointer Pointer to a <tt>GD_FILE</tt> object that identifies an input stream to read data from.
 *
 * @param format C string that contains a sequence of characters that control how characters extracted from the stream are treated.
 *
 * @return <tt>int</tt> On success, the function returns the number of items of the argument list successfully filled.
 * On error, the function returns EOF and sets the error indicator (ferror).
 */
GD_C_API int GD_fscanf(GD_FILE* filePointer, const char*  format, ...) GD_ATTRIBUTE((format(scanf,2,3)));

    
/** Read formatted data from stream into variable argument list.
 * Reads data from the stream and stores them according to parameter format into the locations pointed to by the elements
 * in the variable argument list identified by args.
 *
 * Internally, the function retrieves arguments from the list identified by arg as if va_arg was used on it, 
 * and thus the state of arg is likely to be altered by the call.
 *
 * In any case, arg should have been initialized by va_start at some point before the call, 
 * and it is expected to be released by va_end at some point after the call.
 *
 * @param filePointer Pointer to a <tt>GD_FILE</tt> object that identifies an input stream.
 *
 * @param format C string that contains a format string that follows the same specification as scanf (see scanf for details).
 *
 * @param args A value identifying a variable arguments list initialized with va_start. va_list is a special type defined in &lt;stdarg.h&gt; file.
 *
 * @return <tt>int</tt> On success, the function returns the number of items of the argument list successfully filled.
 * On error, the function returns EOF and sets the error indicator (ferror).
 */
GD_C_API int GD_vfscanf(GD_FILE* filePointer, const char * format, va_list args) GD_ATTRIBUTE((format(scanf,2,0)));
    
/** Test if the file pointer is at the end of the file.
 * Call this function to check if the file pointer is at the end of the file.
 *
 * @param filePointer <tt>GD_FILE*</tt> object which was returned by a previous call to <tt>GD_fopen</tt>.\n
 *
 * @return <tt>int</tt> non-zero if the end of file indicator is set, otherwise 0
 */
GD_C_API int GD_feof(GD_FILE* filePointer);

/** Generate a unique file name.
 * Call this function to check or generate a unique file name
 *
 * @param str <tt>char*</tt> an array of bytes of at least <tt>L_tmpnam</tt> length to contain the proposed file name. If
 * this argument is NULL then an internal static array is used.
 *
 * @return <tt>char*</tt> a pointer to a unique filename. If the <tt>str</tt> argument is not NULL then the pointer will refer to
 * this array otherwise it will point to an internal static array. If the function cannot create a unique filename then NULL is
 * returned.
 */
GD_C_API char* GD_tmpnam(char* str);

/** Truncate a file that is in the secure store.
 * Call this function to truncate a file in the secure store to a specified length.
 * If file was previously larger than the length specified, the file will be truncated and the
 * extra data lost. If the file was previously smaller than the length specified, the file will be
 * extended and padded with null bytes ('\0').
 *
 * @param filename <tt>const char*</tt> pointer to a C string containing the path, within the secure store, that
 * represents the file to be truncated.
 *
 * @param length <tt>off_t</tt> in bytes of the file once truncated.
 *
 * @return <tt>int</tt> 0 for success or -1 for failure
 */
GD_C_API int GD_truncate(const char* filename, off_t length);

/** Truncate a file that is in the secure store.
 * Call this function to truncate a file in the secure store to a specified length.
 * If file was previously larger than the length specified, the file will be truncated and the extra
 * data lost. If the file was previously smaller than the length specified, the file will be
 * extended and padded with null bytes ('\0').
 *
 * @param filePointer <tt>GD_FILE*</tt> object which was returned by a previous call to <tt>GD_fopen</tt>.\n
 *
 * @param length <tt>off_t</tt> in bytes of the file once truncated.
 *
 * @return <tt>int</tt> 0 for success or -1 for failure
 */
GD_C_API int GD_ftruncate(GD_FILE* filePointer, off_t length);

/** Reopen stream with different file or mode.
 * Reuses stream to either open the file specified by filename or to change its access mode.
 * If a new filename is specified, the function first attempts to close any file already associated with filePointer
 * (third parameter) and disassociates it.
 * Then, independently of whether that filePointer was successfuly closed or not, 
 * freopen opens the file specified by filename and associates it with the filePointer just as fopen would do using the specified mode.
 * If filename is a null pointer, the function attempts to change the mode of the filePointer. 
 * The error indicator and eof indicator are automatically cleared (as if clearerr was called).
 *
 * @param filename <tt>const char*</tt> C string containing the name of the file to be opened.
 *
 * @param mode <tt>const char*</tt> pointer to a C string of the mode. The
 *             values are analogous to the standard C call <tt>fopen</tt> and
 *             can be:
 *             - write <tt>"w"</tt>
 *             - read <tt>"r"</tt>
 *             - append <tt>"a"</tt>
 *             .
 *             Note that the "+" qualifier is supported for opening a file for
 *             both reading and writing.\n
 *             The "b" and "t" qualifiers aren't supported.
 *
 * @param filePointer <tt>GD_FILE*</tt> object which was returned by a previous
 *                    call to <tt>GD_fopen</tt>.\n
 *
 * @return <tt>GD_FILE*</tt> If the file is successfully reopened, the function
 *                           returns the pointer passed as parameter
 *                           filePointer, which can be used to identify the
 *                           reopened stream. Otherwise, a null pointer is
 *                           returned.
 */

GD_C_API GD_FILE* GD_freopen(const char* filename, const char* mode, GD_FILE* filePointer);

/** Get current position in stream.
 * Retrieves the current position in the stream. 
 * The function fills the fpost_t object pointed by pos with the information needed from the filePointer's position indicator 
 * to restore the stream to its current position (and multibyte state, if wide-oriented) with a call to fsetpos.
 * The ftell function can be used to retrieve the current position in the stream as an integer value.
 * 
 * @param filePointer <tt>GD_FILE*</tt> object which was returned by a previous call to <tt>GD_fopen</tt>.\n
 * 
 * @param pos <tt>fpos_t</tt> Pointer to a fpos_t object.
 *
 * @return <tt>int</tt> On success, the function returns zero.
 * In case of error, errno is set to a platform-specific positive value and the function returns a non-zero value.
 */
GD_C_API int GD_fgetpos(GD_FILE* filePointer, fpos_t* pos);
   
/** Set position indicator of stream.
 * Restores the current position in the stream to pos.
 * The internal file position indicator associated with stream is set to the position represented by pos, 
 * which is a pointer to an fpos_t object whose value shall have been previously obtained by a call to fgetpos.
 * The end-of-file internal indicator of the stream is cleared after a successful call to this function, 
 * and all effects from previous calls to ungetc on this stream are dropped.
 * On streams open for update (read+write), a call to fsetpos allows to switch between reading and writing.
 *
 * @param filePointer <tt>GD_FILE*</tt> object which was returned by a previous call to <tt>GD_fopen</tt>.\n
 *
 * @param pos <tt>fpos_t</tt> Pointer to a fpos_t object containing a position previously obtained with fgetpos.
 *
 * @return <tt>int</tt> On success, the function returns zero.
 * On failure, a non-zero value is returned and errno is set to a system-specific positive value.
 */
GD_C_API int GD_fsetpos(GD_FILE* filePointer, const fpos_t* pos);

/** Set position of stream to the beginning.
 * Sets the position indicator associated with stream to the beginning of the file.
 * The end-of-file and error internal indicators associated to the stream are cleared after a successful call to this function,
 * and all effects from previous calls to ungetc on this stream are dropped.
 *
 * @param filePointer <tt>GD_FILE*</tt> object which was returned by a previous call to <tt>GD_fopen</tt>.\n
 */
GD_C_API void GD_rewind(GD_FILE* filePointer);

/** Get character from stream.
 * Returns the character currently pointed by the internal file position indicator of the specified stream. 
 * The internal file position indicator is then advanced to the next character.
 * If the stream is at the end-of-file when called, the function returns EOF and sets the end-of-file indicator for the stream (feof). 
 * If a read error occurs, the function returns EOF and sets the error indicator for the stream (ferror).
 *
 * @param filePointer <tt>GD_FILE*</tt> object which was returned by a previous call to <tt>GD_fopen</tt>.\n
 * 
 * @return <tt>int</tt> On success, the character read is returned (promoted to an int value).
 * The return type is int to accommodate for the special value EOF, which indicates failure:
 * If the position indicator was at the end-of-file, the function returns EOF and sets the eof indicator (feof) of stream.
 * If some other reading error happens, the function also returns EOF, but sets its error indicator (ferror) instead.
 */
GD_C_API int GD_fgetc(GD_FILE* filePointer);
    
/** Get string from stream.
 * Reads characters from stream and stores them as a C string into str 
 * until (num-1) characters have been read or either a newline or the end-of-file is reached, whichever happens first.
 * A newline character makes fgets stop reading, but it is considered a valid character by the function and included in the string copied to str.
 * A terminating null character is automatically appended after the characters copied to str.
 *
 * @param buf <tt>char*</tt> Pointer to an array of chars where the string read is copied.
 *
 * @param count <tt>int</tt> Maximum number of characters to be copied into str (including the terminating null-character).
 *
 * @param filePointer <tt>GD_FILE*</tt> object which was returned by a previous call to <tt>GD_fopen</tt>.\n
 *
 * @return <tt>char*</tt> On success, the function returns str.
 * If the end-of-file is encountered while attempting to read a character, the eof indicator is set (feof).
 * If this happens before any characters could be read, the pointer returned is a null pointer 
 * (and the contents of str remain unchanged).
 * If a read error occurs, the error indicator (ferror) is set and a null pointer is also returned 
 * (but the contents pointed by str may have changed).
 */
GD_C_API char* GD_fgets(char* buf, int count, GD_FILE* filePointer);
    
/** Write character to stream.
 * Writes a character to the stream and advances the position indicator.
 * The character is written at the position indicated by the internal position indicator of the stream, 
 * which is then automatically advanced by one.
 * 
 * @param character <tt>int</tt> The int promotion of the character to be written.
 * The value is internally converted to an unsigned char when written.
 *
 * @param filePointer <tt>GD_FILE*</tt> object which was returned by a previous call to <tt>GD_fopen</tt>.\n
 *
 * @return <tt>int</tt> On success, the character written is returned.
 * If a writing error occurs, EOF is returned and the error indicator (ferror) is set.
 */
GD_C_API int GD_fputc(int character, GD_FILE* filePointer);
 
/** Write string to stream.
 * Writes the C string pointed by str to the stream.
 * The function begins copying from the address specified (str) until it reaches the terminating null character ('\0'). 
 * This terminating null-character is not copied to the stream.
 *
 * @param buf <tt>const char*</tt> C string with the content to be written to stream.
 *
 * @param filePointer <tt>GD_FILE*</tt> object which was returned by a previous call to <tt>GD_fopen</tt>.\n
 *
 * @return <tt>int</tt> On success, a non-negative value is returned.
 * On error, the function returns EOF and sets the error indicator (ferror).
 */
GD_C_API int GD_fputs(const char* buf, GD_FILE* filePointer);

/** Write formatted data to stream.
 * Writes the C string pointed by format to the stream. If format includes format specifiers (subsequences beginning 
 * with %), the additional arguments following format are formatted and inserted in the resulting string replacing 
 * their respective specifiers.
 *
 * @param filePointer Pointer to a <tt>GD_FILE</tt> object that identifies an output stream.
 *
 * @param format C string that contains the text to be written to the stream. It can optionally contain embedded format
 * specifiers that are replaced by the values specified in subsequent additional arguments and formatted as requested.
 *
 * @return <tt>int</tt> On success, the total number of characters written is returned.
 * On error, the function returns EOF and sets the error indicator (ferror).
 */
GD_C_API int GD_fprintf(GD_FILE* filePointer, const char*  format, ...) GD_ATTRIBUTE((format(printf,2,3)));

/** Write formatted data from variable argument list to stream.
 * Writes the C string pointed by format to the stream, replacing any format specifier in the same way as printf does, but 
 * using the elements in the variable argument list identified by arg instead of additional function arguments.
 *
 * Internally, the function retrieves arguments from the list identified by arg as if va_arg was used on it, and thus the 
 * state of arg is likely altered by the call.
 *
 * In any case, arg should have been initialized by va_start at some point before the call, and it is expected to be released 
 * by va_end at some point after the call.
 *
 * @param filePointer Pointer to a <tt>GD_FILE</tt> object that identifies an output stream.
 *
 * @param format C string that contains a format string that follows the same specifications as format in printf (see printf for details).
 *
 * @param args A value identifying a variable arguments list initialized with va_start. va_list is a special type defined in the &lt;stdarg.h&gt; file.
 *
 * @return <tt>int</tt> On success, the total number of characters written is returned.
 * On error, the function returns EOF and sets the error indicator (ferror).
 */
GD_C_API int GD_vfprintf(GD_FILE* filePointer, const char * format, va_list args) GD_ATTRIBUTE((format(printf,2,0)));
    
/** Rename file.
 * Changes the name of the file or directory specified by oldname to newname.
 * This is an operation performed directly on a file; No streams are involved in the operation.
 * If oldname and newname specify different paths and this is supported by the system,
 * the file is moved to the new location.
 * If newname names an existing file, the function may either fail or override the existing file,
 * depending on the specific system and library implementation.
 *
 * @param oldname <tt>const char*</tt> C string containing the name of an existing file to be renamed and/or moved.
 *
 * @param newname <tt>const char*</tt> C string containing the new name for the file.
 *
 * @return <tt>int</tt> If the file is successfully renamed, a zero value is returned.
 * On failure, a nonzero value is returned.
 */
GD_C_API int GD_rename(const char* oldname, const char* newname);
  
/** Change stream buffering.
 * Specifies a buffer for stream. The function allows to specify the mode and size of the buffer (in bytes).
 * If buffer is a null pointer, the function automatically allocates a buffer (using size as a hint on the size to use).
 * Otherwise, the array pointed by buffer may be used as a buffer of size bytes.
 * This function should be called once the stream has been associated with an open file, 
 * but before any input or output operation is performed with it.
 * A stream buffer is a block of data that acts as intermediary between the i/o operations and the physical file associated to the stream:
 * For output buffers, data is output to the buffer until its maximum capacity is reached, then it is flushed
 * (i.e.: all data is sent to the physical file at once and the buffer cleared).
 * Likewise, input buffers are filled from the physical file, from which data is sent to the operations until exhausted,
 * at which point new data is acquired from the file to fill the buffer again.
 * Stream buffers can be explicitly flushed by calling fflush. 
 * They are also automatically flushed by fclose and freopen, or when the program terminates normally.
 *
 * @param filePointer <tt>GD_FILE*</tt> object which was returned by a previous call to <tt>GD_fopen</tt>.\n
 *
 * @param buf <tt>char*</tt> User allocated buffer. Shall be at least size bytes long.
 * If set to a null pointer, the function automatically allocates a buffer.
 *
 * @param mode <tt>int</tt> Specifies a mode for file buffering.(_IOFBF, _IOLBF and _IONBF)
 *
 * @param size <tt>size_t</tt> Buffer size, in bytes.
 * If the buffer argument is a null pointer, this value may determine the size automatically allocated by the function for the buffer.
 *
 * @return <tt>int</tt> If the buffer is correctly assigned to the file, a zero value is returned.
 * Otherwise, a non-zero value is returned; 
 * This may be due to an invalid mode parameter or to some other error allocating or assigning the buffer.
 */
GD_C_API int GD_setvbuf(GD_FILE* filePointer, char* buf, int mode, size_t size);

/** Change stream buffering.
 * Specifies a buffer for stream. The function allows to specify the size of the buffer (in bytes).
 * If buffer is a null pointer, the function automatically allocates a buffer (using size as a hint on the size to use).
 * Otherwise, the array pointed by buffer may be used as a buffer of size bytes.
 * This function should be called once the stream has been associated with an open file,
 * but before any input or output operation is performed with it.
 * A stream buffer is a block of data that acts as intermediary between the i/o operations and the physical file associated to the stream:
 * For output buffers, data is output to the buffer until its maximum capacity is reached, then it is flushed
 * (i.e.: all data is sent to the physical file at once and the buffer cleared).
 * Likewise, input buffers are filled from the physical file, from which data is sent to the operations until exhausted,
 * at which point new data is acquired from the file to fill the buffer again.
 * Stream buffers can be explicitly flushed by calling fflush.
 * They are also automatically flushed by fclose and freopen, or when the program terminates normally.
 *
 * Except for the lack of a return value, the GD_setbuffer function is exactly equivalent to the call
 * setvbuf(stream, buf, buf ? _IOFBF : _IONBF, size);
 *
 * @param filePointer <tt>GD_FILE*</tt> object which was returned by a previous call to <tt>GD_fopen</tt>.\n
 *
 * @param buf <tt>char*</tt> User allocated buffer. Shall be at least size bytes long.
 * If set to a null pointer, the function automatically allocates a buffer.
 *
 * @param size <tt>int</tt> Buffer size, in bytes.
 * If the buffer argument is a null pointer, this value may determine the size automatically allocated by the function for the buffer.
 */
GD_C_API void GD_setbuffer(GD_FILE* filePointer, char* buf, int size);

/** Change stream buffering.
 * Specifies a buffer for stream.
 * If buffer is a null pointer, the function automatically allocates a buffer.
 * Otherwise, the array pointed by buffer may be used as a buffer of size BUFSIZ.
 * This function should be called once the stream has been associated with an open file,
 * but before any input or output operation is performed with it.
 * A stream buffer is a block of data that acts as intermediary between the i/o operations and the physical file associated to the stream:
 * For output buffers, data is output to the buffer until its maximum capacity is reached, then it is flushed
 * (i.e.: all data is sent to the physical file at once and the buffer cleared).
 * Likewise, input buffers are filled from the physical file, from which data is sent to the operations until exhausted,
 * at which point new data is acquired from the file to fill the buffer again.
 * Stream buffers can be explicitly flushed by calling fflush.
 * They are also automatically flushed by fclose and freopen, or when the program terminates normally.
 *
 * Except for the lack of a return value, the GD_setbuf() function is exactly equivalent to the call
 * GD_setvbuf(filePointer, buf, buf ? _IOFBF : _IONBF, BUFSIZ);
 *
 * @param filePointer <tt>GD_FILE*</tt> object which was returned by a previous call to <tt>GD_fopen</tt>.\n
 *
 * @param buf <tt>char*</tt> User allocated buffer. Shall be BUFSIZ bytes long.
 * If set to a null pointer, the function automatically allocates a buffer.
 *
 */
GD_C_API void GD_setbuf(GD_FILE* filePointer, char* buf);
    
/** Flush stream.
 * If the given stream was open for writing (or if it was open for updating and the last i/o operation was an output operation) 
 * any unwritten data in its output buffer is written to the file.
 *
 * \note Note that this will not synchronize any read streams open on the write stream. To additionally synchronize with open read streams
 * on the same file, please use GD_fsync() instead.
 *
 * The stream remains open after this call.
 * When a file is closed, either because of a call to fclose or because the program terminates, all the buffers associated with it are automatically flushed.
 *
 * @param filePointer <tt>GD_FILE*</tt> object which was returned by a previous call to <tt>GD_fopen</tt>.\n
 *
 * @return <tt>int</tt> A zero value indicates success.
 * If an error occurs, EOF is returned and the error indicator is set (see ferror).
 */
GD_C_API int GD_fflush(GD_FILE* filePointer);

/** Flush stream and synchronize.
 * If the given stream was open for writing (or if it was open for updating and the last i/o operation was an output operation)
 * any unwritten data in its output buffer is written to the file.
 *
 * \note This will also synchronize any read streams open on the write stream and is therefore less performant than GD_fflush(), which may be
 * more appropriate if such synchronization is not required.
 *
 * The stream remains open after this call.
 * When a file is closed, either because of a call to fclose or because the program terminates, all the buffers associated with it are automatically flushed.
 *
 * @param filePointer <tt>GD_FILE*</tt> object which was returned by a previous call to <tt>GD_fopen</tt>.\n
 *
 * @return <tt>int</tt> A zero value indicates success.
 * If an error occurs, EOF is returned and the error indicator is set (see ferror).
 */
GD_C_API int GD_fsync(GD_FILE* filePointer);
    
/** Clear error indicators.
 * Resets both the error and the eof indicators of the stream.
 * When a i/o function fails either because of an error or because the end of the file has been reached, 
 * one of these internal indicators may be set for the stream. 
 * The state of these indicators is cleared by a call to this function, 
 * or by a call to any of: rewind, fseek, fsetpos and freopen.
 *
 * @param filePointer <tt>GD_FILE*</tt> object which was returned by a previous call to <tt>GD_fopen</tt>.\n
 */
GD_C_API void GD_clearerr(GD_FILE* filePointer);
    
/** Check error indicator.
 * Checks if the error indicator associated with stream is set, returning a value different from zero if it is.
 * This indicator is generally set by a previous operation on the stream that failed, 
 * and is cleared by a call to clearerr, rewind or freopen.
 *
 * @param filePointer <tt>GD_FILE*</tt> object which was returned by a previous call to <tt>GD_fopen</tt>.\n
 *
 * @return <tt>int</tt> A non-zero value is returned in the case that the error indicator associated with the stream is set.
 * Otherwise, zero is returned.
 */
GD_C_API int GD_ferror(GD_FILE* filePointer);

/** Create a directory at the specified path.
 * The directory path is created at the path specified. The mode parameter is not used and exists here for compatability.
 *
 * @param dirname <tt>const char*</tt> directory path to be created.
 *
 * @param mode <tt>mode</tt> not used (all directories are rwx)
 *
 * @return <tt>int</tt>
 */
GD_C_API int GD_mkdir(const char* dirname, mode_t mode);
    
/** Open a directory at specified path.
 * The opendir() function opens the directory named by dirname, associates a directory stream with it, and returns a pointer 
 * to be used to identify the directory stream in subsequent operations.  The pointer NULL is returned if dirname cannot be 
 * accessed or if it cannot malloc(3) enough memory to hold the whole thing.
 *
 * @param dirname <tt>char*</tt> string of the path to the directory.\n
 *
 * @return <tt>GD_DIR*</tt> object which represents the directory, NULL is returned in the case of an error.\n
 */
GD_C_API GD_DIR* GD_opendir(const char *dirname);
    
/** Close an already opened directory stream.
 * The closedir() function closes the named directory stream and frees the structure associated with the dirp pointer, 
 * returning 0 on success.  On failure, -1 is returned and the global variable errno is set to indicate the error.
 *
 * @param dirp <tt>GD_DIR*</tt> directory stream to close
 *
 * @return <tt>int</tt> 0 on success, -1 on failure
 */
GD_C_API int GD_closedir(GD_DIR *dirp);
    
/** Read next directory entry.
 * This function returns a pointer to the next directory entry. It returns NULL
 * upon reaching the end of the directory or detecting an invalid seekdir()
 * operation.
 *
 * @param dirp <tt>dirp</tt> directory stream to read from.
 *
 * @return <tt>struct dirent*</tt> pointer to a directory entry or NULL if the
 * end has been reached.
 */
GD_C_API struct dirent* GD_readdir(GD_DIR *dirp);
    
/** Read next directory entry into a buffer.
 * This function provides the same functionality as GD_readdir(), but the caller
 * must provide a directory entry buffer to store the results in.
 *
 * If the read succeeds, result is pointed at the entry; upon reaching the end
 * of the directory, result is set to NULL. readdir_r() returns 0 on success or
 * an error number to indicate failure.
 *
 * @param dirp <tt>GD_DIR*</tt> directory stream to use.
 *
 * @param entry <tt>struct dirent*</tt> caller provided buffer to store the
 * directory entry.
 *
 * @param result <tt>struct dirent**</tt> on sucess result is pointed to
 * entry.
 *
 * @return <tt>int</tt> 0 on success, -1 on failure.
 */
GD_C_API int GD_readdir_r(GD_DIR* dirp, struct dirent* entry, struct dirent** result);
    
/** Reset directory stream.
 * This function resets the position of the named directory stream to the
 * beginning of the directory.
 *
 * @param dirp <tt>GD_DIR*</tt> directory stream to use.
 */
GD_C_API void GD_rewinddir(GD_DIR *dirp);
    
/** Set the position of a directory stream.
 * This function sets the position of the next readdir() operation on the
 * directory stream. The new position reverts to the one associated with the
 * directory stream when the telldir() operation was performed.
 * 
 * @param dirp <tt>GD_DIR*</tt> directory stream to use.
 *
 * @param loc <tt>long</tt> position to seek to.
 */
GD_C_API void GD_seekdir(GD_DIR *dirp, long loc);
    
/** Current location of a directory stream.
 * This function returns the current location associated with the named
 * directory stream. Values returned by this function are good only for the
 * lifetime of the DIR pointer (e.g., dirp) from which they are derived. If the
 * directory is closed and then reopened, prior values returned by a previous
 * call will no longer be valid.
 *
 * @param dirp <tt>GD_DIR*</tt> directory stream to use.
 * 
 * @return <tt>long</tt> current location in the stream.
 */
GD_C_API long GD_telldir(GD_DIR *dirp);

/** File statistics.
 * This function returns information about the file at a specified path. Read,
 * write or execute permission of the named file is not required, but all
 * directories listed in the path name leading to the file must be searchable.
 *
 * @param path <tt>const char*</tt> pointer to a C string containing the path to the file.\n
 *
 * @param buf <tt>struct stat*</tt> buffer in which to write the stat data.\n
 *
 * @return <tt>int</tt> 0 on success, -1 on failure.\n
 */
GD_C_API int GD_stat(const char* path, struct stat* buf);

/** Obtain information about the directory or file associated with the named directory stream.
*
* @param dirp <tt>GD_DIR*</tt> directory stream to use.\n
*
* @param name <tt>const char*</tt> pointer to a C string containing the name to the file or directory.\n
*
* @param buf <tt>struct stat*</tt> buffer in which to write the stat data.\n
*
* @return <tt>int</tt> 0 on success, -1 on failure.\n
*/
GD_C_API int GD_statdir(GD_DIR *dirp, const char* name, struct stat* buf);

/** Get character from stream.
 * Returns the character currently pointed by the internal file position indicator of the specified stream.
 * The internal file position indicator is then advanced to the next character.
 * If the stream is at the end-of-file when called, the function returns EOF and sets the end-of-file indicator for the stream (feof).
 * If a read error occurs, the function returns EOF and sets the error indicator for the stream (ferror).
 *
 * @param filePointer <tt>GD_FILE*</tt> object which was returned by a previous call to <tt>GD_fopen</tt>.\n
 *
 * @return <tt>int</tt> On success, the character read is returned (promoted to an int value).
 * The return type is int to accommodate for the special value EOF, which indicates failure:
 * If the position indicator was at the end-of-file, the function returns EOF and sets the eof indicator (feof) of stream.
 * If some other reading error happens, the function also returns EOF, but sets its error indicator (ferror) instead.
 */
GD_C_API int GD_getc(GD_FILE* filePointer);

/** Push character back onto stream.
 * This function pushes the character c (converted to an unsigned char) back
 * onto the specified input stream. The pushed-back character will be returned
 * (in reverse order) by subsequent reads on the stream. A successful
 * intervening call to one of the file positioning functions using the same
 * stream, will discard the pushed-back characters.
 *
 * @return The <tt>GD_ungetc</tt> function returns the character pushed-back after the conversion, or EOF if the operation
 * fails.  If the value of the argument c character equals EOF, the operation will fail and the stream will
 * remain unchanged.
 */
GD_C_API int GD_ungetc(int character, GD_FILE* filePointer);
    
#ifdef __cplusplus
}
#endif

/** @}
 */

#endif // GD_C_FILESYSTEM_H
