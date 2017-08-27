#include "stdafx.h"
#include "PageMaking.h"
#include "utility/FileHelper.h"
#include "utility/WinFile.h"

CPageMaking::CPageMaking()
{
	wcscpy_s(PATH_STATE_1[0].nameOfPath, L"�����ļ�");
	wcscpy_s(PATH_STATE_1[1].nameOfPath, L"����ļ�");
	wcscpy_s(PATH_STATE_1[2].nameOfPath, L"���·��");
	PATH_STATE_1[0].isInited = false;
	PATH_STATE_1[1].isInited = false;
	PATH_STATE_1[2].isInited = false;
	
	P1_Line1 = NULL;
	P1_Line2 = NULL;
	P1_Line3 = NULL;
	m_wndHighlight = NULL;
	
	emptyTip1= NULL;

	m_EditMusic   = NULL;
	m_EditLyric   = NULL;
	m_EditOutPath = NULL;

	m_txtMusic = NULL;
	m_txtLyric = NULL;
	
	m_txtTime = NULL;
	m_ProgressTime = NULL;

	m_btnStart = NULL;
	m_btnPreview = NULL;
	m_btnOpenOutput = NULL;
	m_btnLoad = NULL;
	m_btnRestart= NULL;
}

//��ʼ������ҳ��
void CPageMaking::Init(SHostWnd *pMainWnd)
{
	SASSERT(NULL != pMainWnd);

	//���������ڶ���
	m_pMainWnd = pMainWnd;

	//��ô����г��õĿؼ���ָ��
	P1_Line1 = M()->FindChildByID2<SStatic>(R.id.name_1_line_1);
	SASSERT(P1_Line1 != NULL);
	P1_Line2 = M()->FindChildByID2<SStatic>(65000);
	SASSERT(P1_Line2 != NULL);
	P1_Line3 = M()->FindChildByID2<SStatic>(R.id.name_1_line_3);
	SASSERT(P1_Line3 != NULL);
	m_wndHighlight = m_pMainWnd->FindChildByID(R.id.highlight_bkgnd);
	SASSERT(m_wndHighlight != NULL);

	emptyTip1 = M()->FindChildByID2<SStatic>(R.id.empty_tip_block);
	SASSERT(emptyTip1 != NULL);

	
	m_EditMusic = m_pMainWnd->FindChildByID2<SEdit>(R.id.edit_music_1);
	SASSERT(m_EditMusic != NULL);
	m_EditLyric = m_pMainWnd->FindChildByID2<SEdit>(R.id.edit_lyric_1);
	SASSERT(m_EditLyric != NULL);
	m_EditOutPath = m_pMainWnd->FindChildByID2<SEdit>(R.id.edit_output);
	SASSERT(m_EditOutPath != NULL);

	m_txtMusic = m_pMainWnd->FindChildByID2<SStatic>(R.id.line_music_1);
	SASSERT(m_txtMusic != NULL);
	m_txtLyric = m_pMainWnd->FindChildByID2<SStatic>(R.id.line_lyric_1);
	SASSERT(m_txtLyric != NULL);

	m_txtTime = m_pMainWnd->FindChildByID2<SStatic>(R.id.text_time_1);
	SASSERT(m_txtTime != NULL);
	m_ProgressTime = m_pMainWnd->FindChildByID2<SProgress>(R.id.progress_music_1);
	SASSERT(m_ProgressTime != NULL);

	m_btnStart = m_pMainWnd->FindChildByID2<SButton>(R.id.btn_start_making);
	SASSERT(m_btnStart != NULL);
	m_btnPreview = m_pMainWnd->FindChildByID2<SButton>(R.id.btn_preview);
	SASSERT(m_btnPreview != NULL);
	m_btnOpenOutput = m_pMainWnd->FindChildByID2<SButton>(R.id.btn_open_output);
	SASSERT(m_btnOpenOutput != NULL);
	m_btnLoad = m_pMainWnd->FindChildByID2<SButton>(R.id.btn_load_1);
	SASSERT(m_btnLoad != NULL);
	m_btnRestart = m_pMainWnd->FindChildByID2<SButton>(R.id.btn_restart);
	SASSERT(m_btnRestart != NULL);
}

//��������ڶ���
CMainDlg* CPageMaking::M()
{
	return (CMainDlg*)m_pMainWnd;
}

