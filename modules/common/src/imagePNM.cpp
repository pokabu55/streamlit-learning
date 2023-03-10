/**
 * @file
 * @brief PNM画像に関する処理の関数群
 *
 * - PNM画像のロード
 * - PNM形式への保存
 *
 * Copyright (C) 2017 TOPCON CORPORATION, All rights reserved.
*/

#include "imagePNM.hpp"

/*!
  * @brief		コンストラクタ
  *
  * @param[in]	なし
  *
  * @retval		なし
  *
 */
CImagePNM::CImagePNM(void)
{
	m_imgW = -1;
	m_imgH = -1;
	m_imgData = NULL;
	m_iDepth = 0;
	workMem24_ = NULL;
}

/*!
  * @brief		デストラクタ
  *
  * @param[in]	なし
  *
  * @retval		なし
  *
 */
CImagePNM::~CImagePNM(void)
{
	deleteImgMem();
	deleteWorkMem24();
}

/*!
  * @brief		メモリ確保
  *
  * @param[in]	なし
  *
  * @retval		true	処理成功
  * @retval		false	処理失敗
  *
 */
bool CImagePNM::allocImgMem()
{
	if (m_imgW <= 0 || m_imgH <= 0) return false;

	deleteImgMem();

	if (m_iDepth==8) {

		try {
			m_imgData = new unsigned char [m_imgW*m_imgH];
		}
		catch(...){
			return false;
		}

		memset( m_imgData, 0, m_imgW*m_imgH );
	}
	else if (m_iDepth==24) {

		try {
			m_imgData = new unsigned char [m_imgW*m_imgH*3];
		}
		catch(...){
			return false;
		}

		memset( m_imgData, 0, m_imgW*m_imgH*3 );
	}
	else {
		return false;
	}

	return true;
}

/*!
  * @brief		メモリ解放
  *
  * @param[in]	なし
  *
  * @retval		なし
  *
 */
void CImagePNM::deleteImgMem()
{
	if (m_imgData!=NULL) {
		delete [] m_imgData;
		m_imgData = NULL;
	}
}

bool CImagePNM::allocWorkMem24()
{
	if (m_imgW <= 0 || m_imgH <= 0) return false;

	deleteWorkMem24();

	try {
		workMem24_ = new unsigned char [m_imgW*m_imgH*3];
	}
	catch(...){
		return false;
	}

	memset( workMem24_, 0, m_imgW*m_imgH*3 );

	return true;
}

void CImagePNM::deleteWorkMem24()
{
	if (workMem24_!=NULL) {
		delete [] workMem24_;
		workMem24_ = NULL;
	}
}

/*!
  * @brief		２次元配列データをPGM形式の画像フォーマットで保存
  *
  * @param[in]	imgData		画像データ
  * @param[in]	imgW		画像の幅
  * @param[in]	imgH		画像の高さ
  * @param[in]	saveName	保存ファイル名
  * @param[in]	isBin		バイナリ保存の場合、TRUEとする
  *
  * @retval		true		処理成功
  * @retval		false		処理失敗
  *
 */
bool CImagePNM::savePGM( unsigned char *imgData, int imgW, int imgH, string saveName, bool isBin )
{
	// ascii の場合、別関数へ
	if(!isBin) return savePGMp2(imgData, imgW, imgH, saveName);

#ifdef _debug
//	cout << "come" << endl;
#endif

	//サイズのチェック
	if( imgW < 0 || imgH < 0 ) return false;

	ofstream ofs;
	ofs.open( saveName.c_str(), std::ios::binary );
	//ofs.open( saveName.c_str() );

	//オープンＯＫ？
    if( !ofs ) return false;

	ofs << "P5" << endl; //binary format
	//ofs << "P2" << endl;	//asci format

	ofs << imgW << " " << imgH << endl;
	ofs << 255 << endl;

	for( int y = 0; y < imgH; y++ )
	{
		for( int x = 0; x < imgW; x++ )
		{
			//ofs << imgData[ x + (imgH - y - 1) * imgW ];
			ofs << imgData[x+y*imgW];
		}
	}

	ofs.close();

	return true;
}

bool CImagePNM::savePGMp2( unsigned char *imgData, int imgW, int imgH, string saveName )
{
	//cout << "come" << endl;

	//サイズのチェック
	if( imgW < 0 || imgH < 0 ) return false;

	ofstream ofs;
	ofs.open( saveName.c_str() );

    //オープンＯＫ？
    if( !ofs ) return false;

	ofs << "P2" << endl;	//asci format

	ofs << imgW << " " << imgH << endl;
	ofs << 255 << endl;

	for( int y = 0; y < imgH; y++ )
	{
		for( int x = 0; x < imgW; x++ )
		{
			//ofs << imgData[ x + (imgH - y - 1) * imgW ] << " ";
			ofs << (int)imgData[x+y*imgW] << " ";
		}
		ofs << endl;
	}

	ofs.close();

	return true;
}

