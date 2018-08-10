// Win32++   Version 8.5.1
// Release Date: TBA7
//
//      David Nash
//      email: dnash@bigpond.net.au
//      url: https://sourceforge.net/projects/win32-framework
//
//
// Copyright (c) 2005-2017  David Nash
//
// Permission is hereby granted, free of charge, to
// any person obtaining a copy of this software and
// associated documentation files (the "Software"),
// to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify,
// merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom
// the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice
// shall be included in all copies or substantial portions
// of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
// ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
// SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
// ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.
//
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
// wxx_stdcontrols.h
//  Declaration of the CButton, CEdit, CListBox and CStatic classes

// The Button, Edit, ListBox and Static controls are often referred to
// as "standard controls". These set of older controls were originally
// developed for Win16 operating systems (Windows 3.1 and 3.11). They use an
// older form of notification, and send their notifications via a WM_COMMAND
// message. Newer controls send their notifications via a WM_NOTIFY message.


#ifndef _WIN32XX_STDCONTROLS_H_
#define _WIN32XX_STDCONTROLS_H_

#include "wxx_wincore.h"


namespace Win32xx
{

    ///////////////////////////////////////////////
    // The CButton class provides the functionality of a button control.
    class CButton : public CWnd
    {
    public:
        CButton() {}
        virtual ~CButton() {}

        // Attributes
        HBITMAP GetBitmap() const;
        UINT GetButtonStyle() const;
        int GetCheck() const;
        HCURSOR GetCursor() const;
        HICON GetIcon() const;
        UINT GetState() const;
        HBITMAP SetBitmap(HBITMAP hBitmap) const;
        void SetButtonStyle(DWORD style, BOOL redraw) const;
        void SetCheck(int checkState) const;
        HCURSOR SetCursor(HCURSOR hCursor) const;
        HICON SetIcon(HICON hIcon) const;
        void SetState(UINT state) const;

    protected:
        // Overridables
        virtual void PreRegisterClass(WNDCLASS& wc);

    private:
        CButton(const CButton&);                // Disable copy construction
        CButton& operator = (const CButton&);   // Disable assignment operator
    };


    ///////////////////////////////////////////////
    // The CEdit class provides the functionality of an edit control.
    class CEdit : public CWnd
    {
    public:
        // Construction
        CEdit() {}
        virtual ~CEdit() {}

        // Attributes
        BOOL CanUndo() const;
        int CharFromPos(CPoint pt) const;
        int GetFirstVisibleLine() const;
        HLOCAL GetHandle() const;
        UINT GetLimitText() const;
        int GetLine(int index, LPTSTR pBuffer) const;
        int GetLine(int index, LPTSTR pBuffer, int maxLength) const;
        int GetLineCount() const;
        DWORD GetMargins() const;
        BOOL GetModify() const;
        TCHAR GetPasswordChar() const;
        void GetRect(RECT& rc) const;
        void GetSel(int& startChar, int& endChar) const;
        DWORD GetSel() const;
        CPoint PosFromChar(UINT index) const;
        void SetHandle(HLOCAL hBuffer) const;
        void SetLimitText(UINT max) const;
        void SetMargins(UINT left, UINT right) const;
        void SetModify(BOOL isModified = TRUE) const;

        // Operations
        void EmptyUndoBuffer() const;
        BOOL FmtLines(BOOL AddEOL) const;
        void LimitText(int limit = 0) const;
        int LineFromChar(int index = -1) const;
        int LineIndex(int line = -1) const;
        int LineLength(int line = -1) const;
        void LineScroll(int lines, int chars = 0) const;
        void ReplaceSel(LPCTSTR pNewText, BOOL canUndo) const;
        void SetPasswordChar(TCHAR ch) const;
        BOOL SetReadOnly(BOOL isReadOnly = TRUE) const;
        void SetRect(const RECT& rc) const;
        void SetRectNP(const RECT& rc) const;
        void SetSel(DWORD selection, BOOL isScrolled) const;
        void SetSel(int startChar, int endChar, BOOL isScrolled) const;
        BOOL SetTabStops(int tabStops, LPINT pTabStopsArray) const;
        BOOL SetTabStops() const;
        BOOL SetTabStops(const int& cxEachStop) const;

        //Clipboard Operations
        void Clear() const;
        void Copy() const;
        void Cut() const;
        void Paste() const;
        void Undo() const;

    protected:
        // Overridables
        virtual void PreRegisterClass(WNDCLASS& wc);

    private:
        CEdit(const CEdit&);                // Disable copy construction
        CEdit& operator = (const CEdit&);   // Disable assignment operator
    };


    ///////////////////////////////////////////////
    // The CListBox class provides the functionality of a list box control.
    class CListBox : public CWnd
    {
    public:
        CListBox() {}
        virtual ~CListBox() {}

        // Virtual functions
        virtual int CompareItem(LPCOMPAREITEMSTRUCT pCompareItemStruct);

