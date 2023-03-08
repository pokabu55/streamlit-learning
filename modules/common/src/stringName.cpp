//#include "StdAfx.h"
#include "stringName.hpp"

CStringName::CStringName(void)
{
}

CStringName::~CStringName(void)
{
}

string CStringName::getPathName( string path )
{
	//フルパスから、フォルダパスを取得

	size_t pos1;
 
    pos1 = path.rfind('\\');

    if ( pos1 != string::npos) {
        return path.substr( 0, pos1+1 );
    }
 
    pos1 = path.rfind('/');

    if (pos1 != string::npos) {
        return path.substr( 0, pos1+1 );
    }

    return "";
}

string CStringName::getFileName( string path )
{
	//パスからファイル名のみ取り出す

    size_t pos1;

    pos1 = path.rfind('\\');

    if(pos1 != string::npos) {
        return path.substr(pos1+1, path.size()-pos1-1);
    }

    pos1 = path.rfind('/');
    if(pos1 != string::npos) {
        return path.substr(pos1+1, path.size()-pos1-1);
    }

    return path;
}

string CStringName::getExtension( string path )
{
	//パスから拡張子を小文字にして取り出す

    string ext;
    size_t pos1 = path.rfind('.');

    if (pos1 != string::npos) {
        ext = path.substr( pos1+1, path.size()-pos1 );
        string::iterator itr = ext.begin();

        while (itr != ext.end()) {
            *itr = tolower( *itr );
            itr++;
        }

        itr = ext.end()-1;

		// パスの最後に\0やスペースがあったときの対策
        while (itr != ext.begin()) {
            if (*itr == 0 || *itr == 32) {
                ext.erase( itr-- );
            }
            else {
                itr--;
            }
        }
    }

    return ext;
}

string CStringName::extractPathWithoutExt( string fn )
{
	//ファイル名から拡張子を削除

    string::size_type pos;

    if ((pos = fn.find_last_of(".")) == string::npos) {
        return fn;
    }

    return fn.substr( 0, pos );
}

string CStringName::extractFileName( string path, bool without_extension )
{
	//ファイル名を抽出(拡張子を除くフラグ付き)

    string fn;
    string::size_type fpos;

    if ((fpos = path.find_last_of("/")) != string::npos) {
        fn = path.substr(fpos+1);
    }
    else if ((fpos = path.find_last_of("\\")) != string::npos) {
		fn = path.substr( fpos+1 );
	}
	else {
		fn = path;
	}

	if (without_extension && (fpos = fn.find_last_of(".")) != string::npos) {
		fn = fn.substr(0, fpos);
	}

	return fn;
}

string CStringName::getFolderPath( string path )
{
	size_t pos1;

    pos1 = path.rfind('\\');

	if (pos1 != string::npos) {
        return path.substr(0, pos1+1);
    }

    pos1 = path.rfind('/');
    if (pos1 != string::npos) {
        return path.substr(0, pos1+1);
    }

    return "";
}

string CStringName::extractLastFolderName( string path )
{
	//最後のフォルダ名を返す

	size_t len = path.length();
	size_t pos1 = path.rfind('\\');

    if (pos1 != string::npos) {
		//\\のほうです。

		path = path.substr( 0, len - (len-pos1) );

		len = path.length();
		pos1 = path.rfind( '\\');

		path = path.substr( pos1+1, len-pos1-1 );

		return path;
    }

    pos1 = path.rfind('/');

	if (pos1 != string::npos) {
		// '/'の方です。

		path = path.substr( 0, len - (len-pos1) );

		len = path.length();
		pos1 = path.rfind( '/');

		path = path.substr( pos1+1, len-pos1-1 );

		return path;
	}

    return "";
}

string CStringName::int2string( int Src, int digit )
{
	string ret = "";

	if( Src < 0 ) {
		return ret;
	}

	//入力値の桁数
	int SrcDigit = 0;

	int buf = Src;

	while (true) {
		buf /= 10;
		SrcDigit++;

		if (buf <= 0) break;
	};

	string num;
	stringstream ss;
	ss << Src;
	ss >> num;

	if (SrcDigit < digit) {
		int sub = digit - SrcDigit;

		for (int i = 0; i < sub; i++) {
			ret += "0";
		}
	}

	ret += num;

	return ret;
}