bool CImagePNM::savePGM( unsigned char *imgData, int imgW, int imgH, string	fname, int ImgNo, int digit, string	Ext, bool isBin)
{
	//ファイル名の生成
	{
		string strNo;
		stringstream ss;
		ss << ImgNo;
		ss >> strNo;

		int DigCnt = 0;

		do
		{
			ImgNo /= 10;
			DigCnt++;

		}while( ImgNo > 0 );

		string ff;

		if( DigCnt < digit )
		{
			for( int i = 0; i < (digit - DigCnt ); i++ )
			{
				ff += "0";
			}
		}

		ff += strNo;

		fname += ff;
		fname += Ext;
	}

	// 保存関数
	bool ret = savePGM( imgData, imgW,imgH, fname, isBin);

	return ret;
}

bool CImagePNM::savePPM( string saveName )
{
	int W = m_imgW;
	int H = m_imgH;

	int x, y;
	FILE *fp = fopen(saveName.c_str(), "wb"); /* b - binary mode */

	(void) fprintf(fp, "P6\n%d %d\n255\n", W, H);

	static unsigned char color[3];

	if (m_iDepth == 8) {
		for (y=0; y < H; y++) {
			for (x=0; x < W; x++) {
				color[0] = m_imgData[x+y*W];
				color[1] = color[0];
				color[2] = color[0];
				(void) fwrite(color, 1, 3, fp);
			}
		}
	}
	else {
		for (y=0; y < H; y++) {
			for (x=0; x < W; x++) {
				color[0] = m_imgData[(x+y*W)*3+0];
				color[1] = m_imgData[(x+y*W)*3+1];
				color[2] = m_imgData[(x+y*W)*3+2];
				(void) fwrite(color, 1, 3, fp);
			}
		}
	}

	(void) fclose(fp);

	return true;
}
/*
bool CImagePNM::savePPM( string saveName )
{
	//サイズのチェック
	if( m_imgW <= 0 || m_imgH <= 0 ) return false;

	ofstream ofs;
	ofs.open( saveName.c_str() );
	//ofs.open( saveName.c_str(), std::ios::binary );

	//オープンＯＫ？
	if( ofs == NULL ) return false;


	ofs << "P3" << endl;	//asci format
	//ofs << "P6" << endl;	//asci format

	ofs << m_imgW << " " << m_imgH << endl;
	ofs << 255 << endl;

	int W = m_imgW;
	int H = m_imgH;

	for( int y = 0; y < H; y++ )
	{
		for( int x = 0; x < W; x++ )
		{
			ofs << (int)m_imgData[(x+y*W)*3+0] << " ";
			ofs << (int)m_imgData[(x+y*W)*3+1] << " ";
			ofs << (int)m_imgData[(x+y*W)*3+2] << " ";
		}
		ofs << endl;
	}

	ofs.close();

	return true;
}
*/
bool CImagePNM::savePGM( string saveName )
{
	//サイズのチェック
	if( m_imgW <= 0 || m_imgH <= 0 ) return false;

	ofstream ofs;
	ofs.open( saveName.c_str() );

    //オープンＯＫ？
    if( !ofs ) return false;

	ofs << "P2" << endl;	//asci format

	ofs << m_imgW << " " << m_imgH << endl;
	ofs << 255 << endl;

	int W = m_imgW;
	int H = m_imgH;

	for( int y = 0; y < H; y++ )
	{
		for( int x = 0; x < W; x++ )
		{
			ofs << (int)m_imgData[x+y*W] << " ";
		}
		ofs << endl;
	}

	ofs.close();

	return true;
}

/*!
  * @brief		PGM形式の画像をロードして配列へ
  *
  * @param[in]	saveName	ロードするファイル名
  *
  * @retval		true		処理成功
  * @retval		false		処理失敗
  *
 */
