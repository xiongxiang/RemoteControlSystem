#pragma once

//enum KeySize { Bits128, Bits192, Bits256 };  // key size, in bits, for construtor
typedef unsigned char   u1byte; /* an 8 bit unsigned character type */
typedef unsigned short  u2byte; /* a 16 bit unsigned integer type   */
typedef unsigned long   u4byte; /* a 32 bit unsigned integer type   */
typedef signed char     s1byte; /* an 8 bit signed character type   */
typedef signed short    s2byte; /* a 16 bit signed integer type     */
typedef signed long     s4byte; /* a 32 bit signed integer type     */
/* 2. Standard interface for AES cryptographic routines             */
/* These are all based on 32 bit unsigned values and may require    */
/* endian conversion for big-endian architectures                   */
#define LITTLE_ENDIAN

/* 3. Basic macros for speeding up generic operations               */
/* Circular rotate of 32 bit values                                 */
#ifdef _MSC_VER
#  include <stdlib.h>
#  pragma intrinsic(_lrotr,_lrotl)
#  define rotr(x,n) _lrotr(x,n)
#  define rotl(x,n) _lrotl(x,n)
#else
#define rotr(x,n)   (((x) >> ((int)(n))) | ((x) << (32 - (int)(n))))
#define rotl(x,n)   (((x) << ((int)(n))) | ((x) >> (32 - (int)(n))))
#endif
/* Invert byte order in a 32 bit variable                           */
#define bswap(x)    (rotl(x, 8) & 0x00ff00ff | rotr(x, 8) & 0xff00ff00)
/* Extract byte from a 32 bit quantity (little endian notation)     */
#define byte(x,n)   ((u1byte)((x) >> (8 * n)))
/* Input or output a 32 bit word in machine order     */
#ifdef LITTLE_ENDIAN
#define u4byte_in(x)  (*(u4byte*)(x))
#define u4byte_out(x, v) (*(u4byte*)(x) = (v))
#else
#define u4byte_in(x)  bswap(*(u4byte)(x))
#define u4byte_out(x, v) (*(u4byte*)(x) = bswap(v))
#endif

class AES
{
public:
	AES(void);
	~AES(void);

public:
	//char *name(void);
	/**
	 * @Brief set_key 设置加、解密时使用的密钥
	 * @Parameter const u1byte key[]  保存有密钥的数组
	 * @Parameter const u4byte key_len  密钥长度
	 * @Returns void
	 * @Remark  
	 **/
	void set_key(const u1byte key[], const u4byte key_len);

	/**
	 * @Brief encrypt 加密一个16字节也就是128位的数据
	 * @Parameter const u1byte in_blk[16]  要加密的128位数据
	 * @Parameter u1byte out_blk[16]  加密后的128位数据
	 * @Returns void  
	 * @Remark  
	 **/
	void encrypt(const u1byte in_blk[16], u1byte out_blk[16]);

	/**
	 * @Brief decrypt 解密一个16字节的数据
	 * @Parameter const u1byte in_blk[16]  要解密的16字节的数据
	 * @Parameter u1byte out_blk[16] 解密后的16字节的数据
	 * @Returns void
	 * @Remark  
	 **/
	void decrypt(const u1byte in_blk[16], u1byte out_blk[16]);

	/**
	 * @Brief encrypt 加密文件
	 * @Parameter CString fileName  要加密的文件
	 * @Returns void
	 * @Remark  在本项目中，只需要传入要加密的文件的名字，不包括后缀。
	            因为，本项目中假定要加密的文件后缀名为.plain,要解密的文件名为.crypt
	 **/
	void encrypt(CString fileName);

	/**
	 * @Brief decrypt 解密文件
	 * @Parameter CString fileName  要解密的文件
	 * @Returns void
	 * @Remark   在本项目中，只需要传入要解密的文件的名字，不包括后缀。
				 因为，本项目中假定要加密的文件后缀名为.plain,要解密的文件名为.crypt
	 **/
	void decrypt(CString fileName);

private:
	u4byte  k_len;
	u4byte  e_key[64];
	u4byte  d_key[64];
};