int CStringName::string2int( string src )
{
	int rt;
	stringstream ss;
	ss << src;
	ss >> rt;
	return rt;
}

bool CStringName::csv2strvec( string CSV, string delim, vector<string> *Dst )
{
	//string delim = ",";

	//デリミタを検索するインデクス番号
	string::size_type start = 0;

    while (true) {
        //デリミタが現れる最初のインデクスを求める
        string::size_type end = CSV.find(delim, start);

        if (end != string::npos) {
			//デリミタが見つかった場合
            Dst->push_back( CSV.substr(start, end - start) );
        }
        else {
            //文末までを格納して返す
            Dst->push_back( CSV.substr(start, CSV.length()-start) );
            break;
        }

        //次の開始地点へ移動
        start = end + delim.length();
    }

	return true;
}

string CStringName::timeString( bool year, bool month, bool day, bool hour, bool min, bool sec )
{
	string ret="";

	//time_t now = time(NULL);
	//struct tm *pnow = localtime(&now);

	struct tm *now;
    time_t longtime;
	longtime = time(NULL);

    //localtime_s(&now, &longtime);
	now = localtime(&longtime);

	stringstream ss;
	string sYear="", sMonth="", sDay="", sHour="", sMin="", sSec="";

	int buf;

	if (year) {
		//buf = pnow->tm_year + 1900;
		buf = now->tm_year + 1900;
		ss << buf;
		ss >> sYear;
		ss.clear();
	}

	if (month) {
		//buf = pnow->tm_mon + 1;
		buf = now->tm_mon + 1;

		if ( buf < 10) {
			ss << "0" << buf;
		} else {
			ss << buf;
		}

		ss >> sMonth;
		ss.clear();
	}

	if (day) {
		//buf  = pnow->tm_mday;
		buf  = now->tm_mday;

		if (buf < 10) {
			ss << "0" << buf;
		} else {
			ss << buf;
		}
		ss >> sDay;
		ss.clear();
	}

	if (hour) {
		//buf = pnow->tm_hour;
		buf = now->tm_hour;

		if (buf < 10) {
			ss << "0" << buf;
		} else {
			ss << buf;
		}
		ss >> sHour;
		ss.clear();
	}

	if (min) {
		buf  = now->tm_min;
		//buf  = now->tm_min;

		if (buf < 10) {
			ss << "0" << buf;
		}
		else {
			ss << buf;
		}
		ss >> sMin;
		ss.clear();
	}

	if (sec) {
		buf  = now->tm_sec;
		//buf  = now.tm_sec;

		if (buf < 10) {
			ss << "0" << buf;
		} else {
			ss << buf;
		}
		ss >> sSec;
		ss.clear();
	}

	ret = sYear + sMonth + sDay + "_" + sHour + sMin + sSec;

	return ret;
}

string CStringName::extractFileName2( string path, int sno, int eno )
{
	//ファイル名を抽出(拡張子を除くフラグ付き)

    string fn;
    string::size_type fpos;

    if ((fpos = path.find_last_of("/")) != string::npos) {
        fn = path.substr(fpos+1);
    }
    else if ((fpos = path.find_last_of("\\")) != string::npos) {
		fn = path.substr( fpos+1 );
	}
	else {
		fn = path;
	}

	if ((fpos = fn.find_last_of(".")) != string::npos) {
		fn = fn.substr(0, fpos);
	}

	//ファイル名を抜き出したら、指定の範囲を抜き出す
	fn = fn.substr( sno, eno );

	return fn;
}

#if 0
string CStringName::getDirectoryPath()
{
	string dirPath = "";

	char Path[MAX_PATH+1];

	char drive[MAX_PATH+1]
		,dir  [MAX_PATH+1]
		,fname[MAX_PATH+1]
		,ext  [MAX_PATH+1];

	if(0!=GetModuleFileName( NULL, Path, MAX_PATH )){// 実行ファイルの完全パスを取得

		_splitpath_s(Path,drive,dir,fname,ext);//パス名を構成要素に分解します

		/*printf("完全パス : %s\n",Path);
		printf("ドライブ : %s\n",drive);
		printf("ディレクトリ パス : %s\n",dir);
		printf("ベース ファイル名 (拡張子なし) : %s\n",fname);
		printf("ファイル名の拡張子 : %s\n",ext);

		dirPath = string(dir);*/
	}

	return dirPath;
}
#endif