/*
*	�������ҳ�����Ӧ����
*/

//����·����ѡ��
void CPageMaking::OnBtnSelectMusic1()
{
	CBrowseDlg Browser;
	BOOL bRet = Browser.DoFileBrowse(
		::GetActiveWindow(),
		L"��Ƶ�ļ�(mp3,mp2,wma,wav,wv,ape,flac)\0*.mp3;*.mp2;*.wma;*.wav;*.wv;*.ape;*.flac;\0�ֻ�¼��(amr)/�ֻ�����(mmf)\0*amr;*.mmf\0\0",
		FileHelper::CheckFolderExist(M()->m_settingPage.m_default_music_path)? M()->m_settingPage.m_default_music_path.c_str():nullptr
		);

	if(bRet == TRUE)
	{
		if( CFileDialogEx::checkPathName(_T("*.mp3"),Browser.GetFilePath()) 
		 || CFileDialogEx::checkPathName(_T("*.mp2"),Browser.GetFilePath())
		 || CFileDialogEx::checkPathName(_T("*.wma"),Browser.GetFilePath())
		 || CFileDialogEx::checkPathName(_T("*.wav"),Browser.GetFilePath())
		 || CFileDialogEx::checkPathName(_T("*.wv"),Browser.GetFilePath())
		 || CFileDialogEx::checkPathName(_T("*.ape"),Browser.GetFilePath())
		 || CFileDialogEx::checkPathName(_T("*.flac"),Browser.GetFilePath())
		 || CFileDialogEx::checkPathName(_T("*.amr"),Browser.GetFilePath())
		 || CFileDialogEx::checkPathName(_T("*.mmf"),Browser.GetFilePath()))
		{	
			; //ʹ�á��������ж�( || )�� ���á��ҡ������жϣ�&&�����Լ��� checkPathName ���õĴ���
		}
		else 
		{
			_MessageBox(M()->m_hWnd,_T("��ʽ��֧��\\n��ȷ���ļ���ʽΪ��ѡ��Ի���ָ�����ļ����͡�"),_T("��ʾ"),MB_OK|MB_ICONINFORMATION);
			return;
		}

		//��ʾ��ѡ����ļ�
		m_EditMusic->SetWindowTextW(Browser.GetFilePath());

		PATH_STATE_1[0].isInited = true;

		//������������
		M()->maker.setMusicPath(Browser.GetFilePath(),M()->m_hWnd);
	}
}

void CPageMaking::OnBtnSelectLyric1()
{
	CBrowseDlg Browser;
	BOOL bRet = Browser.DoFileBrowse(
		::GetActiveWindow(),
		L"�ı��ļ�(*.txt)\0*.txt\0\0",
		FileHelper::CheckFolderExist(M()->m_settingPage.m_default_lyric_path)? M()->m_settingPage.m_default_lyric_path.c_str():nullptr
		);

	if(bRet == TRUE)
	{
		if(!CFileDialogEx::checkPathName(_T("*.txt"),Browser.GetFilePath()))
		{
			_MessageBox(M()->m_hWnd,_T("��ʽ��֧��\\n��ȷ���ļ���ʽΪ��*.txt��"),_T("��ʾ"),MB_OK|MB_ICONINFORMATION);
			return;
		}
		
		//��ʾ��ѡ����ļ�
		m_EditLyric->SetWindowTextW(Browser.GetFilePath());
		
		PATH_STATE_1[1].isInited = true;
		
		//������������
		M()->maker.setLyricPath(Browser.GetFilePath());
	}
}

void CPageMaking::OnBtnSelectOutput()
{
	CBrowseDlg Browser;
	BOOL bRet = Browser.DoDirBrowse(::GetActiveWindow(),_T("ѡ�� ��LRC����ļ��� Ĭ�����·��"), TRUE,M()->m_settingPage.m_default_output_path.c_str());
	if(bRet == TRUE)
	{
		if(!CFileDialogEx::checkPathName(_T(".."),Browser.GetDirPath()))
		{
			_MessageBox(M()->m_hWnd,_T("��ʽ��֧��\\n��ȷ����ѡ���ļ��С�"),_T("��ʾ"),MB_OK|MB_ICONINFORMATION);
			return;
		}

		//��ʾ��ѡ����ļ�
		m_EditOutPath->SetWindowTextW(Browser.GetDirPath());
		
		PATH_STATE_1[2].isInited = true;
		
		//������������
		M()->maker.setm_szOutputPath(Browser.GetDirPath());
	}
    
}

