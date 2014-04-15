#include "StdAfx.h"
#include "AES.h"
#include <atlconv.h>



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AES::AES(void)
{
}

AES::~AES(void)
{
}

#define LARGE_TABLES
namespace
{
	u1byte  pow_tab[256];
	u1byte  log_tab[256];
	u1byte  sbx_tab[256];
	u1byte  isb_tab[256];
	u4byte  rco_tab[ 10];
	u4byte  ft_tab[4][256];
	u4byte  it_tab[4][256];
#ifdef  LARGE_TABLES
	u4byte  fl_tab[4][256];
	u4byte  il_tab[4][256];
#endif
	u4byte  tab_gen = 0;
#define ff_mult(a,b)    (a && b ? pow_tab[(log_tab[a] + log_tab[b]) % 255] : 0)
#define f_rn(bo, bi, n, k)                          \
    bo[n] =  ft_tab[0][byte(bi[n],0)] ^             \
	ft_tab[1][byte(bi[(n + 1) & 3],1)] ^   \
	ft_tab[2][byte(bi[(n + 2) & 3],2)] ^   \
	ft_tab[3][byte(bi[(n + 3) & 3],3)] ^ *(k + n)
#define i_rn(bo, bi, n, k)                          \
    bo[n] =  it_tab[0][byte(bi[n],0)] ^             \
	it_tab[1][byte(bi[(n + 3) & 3],1)] ^   \
	it_tab[2][byte(bi[(n + 2) & 3],2)] ^   \
	it_tab[3][byte(bi[(n + 1) & 3],3)] ^ *(k + n)
#ifdef LARGE_TABLES
#define ls_box(x)                \
    ( fl_tab[0][byte(x, 0)] ^    \
	fl_tab[1][byte(x, 1)] ^    \
	fl_tab[2][byte(x, 2)] ^    \
	fl_tab[3][byte(x, 3)] )
#define f_rl(bo, bi, n, k)                          \
    bo[n] =  fl_tab[0][byte(bi[n],0)] ^             \
	fl_tab[1][byte(bi[(n + 1) & 3],1)] ^   \
	fl_tab[2][byte(bi[(n + 2) & 3],2)] ^   \
	fl_tab[3][byte(bi[(n + 3) & 3],3)] ^ *(k + n)
#define i_rl(bo, bi, n, k)                          \
    bo[n] =  il_tab[0][byte(bi[n],0)] ^             \
	il_tab[1][byte(bi[(n + 3) & 3],1)] ^   \
	il_tab[2][byte(bi[(n + 2) & 3],2)] ^   \
	il_tab[3][byte(bi[(n + 1) & 3],3)] ^ *(k + n)
#else
#define ls_box(x)                            \
    ((u4byte)sbx_tab[byte(x, 0)] <<  0) ^    \
    ((u4byte)sbx_tab[byte(x, 1)] <<  8) ^    \
    ((u4byte)sbx_tab[byte(x, 2)] << 16) ^    \
    ((u4byte)sbx_tab[byte(x, 3)] << 24)
#define f_rl(bo, bi, n, k)                                      \
    bo[n] = (u4byte)sbx_tab[byte(bi[n],0)] ^                    \
	rotl(((u4byte)sbx_tab[byte(bi[(n + 1) & 3],1)]),  8) ^  \
	rotl(((u4byte)sbx_tab[byte(bi[(n + 2) & 3],2)]), 16) ^  \
	rotl(((u4byte)sbx_tab[byte(bi[(n + 3) & 3],3)]), 24) ^ *(k + n)
#define i_rl(bo, bi, n, k)                                      \
    bo[n] = (u4byte)isb_tab[byte(bi[n],0)] ^                    \
	rotl(((u4byte)isb_tab[byte(bi[(n + 3) & 3],1)]),  8) ^  \
	rotl(((u4byte)isb_tab[byte(bi[(n + 2) & 3],2)]), 16) ^  \
	rotl(((u4byte)isb_tab[byte(bi[(n + 1) & 3],3)]), 24) ^ *(k + n)
#endif
	void gen_tabs(void)
	{   
		u4byte  i, t;
    u1byte  p, q;
    // log and power tables for GF(2**8) finite field with 
    // 0x011b as modular polynomial - the simplest prmitive
    // root is 0x03, used here to generate the tables      
    for(i = 0,p = 1; i < 256; ++i)
    {
        pow_tab[i] = (u1byte)p; log_tab[p] = (u1byte)i;
        p = p ^ (p << 1) ^ (p & 0x80 ? 0x01b : 0);
    }
    log_tab[1] = 0; p = 1;
    for(i = 0; i < 10; ++i)
    {
        rco_tab[i] = p;
        p = (p << 1) ^ (p & 0x80 ? 0x1b : 0);
    }
    for(i = 0; i < 256; ++i)
    {  
        p = (i ? pow_tab[255 - log_tab[i]] : 0); q = p;
        q = (q >> 7) | (q << 1); p ^= q;
        q = (q >> 7) | (q << 1); p ^= q;
        q = (q >> 7) | (q << 1); p ^= q;
        q = (q >> 7) | (q << 1); p ^= q ^ 0x63;
        sbx_tab[i] = p; isb_tab[p] = (u1byte)i;
    }
    for(i = 0; i < 256; ++i)
    {
        p = sbx_tab[i];
#ifdef  LARGE_TABLES       
		
        t = p; fl_tab[0][i] = t;
        fl_tab[1][i] = rotl(t,  8);
        fl_tab[2][i] = rotl(t, 16);
        fl_tab[3][i] = rotl(t, 24);
#endif
        t = ((u4byte)ff_mult(2, p)) |
            ((u4byte)p <<  8) |
            ((u4byte)p << 16) |
            ((u4byte)ff_mult(3, p) << 24);
		
        ft_tab[0][i] = t;
        ft_tab[1][i] = rotl(t,  8);
        ft_tab[2][i] = rotl(t, 16);
        ft_tab[3][i] = rotl(t, 24);
        p = isb_tab[i];
#ifdef  LARGE_TABLES       
		
        t = p; il_tab[0][i] = t;
        il_tab[1][i] = rotl(t,  8);
        il_tab[2][i] = rotl(t, 16);
        il_tab[3][i] = rotl(t, 24);
#endif
        t = ((u4byte)ff_mult(14, p)) |
            ((u4byte)ff_mult( 9, p) <<  8) |
            ((u4byte)ff_mult(13, p) << 16) |
            ((u4byte)ff_mult(11, p) << 24);
		
        it_tab[0][i] = t;
        it_tab[1][i] = rotl(t,  8);
        it_tab[2][i] = rotl(t, 16);
        it_tab[3][i] = rotl(t, 24);
    }
    tab_gen = 1;
	}

#define star_x(x) (((x) & 0x7f7f7f7f) << 1) ^ ((((x) & 0x80808080) >> 7) * 0x1b)

#define imix_col(y,x)       \
    u   = star_x(x);        \
    v   = star_x(u);        \
    w   = star_x(v);        \
    t   = w ^ (x);          \
	(y)  = u ^ v ^ w;        \
	(y) ^= rotr(u ^ t,  8) ^ \
	rotr(v ^ t, 16) ^ \
	rotr(t,24)
} // end of anonymous namespace
/*char *rijndael::name(void)
{
    return "rijndael";
}*/
// initialise the key schedule from the user supplied key  
#define loop4(i)                                    \
{   t = ls_box(rotr(t,  8)) ^ rco_tab[i];           \
    t ^= e_key[4 * i];     e_key[4 * i + 4] = t;    \
    t ^= e_key[4 * i + 1]; e_key[4 * i + 5] = t;    \
    t ^= e_key[4 * i + 2]; e_key[4 * i + 6] = t;    \
    t ^= e_key[4 * i + 3]; e_key[4 * i + 7] = t;    \
}
#define loop6(i)                                    \
{   t = ls_box(rotr(t,  8)) ^ rco_tab[i];           \
    t ^= e_key[6 * i];     e_key[6 * i + 6] = t;    \
    t ^= e_key[6 * i + 1]; e_key[6 * i + 7] = t;    \
    t ^= e_key[6 * i + 2]; e_key[6 * i + 8] = t;    \
    t ^= e_key[6 * i + 3]; e_key[6 * i + 9] = t;    \
    t ^= e_key[6 * i + 4]; e_key[6 * i + 10] = t;   \
    t ^= e_key[6 * i + 5]; e_key[6 * i + 11] = t;   \
}
#define loop8(i)                                    \
{   t = ls_box(rotr(t,  8)) ^ rco_tab[i];           \
    t ^= e_key[8 * i];     e_key[8 * i + 8] = t;    \
    t ^= e_key[8 * i + 1]; e_key[8 * i + 9] = t;    \
    t ^= e_key[8 * i + 2]; e_key[8 * i + 10] = t;   \
    t ^= e_key[8 * i + 3]; e_key[8 * i + 11] = t;   \
    t  = e_key[8 * i + 4] ^ ls_box(t);              \
    e_key[8 * i + 12] = t;                          \
    t ^= e_key[8 * i + 5]; e_key[8 * i + 13] = t;   \
    t ^= e_key[8 * i + 6]; e_key[8 * i + 14] = t;   \
    t ^= e_key[8 * i + 7]; e_key[8 * i + 15] = t;   \
}

