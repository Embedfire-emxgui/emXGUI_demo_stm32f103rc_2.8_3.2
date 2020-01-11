/*
 *GUI_DEMO_IconViewer.c
 *2018��3��17������7:41:26
 *
 */

#include "emXGUI.h"
 //#include	"rtthread.h"

#include "emXGUI_JPEG.h"
#include	"CListMenu.h"
#include "GUI_AppDef.h"


 /*============================================================================*/

#define	ID_EXIT		0x1000
//#define ICON_VIEWER_ID_PREV   0x1003
//#define	ICON_VIEWER_ID_NEXT		0x1004
#define	ID_RB1		0x1101
#define	ID_RB2		0x1102
#define	ID_RB3		0x1103
#define	ID_RB4		0x1104
#define	ID_RB5		0x1105
#define	ID_RB6		0x1106


//static int win_pos=0;
//static u8 hour,min,sec;
//static const WCHAR *pOEMText=NULL;
//static u8 List1_Col,List1_Row;

#define	ID_LIST_1 0x1000
#define ID_LIST_2 0x1001

//extern const char app_1[];

//static const void *pDefIcon = app_1;
//static const void *pIcon_app2 =app_2;

uint8_t Theme_Flag = 0;   // �����־
HWND	hwnd_home;

/*
*   Ӧ�ó���Ŀջص�����
*/
static void dummy(void *p)
{

}
//extern void GUI_DEMO_DrawJPEG(void);
//extern void App_LED_DIALOG(void);
//extern void App_GUI_Tutorial_DEMO(void);
//extern void	GUI_VideoPlayer_DIALOG(void);
//extern void GUI_AVIList_DIALOG(void);
//extern void GUI_DEMO_RectSpeed(void);
//extern void	GUI_RES_WRITER_DIALOG(void);
//extern void GUI_Boot_Interface_DIALOG(void);
//extern void	GUI_PicViewer_Dialog(void);
extern void GUI_LED_KEY_Dialog(void);
extern void	GUI_LED_DIALOG(void);
extern void GUI_ADC_CollectVoltage_Dialog(void);
extern void GUI_T_RH_Dialog(void);
extern void GUI_CLOCK_DIALOG(void);
extern void GUI_Beeper_Dialog(void);
extern void GUI_SMS_Dialog(void);
extern void GUI_Phone_Dialog(void);
extern void	GUI_App_Desktop(void);
//extern void GUI_SimulateUDisk_Dialog(void);
//extern void	GUI_Camera_DIALOG(void);

extern BOOL player_state;
int thread_ctrl = 1;

static const struct __obj_list menu_list_1[] = {
	    L"GUIӦ��",		  NULL, 	L"J", RGB_WHITE, GUI_App_Desktop,//dummy,//
      L"��ˮ��",		  NULL,	  L"L", RGB_WHITE, GUI_LED_DIALOG,//dummy,//GUI_LED_DIALOG
      L"��ѹ��",		  NULL,	  L"W", RGB_WHITE, GUI_ADC_CollectVoltage_Dialog,  
      L"��ʪ��",	    NULL,   L"O", RGB_WHITE, GUI_T_RH_Dialog,
	
      L"ʱ��",		    NULL,	  L"H", RGB_WHITE, GUI_CLOCK_DIALOG,
      L"������",      NULL,	  L"i", RGB_WHITE, GUI_Beeper_Dialog,
      L"�绰",	      NULL, 	L"T", RGB_WHITE, GUI_Phone_Dialog,
      L"����",	      NULL,   L"U", RGB_WHITE, GUI_SMS_Dialog,
			
      L"LED&KEY",     NULL,	  L"j", RGB_WHITE, GUI_LED_KEY_Dialog,

      NULL,	NULL,	NULL,NULL, NULL,//������־!

};