        // General Operations
        int  GetCount() const;
        int  GetHorizontalExtent() const;
        DWORD GetItemData(int index) const;
        void* GetItemDataPtr(int index) const;
        int  GetItemHeight(int index) const;
        int  GetItemRect(int index, RECT& rc) const;
        LCID GetLocale() const;
        int  GetSel(int index) const;
        int  GetText(int index, LPTSTR pBuffer) const;
        int  GetTextLen(int index) const;
        int  GetTopIndex() const;
        UINT ItemFromPoint(CPoint pt, BOOL& isOutside ) const;
        void SetColumnWidth(int cxWidth) const;
        void SetHorizontalExtent(int cxExtent) const;
        int  SetItemData(int index, DWORD itemData) const;
        int  SetItemDataPtr(int index, void* pData) const;
        int  SetItemHeight(int index, UINT cyItemHeight) const;
        LCID SetLocale(LCID newLocale) const;
        BOOL SetTabStops(int tabStops, LPINT pTabStopsArray) const;
        void SetTabStops() const;
        BOOL SetTabStops(const int& cxEachStop) const;
        int  SetTopIndex(int index) const;

        // Single-Selection Operations
        int  GetCurSel() const;
        int  SetCurSel(int select) const;

        // Multiple-Selection Operations
        int  GetAnchorIndex() const;
        int  GetCaretIndex() const;
        int  GetSelCount() const;
        int  GetSelItems(int maxItems, LPINT pItemArray) const;
        int  SelItemRange(BOOL isSelected, int firstItem, int lastItem) const;
        void SetAnchorIndex(int index) const;
        int  SetCaretIndex(int index, BOOL partialScroll) const;
        int  SetSel(int index, BOOL isSelected) const;

        // String Operations
        int  AddString(LPCTSTR pString) const;
        int  DeleteString(UINT index) const;
        int  Dir(UINT attr, LPCTSTR pWildCard) const;
        int  FindString(int startAfter, LPCTSTR pString) const;
        int  FindStringExact(int indexStart, LPCTSTR pFindString) const;
        int  InsertString(int index, LPCTSTR pString) const;
        void ResetContent() const;
        int  SelectString(int startAfter, LPCTSTR pString) const;

    protected:
        // Overridables
        virtual LRESULT OnMessageReflect(UINT msg, WPARAM wparam, LPARAM lparam);
        virtual void PreRegisterClass(WNDCLASS& wc);

    private:
        CListBox(const CListBox&);              // Disable copy construction
        CListBox& operator = (const CListBox&); // Disable assignment operator
    };


    ///////////////////////////////////////////////
    // The CStatic class provides the functionality of a static control.
    class CStatic : public CWnd
    {
    public:
        CStatic() {}
        virtual ~CStatic() {}

        // Operations
        HBITMAP  GetBitmap() const;
        HCURSOR GetCursor() const;
        HENHMETAFILE GetEnhMetaFile() const;
        HICON  GetIcon() const;
        HBITMAP SetBitmap(HBITMAP hBitmap) const;
        HCURSOR SetCursor(HCURSOR hCursor) const;
        HENHMETAFILE SetEnhMetaFile(HENHMETAFILE hMetaFile) const;
        HICON SetIcon(HICON hIcon) const;

    protected:
        // Overridables
        virtual void PreRegisterClass(WNDCLASS& wc);

    private:
        CStatic(const CStatic&);                // Disable copy construction
        CStatic& operator = (const CStatic&);   // Disable assignment operator
    };

}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


namespace Win32xx
{

    ////////////////////////////////////////
    // Definitions for the CButton class
    //

    // Returns the handle to the bitmap associated with the button.
    inline HBITMAP CButton::GetBitmap() const
    {
        assert(IsWindow());
        return reinterpret_cast<HBITMAP>(SendMessage(BM_GETIMAGE, IMAGE_BITMAP, 0));
    }


    // Returns the style of the button. Possible styles are:
    // BS_3STATE, BS_AUTO3STATE, BS_AUTOCHECKBOX, VS_AUTORADIOBUTTON, BS_CHECKBOX, BS_DEFPUSHBUTTON, BS_GROUPBOX,
    // BS_LEFTEXT, BS_OWNERDRAW, BS_BITMAP, BS_BOTTOM, BS_CENTER, BS_ICON, BS_FLAT, BS_MULTILINE, BS_PUSHLIKE,
    // BS_RIGHT, BS_RIGHTBUTTON, BS_TEXT, BS_TOP, BS_TYHPEMASK, BS_VCENTER.
    inline UINT CButton::GetButtonStyle() const
    {
        assert(IsWindow());
        return static_cast<UINT>(GetStyle() & 0xFFFF);
    }


