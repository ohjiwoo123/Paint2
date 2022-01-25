# Paint2

## MFCPaint에서 변형
https://github.com/ohjiwoo123/MFCPaint  
MFCPaint에서 vector를 추가하여, 계속해서 선과 도형들이  
저장되게 만들어 놓았음.  

추가된 내용 핵심 
1. vector<T> ar;
2. 넣는 곳 : ON_WM_LBUTTONUP() -> push_back
3. 사용하는 곳 : ON_WM_PAINT() -> for (int i=0; g_ShapeList.Size();i++)
```
#include <vector>

typedef struct g_MyShape {
	CPoint g_ptStart;
	CPoint g_ptEnd;
	int g_nShape;
	BOOL g_bFill;
}g_MyShape;

g_MyShape MyShape;

std::vector<g_MyShape> g_ShapeList;
```
구조체로 값을 받아서 4가지 변수를 vector에 한 번에 넘겨준다.  
vector는 값을 계속 누적해서 받게 하여, 이전 도형의 기록을 계속해서 남긴다.  
