REM: A batch program to rebuild the Win32++ samples using VS2005 (Express).
REM: The contents of the log file is erased 

::SetPaths
@set PATH=C:\Program Files\Microsoft Visual Studio 8\Common7\IDE;C:\Program Files\Microsoft Visual Studio 8\VC\BIN;C:\Program Files\Microsoft Visual Studio 8\Common7\Tools;C:\Program Files\Microsoft Visual Studio 8\Common7\Tools\bin;C:\Program Files\Microsoft Visual Studio 8\VC\PlatformSDK\bin;C:\Program Files\Microsoft Visual Studio 8\SDK\v2.0\bin;C:\WINDOWS\Microsoft.NET\Framework\v2.0.50727;C:\Program Files\Microsoft Visual Studio 8\VC\VCPackages;%PATH%


::Cleanup
call clean
pushd "..\Networking"
call clean
popd


REM: Change the directory to the parent
pushd ..


::Compile code
devenv /build Debug Browser\ProjectFiles\Browser_2005.sln /projectconfig Debug 				> "Win32xx Tests\VS2005.log"
devenv /build Release Browser\ProjectFiles\Browser_2005.sln /projectconfig Release			>>"Win32xx Tests\VS2005.log"
devenv /build Debug ControlBars\ProjectFiles\ControlBars_2005.sln /projectconfig Debug			>>"Win32xx Tests\VS2005.log"
devenv /build Release ControlBars\ProjectFiles\ControlBars_2005.sln /projectconfig Release		>>"Win32xx Tests\VS2005.log"
devenv /build Debug Dialog\ProjectFiles\Dialog_2005.sln /projectconfig Debug				>>"Win32xx Tests\VS2005.log"
devenv /build Release Dialog\ProjectFiles\Dialog_2005.sln /projectconfig Release			>>"Win32xx Tests\VS2005.log"
devenv /build Debug DlgSubclass\ProjectFiles\DlgSubClass_2005.sln /projectconfig Debug			>>"Win32xx Tests\VS2005.log"
devenv /build Release DlgSubclass\ProjectFiles\DlgSubClass_2005.sln /projectconfig Release		>>"Win32xx Tests\VS2005.log"
devenv /build Debug DockContainer\ProjectFiles\ContainerDocking_2005.sln /projectconfig Debug		>>"Win32xx Tests\VS2005.log"
devenv /build Release DockContainer\ProjectFiles\ContainerDocking_2005.sln /projectconfig Release	>>"Win32xx Tests\VS2005.log"
devenv /build Debug DockSimple\ProjectFiles\Docking_2005.sln /projectconfig Debug			>>"Win32xx Tests\VS2005.log"
devenv /build Release DockSimple\ProjectFiles\Docking_2005.sln /projectconfig Release			>>"Win32xx Tests\VS2005.log"
devenv /build Debug DockTabbedMDI\ProjectFiles\TabbedMDI_2005.sln /projectconfig Debug			>>"Win32xx Tests\VS2005.log"
devenv /build Release DockTabbedMDI\ProjectFiles\TabbedMDI_2005.sln /projectconfig Release		>>"Win32xx Tests\VS2005.log"
devenv /build Debug DocViewForm\ProjectFiles\DocViewForm_2005.sln /projectconfig Debug			>>"Win32xx Tests\VS2005.log"
devenv /build Release DocViewForm\ProjectFiles\DocViewForm_2005.sln /projectconfig Release		>>"Win32xx Tests\VS2005.log"
devenv /build Debug DX\ProjectFiles\DX_2005.sln /projectconfig Debug					>>"Win32xx Tests\VS2005.log"
devenv /build Release DX\ProjectFiles\DX_2005.sln /projectconfig Release				>>"Win32xx Tests\VS2005.log"
devenv /build Debug Explorer\ProjectFiles\Explorer_2005.sln /projectconfig Debug			>>"Win32xx Tests\VS2005.log"
devenv /build Release Explorer\ProjectFiles\Explorer_2005.sln /projectconfig Release			>>"Win32xx Tests\VS2005.log"
devenv /build Debug FastGDI\ProjectFiles\FastGDI_2005.sln /projectconfig Debug				>>"Win32xx Tests\VS2005.log"
devenv /build Release FastGDI\ProjectFiles\FastGDI_2005.sln /projectconfig Release			>>"Win32xx Tests\VS2005.log"
devenv /build Debug Frame\ProjectFiles\Frame_2005.sln /projectconfig Debug				>>"Win32xx Tests\VS2005.log"
devenv /build Release Frame\ProjectFiles\Frame_2005.sln /projectconfig Release				>>"Win32xx Tests\VS2005.log"
devenv /build Debug MDIDemo\ProjectFiles\MDIDemo_2005.sln /projectconfig Debug				>>"Win32xx Tests\VS2005.log"
devenv /build Release MDIDemo\ProjectFiles\MDIDemo_2005.sln /projectconfig Release			>>"Win32xx Tests\VS2005.log"
devenv /build Debug MDIFrame\ProjectFiles\MDIFrame_2005.sln /projectconfig Debug			>>"Win32xx Tests\VS2005.log"
devenv /build Release MDIFrame\ProjectFiles\MDIFrame_2005.sln /projectconfig Release			>>"Win32xx Tests\VS2005.log"
devenv /build Debug Networking\ClientDlg\Client_2005.sln /projectconfig Debug				>>"Win32xx Tests\VS2005.log"
devenv /build Release Networking\ClientDlg\Client_2005.sln /projectconfig Release			>>"Win32xx Tests\VS2005.log"
devenv /build Debug Networking\ServerDlg\Server_2005.sln /projectconfig Debug				>>"Win32xx Tests\VS2005.log"
devenv /build Release Networking\ServerDlg\Server_2005.sln /projectconfig Release			>>"Win32xx Tests\VS2005.log"
devenv /build Debug NotePad\ProjectFiles\Notepad_2005.sln /projectconfig Debug				>>"Win32xx Tests\VS2005.log"
devenv /build Release NotePad\ProjectFiles\Notepad_2005.sln /projectconfig Release			>>"Win32xx Tests\VS2005.log"
devenv /build Debug Performance\ProjectFiles\Performance_2005.sln /projectconfig Debug			>>"Win32xx Tests\VS2005.log"
devenv /build Release Performance\ProjectFiles\Performance_2005.sln /projectconfig Release		>>"Win32xx Tests\VS2005.log"
devenv /build Debug Picture\ProjectFiles\Picture_2005.sln /projectconfig Debug				>>"Win32xx Tests\VS2005.log"
devenv /build Release Picture\ProjectFiles\Picture_2005.sln /projectconfig Release			>>"Win32xx Tests\VS2005.log"
devenv /build Debug PropertySheet\ProjectFiles\PropertySheet_2005.sln /projectconfig Debug		>>"Win32xx Tests\VS2005.log"
devenv /build Release PropertySheet\ProjectFiles\PropertySheet_2005.sln /projectconfig Release		>>"Win32xx Tests\VS2005.log"
devenv /build Debug Scribble\ProjectFiles\Scribble_2005.sln /projectconfig Debug			>>"Win32xx Tests\VS2005.log"
devenv /build Release Scribble\ProjectFiles\Scribble_2005.sln /projectconfig Release			>>"Win32xx Tests\VS2005.log"
devenv /build Debug Simple\ProjectFiles\Simple_2005.sln /projectconfig Debug				>>"Win32xx Tests\VS2005.log"
devenv /build Release Simple\ProjectFiles\Simple_2005.sln /projectconfig Release			>>"Win32xx Tests\VS2005.log"
devenv /build Debug Splitter\ProjectFiles\Splitter_2005.sln /projectconfig Debug			>>"Win32xx Tests\VS2005.log"
devenv /build Release Splitter\ProjectFiles\Splitter_2005.sln /projectconfig Release			>>"Win32xx Tests\VS2005.log"
devenv /build Debug Subclass\ProjectFiles\Subclass_2005.sln /projectconfig Debug			>>"Win32xx Tests\VS2005.log"
devenv /build Release Subclass\ProjectFiles\Subclass_2005.sln /projectconfig Release			>>"Win32xx Tests\VS2005.log"
devenv /build Debug TabDemo\ProjectFiles\TabDemo_2005.sln /projectconfig Debug				>>"Win32xx Tests\VS2005.log"
devenv /build Release TabDemo\ProjectFiles\TabDemo_2005.sln /projectconfig Release			>>"Win32xx Tests\VS2005.log"
devenv /build Debug TabDialogDemo\ProjectFiles\TabDialogDemo_2005.sln /projectconfig Debug		>>"Win32xx Tests\VS2005.log"
devenv /build Release TabDialogDemo\ProjectFiles\TabDialogDemo_2005.sln /projectconfig Release		>>"Win32xx Tests\VS2005.log"
devenv /build Debug Themes\ProjectFiles\Themes_2005.sln /projectconfig Debug				>>"Win32xx Tests\VS2005.log"
devenv /build Release Themes\ProjectFiles\Themes_2005.sln /projectconfig Release			>>"Win32xx Tests\VS2005.log"
devenv /build Debug Threads\ProjectFiles\Threads_2005.sln /projectconfig Debug				>>"Win32xx Tests\VS2005.log"
devenv /build Release Threads\ProjectFiles\Threads_2005.sln /projectconfig Release			>>"Win32xx Tests\VS2005.log"


