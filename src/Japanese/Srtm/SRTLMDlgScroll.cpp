
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* 本ソースコードは MIT License に基づき配布されています。
//*
//* 詳細については LICENSE ファイルを参照してください。


// SRTLM.cpp : アプリケーション用クラスの定義を行います。
//

#include "stdafx.h"
#include "SRTLM.h"
#include "SRTLMDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CSRTLMDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    // TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください

    switch(pScrollBar->GetDlgCtrlID())
    {
        case IDC_SPIN_LP_X:    //* Process scroll messages from IDC_SPIN_LP_X only
        {
            //* 20251116 (Ver.2.27.0) エディットボックスなどがフォーカスを握っていたら、そのフォーカスを外す
            SetFocus();

            if (nSBCode == SB_ENDSCROLL) {
                return; //* Reject spurious messages
            }

            int iPosition;
            iPosition = nPos;

            switch(m_bJujiRendou)
            {
                case true:
                {
                    double dRad_PG_Memori = m_dPintGlassMemori * KK_PI / 180.0;
                    m_dTLX[5] = m_dTLX[5] + double(iPosition - m_iLensPosXOld) / 10.0 * cos(dRad_PG_Memori);
                    m_dTLX[6] = m_dTLX[5];
                    m_dTLY[5] = m_dTLY[5] - double(iPosition - m_iLensPosXOld) / 10.0 * sin(dRad_PG_Memori);
                    m_dTLY[6] = m_dTLY[5];
                    if(m_bKeisyaRendou)    SRTLM_Keisya_Rendou();
                    break;
                }
                case false:
                {
                    m_dTLX[5] = m_dTLX[5] + double(iPosition - m_iLensPosXOld) / 10.0 ;
                    m_dTLX[6] = m_dTLX[5];
                    if(m_bKeisyaRendou)    SRTLM_Keisya_Rendou();
                    break;
                }
            }
            m_bSyokika = false;
            m_iLensPosXOld = iPosition;
            //*    MainProgram();
            Invalidate(FALSE);
            break;
        }
        case IDC_SPIN_TARGET_DPT:    //* Process scroll messages from IDC_SPIN_TARGET_DPT only
        {
            //* 20251116 (Ver.2.27.0) When the spin buttons are pressed, if the lens group edit boxes have focus, kill their focus.
            SetFocus();

            if (nSBCode == SB_ENDSCROLL) {
                return; //* Reject spurious messages
            }

            int iPosition;
            iPosition = nPos;

            m_dDpt = double(iPosition) / 100.0;

            Target(m_dDpt, &m_dObjZ);
            m_bSyokika = false;
            //*    MainProgram();
            Invalidate(FALSE);

            CSliderCtrl* pSlider_target_dpt = (CSliderCtrl*) GetDlgItem(IDC_SLIDER_TARGET_DPT);
            pSlider_target_dpt->SetPos(iPosition / 25);
            break;
        }
        case IDC_SPIN_PG_ROTATE:    //* Process scroll messages from IDC_SPIN_PG_ROTATE only
        {
            //* 20251116 (Ver.2.27.0) When the spin buttons are pressed, if the lens group edit boxes have focus, kill their focus.
            SetFocus();

            if (nSBCode == SB_ENDSCROLL) {
                return; //* Reject spurious messages
            }

            int iPosition;
            iPosition = nPos;

            m_dPintGlassBar = double(iPosition);
            Ax_Henkan(4, m_dPintGlassBar);

            if(m_bKeisyaRendou)    SRTLM_Keisya_Rendou();
            m_bSyokika = false;
            //*    MainProgram();
            Invalidate(FALSE);

            CSliderCtrl* pSlider_PG_rotate = (CSliderCtrl*) GetDlgItem(IDC_SLIDER_PG_ROTATE);
            pSlider_PG_rotate->SetPos(iPosition);
            break;
        }
        case IDC_SPIN_LENS_ROTATE:    //* Process scroll messages from IDC_SPIN_LENS_ROTATE only
        {
            //* 20251116 (Ver.2.27.0) When the spin buttons are pressed, if the lens group edit boxes have focus, kill their focus.
            SetFocus();

            if (nSBCode == SB_ENDSCROLL) {
                return; //* Reject spurious messages
            }

            int iPosition;
            iPosition = nPos;

            m_dCylTheta[5] = double(-iPosition);
            m_dAx_Hyouji = -m_dCylTheta[5];
            Ax_Henkan(1, m_dAx_Hyouji);
            Ax_Henkan(2, m_dCylTheta[5]);
            m_dCylTheta[6] = m_dCylTheta[5];

            //m_dAx2 = -m_dCylTheta[5];   //* 20251029 (Ver.2.26.0) Linked to [Lens Data] <- リンクさせない仕様に決定
            //Ax_Henkan(6, m_dAx2);       //* 20251029 (Ver.2.26.0) Linked to [Lens Data] <- リンクさせない仕様に決定

            if(m_bKeisyaRendou)    SRTLM_Keisya_Rendou();
            m_bSyokika = false;
            //*    MainProgram();
            Invalidate(FALSE);

            CSliderCtrl* pSlider_lens_rotate = (CSliderCtrl*) GetDlgItem(IDC_SLIDER_LENS_ROTATE);
            pSlider_lens_rotate->SetPos(iPosition);
            break;
        }
        case IDC_SPIN_L_TILT_X:    //* Process scroll messages from IDC_SPIN_L_TILT_X only
        {
            //* 20251116 (Ver.2.27.0) When the spin buttons are pressed, if the lens group edit boxes have focus, kill their focus.
            SetFocus();

            if (nSBCode == SB_ENDSCROLL) {
                return; //* Reject spurious messages
            }

            int iPosition;
            iPosition = nPos;

            m_dHenFai[5] = double(iPosition) / 10.0;
            m_dHenFai[6] = m_dHenFai[5];

            m_bSyokika = false;
            //*    MainProgram();
            Invalidate(FALSE);
            break;
        }
        case IDC_SLIDER_TARGET_DPT:    //* Process slider messages from IDC_SLIDER_TARGET_DPT only
        {
            if (nSBCode == SB_ENDSCROLL) {
            return; //* Reject spurious messages
            }

            int iPosition;
            iPosition = nPos;
//*            TRACE("mpos = %d\n", nPos);

            switch(nSBCode)
            {
                case 0:    //* SB_LINELEFT, SB_LINEUP(矢印キー: 左, 上)
                case 2:    //* SB_PAGELEFT, SB_PAGEDOWN(スライダーのつまみの左側の領域)
                {
                    iPosition = int(m_dDpt * 4.0) - 1;
                    CSliderCtrl* pSlider_target_dpt = (CSliderCtrl*) GetDlgItem(IDC_SLIDER_TARGET_DPT);
                    pSlider_target_dpt->SetPos(iPosition);
                    break;
                }
                case 1:    //* SB_LINERIGHT, SB_LINEDOWN(矢印キー: 右, 下)
                case 3:    //* SB_PAGERIGHT, SB_PAGEUP(スライダーのつまみの右側の領域)
                {
                    iPosition = int(m_dDpt * 4.0) + 1;
                    CSliderCtrl* pSlider_target_dpt = (CSliderCtrl*) GetDlgItem(IDC_SLIDER_TARGET_DPT);
                    pSlider_target_dpt->SetPos(iPosition);
                    break;
                }
            }
            m_dDpt = double(iPosition) / 4.0;

            Target(m_dDpt, &m_dObjZ);
            m_bSyokika = false;
            //*    MainProgram();
            Invalidate(FALSE);

            CSpinButtonCtrl* pSpin_target_dpt = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_TARGET_DPT);
            pSpin_target_dpt->SetPos(iPosition * 25);
            break;
        }
        case IDC_SLIDER_PG_ROTATE:    //* Process slider messages from IDC_SLIDER_PG_ROTATE only
        {
            if (nSBCode == SB_ENDSCROLL) {
                return; //* Reject spurious messages
            }

            int iPosition;
            iPosition = nPos;

            switch(nSBCode)
            {
                case 0:    //* SB_LINELEFT, SB_LINEUP(矢印キー: 左, 上)
                case 2:    //* SB_PAGELEFT, SB_PAGEDOWN(スライダーのつまみの左側の領域)
                {
                    iPosition = int(m_dPintGlassBar) - 5;
                    CSliderCtrl* pSlider_PG_rotate = (CSliderCtrl*) GetDlgItem(IDC_SLIDER_PG_ROTATE);
                    pSlider_PG_rotate->SetPos(iPosition);
                    break;
                }
                case 1:    //* SB_LINERIGHT, SB_LINEDOWN(矢印キー: 右, 下)
                case 3:    //* SB_PAGERIGHT, SB_PAGEUP(スライダーのつまみの右側の領域)
                {
                    iPosition = int(m_dPintGlassBar) + 5;
                    CSliderCtrl* pSlider_PG_rotate = (CSliderCtrl*) GetDlgItem(IDC_SLIDER_PG_ROTATE);
                    pSlider_PG_rotate->SetPos(iPosition);
                    break;
                }
            }

            m_dPintGlassBar = double(iPosition);
            Ax_Henkan(4, m_dPintGlassBar);

            if(m_bKeisyaRendou)    SRTLM_Keisya_Rendou();
            m_bSyokika = false;
            //*    MainProgram();
            Invalidate(FALSE);

            CSpinButtonCtrl* pSpin_PG_rotate = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_PG_ROTATE);
            pSpin_PG_rotate->SetPos(iPosition);
            break;
        }
        case IDC_SLIDER_LENS_ROTATE:    //* Process slider messages from IDC_SLIDER_LENS_ROTATE only
        {
            if (nSBCode == SB_ENDSCROLL) {
                return; //* Reject spurious messages
            }

            int iPosition;
            iPosition = nPos;

            switch(nSBCode)
            {
            case 0:    //* SB_LINELEFT, SB_LINEUP(矢印キー: 左, 上)
            case 2:    //* SB_PAGELEFT, SB_PAGEDOWN(スライダーのつまみの左側の領域)
            {
                iPosition = int(-m_dCylTheta[5]) - 5;
                CSliderCtrl* pSlider_lens_rotate = (CSliderCtrl*) GetDlgItem(IDC_SLIDER_LENS_ROTATE);
                pSlider_lens_rotate->SetPos(iPosition);
                break;
            }
            case 1:    //* SB_LINERIGHT, SB_LINEDOWN(矢印キー: 右, 下)
            case 3:    //* SB_PAGERIGHT, SB_PAGEUP(スライダーのつまみの右側の領域)
            {
                iPosition = int(-m_dCylTheta[5]) + 5;
                CSliderCtrl* pSlider_lens_rotate = (CSliderCtrl*) GetDlgItem(IDC_SLIDER_LENS_ROTATE);
                pSlider_lens_rotate->SetPos(iPosition);
                break;
            }
            }
            m_dCylTheta[5] = double(-iPosition);
            m_dAx_Hyouji = -m_dCylTheta[5];
            Ax_Henkan(1, m_dAx_Hyouji);
            Ax_Henkan(2, m_dCylTheta[5]);
            m_dCylTheta[6] = m_dCylTheta[5];

            //m_dAx2 = -m_dCylTheta[5];   //* 20251029 (Ver.2.26.0) Linked to [Lens Data] <- リンクさせない仕様に決定
            //Ax_Henkan(6, m_dAx2);       //* 20251029 (Ver.2.26.0) Linked to [Lens Data] <- リンクさせない仕様に決定

            if(m_bKeisyaRendou)    SRTLM_Keisya_Rendou();
            m_bSyokika = false;
            //*    MainProgram();
            Invalidate(FALSE);

            CSpinButtonCtrl* pSpin_lens_rotate = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_LENS_ROTATE);
            pSpin_lens_rotate->SetPos(iPosition);
            break;
        }
    }
        CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CSRTLMDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    //* TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください

    switch(pScrollBar->GetDlgCtrlID())
    {
        case IDC_SPIN_LP_Y:    //* Process scroll messages from IDC_SPIN_LP_Y only
        {
            //* 20251116 (Ver.2.27.0) When the spin buttons are pressed, if the lens group edit boxes have focus, kill their focus.
            SetFocus();

            if (nSBCode == SB_ENDSCROLL) {
                return; //* Reject spurious messages
            }

            int iPosition;
            iPosition = nPos;

            switch(m_bJujiRendou)
            {
            case true:
            {
                double dRad_PG_Memori = m_dPintGlassMemori * KK_PI / 180.0;
                m_dTLX[5] = m_dTLX[5] - double(iPosition - m_iLensPosYOld) / 10.0 * cos(dRad_PG_Memori + KK_PI / 2.0);
                m_dTLX[6] = m_dTLX[5];
                m_dTLY[5] = m_dTLY[5] + double(iPosition - m_iLensPosYOld) / 10.0 * sin(dRad_PG_Memori + KK_PI / 2.0);
                m_dTLY[6] = m_dTLY[5];
                if(m_bKeisyaRendou)    SRTLM_Keisya_Rendou();
                break;
            }
            case false:
            {
                m_dTLY[5] = m_dTLY[5] + double(iPosition - m_iLensPosYOld) / 10.0;
                m_dTLY[6] = m_dTLY[5];
                if(m_bKeisyaRendou)    SRTLM_Keisya_Rendou();
                break;
            }
            }
            m_bSyokika = false;
            m_iLensPosYOld = iPosition;
            //*    MainProgram();
            Invalidate(FALSE);
            break;
        }
        case IDC_SPIN_L_TILT_Y:    //* Process scroll messages from IDC_SPIN_L_TILT_Y only
        {
            //* 20251116 (Ver.2.27.0) When the spin buttons are pressed, if the lens group edit boxes have focus, kill their focus.
            SetFocus();

            if (nSBCode == SB_ENDSCROLL) {
                return; //* Reject spurious messages
            }

            int iPosition;
            iPosition = nPos;

            m_dHenTheta[5] = double(iPosition) / 10.0;
            m_dHenTheta[6] = m_dHenTheta[5];

            m_bSyokika = false;
            //*    MainProgram();
            Invalidate(FALSE);
            break;
        }
    }
    CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}