void AES::set_key(const u1byte in_key[], const u4byte key_len)
{   
	u4byte  i, t, u, v, w;
	if(!tab_gen)
		gen_tabs();
	k_len = (key_len + 31) / 32;
	e_key[0] = u4byte_in(in_key     );
	e_key[1] = u4byte_in(in_key +  4);
	e_key[2] = u4byte_in(in_key +  8);
	e_key[3] = u4byte_in(in_key + 12);
	switch(k_len)
	{
	case 4: 
		t = e_key[3];
		for(i = 0; i < 10; ++i)
			loop4(i);
		break;
	case 6: 
		e_key[4] = u4byte_in(in_key + 16); t = e_key[5] = u4byte_in(in_key + 20);
		for(i = 0; i < 8; ++i)
			loop6(i);
		break;
	case 8: 
		e_key[4] = u4byte_in(in_key + 16); e_key[5] = u4byte_in(in_key + 20);
		e_key[6] = u4byte_in(in_key + 24); t = e_key[7] = u4byte_in(in_key + 28);
		for(i = 0; i < 7; ++i)
			loop8(i);
		break;
	}
	d_key[0] = e_key[0]; d_key[1] = e_key[1];
	d_key[2] = e_key[2]; d_key[3] = e_key[3];
	for(i = 4; i < 4 * k_len + 24; ++i)
	{
		imix_col(d_key[i], e_key[i]);
	}
	return;
}
// encrypt a block of text 
#define f_nround(bo, bi, k) \
    f_rn(bo, bi, 0, k);     \
    f_rn(bo, bi, 1, k);     \
    f_rn(bo, bi, 2, k);     \
    f_rn(bo, bi, 3, k);     \
	k += 4

