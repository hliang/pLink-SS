/*
 * MGFOutput.h
 *
 *  Created on: 2010-2-25
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

#ifndef MGFOUTPUT_H_
#define MGFOUTPUT_H_
#include "../../include/sdk.h"
#include "../../include/interface.h"
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include "../MS2Input/SpecUtility.h"

using namespace std;

namespace proteomics_sdk {

class CMS2Output;
//class CMS2Info;

class CMGFOutput :
	public CMS2Output{
public:
	CMGFOutput();
	virtual ~CMGFOutput();
//	virtual void WriteAll(string strPath, vector<CSpectrum> & S);
	virtual void WriteAll(string strPath, vector<CSpectrum> & S);
	virtual void StartWrite(string strPath, int & nTotal);
	virtual void WriteNext(CSpectrum & spec, int & idx);
	virtual void WriteNextBatch(int nNumber ,vector<CSpectrum> & S, int &idx);
	virtual void EndWrite(void);

	/*virtual void StartWrite(string strPath);
	virtual void WriteNext(CSpectrum & spec);
	virtual void EndWrite(void);
	*/
	virtual MS2FormatType GetType(void) {return PFF_MGF;};

protected:
	void OpenOutFile(string strFilePath);
	void CloseOutFile(void);
	void WriteMGFHead(CSpectrum& spec);
	void WriteMZAndItensity(CSpectrum& spec, bool bAdmitBlank = false);
//	bool GetLine(string& str, bool bAdmitBlank = false);
//	void OpenOutFile(string strFilePath);
//	void CloseOutFile(void);
	bool m_bMono;
//	void WriteSingleMGF(CSpectrum & spec);
	FILE * m_ofOut;
	ifstream m_ifIn;
//	ofstream m_ofOut;
	string m_strOutPath;
//	string m_strOutPath;
	int m_nOutCount;
//	int m_nOutCount;
	size_t m_tMaxPeaksNum;

	////�����ļ�ͷ��CHARGE��Ϣ
	vector<int>  m_vCharge;//CHARGE�ĸ�������AND�ֿ�����2+ and 3+
	vector<int> m_vCurrCharge;//��ǰ��CHARGE
	bool m_bMissCharge;//��ÿ�����Ƿ�ȱʧCHARGE��ȱʧ����m_vCharge�е���Ŀ�,����ǰ�м�¼��m_strMissCharge�С�
	string m_buffString;//���ڼ�¼�����ĵ�һ����ͼ��Ŀ��
	string m_strMissCharge;
	CSpectrum m_specTemp;
	////END�����ļ�ͷ��CHARGE��Ϣ

	void WriteFileHead();
	string GetTitle(CSpectrum& spec);
//	void WriteFloat(double lfNum, int precision = PRECISION);
};

}

#endif /* MGFINPUT_H_ */