    // Returns the check state of the button. The possible states are:
    // BST_CHECKED Button is checked.
    // BST_INDETERMINATE Button is grayed.
    // BST_UNCHECKED Button is cleared.
    inline int CButton::GetCheck() const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(BM_GETCHECK, 0, 0));
    }


    // Returns the handle to the cursor associated with the button.
    inline HCURSOR CButton::GetCursor() const
    {
        assert(IsWindow());
        return reinterpret_cast<HCURSOR>(SendMessage(BM_GETIMAGE, IMAGE_CURSOR, 0));
    }


    // Returns the handle to the icon associated with the button.
    inline HICON CButton::GetIcon() const
    {
        assert(IsWindow());
        return reinterpret_cast<HICON>(SendMessage(BM_GETIMAGE, IMAGE_ICON, 0));
    }


    // Returns the state of the button. Possible states are:
    // BST_CHECKED
    // BST_FOCUS
    // BST_INDETERMINATE
    // BST_PUSHED
    // BST_UNCHECKED
    inline UINT CButton::GetState() const
    {
        assert(IsWindow());
        return static_cast<UINT>(SendMessage(BM_GETSTATE, 0, 0));
    }


    // sets the bitmap associated with the button.
    inline HBITMAP CButton::SetBitmap(HBITMAP hBitmap) const
    {
        assert(IsWindow());
        return reinterpret_cast<HBITMAP>(SendMessage(BM_SETIMAGE, IMAGE_BITMAP, reinterpret_cast<LPARAM>(hBitmap)));
    }


    // Sets the button style. Possible styles are:
    // BS_3STATE, BS_AUTO3STATE, BS_AUTOCHECKBOX, VS_AUTORADIOBUTTON, BS_CHECKBOX, BS_DEFPUSHBUTTON, BS_GROUPBOX,
    // BS_LEFTEXT, BS_OWNERDRAW, BS_BITMAP, BS_BOTTOM, BS_CENTER, BS_ICON, BS_FLAT, BS_MULTILINE, BS_PUSHLIKE,
    // BS_RIGHT, BS_RIGHTBUTTON, BS_TEXT, BS_TOP, BS_TYHPEMASK, BS_VCENTER.
    inline void CButton::SetButtonStyle(DWORD style, BOOL redraw) const
    {
        assert(IsWindow());
        SendMessage(BM_SETSTYLE, style, redraw);
    }


    // Sets the button check state. The possible states are:
    // BST_CHECKED Button is checked.
    // BST_INDETERMINATE Button is grayed.
    // BST_UNCHECKED Button is cleared.
    inline void CButton::SetCheck(int checkState) const
    {
        assert(IsWindow());
        SendMessage(BM_SETCHECK, checkState, 0);
    }


    // Sets the cursor associated with the button.
    inline HCURSOR CButton::SetCursor(HCURSOR hCursor) const
    {
        assert(IsWindow());
        return reinterpret_cast<HCURSOR>(SendMessage(STM_SETIMAGE, IMAGE_CURSOR, reinterpret_cast<LPARAM>(hCursor)));
    }


    // Sets the icon associated with the button.
    inline HICON CButton::SetIcon(HICON hIcon) const
    {
        assert(IsWindow());
        return reinterpret_cast<HICON>(SendMessage( BM_SETIMAGE, IMAGE_ICON, reinterpret_cast<LPARAM>(hIcon)));
    }


    // Sets  the state of the button. Possible states are:
    // BST_CHECKED
    // BST_FOCUS
    // BST_INDETERMINATE
    // BST_PUSHED
    // BST_UNCHECKED
    inline void CButton::SetState(UINT state) const
    {
        assert(IsWindow());
        SendMessage(BM_SETSTATE, state, 0);
    }


    // Sets the window class.
    inline void CButton::PreRegisterClass(WNDCLASS& wc)
    {
        wc.lpszClassName =  _T("Button");
    }


    ////////////////////////////////////////
    // Definitions for the CEdit class
    //

    // Returns TRUE if the edit control operation can be undone.
    inline BOOL CEdit::CanUndo() const
    {
        assert(IsWindow());
        return (SendMessage(EM_CANUNDO, 0, 0) != 0);
    }


    // Returns the character index and line index of the character nearest the specified point.
    inline int CEdit::CharFromPos(CPoint pt) const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(EM_CHARFROMPOS, 0, MAKELPARAM(pt.x, pt.y)));
    }


    // Returns the zero-based index of the first visible character in a single-line edit control
    // or the zero-based index of the uppermost visible line in a multi-line edit control.
    inline int CEdit::GetFirstVisibleLine() const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(EM_GETFIRSTVISIBLELINE, 0, 0));
    }


    // Returns a handle identifying the buffer containing the multi-line edit control's text.
    // It is not processed by single-line edit controls.
    inline HLOCAL CEdit::GetHandle() const
    {
        assert(IsWindow());
        return reinterpret_cast<HLOCAL>(SendMessage(EM_GETHANDLE, 0, 0));
    }


    // Returns the current text limit, in characters.
    inline UINT CEdit::GetLimitText() const
    {
        assert(IsWindow());
        return static_cast<UINT>(SendMessage(EM_GETLIMITTEXT, 0, 0));
    }


    // Copies characters to a buffer and returns the number of characters copied.
    inline int CEdit::GetLine(int index, LPTSTR pBuffer) const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(EM_GETLINE, index, reinterpret_cast<LPARAM>(pBuffer)));
    }


    // Copies characters to a buffer and returns the number of characters copied.
    inline int CEdit::GetLine(int index, LPTSTR pBuffer, int maxLength) const
    {
        assert(IsWindow());
        *(LPWORD)pBuffer = static_cast<WORD>(maxLength);
        return static_cast<int>(SendMessage(EM_GETLINE, index, reinterpret_cast<LPARAM>(pBuffer)));
    }


    // Returns the number of lines in the edit control.
    inline int CEdit::GetLineCount() const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(EM_GETLINECOUNT, 0, 0));
    }


    // Returns the widths of the left and right margins.
    inline DWORD CEdit::GetMargins() const
    {
        assert(IsWindow());
        return static_cast<DWORD>(SendMessage(EM_GETMARGINS, 0, 0));
    }


    // Returns a flag indicating whether the content of an edit control has been modified.
    inline BOOL CEdit::GetModify() const
    {
        assert(IsWindow());
        return (SendMessage(EM_GETMODIFY, 0, 0) != 0);
    }


    // Returns the character that edit controls use in conjunction with the ES_PASSWORD style.
    inline TCHAR CEdit::GetPasswordChar() const
    {
        assert(IsWindow());
        return static_cast<TCHAR>(SendMessage(EM_GETPASSWORDCHAR, 0, 0));
    }


    // Returns the coordinates of the formatting rectangle in an edit control.
    inline void CEdit::GetRect(RECT& rc) const
    {
        assert(IsWindow());
        SendMessage(EM_GETRECT, 0, reinterpret_cast<LPARAM>(&rc));
    }


    // Returns the starting and ending character positions of the current selection in the edit control.
    inline void CEdit::GetSel(int& startChar, int& endChar) const
    {
        assert(IsWindow());
        SendMessage(EM_GETSEL, reinterpret_cast<WPARAM>(&startChar), reinterpret_cast<LPARAM>(&endChar));
    }


    // Returns the starting and ending character positions of the current selection in the edit control.
    inline DWORD CEdit::GetSel() const
    {
        assert(IsWindow());
        return static_cast<DWORD>(SendMessage(EM_GETSEL, 0, 0));
    }


    // Returns the client coordinates of the specified character.
    inline CPoint CEdit::PosFromChar(UINT index) const
    {
        assert(IsWindow());
        return CPoint( static_cast<DWORD_PTR>(SendMessage(EM_POSFROMCHAR, index, 0)) );
    }


    // Sets a handle to the memory used as a text buffer, empties the undo buffer,
    // resets the scroll positions to zero, and redraws the window.
    inline void CEdit::SetHandle(HLOCAL hBuffer) const
    {
        assert(IsWindow());
        SendMessage(EM_SETHANDLE, reinterpret_cast<WPARAM>(hBuffer), 0);
    }


    // Sets the maximum number of characters the user may enter in the edit control.
    inline void CEdit::SetLimitText(UINT max) const
    {
        assert(IsWindow());
        SendMessage(EM_SETLIMITTEXT, max, 0);
    }


    // Sets the widths of the left and right margins, and redraws the edit control to reflect the new margins.
    inline void CEdit::SetMargins(UINT left, UINT right) const
    {
        assert(IsWindow());
        SendMessage(EM_SETMARGINS, EC_LEFTMARGIN|EC_RIGHTMARGIN, MAKELONG(left, right));
    }


    // Sets or clears the modification flag to indicate whether the edit control has been modified.
    inline void CEdit::SetModify(BOOL isModified) const
    {
        assert(IsWindow());
        SendMessage(EM_SETMODIFY, isModified, 0);
    }


    // Empties the undo buffer. The CanUndo function will now return FALSE.
    inline void CEdit::EmptyUndoBuffer() const
    {
        assert(IsWindow());
        SendMessage(EM_EMPTYUNDOBUFFER, 0, 0);
    }


    // Adds or removes soft line-break characters (two carriage returns and a line feed) to the ends of wrapped lines
    // in a multi-line edit control. It is not processed by single-line edit controls.
    inline BOOL CEdit::FmtLines(BOOL addEOL) const
    {
        assert(IsWindow());
        return (SendMessage(EM_FMTLINES, addEOL, 0) != 0);
    }


    // Sets the text limit of an edit control. The text limit is the maximum amount of text, in TCHARs,
    // that the user can type into the edit control.
    inline void CEdit::LimitText(int limit) const
    {
        assert(IsWindow());
        SendMessage(EM_LIMITTEXT, limit, 0);
    }


    // Returns the zero-based number of the line in a multi-line edit control that contains a specified character index.
    // This message is the reverse of LineIndex function.
    inline int CEdit::LineFromChar(int index) const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(EM_LINEFROMCHAR, index, 0));
    }


    // Returns the character of a line in a multi-line edit control.
    // This message is the reverse of the LineFromChar function.
    inline int CEdit::LineIndex(int line) const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(EM_LINEINDEX, line, 0));
    }


    // Returns the length, in characters, of a single-line edit control. In a multi-line edit control,
    //  returns the length, in characters, of a specified line.
    inline int CEdit::LineLength(int line) const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(EM_LINELENGTH, line, 0));
    }


    // Scrolls the text vertically in a single-line edit control or horizontally in a multi-line edit control.
    inline void CEdit::LineScroll(int lines, int chars) const
    {
        assert(IsWindow());
        SendMessage(EM_LINESCROLL, chars, lines);
    }


    // Replaces the current selection with the text in an application-supplied buffer, sends the parent window
    // EN_UPDATE and EN_CHANGE messages, and updates the undo buffer.
    inline void CEdit::ReplaceSel(LPCTSTR pNewText, BOOL canUndo) const
    {
        assert(IsWindow());
        SendMessage(EM_REPLACESEL, canUndo, reinterpret_cast<LPARAM>(pNewText));
    }


    // Defines the character that edit controls use in conjunction with the ES_PASSWORD style.
    inline void CEdit::SetPasswordChar(TCHAR ch) const
    {
        assert(IsWindow());
        SendMessage(EM_SETPASSWORDCHAR, ch, 0);
    }


    // Sets or removes the read-only style (ES_READONLY) in an edit control.
    inline BOOL CEdit::SetReadOnly(BOOL isReadOnly) const
    {
        assert(IsWindow());
        return (SendMessage(EM_SETREADONLY, isReadOnly, 0) != 0);
    }


    // Sets the formatting rectangle for the multi-line edit control and redraws the window.
    inline void CEdit::SetRect(const RECT& rc) const
    {
        assert(IsWindow());
        SendMessage(EM_SETRECT, 0, reinterpret_cast<LPARAM>(&rc));
    }


    // Sets the formatting rectangle for the multi-line edit control but does not redraw the window.
    inline void CEdit::SetRectNP(const RECT& rc) const
    {
        assert(IsWindow());
        SendMessage(EM_SETRECTNP, 0, reinterpret_cast<LPARAM>(&rc));
    }


    // Selects a range of characters in the edit control by setting the starting and ending positions to be selected.
    inline void CEdit::SetSel(DWORD selection, BOOL isScrolled) const
    {
        assert(IsWindow());
        SendMessage(EM_SETSEL, LOWORD(selection), HIWORD(selection));
        if (isScrolled)
            SendMessage(EM_SCROLLCARET, 0, 0);
    }


    // Selects a range of characters in the edit control by setting the starting and ending positions to be selected.
    inline void CEdit::SetSel(int startChar, int endChar, BOOL isScrolled) const
    {
        assert(IsWindow());
        SendMessage(EM_SETSEL, startChar, endChar);
        if (isScrolled)
            SendMessage(EM_SCROLLCARET, 0, 0);
    }


    // Sets tab-stop positions in the multi-line edit control.
    inline BOOL CEdit::SetTabStops(int tabStops, LPINT pTabStopsArray) const
    {
        assert(IsWindow());
        return (SendMessage(EM_SETTABSTOPS, tabStops, reinterpret_cast<LPARAM>(pTabStopsArray)) != 0);
    }


    // Sets tab-stop positions in the multi-line edit control.
    inline BOOL CEdit::SetTabStops() const
    {
        assert(IsWindow());
        return (SendMessage( EM_SETTABSTOPS, 0, 0) != 0);
    }


    // Sets tab-stop positions in the multi-line edit control.
    inline BOOL CEdit::SetTabStops(const int& cxEachStop) const
    {
        assert(IsWindow());
        return (SendMessage(EM_SETTABSTOPS, 1, reinterpret_cast<LPARAM>(&cxEachStop)) != 0);
    }


    // Clears the current selection, if any, in an edit control.
    inline void CEdit::Clear() const
    {
        assert(IsWindow());
        SendMessage(WM_CLEAR, 0, 0);
    }


    // Copies text to the clipboard unless the style is ES_PASSWORD, in which case the message returns zero.
    inline void CEdit::Copy() const
    {
        assert(IsWindow());
        SendMessage(WM_COPY, 0, 0);
    }


    // Cuts the selection to the clipboard, or deletes the character to the left of the cursor if there is no selection.
    inline void CEdit::Cut() const
    {
        assert(IsWindow());
        SendMessage(WM_CUT, 0, 0);
    }


    // Pastes text from the clipboard into the edit control window at the caret position.
    inline void CEdit::Paste() const
    {
        assert(IsWindow());
        SendMessage(WM_PASTE, 0, 0);
    }


    // Removes any text that was just inserted or inserts any deleted characters and sets the selection to the inserted text.
    inline void CEdit::Undo() const
    {
        assert(IsWindow());
        SendMessage(EM_UNDO, 0, 0);
    }


    // Set the window class
    inline void CEdit::PreRegisterClass(WNDCLASS& wc)
    {
        wc.lpszClassName =  _T("Edit");
    }


    ////////////////////////////////////////
    // Definitions for the CListbox class
    //

    // Called by in response to the WM_COMPAREITEM message to determine the relative position
    // of a new item in a sorted owner-draw list box. Override this function in an owner-drawn
    // List-Box to specify the sort order when items are added using AddString.
    inline int CListBox::CompareItem(LPCOMPAREITEMSTRUCT)
    {
        // The return value indicates the relative position of the two items.
        // It may be any of the values shown in the following table.
        //
        //  Value Meaning
        //  -1 Item 1 precedes item 2 in the sorted order.
        //   0 Items 1 and 2 are equivalent in the sorted order.
        //   1 Item 1 follows item 2 in the sorted order.

        return 0;
    }

    // Returns the number of items in the list box.
    inline int CListBox::GetCount() const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(LB_GETCOUNT, 0, 0));
    }


    // Returns the scrollable width, in pixels, of a list box.
    inline int CListBox::GetHorizontalExtent() const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(LB_GETHORIZONTALEXTENT, 0, 0));
    }


    // Returns the value associated with the specified item.
    inline DWORD CListBox::GetItemData(int index) const
    {
        assert(IsWindow());
        return static_cast<DWORD>(SendMessage(LB_GETITEMDATA, index, 0));
    }


    // Returns the value associated with the specified item.
    inline void* CListBox::GetItemDataPtr(int index) const
    {
        assert(IsWindow());
        return reinterpret_cast<LPVOID>(SendMessage(LB_GETITEMDATA, index, 0));
    }


    // Returns the height, in pixels, of an item in a list box.
    inline int CListBox::GetItemHeight(int index) const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(LB_GETITEMHEIGHT, index, 0));
    }


    // Retrieves the client coordinates of the specified list box item.
    inline int CListBox::GetItemRect(int index, RECT& rc) const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(LB_GETITEMRECT, index, reinterpret_cast<LPARAM>(&rc)));
    }


    // Retrieves the locale of the list box. The high-order word contains the country/region code
    // and the low-order word contains the language identifier.
    inline LCID CListBox::GetLocale() const
    {
        assert(IsWindow());
        return static_cast<LCID>(SendMessage(LB_GETLOCALE, 0, 0));
    }


    // Returns the selection state of a list box item.
    inline int CListBox::GetSel(int index) const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(LB_GETSEL, index, 0));
    }


    // Retrieves the string associated with a specified item and the length of the string.
    inline int CListBox::GetText(int index, LPTSTR pBuffer) const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(LB_GETTEXT, index, reinterpret_cast<LPARAM>(pBuffer)));
    }


    // Returns the length, in characters, of the string associated with a specified item.
    inline int CListBox::GetTextLen(int index) const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage( LB_GETTEXTLEN, index, 0));
    }


    // Returns the index of the first visible item in a list box.
    inline int CListBox::GetTopIndex() const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(LB_GETTOPINDEX, 0, 0));
    }


    // Retrieves the zero-based index of the item nearest the specified point in a list box.
    inline UINT CListBox::ItemFromPoint(CPoint pt, BOOL& isOutside) const
    {
        assert(IsWindow());
        DWORD dw = static_cast<DWORD>(SendMessage(LB_ITEMFROMPOINT, 0, MAKELPARAM(pt.x, pt.y)));
        isOutside = !!HIWORD(dw);
        return LOWORD(dw);
    }


    // Sets the width, in pixels, of all columns in a list box.
    inline void CListBox::SetColumnWidth(int cxWidth) const
    {
        assert(IsWindow());
        SendMessage(LB_SETCOLUMNWIDTH, cxWidth, 0);
    }


    // Sets the scrollable width, in pixels, of a list box.
    inline void CListBox::SetHorizontalExtent(int cxExtent) const
    {
        assert(IsWindow());
        SendMessage(LB_SETHORIZONTALEXTENT, cxExtent, 0);
    }


    // Associates a value with a list box item.
    inline int CListBox::SetItemData(int index, DWORD itemData) const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(LB_SETITEMDATA, index, itemData));
    }


    // Associates a value with a list box item.
    inline int CListBox::SetItemDataPtr(int index, void* pData) const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(LB_SETITEMDATA, index, reinterpret_cast<LPARAM>(pData)));
    }


    // Sets the height, in pixels, of an item or items in a list box.
    inline int CListBox::SetItemHeight(int index, UINT cyItemHeight) const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(LB_SETITEMHEIGHT, index, MAKELONG(cyItemHeight, 0)));
    }


    // Sets the locale of a list box and returns the previous locale identifier.
    inline LCID CListBox::SetLocale(LCID newLocale) const
    {
        assert(IsWindow());
        return static_cast<LCID>(SendMessage(LB_SETLOCALE, newLocale, 0));
    }


    // Sets the tab stops to those specified in a specified array.
    inline BOOL CListBox::SetTabStops(int tabStops, LPINT pTabStopsArray) const
    {
        assert(IsWindow());
        return (SendMessage(LB_SETTABSTOPS, tabStops, reinterpret_cast<LPARAM>(pTabStopsArray)) != 0);
    }


    // Sets the tab stops to those specified in a specified array.
    inline void CListBox::SetTabStops() const
    {
        assert(IsWindow());
        SendMessage(LB_SETTABSTOPS, 0, 0);
    }


    inline BOOL CListBox::SetTabStops(const int& cxEachStop) const
    // Sets the tab stops to those specified in a specified array.
    {
        assert(IsWindow());
        return (SendMessage(LB_SETTABSTOPS, 1, reinterpret_cast<LPARAM>(&cxEachStop))!= 0);
    }


    // Scrolls the list box so the specified item is at the top of the visible range.
    inline int CListBox::SetTopIndex(int index) const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(LB_SETTOPINDEX, index, 0));
    }


    // Returns the index of the currently selected item.
    inline int CListBox::GetCurSel() const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(LB_GETCURSEL, 0, 0));
    }


    // Selects a specified list box item.
    inline int CListBox::SetCurSel(int select) const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(LB_SETCURSEL, select, 0));
    }


    // Returns the index of the item that the mouse last selected.
    inline int CListBox::GetAnchorIndex() const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(LB_GETANCHORINDEX, 0, 0));
    }


    // Returns the index of the item that has the focus rectangle.
    inline int CListBox::GetCaretIndex() const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(LB_GETCARETINDEX, 0, 0));
    }


    // Returns the number of selected items in a multiple-selection list box.
    inline int CListBox::GetSelCount() const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(LB_GETSELCOUNT, 0, 0));
    }


    // Creates an array of the indexes of all selected items in a multiple-selection list box
    // and returns the total number of selected items.
    inline int CListBox::GetSelItems(int maxItems, LPINT pIndexArray) const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(LB_GETSELITEMS, maxItems, reinterpret_cast<LPARAM>(pIndexArray)));
    }


    // Selects a specified range of items in a list box.
    inline int CListBox::SelItemRange(BOOL isSelected, int firstItem, int lastItem) const
    {
        assert(IsWindow());
        if (isSelected)
            return static_cast<int>(SendMessage(LB_SELITEMRANGEEX, firstItem, lastItem));
        else
            return static_cast<int>(SendMessage(LB_SELITEMRANGEEX, lastItem, firstItem));
    }


    // Sets the item that the mouse last selected to a specified item.
    inline void CListBox::SetAnchorIndex(int index) const
    {
        assert(IsWindow());
        SendMessage(LB_SETANCHORINDEX, index, 0);
    }


    // Sets the focus rectangle to a specified list box item.
    inline int CListBox::SetCaretIndex(int index, BOOL partialScroll) const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(LB_SETCARETINDEX, index, MAKELONG(partialScroll, 0)));
    }


    // Selects an item in a multiple-selection list box.
    inline int CListBox::SetSel(int index, BOOL isSelected) const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(LB_SETSEL, isSelected, index));
    }


    // Adds a string to a list box and returns its index.
    inline int CListBox::AddString(LPCTSTR pString) const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(pString)));
    }


    // Removes a string from a list box and returns the number of strings remaining in the list.
    inline int CListBox::DeleteString(UINT index) const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(LB_DELETESTRING, index, 0));
    }


    // Adds a list of filenames to a list box and returns the index of the last filename added.
    inline int CListBox::Dir(UINT attr, LPCTSTR pWildCard) const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(LB_DIR, attr, reinterpret_cast<LPARAM>(pWildCard)));
    }


    // Returns the index of the first string in the list box that begins with a specified string.
    inline int CListBox::FindString(int startAfter, LPCTSTR pString) const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(LB_FINDSTRING, startAfter, reinterpret_cast<LPARAM>(pString)));
    }


    // Returns the index of the string in the list box that is equal to a specified string.
    inline int CListBox::FindStringExact(int indexStart, LPCTSTR pFindString) const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(LB_FINDSTRINGEXACT, indexStart, reinterpret_cast<LPARAM>(pFindString)));
    }


    // Inserts a string at a specified index in a list box.
    inline int CListBox::InsertString(int index, LPCTSTR pString) const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(LB_INSERTSTRING, index, reinterpret_cast<LPARAM>(pString)));
    }


    // Removes all items from a list box.
    inline void CListBox::ResetContent() const
    {
        assert(IsWindow());
        SendMessage(LB_RESETCONTENT, 0, 0);
    }


    // Selects the first string it finds that matches a specified prefix.
    inline int CListBox::SelectString(int startAfter, LPCTSTR pString) const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(LB_SELECTSTRING, startAfter, reinterpret_cast<LPARAM>(pString)));
    }


    // Handle messages reflected back from the parent window.
    // Override this function in your derived class to handle these special messages:
    // WM_COMMAND, WM_CTLCOLORBTN, WM_CTLCOLOREDIT, WM_CTLCOLORDLG, WM_CTLCOLORLISTBOX,
    // WM_CTLCOLORSCROLLBAR, WM_CTLCOLORSTATIC, WM_CHARTOITEM,  WM_VKEYTOITEM,
    // WM_HSCROLL, WM_VSCROLL, WM_DRAWITEM, WM_MEASUREITEM, WM_DELETEITEM,
    // WM_COMPAREITEM, WM_PARENTNOTIFY.
    inline LRESULT CListBox::OnMessageReflect(UINT msg, WPARAM, LPARAM lparam)
    {
        switch (msg)
        {
        case WM_COMPAREITEM:
            {
                LPCOMPAREITEMSTRUCT pCompareItemStruct = (LPCOMPAREITEMSTRUCT)lparam;
                return CompareItem(pCompareItemStruct);
            }
        }

        return 0;   // Allow other messages to be handled elsewhere. 
    }


    // Set the window class.
    inline void CListBox::PreRegisterClass(WNDCLASS& wc)
    {
        wc.lpszClassName =  _T("ListBox");
    }


    ////////////////////////////////////////
    // Definitions for the CStatic class
    //

    // Returns the handle to the bitmap for the static control set by CStatic::SetBitmap.
    inline HBITMAP CStatic::GetBitmap() const
    {
        assert(IsWindow());
        return reinterpret_cast<HBITMAP>(SendMessage(STM_GETIMAGE, IMAGE_BITMAP, 0));
    }


    // Returns the handle to the cursor for the static control set by CStatic::SetCursor.
    inline HCURSOR CStatic::GetCursor() const
    {
        assert(IsWindow());
        return reinterpret_cast<HCURSOR>(SendMessage(STM_GETIMAGE, IMAGE_CURSOR, 0));
    }


    // Returns the handle to the enhanced meta-file for the static control set by CStatic::SetEnhMetaFile.
    inline HENHMETAFILE CStatic::GetEnhMetaFile() const

    {
        assert(IsWindow());
        return reinterpret_cast<HENHMETAFILE>(SendMessage(STM_GETIMAGE, IMAGE_ENHMETAFILE, 0));
    }


    // Returns the handle to the icon for the static control set by CStatic::SetIcon.
    inline HICON CStatic::GetIcon() const
    {
        assert(IsWindow());
        return reinterpret_cast<HICON>(SendMessage(STM_GETIMAGE, IMAGE_ICON, 0));
    }


    // Associates a new bitmap with the static control.
    // The bitmap will be drawn in the upper-left corner, and the static
    // control will be resized to the size of the bitmap.
    // This function requires the SS_BITMAP style.
    inline HBITMAP CStatic::SetBitmap(HBITMAP hBitmap) const
    {
        assert(IsWindow());
        return reinterpret_cast<HBITMAP>(SendMessage(STM_SETIMAGE, IMAGE_BITMAP, reinterpret_cast<LPARAM>(hBitmap)));
    }


    // Associates a new cursor image with the static control.
    // The cursor will be drawn in the upper-left corner and the static
    // control will be resized to the size of the cursor.
    // This function requires the SS_ICON style
    inline HCURSOR CStatic::SetCursor(HCURSOR hCursor) const
    {
        assert(IsWindow());
        return reinterpret_cast<HCURSOR>(SendMessage(STM_SETIMAGE, IMAGE_CURSOR, reinterpret_cast<LPARAM>(hCursor)));
    }


    // Associates a new enhanced metafile image with the static control.
    // The enhanced metafile will be drawn in the upper-left corner and the static
    // control will be resized to the size of the enhanced metafile.
    // This function requires the SS_ENHMETAFILE style
    inline HENHMETAFILE CStatic::SetEnhMetaFile(HENHMETAFILE hMetaFile) const
    {
        assert(IsWindow());
        return reinterpret_cast<HENHMETAFILE>(SendMessage(STM_SETIMAGE, IMAGE_ENHMETAFILE, reinterpret_cast<LPARAM>(hMetaFile)));
    }


    // Associates a new icon image with the static control.
    // The icon will be drawn in the upper-left corner and the static
    // control will be resized to the size of the icon.
    // This function requires the SS_ICON style
    inline HICON CStatic::SetIcon(HICON hIcon) const
    {
        assert(IsWindow());
        return reinterpret_cast<HICON>(SendMessage(STM_SETIMAGE, IMAGE_ICON, reinterpret_cast<LPARAM>(hIcon)));
    }


    // Set the window class.
    inline void CStatic::PreRegisterClass(WNDCLASS& wc)
    {

        wc.lpszClassName =  _T("Static");
    }

}

#endif  // _WIN32XX_STDCONTROLS_H_