mkdir "Win32xx Tests\VS2005"
mkdir "Win32xx Tests\VS2005\Debug"

copy Browser\ProjectFiles\Debug\Browser.exe                 "Win32xx Tests\VS2005\Debug"
copy ControlBars\ProjectFiles\Debug\ControlBars.exe         "Win32xx Tests\VS2005\Debug"
copy Dialog\ProjectFiles\Debug\Dialog.exe                   "Win32xx Tests\VS2005\Debug"
copy DlgSubclass\ProjectFiles\Debug\DlgSubClass.exe         "Win32xx Tests\VS2005\Debug"
copy DockContainer\ProjectFiles\Debug\ContainerDocking.exe  "Win32xx Tests\VS2005\Debug"
copy DockSimple\ProjectFiles\Debug\Docking.exe              "Win32xx Tests\VS2005\Debug"
copy DockTabbedMDI\ProjectFiles\Debug\TabbedMDI.exe         "Win32xx Tests\VS2005\Debug"
copy DocViewForm\ProjectFiles\Debug\DocViewForm.exe         "Win32xx Tests\VS2005\Debug"
copy DX\ProjectFiles\Debug\DX.exe                           "Win32xx Tests\VS2005\Debug"
copy Explorer\ProjectFiles\Debug\Explorer.exe               "Win32xx Tests\VS2005\Debug"
copy FastGDI\ProjectFiles\Debug\FastGDI.exe                 "Win32xx Tests\VS2005\Debug"
copy Frame\ProjectFiles\Debug\Frame.exe                     "Win32xx Tests\VS2005\Debug"
copy MDIDemo\ProjectFiles\Debug\MDIDemo.exe                 "Win32xx Tests\VS2005\Debug"
copy MDIFrame\ProjectFiles\Debug\MDIFrame.exe               "Win32xx Tests\VS2005\Debug"
copy Networking\ClientDlg\Debug\Client.exe                  "Win32xx Tests\VS2005\Debug"
copy Networking\ServerDlg\Debug\Server.exe                  "Win32xx Tests\VS2005\Debug"
copy NotePad\ProjectFiles\Debug\Notepad.exe                 "Win32xx Tests\VS2005\Debug"
copy Performance\ProjectFiles\Debug\Performance.exe         "Win32xx Tests\VS2005\Debug"
copy Picture\ProjectFiles\Debug\Picture.exe                 "Win32xx Tests\VS2005\Debug"
copy PropertySheet\ProjectFiles\Debug\PropertySheet.exe     "Win32xx Tests\VS2005\Debug"
copy Scribble\ProjectFiles\Debug\Scribble.exe               "Win32xx Tests\VS2005\Debug"
copy Simple\ProjectFiles\Debug\Simple.exe                   "Win32xx Tests\VS2005\Debug"
copy Splitter\ProjectFiles\Debug\Splitter.exe               "Win32xx Tests\VS2005\Debug"
copy Subclass\ProjectFiles\Debug\Subclass.exe               "Win32xx Tests\VS2005\Debug"
copy TabDemo\ProjectFiles\Debug\TabDemo.exe                 "Win32xx Tests\VS2005\Debug"
copy TabDialogDemo\ProjectFiles\Debug\TabDialogDemo.exe     "Win32xx Tests\VS2005\Debug"
copy Themes\ProjectFiles\Debug\Themes.exe                   "Win32xx Tests\VS2005\Debug"
copy Threads\ProjectFiles\Debug\Threads.exe                 "Win32xx Tests\VS2005\Debug"

