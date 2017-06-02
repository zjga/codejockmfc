#pragma once


// CPngPicture

class CPngPicture : public CStatic
{
	DECLARE_DYNAMIC(CPngPicture)

public:
	CPngPicture();
	virtual ~CPngPicture();

	void SetPictureID(UINT dwID);
private:
	BOOL LoadImageFromResource(CImage *pImage, UINT nResID,LPCTSTR lpTyp);
	UINT m_dwID;
	CImage m_imgPng;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