bool CImagePNM::loadPGM( string saveName )
{
	FILE *fp;
	int ImgW, ImgH, ImgDpt;
	bool IsBinary = false;

	//errno_t error = fopen_s(&fp, saveName.c_str(), "rb");
	//if (error != 0) return false;
	fp = fopen(saveName.c_str(),"rb");
	if (fp==NULL) return false;

	//ヘッダ読み込み時のバッファ
	char ss[256];
	//ファイル形式
	int type;

	//-------------------- ヘッダ取得 ここから --------------------
	fgets( ss, 255, fp );

    // ファイル形式が違う
	if( ss[0] != 'P' ) {
		//AfxMessageBox( _T("PGMのフォーマットが対応していません。") );
		return false;
	}

	//sscanf_s( ss, "P%d", &type, sizeof(type) );
	sscanf( ss, "P%d", &type );

	if( type == 2 ) {
		IsBinary = false;
	}
	else if( type == 5 ) {
		IsBinary = true;
	}
	else if( type == 7 )
	{
		//一旦クローズする
		if( fclose(fp) ) return false;

		//16bitオープン関数へ渡します
		return false;//OpenPGM16File( lpszFileName, 0, 1, NotNorm );
	}
	else {
		//AfxMessageBox( _T("PGMのフォーマットが対応していません。") );
		return false;
	}

	// コメント読み飛ばし
	do {
		fgets( ss, 255, fp );
	}
	while( ss[0] == '#' );

	//サイズ
	//sscanf_s( ss, "%d%d", &ImgW, &ImgH, sizeof(ImgW), sizeof(ImgH) );
	sscanf( ss, "%d%d", &ImgW, &ImgH );

	// コメント読み飛ばし
	do {
		fgets( ss, 255, fp );
	}
	while( ss[0] == '#' );

	//深さ
	//sscanf_s( ss, "%d", &ImgDpt, sizeof(ImgDpt) );
	sscanf( ss, "%d", &ImgDpt );

	//サイズチェック
	if( ImgW < 0 || ImgH < 0 || ImgDpt != 255 ) {
		//AfxMessageBox( _T("PGMのフォーマットが対応していません。") );
		return false;
	}
	//-------------------- ヘッダ取得 ここまで --------------------

	//パリティ幅の計算
	m_imgW = ImgW;
	m_imgH = ImgH;
	m_iDepth = 8;

	/*if( ImgW % 4 != 0) {
		PrtW = ( 4 - ImgW % 4 ) + ImgW;
		m_iPrtW = PrtW;
	}*/

	if(!allocImgMem()) {
		return false;
	}

	//サイズをメンバへ
	//m_sImgSz.cx = ImgW;
	//m_sImgSz.cy = ImgH;

	//画像データのコピー（パリティ考慮無し）
	for( int i = 0; i < ImgW * ImgH; i++ ) {

		if( IsBinary ) {
			//fscanf_s(fp, "%c", &m_imgData[i]);
			fscanf(fp, "%c", &m_imgData[i]);
		}
		else {
			int ii;
			//fscanf_s(fp, "%d", &ii);
			fscanf(fp, "%d", &ii);
			m_imgData[i] = (unsigned char)ii;
		}
    }

	//画像データを上下逆さにしてコピー（パリティ考慮）
	/*for( int y = 0; y < ImgH; y++ ) {
		for( int x = 0; x < ImgW; x++ ) {
			m_bPnmImg[ x + (ImgH - y-1) * PrtW ] = m_bBufImg[ x + y * ImgW ];
		}
	}*/

	fclose(fp);

	return true;
}

/*!
  * @brief		PPM形式の画像をロードして配列へ
  *
  * @param[in]	saveName	ロードするファイル名
  * @param[in]	convertGray	グレイスケール変換フラグ
  *
  * @retval		true		処理成功
  * @retval		false		処理失敗
  *
 */