#define f_lround(bo, bi, k) \
    f_rl(bo, bi, 0, k);     \
    f_rl(bo, bi, 1, k);     \
    f_rl(bo, bi, 2, k);     \
	f_rl(bo, bi, 3, k)

void AES::encrypt(const u1byte in_blk[16], u1byte out_blk[16])
{   
	u4byte  b0[4], b1[4], *kp;
	b0[0] = u4byte_in(in_blk    ) ^ e_key[0]; b0[1] = u4byte_in(in_blk +  4) ^ e_key[1];
	b0[2] = u4byte_in(in_blk + 8) ^ e_key[2]; b0[3] = u4byte_in(in_blk + 12) ^ e_key[3];
	kp = e_key + 4;
	if(k_len > 6)
	{
		f_nround(b1, b0, kp); f_nround(b0, b1, kp);
	}
	if(k_len > 4)
	{
		f_nround(b1, b0, kp); f_nround(b0, b1, kp);
	}
	f_nround(b1, b0, kp); f_nround(b0, b1, kp);
	f_nround(b1, b0, kp); f_nround(b0, b1, kp);
	f_nround(b1, b0, kp); f_nround(b0, b1, kp);
	f_nround(b1, b0, kp); f_nround(b0, b1, kp);
	f_nround(b1, b0, kp); f_lround(b0, b1, kp);
	u4byte_out(out_blk,      b0[0]); u4byte_out(out_blk +  4, b0[1]);
	u4byte_out(out_blk +  8, b0[2]); u4byte_out(out_blk + 12, b0[3]);
}

