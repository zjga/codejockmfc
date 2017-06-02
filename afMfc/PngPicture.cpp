// PngPicture.cpp : 实现文件
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
		MessageBox(_T("没加载成功"));
		return;
	}
	if (m_imgPng.GetBPP() == 32) //确认该图像包含Alpha通道
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
	// 查找资源
	HRSRC hRsrc = ::FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(nResID), lpTyp);
	if (hRsrc == NULL) 
		return false;
	// 加载资源
	HGLOBAL hImgData = ::LoadResource(AfxGetResourceHandle(), hRsrc);
	if (hImgData == NULL)
	{
		::FreeResource(hImgData);
		return false;
	}
	// 锁定内存中的指定资源
	LPVOID lpVoid = ::LockResource(hImgData);
	LPSTREAM pStream = NULL;
	DWORD dwSize = ::SizeofResource(AfxGetResourceHandle(), hRsrc);
	HGLOBAL hNew = ::GlobalAlloc(GHND, dwSize);
	LPBYTE lpByte = (LPBYTE)::GlobalLock(hNew);
	::memcpy(lpByte, lpVoid, dwSize);
	// 解除内存中的指定资源
	::GlobalUnlock(hNew);
	// 从指定内存创建流对象
	HRESULT ht = ::CreateStreamOnHGlobal(hNew, TRUE, &pStream);
	if ( ht != S_OK )
	{
		GlobalFree(hNew);
	}
	else
	{
		// 加载图片
		pImage->Load(pStream);
		GlobalFree(hNew);
	}
	// 释放资源
	::FreeResource(hImgData);
	return true;
}
// CPngPicture 消息处理程序




void CPngPicture::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CStatic::OnPaint()
	if (m_imgPng.IsNull()) return;

	m_imgPng.Draw(dc.m_hDC,0,0);
}
