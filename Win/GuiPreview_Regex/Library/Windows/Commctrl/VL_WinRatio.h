/*******************************************************************************
Vczh Library++ 2.0
Windows界面::数值
开发者：陈梓瀚

接口：
类：
  VL_WinScroll				：滚动条
  VL_WinTrack				：指示器
  VL_WinProgress			：进度条
函数：
*******************************************************************************/

#ifndef VL_WINRATIO
#define VL_WINRATIO

#include "..\VL_WinClass.h"
#include "commctrl.h"

namespace vl
{
	namespace windows
	{
		class VL_WinScroll : public VL_WinControl
		{
		protected:
			VInt					FLineSize;

			void					GetInfo(SCROLLINFO& Info);
			void					SetInfo(SCROLLINFO& Info);
		public:
			VL_WinScroll(VL_WinContainer* Parent , VBool Horizontal);
			~VL_WinScroll();
			LRESULT					ProcessMessage(UINT Message , WPARAM& wParam , LPARAM& lParam , VBool& CallDefaultProcedure);

			VE_NotifyEvent			OnScrollMin;
			VE_NotifyEvent			OnScrollMax;
			VE_NotifyEvent			OnPageDec;
			VE_NotifyEvent			OnPageInc;
			VE_NotifyEvent			OnArrowDec;
			VE_NotifyEvent			OnArrowInc;
			VE_NotifyEvent			OnTracking;
			VE_NotifyEvent			OnThumbUp;
			VE_NotifyEvent			OnPositionChanged;
			VE_NotifyEvent			OnEndScroll;

			VInt					GetMin();
			void					SetMin(VInt Value);

			VInt					GetMax();
			void					SetMax(VInt Value);

			VInt					GetLineSize();
			void					SetLineSize(VInt Value);

			VInt					GetPageSize();
			void					SetPageSize(VInt Value);

			VInt					GetPosition();
			void					SetPosition(VInt Value);
		};

		class VL_WinTrack : public VL_WinControl
		{
		protected:
			void					GetTickVisible(VBool& Top , VBool& Bottom);
			void					SetTickVisible(VBool Top , VBool Bottom);
		public:
			VL_WinTrack(VL_WinContainer* Parent , VBool Horizontal);
			~VL_WinTrack();
			LRESULT					ProcessMessage(UINT Message , WPARAM& wParam , LPARAM& lParam , VBool& CallDefaultProcedure);

			VE_NotifyEvent			OnScrollMin;
			VE_NotifyEvent			OnScrollMax;
			VE_NotifyEvent			OnPageDec;
			VE_NotifyEvent			OnPageInc;
			VE_NotifyEvent			OnArrowDec;
			VE_NotifyEvent			OnArrowInc;
			VE_NotifyEvent			OnTracking;
			VE_NotifyEvent			OnThumbUp;
			VE_NotifyEvent			OnPositionChanged;
			VE_NotifyEvent			OnEndScroll;

			VBool					GetShowLeftTopTick();
			void					SetShowLeftTopTick(VBool Value);

			VBool					GetShowRightBottomTick();
			void					SetShowRightBottomTick(VBool Value);

			VBool					GetEnableSelection();
			void					SetEnableSelection(VBool Value);

			VBool					GetAutoTicks();
			void					SetAutoTicks(VBool Value);

			VInt					GetMin();
			void					SetMin(VInt Value);

			VInt					GetMax();
			void					SetMax(VInt Value);

			VInt					GetLineSize();
			void					SetLineSize(VInt Value);

			VInt					GetPageSize();
			void					SetPageSize(VInt Value);

			VInt					GetPosition();
			void					SetPosition(VInt Value);

			VInt					GetSelStart();
			void					SetSelStart(VInt Value);

			VInt					GetSelEnd();
			void					SetSelEnd(VInt Value);

			void					ClearSelection();

			void					ClearTicks();
			VInt					GetTicksCount();
			void					GetAdditionalTicks(VL_List<VInt , true>& TickPos);
			VInt					GetTickPos(VInt Index);
			void					SetTick(VInt Position);
			void					BuildAutoTicks(VInt Value);
		};

		class VL_WinProgress : public VL_WinControl
		{
		protected:
			VBool					FMarqueeRunning;
			VInt					FMarqueeInterval;

			void					InternalSetMarquee();
		public:
			VL_WinProgress(VL_WinContainer* Parent , VBool Horizontal);
			~VL_WinProgress();

			VBool					GetMarquee();
			void					SetMarquee(VBool Value);

			VBool					GetSmooth();
			void					SetSmooth(VBool Value);

			VBool					GetSmoothReverse();
			void					SetSmoothReverse(VBool Value);

			COLORREF				GetBarColor();
			void					SetBarColor(COLORREF Value);

			COLORREF				GetBackColor();
			void					SetBackColor(COLORREF Value);

			VInt					GetPosition();
			void					SetPosition(VInt Value);

			VInt					GetMin();
			void					SetMin(VInt Value);

			VInt					GetMax();
			void					SetMax(VInt Value);

			VInt					GetStep();
			void					SetStep(VInt Value);

			VBool					GetMarqueeRunning();
			void					SetMarqueeRunning(VBool Value);

			VInt					GetMarqueeInterval();
			void					SetMarqueeInterval(VInt Value);
		};
	}
}

#endif