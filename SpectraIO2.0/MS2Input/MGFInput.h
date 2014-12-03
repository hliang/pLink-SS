/*
 * MGFInput.h
 *
 *  Created on: 2009-7-13
 *      Author: fan
 */

//--------------------------------------------------------------
//              MGF�ļ���ʽ
//      ���ɵ������ļ�����ʼ��"BEGIN IONS",��ֹ��"END IONS"
//      ÿ���ļ�ͷ:TITLE,CHARGE and PEPMASS����������DTA��
//
//--------------------------------------------------------------

//------------------------------
//         class CMgfIO
//       ��MGF�ļ��Ķ�д��
//------------------------------

#ifndef MGFINPUT_H_
#define MGFINPUT_H_
#include "../../include/sdk.h"
#include "../../include/interface.h"
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include "SpecUtility.h"
#include <sys/stat.h>

using namespace std;

namespace proteomics_sdk {

class CMS2Input;
//class CMS2Info;

class CMGFInput :
	public CMS2Input{
public:
	CMGFInput();
	virtual ~CMGFInput();
//	virtual void WriteAll(string strPath, vector<CSpectrum> & S);
	virtual void LoadAll(string strPath, vector<CSpectrum> & S);
	virtual void StartLoad(string strPath, int & nTotal);
	virtual void LoadNext(CSpectrum & spec, int & idx);
	virtual void LoadPrev(CSpectrum & spec, int &idx) ;
	virtual void LoadNextBatch(int nNumber ,vector<CSpectrum> & S, int &idx);
	virtual void LoadSpec(CSpectrum & spec, string strTitle, int& nSpecNo);
	virtual vector<string> GetAllSpecName(int begin, int step, int num);
	virtual void EndLoad(void);

	/*virtual void StartWrite(string strPath);
	virtual void WriteNext(CSpectrum & spec);
	virtual void EndWrite(void);
	*/
	virtual MS2FormatType GetType(void) {return PFF_MGF;};

protected:
	void OpenInFile(string strFilePath);
	void CloseInFile(void);
	void ReadMGFHead(CSpectrum& spec);
	void ReadMZAndItensity(CSpectrum& spec, bool bAdmitBlank = false);
	bool GetLine(string& str, bool bAdmitBlank = false);
//	void OpenOutFile(string strFilePath);
//	void CloseOutFile(void);
	bool m_bMono;
//	void WriteSingleMGF(CSpectrum & spec);
	ifstream m_ifIn;
//	ofstream m_ofOut;
	string m_strInPath;
//	string m_strOutPath;
	int m_nInCount;
//	int m_nOutCount;
	size_t m_tMaxPeaksNum;
	int m_nTotal;

	////�����ļ�ͷ��CHARGE��Ϣ
	vector<int>  m_vCharge;//CHARGE�ĸ�������AND�ֿ�����2+ and 3+
	vector<int> m_vCurrCharge;//��ǰ��CHARGE
	bool m_bMissCharge;//��ÿ�����Ƿ�ȱʧCHARGE��ȱʧ����m_vCharge�е���Ŀ�,����ǰ�м�¼��m_strMissCharge�С�
	string m_buffString;//���ڼ�¼�����ĵ�һ����ͼ��Ŀ��
	string m_strMissCharge;
	CSpectrum m_specTemp;
	map<string, int> m_mapTitle2Loc;
	vector<int> m_vSpecLoc;
	////END�����ļ�ͷ��CHARGE��Ϣ

	void ReadFileHead();
	
	double m_lfLineCount;//��¼�����ڼ���
//	void WriteFloat(double lfNum, int precision = PRECISION);
};

}

#endif /* MGFINPUT_H_ */