//������ʣ����� (��ʼ�� LyricMaker)
void CPageMaking::OnBtnLoad1()
{
	//ȷ������·�������ݶ��Ѿ���ʼ��
	if(!isPathReady_1())
	{
		//CMainDlg::getPathNotReady_1() ��ʱ���ص����� δ��ʼ����·�� �� PATH_STATE �ж�Ӧ���±�
		_MessageBox(M()->m_hWnd,SStringT().Format(_T("����ûѡ��%s��"),PATH_STATE_1[getPathNotReady_1()].nameOfPath),
			_T("��ʾ"),MB_OK|MB_ICONASTERISK);
		return;
	}

	//ȷ�� ����ļ� �� �����ļ���Ч
	File lyricFile(M()->maker.m_szLyricPathName,_T("r"));

	if(!lyricFile.isValidFile()) 
	{
		_MessageBox(M()->m_hWnd,SStringT().Format(_T("�ļ���ʧ��:\\n��%s��\\n!��ȷ���ļ���Ч"),M()->maker.m_szLyricPathName),
			_T("ʧ����ʾ"),MB_OK|MB_ICONWARNING);
		return;
	}

	//���� ҳ��� ��ǰ���� �� ��ǰ��ʵ���Ϣ
	m_txtMusic->SetWindowTextW(M()->maker.m_szMusicPathName);
	m_txtLyric->SetWindowTextW(M()->maker.m_szLyricPathName);
	
	//���� LyricMaker�� �������Ϊ��
	M()->maker.reloadMaker();

	//���ļ���ȡÿһ�еĸ��
	M()->maker.m_vLyricOrigin = M()->maker.getLyricOrigin(lyricFile);
	 
	//��ȡ��ϣ������ʾ��壬��ʾ��һ���ǿո��
	P1_Line1->SetWindowTextW(_T(""));
	P1_Line2->SetWindowTextW(_T(""));
	P1_Line3->SetWindowTextW(M()->maker.m_vLyricOrigin[0]);

	//�ı䰴ť��״̬
	m_btnStart->EnableWindow(TRUE,TRUE); //��һ������bEnableΪ �Ƿ����ã��ڶ�������bUpdateΪ�Ƿ��ڸı�״̬�������ʾ
	//m_btnStart->Invalidate();			//���û��ָ���ڶ�������bUpdate����Ĭ��ֵΪ FALSE��Ҫˢ������Ҫ�Լ�Invalidate()
	
	//�ı�Ԥ����ť��״̬
	m_btnPreview->EnableWindow(FALSE,TRUE);
	m_btnOpenOutput->EnableWindow(FALSE,TRUE);
}

//����Ԥ���ո�������ɵĴ�ʱ��ʱ������
void CPageMaking::OnBtnPreview()
{
	//�л���Ԥ��ҳ��
	STabCtrl* tab = M()->FindChildByID2<STabCtrl>(R.id.tab_main);
	if(tab)
		tab->SetCurSel(1);

	Sleep(500);

	//����player��״̬
	M()->player.setMusicPath(M()->maker.m_szMusicPathName,M()->m_hWnd);
	M()->player.setLyricPath(M()->maker.m_szOutputPathName);
	
	M()->m_pageResult->PATH_STATE_2[0].isInited = true;
	M()->m_pageResult->PATH_STATE_2[1].isInited = true;

	//����ҳ�� ·�������͵�ǰѡ������ֺ͸�ʣ�������׼��������֮���״̬��
	//��ʾ��ѡ����ļ�
	M()->m_pageResult->m_EditMusic->SetWindowTextW(M()->player.m_szMusicPathName);
	//��ʾ��ѡ����ļ�
	M()->m_pageResult->m_EditLyric->SetWindowTextW(M()->player.m_szLyricPathName);


	M()->m_pageResult->OnBtnLoad2();
}

