/////////////////////////////
// MyDialog.h
//

#ifndef MYDIALOG_H
#define MYDIALOG_H


/////////////////////////////////////////////////////
// CButtonDialog manages a dialog with several button
// controls.
class CButtonDialog : public CDialog
{
public:
    CButtonDialog(UINT resID);
    virtual ~CButtonDialog();

    BOOL OnButton();
    BOOL OnCheck1();
    BOOL OnCheck2();
    BOOL OnCheck3();
    INT_PTR OnCtlColorDlg(UINT msg, WPARAM wparam, LPARAM lparam);
    INT_PTR OnCtlColorStatic(UINT msg, WPARAM wparam, LPARAM lparam);
    BOOL OnRangeOfRadioIDs(UINT firstID, UINT lastID, UINT clickedID);

protected:
    virtual INT_PTR DialogProc(UINT msg, WPARAM wparam, LPARAM lparam);
    virtual BOOL OnCommand(WPARAM wparam, LPARAM lparam);
    virtual void OnOK() {}      // suppress closing dialog with the enter key
    virtual void OnCancel() {}  // suppress closing dialog with the esc key

private:
    CBrush m_brush;
};


/////////////////////////////////////////////////////////
// CComboBoxDialog manages a dialog that contains several
// ComboBox controls.
class CComboBoxDialog : public CDialog
{
public:
    CComboBoxDialog (UINT resID);
    virtual ~CComboBoxDialog();

protected:
    virtual INT_PTR DialogProc(UINT msg, WPARAM wparam, LPARAM lparam);
    virtual BOOL OnInitDialog();
    virtual void OnOK() {}      // supress closing dialog with the enter key
    virtual void OnCancel() {}  // supress closing dialog with the esc key

private:
    CBrush m_brush;
};


/////////////////////////////////////////////////////
// CMyDialog manages the application's main dialog.
// The main dialog has a tab control. The tab control
// is used to display either the button dialog or the
// ComboBox dialog.
class CMyDialog : public CDialog
{
public:
    CMyDialog(UINT resID);
    virtual ~CMyDialog();

protected:
    virtual void OnDestroy();
    virtual BOOL OnInitDialog();
    virtual INT_PTR DialogProc(UINT msg, WPARAM wparam, LPARAM lparam);
    virtual void OnOK();

private:
    CTab m_tab;
    CButtonDialog* m_pButtonDlg;
    CComboBoxDialog* m_pComboDlg;
};

#endif //MYDIALOG_H