static void button_owner_draw(DRAWITEM_HDR *ds) //����һ����ť���
{
    HWND hwnd;
    HDC hdc;
    RECT rc, rc_temp;
    WCHAR wbuf[128];

    hwnd = ds->hwnd; //button�Ĵ��ھ��.
    hdc = ds->hDC;   //button�Ļ�ͼ�����ľ��.
    rc = ds->rc;     //button�Ļ��ƾ�����.
  
    if (Theme_Flag == 0) 
    {
//      GetClientRect(hwnd, &rc_temp);//�õ��ؼ���λ��
//      WindowToScreen(hwnd, (POINT *)&rc_temp, 1);//����ת��
//      BitBlt(hdc, rc.x, rc.y, rc.w, rc.h, hdc_home_bk, rc_temp.x, rc_temp.y, SRCCOPY);
//      BitBlt(hdc, rc.x, rc.y, rc.w, rc.h, hdc, rc_temp.x, rc_temp.y, SRCCOPY);
			SetBrushColor(hdc, MapRGB(hdc, COLOR_DESKTOP_BACK_GROUND2));
      FillRect(hdc, &rc); //�þ�����䱳��
    }
    else if (Theme_Flag == 1)
    {
      SetBrushColor(hdc, MapRGB(hdc, COLOR_DESKTOP_BACK_GROUND));
      FillRect(hdc, &rc); //�þ�����䱳��
    }
    else
    {
      SetBrushColor(hdc, MapRGB(hdc, COLOR_DESKTOP_BACK_GROUND));
      FillRect(hdc, &rc); //�þ�����䱳��
    }

    

    if (IsWindowEnabled(hwnd) == FALSE)
    {
        SetTextColor(hdc, MapRGB(hdc, COLOR_INVALID));
    }
    else if (ds->State & BST_PUSHED)
    { //��ť�ǰ���״̬
  //    GUI_DEBUG("ds->ID=%d,BST_PUSHED",ds->ID);
  //		SetBrushColor(hdc,MapRGB(hdc,150,200,250)); //�������ɫ(BrushColor��������Fill���͵Ļ�ͼ����)
  //		SetPenColor(hdc,MapRGB(hdc,250,0,0));        //���û���ɫ(PenColor��������Draw���͵Ļ�ͼ����)
        SetTextColor(hdc, MapRGB(hdc, 105, 105, 105));      //��������ɫ
    }
    else
    { //��ť�ǵ���״̬
  //		SetBrushColor(hdc,MapRGB(hdc,255,255,255));
  //		SetPenColor(hdc,MapRGB(hdc,0,250,0));
        SetTextColor(hdc, MapRGB(hdc, 255, 255, 255));
    }


    //	SetBrushColor(hdc,COLOR_BACK_GROUND);

    //	FillRect(hdc,&rc); //�þ�����䱳��
    //	DrawRect(hdc,&rc); //���������
    //  
    //  FillCircle(hdc,rc.x+rc.w/2,rc.x+rc.w/2,rc.w/2); //�þ�����䱳��FillCircle
    //	DrawCircle(hdc,rc.x+rc.w/2,rc.x+rc.w/2,rc.w/2); //���������

      /* ʹ�ÿ���ͼ������ */
    SetFont(hdc, controlFont_32);
    //  SetTextColor(hdc,MapRGB(hdc,255,255,255));

    GetWindowText(ds->hwnd, wbuf, 128); //��ð�ť�ؼ�������

    DrawText(hdc, wbuf, -1, &rc, DT_VCENTER | DT_CENTER);//��������(���ж��뷽ʽ)


    /* �ָ�Ĭ������ */
    SetFont(hdc, defaultFont);

}


