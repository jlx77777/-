#include<openssl/evp.h>
#include<iostream>
#include<ctime>
using namespace std;
#define rol(x,n) (((x)<<(n))|((x)>>(32-(n))))
#define P0(x) ((x)^(rol((x),9))^(rol((x),17)))
#define P1(x) ((x)^(rol((x),15))^(rol((x),23)))
#define FF0(x,y,z) ((x)^(y)^(z))
#define FF1(x,y,z) (((x)&(y))|((x)&(z))|((y)&(z)))
#define GG0(x,y,z) ((x)^(y)^(z))
#define GG1(x,y,z) (((x)&(y))|((~(x))&(z)))
void SM3(unsigned char* input, const unsigned long long mlen, unsigned char* buffer) {
	char V[] = { 0x73,0x80,0x16,0x6F,0x49,0x14,0xB2,0xB9,0x17,0x24,0x42,0xD7,0xDA,0x8A,0x06,0x00,0xA9,0x6F,0x30,0xBC,0x16,0x31,0x38,0xAA,0xE3,0x8D,0xEE,0x4D,0xB0,0xFB,0x0E,0x4E };
	unsigned int W[68], W1[64], A, B, C, D, E, F, G, H;
	unsigned long long len = mlen;
	unsigned char* p = input;

	while (len >= 64) {
		for (int i = 0; i < 16; i++) {
			W[i] = *((unsigned int*)p + i);
		}
		//转成按大端序读的数
		for (int i = 0; i < 16; i++) {
			W[i] = ((W[i] & 0xff) << 24) | ((W[i] & 0xff00) << 8) | (((W[i] & 0xff0000) >> 8)) | ((W[i] & 0xff000000) >> 24);
		}
		for (int i = 16; i < 68; i++) {
			W[i] = P1(W[i - 16] ^ W[i - 9] ^ rol(W[i - 3], 15)) ^ rol(W[i - 13], 7) ^ W[i - 6];
		}
		for (int i = 0; i < 64; i++) {
			W1[i] = W[i] ^ W[i + 4];
		}
		A = *(unsigned int*)V;
		B = *((unsigned int*)V + 1);
		C = *((unsigned int*)V + 2);
		D = *((unsigned int*)V + 3);
		E = *((unsigned int*)V + 4);
		F = *((unsigned int*)V + 5);
		G = *((unsigned int*)V + 6);
		H = *((unsigned int*)V + 7);
		A = ((A & 0xff) << 24) | ((A & 0xff00) << 8) | (((A & 0xff0000) >> 8)) | ((A & 0xff000000) >> 24);//转成大端序读的数
		B = ((B & 0xff) << 24) | ((B & 0xff00) << 8) | (((B & 0xff0000) >> 8)) | ((B & 0xff000000) >> 24);
		C = ((C & 0xff) << 24) | ((C & 0xff00) << 8) | (((C & 0xff0000) >> 8)) | ((C & 0xff000000) >> 24);
		D = ((D & 0xff) << 24) | ((D & 0xff00) << 8) | (((D & 0xff0000) >> 8)) | ((D & 0xff000000) >> 24);
		E = ((E & 0xff) << 24) | ((E & 0xff00) << 8) | (((E & 0xff0000) >> 8)) | ((E & 0xff000000) >> 24);
		F = ((F & 0xff) << 24) | ((F & 0xff00) << 8) | (((F & 0xff0000) >> 8)) | ((F & 0xff000000) >> 24);
		G = ((G & 0xff) << 24) | ((G & 0xff00) << 8) | (((G & 0xff0000) >> 8)) | ((G & 0xff000000) >> 24);
		H = ((H & 0xff) << 24) | ((H & 0xff00) << 8) | (((H & 0xff0000) >> 8)) | ((H & 0xff000000) >> 24);
		unsigned int SS1, SS2, TT1, TT2, T[64];
		for (int i = 0; i < 16; i++) {
			T[i] = 0x79CC4519;
			SS1 = rol(rol(A, 12) + E + rol(T[i], i), 7);
			SS2 = SS1 ^ rol(A, 12);
			TT1 = FF0(A, B, C) + D + SS2 + W1[i];
			TT2 = GG0(E, F, G) + H + SS1 + W[i];
			D = C;
			C = rol(B, 9);
			B = A;
			A = TT1;
			H = G;
			G = rol(F, 19);
			F = E;
			E = P0(TT2);
		}
		for (int i = 16; i < 64; i++) {
			T[i] = 0x7a879d8a;
			SS1 = rol(rol(A, 12) + E + rol(T[i], i), 7);
			SS2 = SS1 ^ rol(A, 12);
			TT1 = FF1(A, B, C) + D + SS2 + W1[i];
			TT2 = GG1(E, F, G) + H + SS1 + W[i];
			D = C;
			C = rol(B, 9);
			B = A;
			A = TT1;
			H = G;
			G = rol(F, 19);
			F = E;
			E = P0(TT2);
		}
		A = ((A & 0xff) << 24) | ((A & 0xff00) << 8) | (((A & 0xff0000) >> 8)) | ((A & 0xff000000) >> 24);//写进去的时候转回来
		B = ((B & 0xff) << 24) | ((B & 0xff00) << 8) | (((B & 0xff0000) >> 8)) | ((B & 0xff000000) >> 24);
		C = ((C & 0xff) << 24) | ((C & 0xff00) << 8) | (((C & 0xff0000) >> 8)) | ((C & 0xff000000) >> 24);
		D = ((D & 0xff) << 24) | ((D & 0xff00) << 8) | (((D & 0xff0000) >> 8)) | ((D & 0xff000000) >> 24);
		E = ((E & 0xff) << 24) | ((E & 0xff00) << 8) | (((E & 0xff0000) >> 8)) | ((E & 0xff000000) >> 24);
		F = ((F & 0xff) << 24) | ((F & 0xff00) << 8) | (((F & 0xff0000) >> 8)) | ((F & 0xff000000) >> 24);
		G = ((G & 0xff) << 24) | ((G & 0xff00) << 8) | (((G & 0xff0000) >> 8)) | ((G & 0xff000000) >> 24);
		H = ((H & 0xff) << 24) | ((H & 0xff00) << 8) | (((H & 0xff0000) >> 8)) | ((H & 0xff000000) >> 24);
		*(unsigned int*)V ^= A;
		*((unsigned int*)V + 1) ^= B;
		*((unsigned int*)V + 2) ^= C;
		*((unsigned int*)V + 3) ^= D;
		*((unsigned int*)V + 4) ^= E;
		*((unsigned int*)V + 5) ^= F;
		*((unsigned int*)V + 6) ^= G;
		*((unsigned int*)V + 7) ^= H;
		len -= 64;
		p += 64;
	}
	unsigned char* m = new unsigned char[64];
	for (int i = 0; i < len; i++) {
		m[i] = p[i];
	}
	m[len] = 0x80;
	for (int i = len + 1; i < 56; i++) {
		m[i] = 0;
	}
	unsigned long long l = mlen * 8;
	for (int i = 63; i >= 56; i--) {
		m[i] = l & 0xff;
		l >>= 8;
	}
	for (int i = 0; i < 16; i++) {
		W[i] = *((unsigned int*)m + i);
	}
	//转成按大端序读的数
	for (int i = 0; i < 16; i++) {
		W[i] = ((W[i] & 0xff) << 24) | ((W[i] & 0xff00) << 8) | (((W[i] & 0xff0000) >> 8)) | ((W[i] & 0xff000000) >> 24);
	}/*
	printf("填充后的消息\n");
	for (int i = 0; i < 16; i++) {
		if (i % 8 == 0) std::cout << std::endl;
		printf("%08x ", W[i]);
	}*/
	std::cout << std::endl;
	for (int i = 16; i < 68; i++) {
		W[i] = P1(W[i - 16] ^ W[i - 9] ^ rol(W[i - 3], 15)) ^ rol(W[i - 13], 7) ^ W[i - 6];
	}
	for (int i = 0; i < 64; i++) {
		W1[i] = W[i] ^ W[i + 4];
	}/*
	printf("扩展后的消息\nW0W1...W67");
	for (int i = 0; i < 68; i++) {
		if (i % 8 == 0) std::cout << std::endl;
		printf("%08x ", W[i]);
	}
	std::cout << std::endl;
	printf("W0'W1'...W63'");
	for (int i = 0; i < 64; i++) {
		if (i % 8 == 0) std::cout << std::endl;
		printf("%08x ", W1[i]);
	}
	std::cout << std::endl;*/
	A = *(unsigned int*)V;//这么赋值是按小端序读
	B = *((unsigned int*)V + 1);
	C = *((unsigned int*)V + 2);
	D = *((unsigned int*)V + 3);
	E = *((unsigned int*)V + 4);
	F = *((unsigned int*)V + 5);
	G = *((unsigned int*)V + 6);
	H = *((unsigned int*)V + 7);
	A = ((A & 0xff) << 24) | ((A & 0xff00) << 8) | (((A & 0xff0000) >> 8)) | ((A & 0xff000000) >> 24);//转成大端序读的数
	B = ((B & 0xff) << 24) | ((B & 0xff00) << 8) | (((B & 0xff0000) >> 8)) | ((B & 0xff000000) >> 24);
	C = ((C & 0xff) << 24) | ((C & 0xff00) << 8) | (((C & 0xff0000) >> 8)) | ((C & 0xff000000) >> 24);
	D = ((D & 0xff) << 24) | ((D & 0xff00) << 8) | (((D & 0xff0000) >> 8)) | ((D & 0xff000000) >> 24);
	E = ((E & 0xff) << 24) | ((E & 0xff00) << 8) | (((E & 0xff0000) >> 8)) | ((E & 0xff000000) >> 24);
	F = ((F & 0xff) << 24) | ((F & 0xff00) << 8) | (((F & 0xff0000) >> 8)) | ((F & 0xff000000) >> 24);
	G = ((G & 0xff) << 24) | ((G & 0xff00) << 8) | (((G & 0xff0000) >> 8)) | ((G & 0xff000000) >> 24);
	H = ((H & 0xff) << 24) | ((H & 0xff00) << 8) | (((H & 0xff0000) >> 8)) | ((H & 0xff000000) >> 24);
	unsigned int SS1, SS2, TT1, TT2, T[64];/*
	printf("迭代压缩中间值\n");
	printf("j    A        B        C        D        E        F        G        H\n");
	printf("  %08x %08x %08x %08x %08x %08x %08x %08x\n", A, B, C, D, E, F, G, H);*/
	for (int i = 0; i < 16; i++) {
		T[i] = 0x79CC4519;
		SS1 = rol(rol(A, 12) + E + rol(T[i], i), 7);
		SS2 = SS1 ^ rol(A, 12);
		TT1 = FF0(A, B, C) + D + SS2 + W1[i];
		TT2 = GG0(E, F, G) + H + SS1 + W[i];
		D = C;
		C = rol(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = rol(F, 19);
		F = E;
		E = P0(TT2);
		//printf("%d %08x %08x %08x %08x %08x %08x %08x %08x\n", i, A, B, C, D, E, F, G, H);
	}
	for (int i = 16; i < 64; i++) {
		T[i] = 0x7a879d8a;
		SS1 = rol(rol(A, 12) + E + rol(T[i], i), 7);
		SS2 = SS1 ^ rol(A, 12);
		TT1 = FF1(A, B, C) + D + SS2 + W1[i];
		TT2 = GG1(E, F, G) + H + SS1 + W[i];
		D = C;
		C = rol(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = rol(F, 19);
		F = E;
		E = P0(TT2);
		//printf("%d %08x %08x %08x %08x %08x %08x %08x %08x\n", i, A, B, C, D, E, F, G, H);
	}
	A = ((A & 0xff) << 24) | ((A & 0xff00) << 8) | (((A & 0xff0000) >> 8)) | ((A & 0xff000000) >> 24);//写进去的时候转回来
	B = ((B & 0xff) << 24) | ((B & 0xff00) << 8) | (((B & 0xff0000) >> 8)) | ((B & 0xff000000) >> 24);
	C = ((C & 0xff) << 24) | ((C & 0xff00) << 8) | (((C & 0xff0000) >> 8)) | ((C & 0xff000000) >> 24);
	D = ((D & 0xff) << 24) | ((D & 0xff00) << 8) | (((D & 0xff0000) >> 8)) | ((D & 0xff000000) >> 24);
	E = ((E & 0xff) << 24) | ((E & 0xff00) << 8) | (((E & 0xff0000) >> 8)) | ((E & 0xff000000) >> 24);
	F = ((F & 0xff) << 24) | ((F & 0xff00) << 8) | (((F & 0xff0000) >> 8)) | ((F & 0xff000000) >> 24);
	G = ((G & 0xff) << 24) | ((G & 0xff00) << 8) | (((G & 0xff0000) >> 8)) | ((G & 0xff000000) >> 24);
	H = ((H & 0xff) << 24) | ((H & 0xff00) << 8) | (((H & 0xff0000) >> 8)) | ((H & 0xff000000) >> 24);
	*(unsigned int*)V ^= A;
	*((unsigned int*)V + 1) ^= B;
	*((unsigned int*)V + 2) ^= C;
	*((unsigned int*)V + 3) ^= D;
	*((unsigned int*)V + 4) ^= E;
	*((unsigned int*)V + 5) ^= F;
	*((unsigned int*)V + 6) ^= G;
	*((unsigned int*)V + 7) ^= H;
	for (int i = 0; i < 32; i++) {
		buffer[i] = V[i];
	}
	return;
}
void sm3_len_attk(unsigned char*iv,unsigned char *input,unsigned long long mlen,unsigned long long olen) {
	unsigned char V[32];
	for (int i = 0; i < 32; i++) {
		V[i] = iv[i];
	}
	unsigned int W[68], W1[64], A, B, C, D, E, F, G, H;
	unsigned long long len = mlen;
	unsigned char* p = input;

	while (len >= 64) {
		for (int i = 0; i < 16; i++) {
			W[i] = *((unsigned int*)p + i);
		}
		//转成按大端序读的数
		for (int i = 0; i < 16; i++) {
			W[i] = ((W[i] & 0xff) << 24) | ((W[i] & 0xff00) << 8) | (((W[i] & 0xff0000) >> 8)) | ((W[i] & 0xff000000) >> 24);
		}
		for (int i = 16; i < 68; i++) {
			W[i] = P1(W[i - 16] ^ W[i - 9] ^ rol(W[i - 3], 15)) ^ rol(W[i - 13], 7) ^ W[i - 6];
		}
		for (int i = 0; i < 64; i++) {
			W1[i] = W[i] ^ W[i + 4];
		}
		A = *(unsigned int*)V;
		B = *((unsigned int*)V + 1);
		C = *((unsigned int*)V + 2);
		D = *((unsigned int*)V + 3);
		E = *((unsigned int*)V + 4);
		F = *((unsigned int*)V + 5);
		G = *((unsigned int*)V + 6);
		H = *((unsigned int*)V + 7);
		A = ((A & 0xff) << 24) | ((A & 0xff00) << 8) | (((A & 0xff0000) >> 8)) | ((A & 0xff000000) >> 24);//转成大端序读的数
		B = ((B & 0xff) << 24) | ((B & 0xff00) << 8) | (((B & 0xff0000) >> 8)) | ((B & 0xff000000) >> 24);
		C = ((C & 0xff) << 24) | ((C & 0xff00) << 8) | (((C & 0xff0000) >> 8)) | ((C & 0xff000000) >> 24);
		D = ((D & 0xff) << 24) | ((D & 0xff00) << 8) | (((D & 0xff0000) >> 8)) | ((D & 0xff000000) >> 24);
		E = ((E & 0xff) << 24) | ((E & 0xff00) << 8) | (((E & 0xff0000) >> 8)) | ((E & 0xff000000) >> 24);
		F = ((F & 0xff) << 24) | ((F & 0xff00) << 8) | (((F & 0xff0000) >> 8)) | ((F & 0xff000000) >> 24);
		G = ((G & 0xff) << 24) | ((G & 0xff00) << 8) | (((G & 0xff0000) >> 8)) | ((G & 0xff000000) >> 24);
		H = ((H & 0xff) << 24) | ((H & 0xff00) << 8) | (((H & 0xff0000) >> 8)) | ((H & 0xff000000) >> 24);
		unsigned int SS1, SS2, TT1, TT2, T[64];
		for (int i = 0; i < 16; i++) {
			T[i] = 0x79CC4519;
			SS1 = rol(rol(A, 12) + E + rol(T[i], i), 7);
			SS2 = SS1 ^ rol(A, 12);
			TT1 = FF0(A, B, C) + D + SS2 + W1[i];
			TT2 = GG0(E, F, G) + H + SS1 + W[i];
			D = C;
			C = rol(B, 9);
			B = A;
			A = TT1;
			H = G;
			G = rol(F, 19);
			F = E;
			E = P0(TT2);
		}
		for (int i = 16; i < 64; i++) {
			T[i] = 0x7a879d8a;
			SS1 = rol(rol(A, 12) + E + rol(T[i], i), 7);
			SS2 = SS1 ^ rol(A, 12);
			TT1 = FF1(A, B, C) + D + SS2 + W1[i];
			TT2 = GG1(E, F, G) + H + SS1 + W[i];
			D = C;
			C = rol(B, 9);
			B = A;
			A = TT1;
			H = G;
			G = rol(F, 19);
			F = E;
			E = P0(TT2);
		}
		A = ((A & 0xff) << 24) | ((A & 0xff00) << 8) | (((A & 0xff0000) >> 8)) | ((A & 0xff000000) >> 24);//写进去的时候转回来
		B = ((B & 0xff) << 24) | ((B & 0xff00) << 8) | (((B & 0xff0000) >> 8)) | ((B & 0xff000000) >> 24);
		C = ((C & 0xff) << 24) | ((C & 0xff00) << 8) | (((C & 0xff0000) >> 8)) | ((C & 0xff000000) >> 24);
		D = ((D & 0xff) << 24) | ((D & 0xff00) << 8) | (((D & 0xff0000) >> 8)) | ((D & 0xff000000) >> 24);
		E = ((E & 0xff) << 24) | ((E & 0xff00) << 8) | (((E & 0xff0000) >> 8)) | ((E & 0xff000000) >> 24);
		F = ((F & 0xff) << 24) | ((F & 0xff00) << 8) | (((F & 0xff0000) >> 8)) | ((F & 0xff000000) >> 24);
		G = ((G & 0xff) << 24) | ((G & 0xff00) << 8) | (((G & 0xff0000) >> 8)) | ((G & 0xff000000) >> 24);
		H = ((H & 0xff) << 24) | ((H & 0xff00) << 8) | (((H & 0xff0000) >> 8)) | ((H & 0xff000000) >> 24);
		*(unsigned int*)V ^= A;
		*((unsigned int*)V + 1) ^= B;
		*((unsigned int*)V + 2) ^= C;
		*((unsigned int*)V + 3) ^= D;
		*((unsigned int*)V + 4) ^= E;
		*((unsigned int*)V + 5) ^= F;
		*((unsigned int*)V + 6) ^= G;
		*((unsigned int*)V + 7) ^= H;
		len -= 64;
		p += 64;
	}
	unsigned char* m = new unsigned char[64];
	for (int i = 0; i < len; i++) {
		m[i] = p[i];
	}
	m[len] = 0x80;
	for (int i = len + 1; i < 56; i++) {
		m[i] = 0;
	}
	unsigned long long l = (mlen+olen) * 8;
	for (int i = 63; i >= 56; i--) {
		m[i] = l & 0xff;
		l >>= 8;
	}
	for (int i = 0; i < 16; i++) {
		W[i] = *((unsigned int*)m + i);
	}
	//转成按大端序读的数
	for (int i = 0; i < 16; i++) {
		W[i] = ((W[i] & 0xff) << 24) | ((W[i] & 0xff00) << 8) | (((W[i] & 0xff0000) >> 8)) | ((W[i] & 0xff000000) >> 24);
	}/*
	printf("填充后的消息\n");
	for (int i = 0; i < 16; i++) {
		if (i % 8 == 0) std::cout << std::endl;
		printf("%08x ", W[i]);
	}
	std::cout << std::endl;*/
	for (int i = 16; i < 68; i++) {
		W[i] = P1(W[i - 16] ^ W[i - 9] ^ rol(W[i - 3], 15)) ^ rol(W[i - 13], 7) ^ W[i - 6];
	}
	for (int i = 0; i < 64; i++) {
		W1[i] = W[i] ^ W[i + 4];
	}/*
	printf("扩展后的消息\nW0W1...W67");
	for (int i = 0; i < 68; i++) {
		if (i % 8 == 0) std::cout << std::endl;
		printf("%08x ", W[i]);
	}
	std::cout << std::endl;
	printf("W0'W1'...W63'");
	for (int i = 0; i < 64; i++) {
		if (i % 8 == 0) std::cout << std::endl;
		printf("%08x ", W1[i]);
	}
	std::cout << std::endl;*/
	A = *(unsigned int*)V;//这么赋值是按小端序读
	B = *((unsigned int*)V + 1);
	C = *((unsigned int*)V + 2);
	D = *((unsigned int*)V + 3);
	E = *((unsigned int*)V + 4);
	F = *((unsigned int*)V + 5);
	G = *((unsigned int*)V + 6);
	H = *((unsigned int*)V + 7);
	A = ((A & 0xff) << 24) | ((A & 0xff00) << 8) | (((A & 0xff0000) >> 8)) | ((A & 0xff000000) >> 24);//转成大端序读的数
	B = ((B & 0xff) << 24) | ((B & 0xff00) << 8) | (((B & 0xff0000) >> 8)) | ((B & 0xff000000) >> 24);
	C = ((C & 0xff) << 24) | ((C & 0xff00) << 8) | (((C & 0xff0000) >> 8)) | ((C & 0xff000000) >> 24);
	D = ((D & 0xff) << 24) | ((D & 0xff00) << 8) | (((D & 0xff0000) >> 8)) | ((D & 0xff000000) >> 24);
	E = ((E & 0xff) << 24) | ((E & 0xff00) << 8) | (((E & 0xff0000) >> 8)) | ((E & 0xff000000) >> 24);
	F = ((F & 0xff) << 24) | ((F & 0xff00) << 8) | (((F & 0xff0000) >> 8)) | ((F & 0xff000000) >> 24);
	G = ((G & 0xff) << 24) | ((G & 0xff00) << 8) | (((G & 0xff0000) >> 8)) | ((G & 0xff000000) >> 24);
	H = ((H & 0xff) << 24) | ((H & 0xff00) << 8) | (((H & 0xff0000) >> 8)) | ((H & 0xff000000) >> 24);
	unsigned int SS1, SS2, TT1, TT2, T[64];/*
	printf("迭代压缩中间值\n");
	printf("j    A        B        C        D        E        F        G        H\n");
	printf("  %08x %08x %08x %08x %08x %08x %08x %08x\n", A, B, C, D, E, F, G, H);*/
	for (int i = 0; i < 16; i++) {
		T[i] = 0x79CC4519;
		SS1 = rol(rol(A, 12) + E + rol(T[i], i), 7);
		SS2 = SS1 ^ rol(A, 12);
		TT1 = FF0(A, B, C) + D + SS2 + W1[i];
		TT2 = GG0(E, F, G) + H + SS1 + W[i];
		D = C;
		C = rol(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = rol(F, 19);
		F = E;
		E = P0(TT2);
		//printf("%d %08x %08x %08x %08x %08x %08x %08x %08x\n", i, A, B, C, D, E, F, G, H);
	}
	for (int i = 16; i < 64; i++) {
		T[i] = 0x7a879d8a;
		SS1 = rol(rol(A, 12) + E + rol(T[i], i), 7);
		SS2 = SS1 ^ rol(A, 12);
		TT1 = FF1(A, B, C) + D + SS2 + W1[i];
		TT2 = GG1(E, F, G) + H + SS1 + W[i];
		D = C;
		C = rol(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = rol(F, 19);
		F = E;
		E = P0(TT2);
		//printf("%d %08x %08x %08x %08x %08x %08x %08x %08x\n", i, A, B, C, D, E, F, G, H);
	}
	A = ((A & 0xff) << 24) | ((A & 0xff00) << 8) | (((A & 0xff0000) >> 8)) | ((A & 0xff000000) >> 24);//写进去的时候转回来
	B = ((B & 0xff) << 24) | ((B & 0xff00) << 8) | (((B & 0xff0000) >> 8)) | ((B & 0xff000000) >> 24);
	C = ((C & 0xff) << 24) | ((C & 0xff00) << 8) | (((C & 0xff0000) >> 8)) | ((C & 0xff000000) >> 24);
	D = ((D & 0xff) << 24) | ((D & 0xff00) << 8) | (((D & 0xff0000) >> 8)) | ((D & 0xff000000) >> 24);
	E = ((E & 0xff) << 24) | ((E & 0xff00) << 8) | (((E & 0xff0000) >> 8)) | ((E & 0xff000000) >> 24);
	F = ((F & 0xff) << 24) | ((F & 0xff00) << 8) | (((F & 0xff0000) >> 8)) | ((F & 0xff000000) >> 24);
	G = ((G & 0xff) << 24) | ((G & 0xff00) << 8) | (((G & 0xff0000) >> 8)) | ((G & 0xff000000) >> 24);
	H = ((H & 0xff) << 24) | ((H & 0xff00) << 8) | (((H & 0xff0000) >> 8)) | ((H & 0xff000000) >> 24);
	*(unsigned int*)V ^= A;
	*((unsigned int*)V + 1) ^= B;
	*((unsigned int*)V + 2) ^= C;
	*((unsigned int*)V + 3) ^= D;
	*((unsigned int*)V + 4) ^= E;
	*((unsigned int*)V + 5) ^= F;
	*((unsigned int*)V + 6) ^= G;
	*((unsigned int*)V + 7) ^= H;
	return;
}
unsigned char iv[] = { 0x73, 0x80, 0x16, 0x6f, 0x49, 0x14, 0xb2, 0xb9,
                       0x17, 0x24, 0x42, 0xd7, 0xda, 0x8a, 0x06, 0x00,
                       0xa9, 0x6f, 0x30, 0xbc, 0x16, 0x31, 0x38, 0xaa,
                       0xe3, 0x8d, 0xee, 0x4d, 0xb0, 0xfb, 0x0e, 0x4e };
int main() {
    srand(time(0));
    unsigned char s[192],buf[32],buf2[32];
    unsigned int len = 32;
    for (int i = 0; i < 192; i++) {
        s[i] = rand() & 0xff;
    }
    s[64] = 0x80;
    for (int i = 64; i < 128; i++) {
        s[i] = 0;
    }
    s[125] = 2;
    //printf("M1 = 0x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x\n", *((unsigned int*)s + 0), *((unsigned int*)s + 1), *((unsigned int*)s + 2), *((unsigned int*)s + 3), *((unsigned int*)s + 4), *((unsigned int*)s + 5), *((unsigned int*)s + 6), *((unsigned int*)s + 7), *((unsigned int*)s + 8), *((unsigned int*)s + 9), *((unsigned int*)s + 10), *((unsigned int*)s + 11), *((unsigned int*)s + 12), *((unsigned int*)s + 13), *((unsigned int*)s + 14), *((unsigned int*)s + 15));
    //printf("M2 = 0x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x\n", *((unsigned int*)s + 32), *((unsigned int*)s + 33), *((unsigned int*)s + 34), *((unsigned int*)s + 35), *((unsigned int*)s + 36), *((unsigned int*)s + 37), *((unsigned int*)s + 38), *((unsigned int*)s + 39), *((unsigned int*)s + 40), *((unsigned int*)s + 41), *((unsigned int*)s + 42), *((unsigned int*)s + 43), *((unsigned int*)s + 44), *((unsigned int*)s + 45), *((unsigned int*)s + 46), *((unsigned int*)s + 47));
    SM3(s, 64, buf);
    printf("SM3(M1)=0x%08x%08x%08x%08x%08x%08x%08x%08x\n", *((unsigned int*)buf + 0), *((unsigned int*)buf + 1), *((unsigned int*)buf + 2), *((unsigned int*)buf + 3), *((unsigned int*)buf + 4), *((unsigned int*)buf + 5), *((unsigned int*)buf + 6), *((unsigned int*)buf + 7));
    SM3(s, 192, buf);
    printf("SM3(M1|padding|M2)=0x%08x%08x%08x%08x%08x%08x%08x%08x\n", *((unsigned int*)buf + 0), *((unsigned int*)buf + 1), *((unsigned int*)buf + 2), *((unsigned int*)buf + 3), *((unsigned int*)buf + 4), *((unsigned int*)buf + 5), *((unsigned int*)buf + 6), *((unsigned int*)buf + 7));
    SM3(s, 64, buf2);
	sm3_len_attk(buf2,s+128,64,128);
	printf("利用SM3(M1)和M2计算得0x%08x%08x%08x%08x%08x%08x%08x%08x\n", *((unsigned int*)buf + 0), *((unsigned int*)buf + 1), *((unsigned int*)buf + 2), *((unsigned int*)buf + 3), *((unsigned int*)buf + 4), *((unsigned int*)buf + 5), *((unsigned int*)buf + 6), *((unsigned int*)buf + 7));
    return 0;
}