//�����ɵ��ļ�
void CPageMaking::OnBtnOpenOutput()
{
	if(_tcslen(M()->maker.m_szOutputPath)!=0)
	{
		//���ļ���
		ShellExecute(NULL,L"explore", M()->maker.m_szOutputPath,NULL, NULL,SW_SHOWNORMAL);
			
		//��windowĬ�ϱ༭���򿪸���ļ�
		ShellExecute(NULL,L"open",L"notepad", M()->maker.m_szOutputPathName,NULL,SW_SHOWNORMAL);
	}
}

//��һ��ҳ��(�������)���ص������ذ�ť�����º��״̬
void CPageMaking::backToInit_1()
{
	M()->maker.m_vLyricOutput.clear();
	M()->maker.stopMusic();

	//������ʾ��壬��ʾ��һ���ǿո��
	P1_Line1->SetWindowTextW(_T(""));
	P1_Line2->SetWindowTextW(_T(""));
	P1_Line3->SetWindowTextW(M()->maker.m_vLyricOrigin[0]);

	//���ؿ�����ʾ
	emptyTip1->SetVisible(FALSE,TRUE);
	
	//�ı䰴ť��״̬
	m_btnLoad->EnableWindow(TRUE,TRUE);
	m_btnStart->EnableWindow(TRUE,TRUE);
	m_btnRestart->EnableWindow(FALSE,TRUE);
	
	//ȡ�������ʾ����еġ���ǰ�С��ĸ�������
	m_wndHighlight->SetVisible(FALSE,TRUE);

	//����ʱ���ǩ�ͽ�����
	m_txtTime->SetWindowTextW(_T("00:00.000"));
	m_ProgressTime->SetValue( 0 );//����ǧ����ֵ

	//�ı�״̬  ����������Ϣ
	M()->m_bIsLyricMaking = FALSE;

	M()->KillTimer(101);
}

//��Ҫ����
void CPageMaking::OnBtnRestart()
{
	//����״̬
	backToInit_1();
}

//��ʼ����
void CPageMaking::OnBtnStartMaking()
{
	//������ڣ�����Ԥ����� ��״̬���������������
	if(M()->m_bIsLyricPlaying == TRUE)
	{
		_MessageBox(M()->m_hWnd,_T("���Ƚ�������ʹ���Ԥ������"),_T("��ʾ"),MB_OK|MB_ICONINFORMATION);
		return;
	}

	//�ı���Ӧ������״̬
	M()->m_bIsLyricMaking = TRUE;
	M()->maker.makingStart();
	
	//�ı䰴ť��״̬
	m_btnLoad->EnableWindow(FALSE,TRUE);
	m_btnStart->EnableWindow(FALSE,TRUE);
	m_btnRestart->EnableWindow(TRUE,TRUE);
	
	//�ı�Ԥ����ť��״̬
	m_btnPreview->EnableWindow(FALSE,TRUE);
	m_btnOpenOutput->EnableWindow(FALSE,TRUE);

	//��ʾ�����ʾ����еġ���ǰ�С��ĸ�������
	m_wndHighlight->SetVisible(TRUE,TRUE);

	M()->SetTimer(101,1);

	//��¼ҳ�沥���㼣���꿴������˵��
	M()->FootPrintPage = 0;
}


void CPageMaking::OnBtnSoundOpen1()
{
	M()->OnBtnSoundOpen();
}

void CPageMaking::OnBtnSoundClose1()
{
	M()->OnBtnSoundClose();
}

//��������slider λ�õı仯
void  CPageMaking::OnSliderPos1(EventArgs *pEvt)
{
	M()->OnSliderPos(true);
}



//�жϵ�һ��ҳ��(�������) �� ����·���Ƿ�ѡ����� */
bool CPageMaking::isPathReady_1()				
{
	bool ret = true;
	for(int i=0; i< 3; i++)
		if(!PATH_STATE_1[i].isInited)
		{
			ret = PATH_STATE_1[i].isInited;
			break;
		}
	return ret;
}

/* ��õ�ǰδ��ʼ���ĵ�һ��·�� ��PATH_STATE_1 �ж�Ӧ���±�;����ʼ�����򷵻�-1 */
int CPageMaking::getPathNotReady_1()			
{
	int index = -1;
	for(int i=0; i< sizeof(PATH_STATE_1)/sizeof(PATH_STATE_1[0]); i++)
		if(!PATH_STATE_1[i].isInited)
		{
			index = i;
			break;
		}
	return index;
}