static	LRESULT	WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HWND wnd;
    switch (msg)
    {
    case WM_CREATE:
    {
        list_menu_cfg_t cfg;
        RECT rc;
        HWND chwnd;

        //			win_pos =0;
        //			GetTime(&hour,&min,&sec);

        GetClientRect(hwnd, &rc);

        //			rc.x =0;
        //			rc.y =0;
        //			rc.w =rc0.w;
        //			rc.h =200;

              //ListMenu�ؼ�����Ҫ�ڴ���ʱ����һ�� list_menu_cfg_t �Ľṹ�����.
        cfg.list_objs = menu_list_1; //ָ��list�б�.
        cfg.x_num = 4; //ˮƽ����.
        cfg.y_num = 3; //��ֱ����.
			  if (Theme_Flag == 0)
				{
					cfg.bg_color = 1;    // Ϊ 1 ʱ��ʹ�������ɫ��Ϊ����ɫ
				}
				else 
				{
					cfg.bg_color = COLOR_DESKTOP_BACK_GROUND_HEX;    // Ϊ 1 ʱ��ʹ�������ɫ��Ϊ����ɫ
				}

        chwnd = CreateWindow(&wcex_ListMenu,
                                L"ListMenu1",
                                WS_VISIBLE | LMS_PAGEMOVE,
                                rc.x + 30, rc.y + 10
                                , rc.w - 60, rc.h - 10,
                                hwnd,
                                ID_LIST_1,
                                NULL,
                                &cfg);                                

        ///* ��һ����ť */
        wnd = CreateWindow(BUTTON, L"L", BS_FLAT | BS_NOTIFY | WS_OWNERDRAW | WS_VISIBLE,
            2, (rc.h) / 2, 30, 30, hwnd, ICON_VIEWER_ID_PREV, NULL, NULL);
        SetWindowFont(wnd, controlFont_32); //���ÿؼ���������.

         /* ��һ����ť */
        wnd = CreateWindow(BUTTON, L"K", BS_FLAT | BS_NOTIFY | WS_OWNERDRAW | WS_VISIBLE,
            rc.w - 30, (rc.h ) / 2, 30, 30, hwnd, ICON_VIEWER_ID_NEXT, NULL, NULL);
        SetWindowFont(wnd, controlFont_32); //���ÿؼ���������.

        SetTimer(hwnd, 1, 50, TMR_START, NULL);
    }
    break;
    ////

    case WM_NOTIFY:
    {
        u16 code, id;
        LM_NMHDR *nm;

        code = HIWORD(wParam);
        id = LOWORD(wParam);

        nm = (LM_NMHDR*)lParam;

        if (code == LMN_CLICKED)
        {
            switch (id)
            {
            case ID_LIST_1:
                menu_list_1[nm->idx].cbStartup(hwnd);
                break;
                ////
            case ID_LIST_2:
                //					menu_list_2[nm->idx].cbStartup(hwnd);
                break;
                ////
            }

        }
        ////
        if (code == BN_CLICKED && id == ICON_VIEWER_ID_PREV)
        {
            SendMessage(GetDlgItem(hwnd, ID_LIST_1), MSG_MOVE_PREV, TRUE, 0);
        }
        ////
        if (code == BN_CLICKED && id == ICON_VIEWER_ID_NEXT)
        {
            SendMessage(GetDlgItem(hwnd, ID_LIST_1), MSG_MOVE_NEXT, TRUE, 0);
        }

    }
    break;
    ////

    case WM_ERASEBKGND:
    {
      HDC hdc = (HDC)wParam;
      RECT rc = {0, 0, GUI_XSIZE, GUI_YSIZE};

      if (Theme_Flag == 0) 
      {
//          BitBlt(hdc, rc.x, rc.y, rc.w, rc.h, hdc_home_bk, rc.x, rc.y, SRCCOPY);
//          BitBlt(hdc, rc.x, rc.y, rc.w, rc.h, hdc, rc.x, rc.y, SRCCOPY);
				  GetClientRect(hwnd, &rc);
          SetBrushColor(hdc, MapRGB(hdc, COLOR_DESKTOP_BACK_GROUND2));
          FillRect(hdc, &rc);
      }
      else if (Theme_Flag == 1)
      {
          GetClientRect(hwnd, &rc);
          SetBrushColor(hdc, MapRGB(hdc, COLOR_DESKTOP_BACK_GROUND));
          FillRect(hdc, &rc);
      }
      else
      {
          GetClientRect(hwnd, &rc);
          SetBrushColor(hdc, MapRGB(hdc, 100, 100, 100));
          FillRect(hdc, &rc);
      }
    }
    return FALSE;

    case WM_PAINT:
    {
        //			HDC hdc;
        PAINTSTRUCT ps;
        //			RECT rc;
        //			WCHAR wbuf[128];

        BeginPaint(hwnd, &ps);

        EndPaint(hwnd, &ps);
        ////

    }
    break;
    ////
#if 1    
    case	WM_DRAWITEM:
    {
        /*�����ؼ�ָ����WS_OWNERDRAW�����ÿ���ڻ���ǰ����������ڷ���WM_DRAWITEM��Ϣ��
         *  wParam����ָ���˷��͸���Ϣ�Ŀؼ�ID;lParam����ָ��һ��DRAWITEM_HDR�Ľṹ��ָ�룬
         *  ��ָ���Ա������һЩ�ؼ�������صĲ���.
         */

        DRAWITEM_HDR *ds;

        ds = (DRAWITEM_HDR*)lParam;

        button_owner_draw(ds); //ִ���Ի��ư�ť

      //			if(ds->ID == ICON_VIEWER_ID_PREV)
      //			{
      //				button_owner_draw(ds); //ִ���Ի��ư�ť
      //			}
      //      else if(ds->ID == ICON_VIEWER_ID_NEXT)
      //      {
      //        button_owner_draw(ds); //ִ���Ի��ư�ť
      //      }

         /* ����TRUE����ʹ���ػ���� */
        return TRUE;
    }
    //		break;
#else


    case WM_CTLCOLOR:
    {
        u16 id;

        id = LOWORD(wParam);

        if (id == ICON_VIEWER_ID_PREV || id == ICON_VIEWER_ID_NEXT)
        {
            CTLCOLOR *cr;
            cr = (CTLCOLOR*)lParam;

            if (IsWindowEnabled(GetDlgItem(hwnd, id)) == FALSE)
            {
                cr->TextColor = RGB888_COLOR_INVALID;
                cr->BackColor = RGB888_COLOR_DESKTOP_BACK_GROUND;
                cr->BorderColor = RGB888_COLOR_DESKTOP_BACK_GROUND;
                GUI_DEBUG("disable");
                //          cr->ForeColor = RGB888(255,255,255);
            }
            else if (SendMessage(GetDlgItem(hwnd, id), BM_GETSTATE, 0, 0)&BST_PUSHED)
            {
                cr->TextColor = RGB888(255, 0, 0);
                cr->BackColor = RGB888_COLOR_DESKTOP_BACK_GROUND;
                cr->BorderColor = RGB888_COLOR_DESKTOP_BACK_GROUND;
            }
            else
            {
                cr->TextColor = RGB888(255, 255, 255);
                cr->BackColor = RGB888_COLOR_DESKTOP_BACK_GROUND;
                cr->BorderColor = RGB888_COLOR_DESKTOP_BACK_GROUND;
            }
            return TRUE;
        }
        else
        {
            //������ťʹ��ϵͳĬ�ϵ���ɫ���л��ƣ�����ֱ�ӷ���FALSE.
            return FALSE;
        }
    }
#endif
    //    break;

    case WM_LBUTTONDOWN:
    {
    }
    break;
    ////

    case WM_TIMER:
    {
    }
    break;
    ////

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);


    }
    return WM_NULL;

}


