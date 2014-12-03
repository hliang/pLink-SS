#ifndef PEPPAIRSORTER_H_
#define PEPPAIRSORTER_H_

#include <string>
#include <cfloat>
#include "../include/sdk.h"
using namespace std;
using namespace proteomics_sdk;

namespace proteomics_search {

class CPepPairSorter
{
public:
	CPepPairSorter();
	CPepPairSorter(string strFile, size_t tDataNum);
	virtual ~CPepPairSorter() {}

	void SetDataInfo(string strFile, size_t tDataNum);
	/* divide original file into several chunks, meanwhile sort them */
	virtual bool BatchDivision() = 0;
	/* merge all those chunks */
	virtual bool BatchMergeSort() = 0;
protected:
	/* file to read */
	string m_strFileName;
	/* how many elements */
	size_t m_tDataNum;
};

/* Written by Jeremy */
class CPepPairMoreWaySorter : public CPepPairSorter
{
public:
	CPepPairMoreWaySorter();
	CPepPairMoreWaySorter(string strFile, size_t tDataNum);
	virtual ~CPepPairMoreWaySorter();

	virtual bool BatchDivision();
	virtual bool BatchMergeSort();
private:
	vector<string> m_vTmpFileName;
	size_t m_tTmpFileNum;

	PEP_PAIR_ITEM *m_arrData;

	CTrace *m_pTrace;
#define MIN_MASS (-DBL_MAX)
#define MAX_MASS DBL_MAX
private:
	class LoserTree {
	public:
		LoserTree(const size_t tWay);
		~LoserTree();
		void ConnectToChunks(const vector<string> &vInFileName,
				const string &strOutFileName);
		void CreateLoserTree();
		void Merge();
	private:
		void _Adjust(int nItem);
	private:
		FILE **m_fpIn;
		FILE *m_fpOut;

		size_t m_tChunkNum; /* how many chunks to merge */
		PEP_PAIR_ITEM *m_arrBuf; /* m_tChunkNum+1 */
		int *m_nTree; /* the number of nodes is m_tChunkNum */
	};
};

/* Designed by Wu */
class CPepPairTwoWaySorter : public CPepPairSorter
{
public:
	CPepPairTwoWaySorter();
	CPepPairTwoWaySorter(string strFile, size_t tDataNum);
	virtual ~CPepPairTwoWaySorter();
	
	virtual bool BatchDivision();
	virtual bool BatchMergeSort();
private:
	void QuickSort_NoneRecursive();

	//�����������
	//��ȡ�����ļ�������ָ��������ļ�
	//���ļ���Ŀ��m_nTmpFileNum��¼
	//���ļ�����m_strTmpFileName�����¼
	//ÿ�����ļ���8Bdouble���������
	bool BatchReadFile();
	//���ļ�����=�����ļ�����+����ļ��鲢
	bool BatchSort();
	//���ս��鲢��ɵ��ļ���������ļ�
	bool BatchWriteFile();
	//��ʱ�ļ������ļ�ɾ��+���մ洢�ļ����Ŀռ�
	void ClearTmpFile();

	//���������ڵ�����
	int quicksort_part(int low,int high);
	void quicksort(int low,int high);
	void bubblesort(int low,int high);

private:
	char **m_strTmpFileName; //��ʱ�ļ���
	int m_nTmpFileNum; // ��ʱ�ļ�����

	PEP_PAIR_ITEM * m_Data; //���ݴ洢��
	size_t m_tCurDataNum;

	CTrace *m_pTrace;
};

}

#endif /*PEPPAIRSORTER_H_*/
