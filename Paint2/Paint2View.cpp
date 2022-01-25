
// Paint2View.cpp: CPaint2View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Paint2.h"
#endif

#include "Paint2Doc.h"
#include "Paint2View.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPaint2View

IMPLEMENT_DYNCREATE(CPaint2View, CView)

BEGIN_MESSAGE_MAP(CPaint2View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_LINE, &CPaint2View::OnLine)
	ON_UPDATE_COMMAND_UI(ID_LINE, &CPaint2View::OnUpdateLine)
	ON_COMMAND(ID_RECTANGLE, &CPaint2View::OnRectangle)
	ON_UPDATE_COMMAND_UI(ID_RECTANGLE, &CPaint2View::OnUpdateRectangle)
	ON_COMMAND(ID_FILL, &CPaint2View::OnFill)
	ON_UPDATE_COMMAND_UI(ID_FILL, &CPaint2View::OnUpdateFill)
	ON_COMMAND(ID_ELLIPSE, &CPaint2View::OnEllipse)
	ON_UPDATE_COMMAND_UI(ID_ELLIPSE, &CPaint2View::OnUpdateEllipse)
END_MESSAGE_MAP()

// CPaint2View 생성/소멸
typedef struct g_MyShape {
	CPoint g_ptStart;
	CPoint g_ptEnd;
	int g_nShape;
	BOOL g_bFill;
}g_MyShape;

g_MyShape MyShape;

std::vector<g_MyShape> g_ShapeList;



CPaint2View::CPaint2View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	MyShape.g_ptStart.x=0;
	MyShape.g_ptStart.y=0;
	MyShape.g_ptEnd.x = 0;
	MyShape.g_ptEnd.y=0;
	MyShape.g_nShape = 0;
	MyShape.g_bFill = FALSE;
	m_bDrag = FALSE;

}

CPaint2View::~CPaint2View()
{
}

BOOL CPaint2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CPaint2View 그리기

void CPaint2View::OnDraw(CDC* /*pDC*/)
{
	CPaint2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CPaint2View 인쇄

BOOL CPaint2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CPaint2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CPaint2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CPaint2View 진단

#ifdef _DEBUG
void CPaint2View::AssertValid() const
{
	CView::AssertValid();
}

void CPaint2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPaint2Doc* CPaint2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPaint2Doc)));
	return (CPaint2Doc*)m_pDocument;
}
#endif //_DEBUG


// CPaint2View 메시지 처리기


void CPaint2View::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.
	CBrush* OldBrush=NULL;
	CPen* OldPen=NULL;
	CBrush MyBrush(RGB(255, 0, 0));
	CPen MyPen(0, 10, RGB(255, 0, 0));

	for (int i = 0; i < g_ShapeList.size(); i++)
	{
		if (g_ShapeList[i].g_bFill)
		{
			OldBrush = dc.SelectObject(&MyBrush);
			OldPen = dc.SelectObject(&MyPen);
		}

		switch (g_ShapeList[i].g_nShape)
		{
		case 0:
			dc.MoveTo(g_ShapeList[i].g_ptStart);
			dc.LineTo(g_ShapeList[i].g_ptEnd);
			break;
		case 1:
			dc.Rectangle(g_ShapeList[i].g_ptStart.x, g_ShapeList[i].g_ptStart.y, g_ShapeList[i].g_ptEnd.x, g_ShapeList[i].g_ptEnd.y);
			break;
		case 2:
			dc.Ellipse(g_ShapeList[i].g_ptStart.x, g_ShapeList[i].g_ptStart.y, g_ShapeList[i].g_ptEnd.x, g_ShapeList[i].g_ptEnd.y);
			break;
		}

		if (g_ShapeList[i].g_bFill)
		{
			dc.SelectObject(OldBrush);
			dc.SelectObject(OldPen);
		}
	}
}


void CPaint2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	m_bDrag = TRUE;
	MyShape.g_ptStart = point;

	CView::OnLButtonDown(nFlags, point);
}


void CPaint2View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bDrag)
	{
		MyShape.g_ptEnd = point;
		RedrawWindow();
	}
	CView::OnMouseMove(nFlags, point);
}


void CPaint2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bDrag)
	{
		MyShape.g_ptEnd = point;
		g_ShapeList.push_back(MyShape);
		RedrawWindow();
		m_bDrag = FALSE;
	}
	CView::OnLButtonUp(nFlags, point);
}


void CPaint2View::OnLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	MyShape.g_nShape = 0;
}


void CPaint2View::OnUpdateLine(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (MyShape.g_nShape == 0)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
}


void CPaint2View::OnRectangle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	MyShape.g_nShape = 1;
}


void CPaint2View::OnUpdateRectangle(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (MyShape.g_nShape == 1)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
}


void CPaint2View::OnFill()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (MyShape.g_bFill)
	{
		MyShape.g_bFill = FALSE;
	}
	else
	{
		MyShape.g_bFill = TRUE;
	}
}


void CPaint2View::OnUpdateFill(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (MyShape.g_bFill)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
}


void CPaint2View::OnEllipse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	MyShape.g_nShape = 2;
}


void CPaint2View::OnUpdateEllipse(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (MyShape.g_nShape==2)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
}