/*============================================================================*/

void	GUI_Board_App_Desktop(void *p)
{
    WNDCLASS	wcex;
    MSG msg;

    /////
    wcex.Tag = WNDCLASS_TAG;

    wcex.Style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WinProc; //������������Ϣ����Ļص�����.
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = NULL;//hInst;
    wcex.hIcon = NULL;//LoadIcon(hInstance, (LPCTSTR)IDI_WIN32_APP_TEST);
    wcex.hCursor = NULL;//LoadCursor(NULL, IDC_ARROW);

    //����������
    hwnd_home = CreateWindowEx(WS_EX_FRAMEBUFFER,//
        &wcex,
        L"IconViewer",
        //								/*WS_MEMSURFACE|*/WS_CAPTION|WS_DLGFRAME|WS_BORDER|WS_CLIPCHILDREN,
        /*WS_MEMSURFACE|*/WS_CLIPCHILDREN,

        0, 0, GUI_XSIZE, GUI_YSIZE-HEAD_INFO_HEIGHT,
        NULL, NULL, NULL, NULL);//GetDesktopWindow()

    //��ʾ������
    ShowWindow(hwnd_home, SW_SHOW);

    //��ʼ������Ϣѭ��(���ڹرղ�����ʱ,GetMessage������FALSE,�˳�����Ϣѭ��)��
    while (GetMessage(&msg, hwnd_home))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
}


/*============================================================================*/