mkdir "Win32xx Tests\VS2005\Release"

copy Browser\ProjectFiles\Release\Browser.exe                 "Win32xx Tests\VS2005\Release"
copy ControlBars\ProjectFiles\Release\ControlBars.exe         "Win32xx Tests\VS2005\Release"
copy Dialog\ProjectFiles\Release\Dialog.exe                   "Win32xx Tests\VS2005\Release"
copy DlgSubclass\ProjectFiles\Release\DlgSubClass.exe         "Win32xx Tests\VS2005\Release"
copy DockContainer\ProjectFiles\Release\ContainerDocking.exe  "Win32xx Tests\VS2005\Release"
copy DockSimple\ProjectFiles\Release\Docking.exe              "Win32xx Tests\VS2005\Release"
copy DockTabbedMDI\ProjectFiles\Release\TabbedMDI.exe         "Win32xx Tests\VS2005\Release"
copy DocViewForm\ProjectFiles\Release\DocViewForm.exe         "Win32xx Tests\VS2005\Release"
copy DX\ProjectFiles\Release\DX.exe                           "Win32xx Tests\VS2005\Release"
copy Explorer\ProjectFiles\Release\Explorer.exe               "Win32xx Tests\VS2005\Release"
copy FastGDI\ProjectFiles\Release\FastGDI.exe                 "Win32xx Tests\VS2005\Release"
copy Frame\ProjectFiles\Release\Frame.exe                     "Win32xx Tests\VS2005\Release"
copy MDIDemo\ProjectFiles\Release\MDIDemo.exe                 "Win32xx Tests\VS2005\Release"
copy MDIFrame\ProjectFiles\Release\MDIFrame.exe               "Win32xx Tests\VS2005\Release"
copy Networking\ClientDlg\Release\Client.exe                  "Win32xx Tests\VS2005\Release"
copy Networking\ServerDlg\Release\Server.exe                  "Win32xx Tests\VS2005\Release"
copy NotePad\ProjectFiles\Release\Notepad.exe                 "Win32xx Tests\VS2005\Release"
copy Performance\ProjectFiles\Release\Performance.exe         "Win32xx Tests\VS2005\Release"
copy Picture\ProjectFiles\Release\Picture.exe                 "Win32xx Tests\VS2005\Release"
copy PropertySheet\ProjectFiles\Release\PropertySheet.exe     "Win32xx Tests\VS2005\Release"
copy Scribble\ProjectFiles\Release\Scribble.exe               "Win32xx Tests\VS2005\Release"
copy Simple\ProjectFiles\Release\Simple.exe                   "Win32xx Tests\VS2005\Release"
copy Splitter\ProjectFiles\Release\Splitter.exe               "Win32xx Tests\VS2005\Release"
copy Subclass\ProjectFiles\Release\Subclass.exe               "Win32xx Tests\VS2005\Release"
copy TabDemo\ProjectFiles\Release\TabDemo.exe                 "Win32xx Tests\VS2005\Release"
copy TabDialogDemo\ProjectFiles\Release\TabDialogDemo.exe     "Win32xx Tests\VS2005\Release"
copy Themes\ProjectFiles\Release\Themes.exe                   "Win32xx Tests\VS2005\Release"
copy Threads\ProjectFiles\Release\Threads.exe                 "Win32xx Tests\VS2005\Release"







popd