#pragma once

#include <time.h>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

//windowsのみ
//#include <Windows.h>

using namespace std;
#define MAX_PATH (1024)

class CStringName
{
public:
	CStringName(void);
	virtual ~CStringName(void);

	string	getPathName( string src );			//フルパスから、ファイル名、拡張子を除いたもの（GetFolderPathと同じ）/*c\abc\efg\hik.jpg -> c\abc\efg\ */
	string	getFolderPath( string path );		//フルパスから、ファイル名、拡張子を除いたもの（GetPathNameと同じ）  /*c\abc\efg\hik.jpg -> c\abc\efg\ */

	string	getFileName( string path );			//フルパスからパスを除いたもの		//c\abc\efg\hik.jpg -> hik.jpg
	string	getExtension( string path );		//拡張子のみを取出す（.はないよ）	//c\abc\efg\hik.jpg -> jpg
	string	extractPathWithoutExt( string fn );	//フルパスから、拡張子を抜いたもの	//c\abc\efg\hik.jpg -> c\abc\efg\hik

	string	extractFileName( string path, bool without_extension = true );	//フルパスから、パスと拡張子を除いたもの//c\abc\efg\hik.jpg ->hik
	string	extractFileName2( string path, int sno, int eno );//抜き出す範囲を指定、拡張子なし

	string	extractLastFolderName( string path );//フルパスから、最後のフォルダ名を返す	//c:\abc\efg\hik.jpg -> efg

	string	int2string( int Src, int digit );
	int		string2int( string src );
	bool	csv2strvec( string CSV, string delim, vector<string> *Dst );

	string	timeString( bool year = true, bool month = true, bool day = true, bool hour = true, bool min = true, bool sec = true );

	//string	getDirectoryPath(); // 関数の中身が入ってないため一旦、削除
};

