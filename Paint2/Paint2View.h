
// Paint2View.h: CPaint2View 클래스의 인터페이스
//

#pragma once


class CPaint2View : public CView
{
protected: // serialization에서만 만들어집니다.
	CPaint2View() noexcept;
	DECLARE_DYNCREATE(CPaint2View)

// 특성입니다.
public:
	CPaint2Doc* GetDocument() const;

// 작업입니다.
public:

	BOOL m_bDrag;
	enum Shape_Name;

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CPaint2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLine();
	afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
	afx_msg void OnRectangle();
	afx_msg void OnUpdateRectangle(CCmdUI* pCmdUI);
	afx_msg void OnFill();
	afx_msg void OnUpdateFill(CCmdUI* pCmdUI);
	afx_msg void OnEllipse();
	afx_msg void OnUpdateEllipse(CCmdUI* pCmdUI);
};

#ifndef _DEBUG  // Paint2View.cpp의 디버그 버전
inline CPaint2Doc* CPaint2View::GetDocument() const
   { return reinterpret_cast<CPaint2Doc*>(m_pDocument); }
#endif

