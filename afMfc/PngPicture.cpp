// PngPicture.cpp : ʵ���ļ�
//

#include "stdafx.h"

#include "PngPicture.h"


// CPngPicture

IMPLEMENT_DYNAMIC(CPngPicture, CStatic)

CPngPicture::CPngPicture()
{

}

CPngPicture::~CPngPicture()
{
}


BEGIN_MESSAGE_MAP(CPngPicture, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void CPngPicture::SetPictureID(UINT dwID)
{
	m_dwID = dwID;
	LoadImageFromResource(&m_imgPng,m_dwID,"PNG");

	if (m_imgPng.IsNull())
	{
		MessageBox(_T("û���سɹ�"));
		return;
	}
	if (m_imgPng.GetBPP() == 32) //ȷ�ϸ�ͼ�����Alphaͨ��
	{ 
		//CDC *pDC = GetDC();
		int i;
		int j;
		for (i=0; i<m_imgPng.GetWidth(); i++)
		{
			for (j=0; j<m_imgPng.GetHeight(); j++)
			{
				byte *pByte = (byte *)m_imgPng.GetPixelAddress(i, j);
				pByte[0] = pByte[0] * pByte[3] / 255;
				pByte[1] = pByte[1] * pByte[3] / 255;
				pByte[2] = pByte[2] * pByte[3] / 255;
			}
		}
		//m_imgPng.Draw(pDC->m_hDC,0,0);
		//ReleaseDC(pDC);
	}
}

BOOL CPngPicture::LoadImageFromResource(CImage *pImage, UINT nResID,LPCTSTR lpTyp)
{
	if ( pImage == NULL) 
		return false;
	pImage->Destroy();
	// ������Դ
	HRSRC hRsrc = ::FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(nResID), lpTyp);
	if (hRsrc == NULL) 
		return false;
	// ������Դ
	HGLOBAL hImgData = ::LoadResource(AfxGetResourceHandle(), hRsrc);
	if (hImgData == NULL)
	{
		::FreeResource(hImgData);
		return false;
	}
	// �����ڴ��е�ָ����Դ
	LPVOID lpVoid = ::LockResource(hImgData);
	LPSTREAM pStream = NULL;
	DWORD dwSize = ::SizeofResource(AfxGetResourceHandle(), hRsrc);
	HGLOBAL hNew = ::GlobalAlloc(GHND, dwSize);
	LPBYTE lpByte = (LPBYTE)::GlobalLock(hNew);
	::memcpy(lpByte, lpVoid, dwSize);
	// ����ڴ��е�ָ����Դ
	::GlobalUnlock(hNew);
	// ��ָ���ڴ洴��������
	HRESULT ht = ::CreateStreamOnHGlobal(hNew, TRUE, &pStream);
	if ( ht != S_OK )
	{
		GlobalFree(hNew);
	}
	else
	{
		// ����ͼƬ
		pImage->Load(pStream);
		GlobalFree(hNew);
	}
	// �ͷ���Դ
	::FreeResource(hImgData);
	return true;
}
// CPngPicture ��Ϣ�������




void CPngPicture::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CStatic::OnPaint()
	if (m_imgPng.IsNull()) return;

	m_imgPng.Draw(dc.m_hDC,0,0);
}
