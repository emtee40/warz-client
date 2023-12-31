// CkCsv.h: interface for the CkCsv class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _CkCsv_H
#define _CkCsv_H



#include "CkString.h"
class CkByteData;
#include "CkMultiByteBase.h"

#ifndef __sun__
#pragma pack (push, 8)
#endif
 

// CLASS: CkCsv
class CkCsv  : public CkMultiByteBase
{
    private:
	// Don't allow assignment or copying these objects.
	CkCsv(const CkCsv &);
	CkCsv &operator=(const CkCsv &);

    public:

	CkCsv(void *impl);

	CkCsv();
	virtual ~CkCsv();

	// May be called when finished with the object to free/dispose of any
	// internal resources held by the object. 
	void dispose(void);

	// BEGIN PUBLIC INTERFACE


	// LOADFILE_BEGIN
	bool LoadFile(const char *path);
	// LOADFILE_END
	// SAVEFILE_BEGIN
	bool SaveFile(const char *path);
	// SAVEFILE_END
	// SAVEFILE2_BEGIN
	bool SaveFile2(const char *path, const char *charset);
	// SAVEFILE2_END
	// LOADFILE2_BEGIN
	bool LoadFile2(const char *path, const char *charset);
	// LOADFILE2_END
	// GETCELL_BEGIN
	bool GetCell(int row, int col, CkString &outStr);
	const char *getCell(int row, int col);
	// GETCELL_END
	// NUMROWS_BEGIN
	int get_NumRows(void);
	// NUMROWS_END
	// SETCELL_BEGIN
	bool SetCell(int row, int col, const char *content);
	// SETCELL_END
	// GETNUMCOLS_BEGIN
	int GetNumCols(int row);
	// GETNUMCOLS_END
	// DELIMITER_BEGIN
	void get_Delimiter(CkString &str);
	const char *delimiter(void);
	void put_Delimiter(const char *newVal);
	// DELIMITER_END
	// CRLF_BEGIN
	bool get_Crlf(void);
	void put_Crlf(bool newVal);
	// CRLF_END
	// HASCOLUMNNAMES_BEGIN
	bool get_HasColumnNames(void);
	void put_HasColumnNames(bool newVal);
	// HASCOLUMNNAMES_END
	// NUMCOLUMNS_BEGIN
	int get_NumColumns(void);
	// NUMCOLUMNS_END
	// GETINDEX_BEGIN
	int GetIndex(const char *columnName);
	// GETINDEX_END
	// GETCOLUMNNAME_BEGIN
	bool GetColumnName(int index, CkString &outStr);
	const char *getColumnName(int index);
	// GETCOLUMNNAME_END
	// LOADFROMSTRING_BEGIN
	bool LoadFromString(const char *csvData);
	// LOADFROMSTRING_END
	// SAVETOSTRING_BEGIN
	bool SaveToString(CkString &outStr);
	const char *saveToString(void);
	// SAVETOSTRING_END
	// SETCOLUMNNAME_BEGIN
	bool SetColumnName(int index, const char *columnName);
	// SETCOLUMNNAME_END

	// CSV_INSERT_POINT

	// END PUBLIC INTERFACE



};
#ifndef __sun__
#pragma pack (pop)
#endif



#endif