void AES::encrypt( CString fileName)
{
	USES_CONVERSION;
	CString inFileName = fileName+_T(".plain");
	CString outFileName = fileName+_T(".crypt");
	FILE* ff;
	FILE* fp;
	ff=fopen(T2A(inFileName),"rb");
	if(!ff) return;
	fseek(ff,0,SEEK_END);
	long length=ftell(ff);
	fseek(ff,0,SEEK_SET);

	long N=length/16;//每16字节一组
	int d=length%16;
	if(d) //作用是当明文长度不是128bit整数倍时调整N值
	{
		length=length+16-length%16;
		N=N+1;
	}
	unsigned char *inBuff=new u1byte[length+1];	
	fread(inBuff,1,length-16+d,ff);
	fclose(ff);

	if(d) //如果明文长度不是128bit的倍数用空格补齐剩余的位
	{
		for(int i=0;i<16-d;i++)
		{
			inBuff[length-16+d+i]=' ';
		}
	}
	u1byte *ouBuff;//用于指向加密后的密文
	ouBuff=new u1byte[length];
	u1byte *keyBuff=new u1byte[256];
	//GetDlgItemText(IDC_EDIT2,(char*)keyBuff,256);//从文本框中取得密钥,将密钥拷贝到keyBuff指向的内存
	//set_key(keyBuff,256);//设置密钥
	for(int j=0;j<N;j++)//循环加密N次，每次128bit
	{
		encrypt(inBuff,ouBuff);
		inBuff+=16;
		ouBuff+=16;
	}
	delete[]keyBuff;
	inBuff=inBuff-16*N;//明文指针回到明文头
	delete[]inBuff;
	ouBuff=ouBuff-16*N;//密文指针回到密文头
	fp=fopen(T2A(outFileName),"wb");
	fwrite(ouBuff,1,length,fp);//输出密文
	delete[]ouBuff;
	fclose(fp);
	// TODO: 在此添加控件通知处理程序代码	
}

// decrypt a block of text 
#define i_nround(bo, bi, k) \
    i_rn(bo, bi, 0, k);     \
    i_rn(bo, bi, 1, k);     \
    i_rn(bo, bi, 2, k);     \
    i_rn(bo, bi, 3, k);     \
	k -= 4
#define i_lround(bo, bi, k) \
    i_rl(bo, bi, 0, k);     \
    i_rl(bo, bi, 1, k);     \
    i_rl(bo, bi, 2, k);     \
    i_rl(bo, bi, 3, k)

void AES::decrypt(const u1byte in_blk[16], u1byte out_blk[16])
{
	u4byte  b0[4], b1[4], *kp;
	b0[0] = u4byte_in(in_blk     ) ^ e_key[4 * k_len + 24];
	b0[1] = u4byte_in(in_blk +  4) ^ e_key[4 * k_len + 25];
	b0[2] = u4byte_in(in_blk +  8) ^ e_key[4 * k_len + 26];
	b0[3] = u4byte_in(in_blk + 12) ^ e_key[4 * k_len + 27];
	kp = d_key + 4 * (k_len + 5);
	if(k_len > 6)
	{
		i_nround(b1, b0, kp); i_nround(b0, b1, kp);
	}
	if(k_len > 4)
	{
		i_nround(b1, b0, kp); i_nround(b0, b1, kp);
	}

	i_nround(b1, b0, kp); i_nround(b0, b1, kp);
	i_nround(b1, b0, kp); i_nround(b0, b1, kp);
	i_nround(b1, b0, kp); i_nround(b0, b1, kp);
	i_nround(b1, b0, kp); i_nround(b0, b1, kp);
	i_nround(b1, b0, kp); i_lround(b0, b1, kp);
	u4byte_out(out_blk,     b0[0]); u4byte_out(out_blk +  4, b0[1]);
	u4byte_out(out_blk + 8, b0[2]); u4byte_out(out_blk + 12, b0[3]);
}

void AES::decrypt( CString fileName )
{
	USES_CONVERSION;
	CString inFileName = fileName+_T(".crypt");
	CString outFileName = fileName+_T(".plain");
	CFile c_ff((LPCTSTR)inFileName,CFile::modeRead);

	long length=c_ff.GetLength();
	long N=length/16;//取得组数做为循环次数
	u1byte *inBuff=new u1byte[length+1];
	c_ff.Read(inBuff,length);//将明文拷贝到inBuff指向的内存
	c_ff.Close();
	u1byte *keyBuff=new u1byte[256];
	//GetDlgItemText(IDC_EDIT2,(char*)keyBuff,256);//从文本框中取得密钥
	//将密钥拷贝到keyBuff指向的内存
	//rij.set_key(keyBuff,256);//设置密钥
	u1byte *ouBuff;//用于指向加密后的密文
	ouBuff=new u1byte[length];

	for(int j=0;j<N;j++) //循环解密N次
	{
		decrypt(inBuff,ouBuff);
		inBuff+=16;
		ouBuff+=16;
	}
	delete[]keyBuff;
	inBuff=inBuff-16*N;
	delete[]inBuff;
	ouBuff=ouBuff-16*N;
	CFile c_fp((LPCTSTR)outFileName,CFile::modeCreate|CFile::modeWrite);
	c_fp.Write(ouBuff,length);
	c_fp.Close();
	delete ouBuff;
//	MessageBox("解密成功！");
//	SetDlgItemText(IDC_FILESELECT,m_filename);	

}