bool CImagePNM::loadPPM( string saveName, bool convertGray )
{
	FILE *fp;
	int ImgW, ImgH, ImgDpt;
	bool IsBinary = false;

	//errno_t error = fopen_s(&fp, saveName.c_str(), "rb");
	//if (error != 0) return false;
	fp = fopen(saveName.c_str(),"rb");
	if (fp==NULL) return false;

	//ヘッダ読み込み時のバッファ
	char ss[256];
	//ファイル形式
	int type;

	//-------------------- ヘッダ取得 ここから --------------------
	fgets( ss, 255, fp );

    // ファイル形式が違う
	if( ss[0] != 'P' ) {
		std::cout << "PGMのフォーマットが対応していません。" << std::endl;
		return false;
	}

	//sscanf_s( ss, "P%d", &type, sizeof(type) );
	sscanf( ss, "P%d", &type );

	if( type == 3 ) {
		IsBinary = false;
	}
	else if( type == 6 ) {
		IsBinary = true;
	}
	else {
		std::cout <<  "PGMのフォーマットが対応していません。" << std::endl;
		return false;
	}

	// コメント読み飛ばし
	do {
		fgets( ss, 255, fp );
	}
	while( ss[0] == '#' );

	//サイズ
	//sscanf_s( ss, "%d%d", &ImgW, &ImgH, sizeof(ImgW), sizeof(ImgH) );
	sscanf( ss, "%d%d", &ImgW, &ImgH );

	// コメント読み飛ばし
	do {
		fgets( ss, 255, fp );
	}
	while( ss[0] == '#' );

	//深さ
	//sscanf_s( ss, "%d", &ImgDpt, sizeof(ImgDpt) );
	sscanf( ss, "%d", &ImgDpt );

	//サイズチェック
	if( ImgW < 0 || ImgH < 0 || ImgDpt != 255 ) {
		std::cout << "PGMのフォーマットが対応していません。" << std::endl;
		return false;
	}
	//-------------------- ヘッダ取得 ここまで --------------------

	//パリティ幅の計算
	m_imgW = ImgW;
	m_imgH = ImgH;
	m_iDepth = 24;

	/*if( ImgW % 4 != 0) {
		PrtW = ( 4 - ImgW % 4 ) + ImgW;
		m_iPrtW = PrtW;
	}*/

	if(!allocImgMem()) {
		return false;
	}

	//サイズをメンバへ
	//m_sImgSz.cx = ImgW;
	//m_sImgSz.cy = ImgH;

	//画像データのコピー（パリティ考慮無し）
	for( int i = 0; i < ImgW * ImgH * 3; i++ ) {

		if( IsBinary ) {
			//fscanf_s(fp, "%c", &m_imgData[i]);
			fscanf(fp, "%c", &m_imgData[i]);
		}
		else {
			int ii;
			//fscanf_s(fp, "%d", &ii);
			fscanf(fp, "%d", &ii);
			m_imgData[i] = (unsigned char)ii;
		}
    }

	//画像データを上下逆さにしてコピー（パリティ考慮）
	/*for( int y = 0; y < ImgH; y++ ) {
		for( int x = 0; x < ImgW; x++ ) {
			m_bPnmImg[ x + (ImgH - y-1) * PrtW ] = m_bBufImg[ x + y * ImgW ];
		}
	}*/

	fclose(fp);

	if (convertGray) {
		if (!convertRGB2Gray()) return false;
	}

	return true;
}

bool CImagePNM::convertRGB2Gray()
{
	// すでにロードしているカラー画像をグレイスケールに変換する
	if (m_iDepth != 24) return false;

	// ワークメモリ
	if (!allocWorkMem24()) return false;
	memcpy(workMem24_, m_imgData, m_imgW*m_imgH*3);

	// グレイ画像用にメモリを取り直す
	m_iDepth = 8;
	if (!allocImgMem()) return false;

	int R, G, B;
	int gray;
	double dGray;
	int W = m_imgW;
	int W3 = m_imgW*3;
	int H = m_imgH;
	int x, y, x3;

	// グレイに変換
	for (y=0; y<H; y++) {
		for (x=0, x3=0; x<W; x++, x3+=3) {
			R = workMem24_[x3+y*W3];
			G = workMem24_[x3+y*W3+1];
			B = workMem24_[x3+y*W3+2];
			gray = (int)(R * 0.3 + G * 0.59 + B * 0.11 + 0.5);
			if (gray<0) gray = 0;
			else if (gray>255) gray = 255;
			m_imgData[x+y*W] = gray;
		}
	}

	return true;
}

bool CImagePNM::loadRAW(string fileName, int imgW, int imgH)
{
	// 拡張子チェック


	ifstream ifs(fileName.c_str(), ios::binary);

	if(ifs.fail()){
		cout << "File NOT FOUND!!" << endl;
		return false;
	}

	streamsize size = ifs.seekg(0, ios::end).tellg();
	ifs.seekg(0, ios::beg);

	int imgType = -1;

	if(size == imgW * imgH +1) imgType = 1;
	else if (size == imgW * imgH) imgType = 0;

	if (imgType < 0) {
		cout << "Picture size is Inaccurate!!" << endl;
		return false;
	}

	// メモリ確保
	m_imgW = imgW;
	m_imgH = imgH;
	m_iDepth = 8;
	if (!allocImgMem()) return false;

	//画像を一気に読み込み
	ifs.read(reinterpret_cast<char*>(m_imgData), imgW * imgH);
	ifs.close();

	return true;
}

