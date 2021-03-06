//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <WinInterface.h>
#include "SynchronizeProgress.h"
#include <Common.h>
#include <Configuration.h>
#include <CoreMain.h>
#include <TextsWin.h>
#include <VCLCommon.h>
#include <GUITools.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "PathLabel"
#ifndef NO_RESOURCES
#pragma resource "*.dfm"
#endif
//---------------------------------------------------------------------------
__fastcall TSynchronizeProgressForm::TSynchronizeProgressForm(TComponent * Owner,
  bool AllowMinimize, bool CompareOnly)
  : TForm(Owner)
{
  FStarted = false;
  FCanceled = false;
  FElapsed = EncodeTimeVerbose(0, 0, 0, 0);
  FShowAsModalStorage = NULL;
  FMinimizedByMe = false;
  FCompareOnly = CompareOnly;
  UseSystemSettings(this);
  if (!AllowMinimize)
  {
    CancelButton->Left = CancelButton->Left +
      (MinimizeButton->Left - CancelButton->Left) / 2;
    MinimizeButton->Visible = false;
  }
  else
  {
    SetGlobalMinimizeHandler(this, GlobalMinimize);
  }
}
//---------------------------------------------------------------------------
__fastcall TSynchronizeProgressForm::~TSynchronizeProgressForm()
{
  ClearGlobalMinimizeHandler(GlobalMinimize);

  ReleaseAsModal(this, FShowAsModalStorage);

  if (IsApplicationMinimized() && FMinimizedByMe)
  {
    ShowNotification(
      NULL, MainInstructions(LoadStr(BALLOON_OPERATION_COMPLETE)),
      qtInformation);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSynchronizeProgressForm::Start()
{
  FStarted = true;
  FStartTime = Now();
  UpdateTimer->Enabled = true;
  StartTimeLabel->Caption = FStartTime.TimeString();
  Caption = FormatFormCaption(this, LoadStr(FCompareOnly ? SYNCHRONIZE_PROGRESS_COMPARE : SYNCHRONIZE_PROGRESS_SYNCHRONIZE2));
  if (!IsApplicationMinimized())
  {
    // Do not showing the progress when the application is minimized,
    // otherwise the form popups up unminimized.
    // Quick and dirty hack: with this form, we do not support showing it
    // once the application restores,
    // otherwise we would have to synchronize it somehow with the TProgressForm,
    // not to show it over the TProgressForm
    ShowAsModal(this, FShowAsModalStorage);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSynchronizeProgressForm::SetData(const UnicodeString LocalDirectory,
  const UnicodeString RemoteDirectory, bool & Continue)
{
  assert(FStarted);
  LocalDirectoryLabel->Caption = LocalDirectory;
  RemoteDirectoryLabel->Caption = RemoteDirectory;
  Continue = !FCanceled;

  UpdateControls();
  Application->ProcessMessages();
}
//---------------------------------------------------------------------------
void __fastcall TSynchronizeProgressForm::UpdateControls()
{
  if (FStarted)
  {
    FElapsed = Now() - FStartTime;
  }
  TimeElapsedLabel->Caption = FormatDateTimeSpan(Configuration->TimeFormat, FElapsed);
  CancelButton->Enabled = !FCanceled;
}
//---------------------------------------------------------------------------
void __fastcall TSynchronizeProgressForm::CancelOperation()
{
  FCanceled = true;
  UpdateControls();
}
//---------------------------------------------------------------------------
void __fastcall TSynchronizeProgressForm::CancelButtonClick(TObject * /*Sender*/)
{
  CancelOperation();
}
//---------------------------------------------------------------------------
void __fastcall TSynchronizeProgressForm::UpdateTimerTimer(TObject * /*Sender*/)
{
  UpdateControls();
}
//---------------------------------------------------------------------------
void __fastcall TSynchronizeProgressForm::MinimizeButtonClick(
  TObject * Sender)
{
  CallGlobalMinimizeHandler(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSynchronizeProgressForm::GlobalMinimize(TObject * /*Sender*/)
{
  ApplicationMinimize();
  FMinimizedByMe = true;
}
//---------------------------------------------------------------------------
void __fastcall TSynchronizeProgressForm::Dispatch(void * AMessage)
{
  TMessage & Message = *reinterpret_cast<TMessage *>(AMessage);
  if (Message.Msg == WM_CLOSE)
  {
    CancelOperation();
  }
  else
  {
    TForm::Dispatch(AMessage);
  }
}
//---------------------------------------------------------------------------
