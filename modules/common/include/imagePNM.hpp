/**
 * @file
 * @brief PNM画像に関する処理の関数群
 *
 * - PNM画像のロード
 * - PNM形式への保存
 *
 * Copyright (C) 2017 TOPCON CORPORATION, All rights reserved.
*/

#ifndef _IMAGEG_PNM
#define _IMAGEG_PNM

#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class CImagePNM
{
public:
	CImagePNM(void);
	virtual ~CImagePNM(void);

	bool	setGrayImg( unsigned char *src, int srcW, int srcH );
	bool	create8(int srcW, int srcH);
	bool	create24(int srcW, int srcH);
	bool 	createClone8(CImagePNM &dst);

	bool	copyImg8(unsigned char *src);
	bool	clearMem();

	bool	convertGray2RGB(CImagePNM &dst);

	bool	savePGM( unsigned char *imgData, int imgW, int imgH, string saveName, bool isBin=true );
	bool	savePGMp2( unsigned char *imgData, int imgW, int imgH, string saveName );
	bool	savePGM( unsigned char *imgData, int imgW, int imgH, string fname, int ImgNo, int digit, string Ext, bool isBin=true );
	bool	savePGM(string fname);
	bool	savePPM(string fname);

	bool	loadPGM( string saveName );
	bool	loadRAW( string fname, int imgW, int imgH );

	bool	allocImgMem();
	void	deleteImgMem();

	bool	setImg(int x, int y, int brit8);
	bool	setImg24(int x, int y, int R, int G, int B);

	bool	cut(int sx, int sy, int cutW, int cutH, CImagePNM *dst);
	bool	paste(CImagePNM &partial, int sx, int sy);

	int		m_imgW;
	int		m_imgH;
	int		m_iDepth;
	unsigned char *m_imgData;
};

#endif