bool CImagePNM::setGrayImg( unsigned char *src, int srcW, int srcH )
{
	if (srcW <= 0 || srcH <= 0) return false;

	m_imgW = srcW;
	m_imgH = srcH;
	m_iDepth = 8;

	// メモリ確保
	if (!allocImgMem()) return false;

	// コピー
	memcpy(m_imgData, src, m_imgW*m_imgH);

	return true;
}

bool CImagePNM::convertGray2RGB(CImagePNM &dst)
{
	// 24bitに変換

	// RGB用のメモリ確保
	dst.m_imgW = m_imgW;
	dst.m_imgH = m_imgH;
	dst.m_iDepth = 24;
	if (!dst.allocImgMem()) {
		return false;
	}

	int x,y,add, brit;
	int W = m_imgW;
	int H = m_imgH;

	for (y=0; y<H; y++) {
		for (x=0; x<W; x++) {

			brit = this->m_imgData[x+y*W];

			add = (x+y*W)*3;
			dst.m_imgData[add+0] = brit;
			dst.m_imgData[add+1] = brit;
			dst.m_imgData[add+2] = brit;
		}
	}

	return true;
}

bool CImagePNM::create8(int srcW, int srcH)
{
	// 空の画像を作る
	if (srcW <= 0 || srcH <= 0) return false;

	m_imgW = srcW;
	m_imgH = srcH;
	m_iDepth = 8;

	if (!allocImgMem()) return false;

	return true;
}

bool CImagePNM::create24(int srcW, int srcH)
{
	// 空の画像を作る
	if (srcW <= 0 || srcH <= 0) return false;

	m_imgW = srcW;
	m_imgH = srcH;
	m_iDepth = 24;

	if (!allocImgMem()) return false;

	return true;
}

bool CImagePNM::setImg(int x, int y, int brit8)
{
	if (m_imgData==NULL) return false;

	if (m_iDepth==8) {
		m_imgData[x+y*m_imgW] = brit8;
	}
	else if (m_iDepth == 24) {
		m_imgData[(x+y*m_imgW)*3+0] = brit8;
		m_imgData[(x+y*m_imgW)*3+1] = brit8;
		m_imgData[(x+y*m_imgW)*3+2] = brit8;
	}
	else {
		return false;
	}

	return true;
}

bool CImagePNM::setImg24(int x, int y, int R, int G, int B)
{
	if (m_imgData==NULL) return false;

	if (m_iDepth==24) {
		m_imgData[(x+y*m_imgW)*3+0] = R;
		m_imgData[(x+y*m_imgW)*3+1] = G;
		m_imgData[(x+y*m_imgW)*3+2] = B;
	}
	else {
		return false;
	}

	return true;
}

bool CImagePNM::copyImg8(unsigned char *src)
{
	if (m_imgData==NULL) return false;

	int size = this->m_imgW * this->m_imgH;

	// 既にメモリ確保されている前提です
	memcpy(this->m_imgData, src, size);

	return true;
}

bool CImagePNM::clearMem()
{
	if (m_iDepth==8) {
		memset(m_imgData, 0, m_imgW*m_imgH);
	}
	else if (m_iDepth==24) {
		memset(m_imgData, 0, m_imgW*m_imgH*3);
	}
	else {
		return false;
	}

	return true;
}

bool CImagePNM::cut(int sx, int sy, int cutW, int cutH, CImagePNM *dst)
{
	// メモリ確保
	if (!dst->create8(cutW, cutH)) return false;

	int x,y;
	int cx, cy;
	int srcW = this->m_imgW;

	for (y=sy,cy=0; y<sy+cutH; y++,cy++) {
		for (x=sx,cx=0; x<sx+cutW; x++,cx++) {
			dst->m_imgData[cx+cy*cutW] = this->m_imgData[x+y*srcW];
		}
	}

	return true;
}

bool CImagePNM::paste(CImagePNM &partial, int sx, int sy)
{
	int W = this->m_imgW;
	int H = this->m_imgH;

	int partW = partial.m_imgW;
	int partH = partial.m_imgH;

	int x, y;
	int px, py;

	for (py = 0, y = sy; y < sy + partH; y++, py++) {
		if (y < 0 || y >= H) continue;

		for (px = 0, x = sx; x < sx + partW; x++, px++) {
			if (x < 0 || x >= W) continue;

			this->setImg(x, y, partial.m_imgData[px+py*partW]);
		}
	}

	return true;
}

bool CImagePNM::createClone8(CImagePNM &dst)
{
	// depthを確認
	if (this->m_iDepth != 8) return false;

	// メモリ確保
	if (!dst.create8(this->m_imgW, this->m_imgH)) return false;

	// コピー
	if (!dst.copyImg8(this->m_imgData)) return false;

	return true;
}