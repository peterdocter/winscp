﻿// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'PngSpeedButton.pas' rev: 27.00 (Windows)

#ifndef PngspeedbuttonHPP
#define PngspeedbuttonHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Vcl.Buttons.hpp>	// Pascal unit
#include <Vcl.Imaging.pngimage.hpp>	// Pascal unit
#include <PngFunctions.hpp>	// Pascal unit
#include <Vcl.Controls.hpp>	// Pascal unit
#include <Vcl.Graphics.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Pngspeedbutton
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TPngSpeedButton;
class PASCALIMPLEMENTATION TPngSpeedButton : public Vcl::Buttons::TSpeedButton
{
	typedef Vcl::Buttons::TSpeedButton inherited;
	
private:
	Vcl::Imaging::Pngimage::TPngImage* FPngImage;
	Pngfunctions::TPngOptions FPngOptions;
	bool FImageFromAction;
	bool __fastcall PngImageStored(void);
	void __fastcall SetPngImage(Vcl::Imaging::Pngimage::TPngImage* const Value);
	void __fastcall SetPngOptions(const Pngfunctions::TPngOptions Value);
	void __fastcall CreatePngGlyph(void);
	
protected:
	DYNAMIC void __fastcall ActionChange(System::TObject* Sender, bool CheckDefaults);
	virtual void __fastcall Paint(void);
	virtual void __fastcall Loaded(void);
	
public:
	__fastcall virtual TPngSpeedButton(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TPngSpeedButton(void);
	
__published:
	__property Vcl::Imaging::Pngimage::TPngImage* PngImage = {read=FPngImage, write=SetPngImage, stored=PngImageStored};
	__property Pngfunctions::TPngOptions PngOptions = {read=FPngOptions, write=SetPngOptions, default=1};
	__property Glyph = {stored=false};
	__property NumGlyphs = {stored=false, default=1};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Pngspeedbutton */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_PNGSPEEDBUTTON)
using namespace Pngspeedbutton;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// PngspeedbuttonHPP
