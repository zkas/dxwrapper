/**
* Copyright (C) 2020 Elisha Riedlinger
*
* This software is  provided 'as-is', without any express  or implied  warranty. In no event will the
* authors be held liable for any damages arising from the use of this software.
* Permission  is granted  to anyone  to use  this software  for  any  purpose,  including  commercial
* applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*   1. The origin of this software must not be misrepresented; you must not claim that you  wrote the
*      original  software. If you use this  software  in a product, an  acknowledgment in the product
*      documentation would be appreciated but is not required.
*   2. Altered source versions must  be plainly  marked as such, and  must not be  misrepresented  as
*      being the original software.
*   3. This notice may not be removed or altered from any source distribution.
*/

#include "ddraw.h"

void ConvertColorControl(DDCOLORCONTROL &ColorControl, DDCOLORCONTROL &ColorControl2)
{
	if (ColorControl.dwSize != sizeof(DDCOLORCONTROL) || ColorControl.dwSize != sizeof(DDCOLORCONTROL))
	{
		LOG_LIMIT(100, __FUNCTION__ << " Error: Incorrect dwSize: " << ColorControl.dwSize << " " << ColorControl.dwSize);
		return;
	}
	CopyMemory(&ColorControl, &ColorControl2, sizeof(DDCOLORCONTROL));
}

void ConvertGammaRamp(DDGAMMARAMP &RampData, DDGAMMARAMP &RampData2)
{
	CopyMemory(&RampData, &RampData2, sizeof(DDGAMMARAMP));
}

void ConvertSurfaceDesc(DDSURFACEDESC &Desc, DDSURFACEDESC &Desc2)
{
	if (Desc.dwSize != sizeof(DDSURFACEDESC) || Desc2.dwSize != sizeof(DDSURFACEDESC))
	{
		LOG_LIMIT(100, __FUNCTION__ << " Error: Incorrect dwSize: " << Desc.dwSize << " " << Desc2.dwSize);
		return;
	}
	CopyMemory(&Desc, &Desc2, sizeof(DDSURFACEDESC));
}

void ConvertSurfaceDesc(DDSURFACEDESC2 &Desc, DDSURFACEDESC2 &Desc2)
{
	if (Desc.dwSize != sizeof(DDSURFACEDESC2) || Desc2.dwSize != sizeof(DDSURFACEDESC2))
	{
		LOG_LIMIT(100, __FUNCTION__ << " Error: Incorrect dwSize: " << Desc.dwSize << " " << Desc2.dwSize);
		return;
	}
	CopyMemory(&Desc, &Desc2, sizeof(DDSURFACEDESC2));
}

void ConvertSurfaceDesc(DDSURFACEDESC &Desc, DDSURFACEDESC2 &Desc2)
{
	// Check for supported dwSize
	if (Desc.dwSize != sizeof(DDSURFACEDESC) || (Desc2.dwSize != sizeof(DDSURFACEDESC2) && Desc2.dwSize != sizeof(DDSURFACEDESC)))
	{
		LOG_LIMIT(100, __FUNCTION__ << " Error: Incorrect dwSize: " << Desc.dwSize << " " << Desc2.dwSize);
		return;
	}
	// Prepare destination structure
	ZeroMemory(&Desc, sizeof(DDSURFACEDESC));
	Desc.dwSize = sizeof(DDSURFACEDESC);
	// Convert varables
	Desc.dwFlags = Desc2.dwFlags & ~(DDSD_ZBUFFERBITDEPTH | DDSD_TEXTURESTAGE | DDSD_FVF | DDSD_SRCVBHANDLE | DDSD_DEPTH);		// Remove unsupported flags
	Desc.dwHeight = Desc2.dwHeight;
	Desc.dwWidth = Desc2.dwWidth;
	Desc.lPitch = Desc2.lPitch;
	Desc.dwBackBufferCount = Desc2.dwBackBufferCount;
	Desc.dwRefreshRate = Desc2.dwRefreshRate;
	Desc.dwAlphaBitDepth = Desc2.dwAlphaBitDepth;
	Desc.dwReserved = Desc2.dwReserved;
	Desc.lpSurface = Desc2.lpSurface;
	Desc.ddckCKDestOverlay = Desc2.ddckCKDestOverlay;
	Desc.ddckCKDestBlt = Desc2.ddckCKDestBlt;
	Desc.ddckCKSrcOverlay = Desc2.ddckCKSrcOverlay;
	Desc.ddckCKSrcBlt = Desc2.ddckCKSrcBlt;
	if (Desc2.dwFlags & DDSD_PIXELFORMAT)
	{
		CopyMemory(&Desc.ddpfPixelFormat, &Desc2.ddpfPixelFormat, sizeof(DDPIXELFORMAT));
		Desc.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
	}
	if (Desc2.ddpfPixelFormat.dwFlags & DDPF_ZBUFFER)
	{
		Desc.dwFlags |= DDSD_ZBUFFERBITDEPTH;
		Desc.dwZBufferBitDepth = Desc2.ddpfPixelFormat.dwZBufferBitDepth;
		Desc.ddpfPixelFormat.dwFlags &= ~DDPF_ZBUFFER;
		Desc.ddpfPixelFormat.dwZBufferBitDepth = 0;
	}
	ConvertCaps(Desc.ddsCaps, Desc2.ddsCaps);
	// Check for dwFlags that did not get converted
	if ((Desc.dwFlags & ~DDSD_ZBUFFERBITDEPTH) != Desc2.dwFlags)
	{
		LOG_LIMIT(100, __FUNCTION__ << " Warning: (Desc2->Desc) Removing unsupported flags: " << Logging::hex(Desc2.dwFlags & ~Desc.dwFlags));
	}
}

void ConvertSurfaceDesc(DDSURFACEDESC2 &Desc2, DDSURFACEDESC &Desc)
{
	// Check for supported dwSize
	if (Desc2.dwSize != sizeof(DDSURFACEDESC2) || Desc.dwSize != sizeof(DDSURFACEDESC))
	{
		LOG_LIMIT(100, __FUNCTION__ << " Error: Incorrect dwSize: " << Desc2.dwSize << " " << Desc.dwSize);
		return;
	}
	// Prepare destination structure
	ZeroMemory(&Desc2, sizeof(DDSURFACEDESC2));
	Desc2.dwSize = sizeof(DDSURFACEDESC2);
	// Convert varables
	Desc2.dwFlags = Desc.dwFlags & ~(DDSD_ZBUFFERBITDEPTH | DDSD_TEXTURESTAGE | DDSD_FVF | DDSD_SRCVBHANDLE | DDSD_DEPTH);		// Remove unsupported flags
	Desc2.dwHeight = Desc.dwHeight;
	Desc2.dwWidth = Desc.dwWidth;
	Desc2.lPitch = Desc.lPitch;
	Desc2.dwBackBufferCount = Desc.dwBackBufferCount;
	Desc2.dwRefreshRate = Desc.dwRefreshRate;
	Desc2.dwAlphaBitDepth = Desc.dwAlphaBitDepth;
	Desc2.dwReserved = Desc.dwReserved;
	Desc2.lpSurface = Desc.lpSurface;
	Desc2.ddckCKDestOverlay = Desc.ddckCKDestOverlay;
	Desc2.ddckCKDestBlt = Desc.ddckCKDestBlt;
	Desc2.ddckCKSrcOverlay = Desc.ddckCKSrcOverlay;
	Desc2.ddckCKSrcBlt = Desc.ddckCKSrcBlt;
	if (Desc.dwFlags & DDSD_PIXELFORMAT)
	{
		CopyMemory(&Desc2.ddpfPixelFormat, &Desc.ddpfPixelFormat, sizeof(DDPIXELFORMAT));
		Desc2.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
	}
	if (Desc.dwFlags & DDSD_ZBUFFERBITDEPTH)
	{
		Desc2.ddpfPixelFormat.dwFlags |= DDPF_ZBUFFER;
		Desc2.ddpfPixelFormat.dwZBufferBitDepth = Desc.dwZBufferBitDepth;
		Desc2.dwRefreshRate = 0;	// Union with dwZBufferBitDepth
	}
	ConvertCaps(Desc2.ddsCaps, Desc.ddsCaps);
	// Extra parameters
	Desc2.dwTextureStage = 0;			// Stage identifier that is used to bind a texture to a specific stage
										// Check for dwFlags that did not get converted
	if (Desc2.dwFlags != (Desc.dwFlags & ~DDSD_ZBUFFERBITDEPTH))
	{
		LOG_LIMIT(100, __FUNCTION__ << " Warning: (Desc->Desc2) Removing unsupported flags: " << Logging::hex(Desc.dwFlags & ~Desc2.dwFlags));
	}
}

void ConvertPixelFormat(DDPIXELFORMAT &Format, DDPIXELFORMAT &Format2)
{
	if (Format.dwSize != sizeof(DDPIXELFORMAT) || Format2.dwSize != sizeof(DDPIXELFORMAT))
	{
		LOG_LIMIT(100, __FUNCTION__ << " Error: Incorrect dwSize: " << Format.dwSize << " " << Format2.dwSize);
		return;
	}
	CopyMemory(&Format, &Format2, sizeof(DDPIXELFORMAT));
}

void ConvertDeviceIdentifier(DDDEVICEIDENTIFIER2 &DeviceID, DDDEVICEIDENTIFIER2 &DeviceID2)
{
	CopyMemory(&DeviceID, &DeviceID2, sizeof(DDDEVICEIDENTIFIER2));
}

void ConvertDeviceIdentifier(DDDEVICEIDENTIFIER &DeviceID, DDDEVICEIDENTIFIER2 &DeviceID2)
{
	CopyMemory(&DeviceID, &DeviceID2, sizeof(DDDEVICEIDENTIFIER));
}

void ConvertDeviceIdentifier(DDDEVICEIDENTIFIER2 &DeviceID2, DDDEVICEIDENTIFIER &DeviceID)
{
	CopyMemory(&DeviceID2, &DeviceID, sizeof(DDDEVICEIDENTIFIER));
	// Extra parameters
	DeviceID2.dwWHQLLevel = 0;
}

void ConvertDeviceIdentifier(DDDEVICEIDENTIFIER2 &DeviceID2, D3DADAPTER_IDENTIFIER9 &Identifier9)
{
	memcpy(DeviceID2.szDriver, Identifier9.Driver, MAX_DDDEVICEID_STRING);
	memcpy(DeviceID2.szDescription, Identifier9.Description, MAX_DDDEVICEID_STRING);
	DeviceID2.guidDeviceIdentifier = Identifier9.DeviceIdentifier;
	DeviceID2.liDriverVersion.LowPart = Identifier9.DriverVersion.LowPart;
	DeviceID2.liDriverVersion.HighPart = Identifier9.DriverVersion.HighPart;
	DeviceID2.dwDeviceId = Identifier9.DeviceId;
	DeviceID2.dwRevision = Identifier9.Revision;
	DeviceID2.dwSubSysId = Identifier9.SubSysId;
	DeviceID2.dwVendorId = Identifier9.VendorId;
	DeviceID2.dwWHQLLevel = Identifier9.WHQLLevel;
}

void ConvertCaps(DDSCAPS2 &Caps, DDSCAPS2 &Caps2)
{
	Caps.dwCaps = Caps2.dwCaps;
	Caps.dwCaps2 = Caps2.dwCaps2;
	Caps.dwCaps3 = Caps2.dwCaps3;
	Caps.dwCaps4 = Caps2.dwCaps4;
	Caps.dwVolumeDepth = Caps2.dwVolumeDepth;
}

void ConvertCaps(DDSCAPS &Caps, DDSCAPS2 &Caps2)
{
	Caps.dwCaps = Caps2.dwCaps;
	// Check for dwFlags that did not get converted
	if (Caps2.dwCaps2 || Caps2.dwVolumeDepth)
	{
		LOG_LIMIT(100, __FUNCTION__ << " Warning: Removing unsupported dwCaps2 and dwVolumeDepth: " << Logging::hex(Caps2.dwCaps2) << " " << Caps2.dwVolumeDepth);
	}
}

void ConvertCaps(DDSCAPS2 &Caps2, DDSCAPS &Caps)
{
	Caps2.dwCaps = Caps.dwCaps;
	// Extra parameters
	Caps2.dwCaps2 = 0;				// Additional surface capabilities
	Caps2.dwCaps3 = 0;				// Not used
	Caps2.dwCaps4 = 0;				// Not used
	Caps2.dwVolumeDepth = 0;		// Not used
}

void ConvertCaps(DDCAPS &Caps, DDCAPS &Caps2)
{
	if ((Caps.dwSize != sizeof(DDCAPS_DX1) && Caps.dwSize != sizeof(DDCAPS_DX3) &&
		Caps.dwSize != sizeof(DDCAPS_DX5) && Caps.dwSize != sizeof(DDCAPS_DX6) &&
		Caps.dwSize != sizeof(DDCAPS_DX7)) || (Caps2.dwSize != sizeof(DDCAPS_DX1) &&
		Caps2.dwSize != sizeof(DDCAPS_DX3) && Caps2.dwSize != sizeof(DDCAPS_DX5) &&
		Caps2.dwSize != sizeof(DDCAPS_DX6) && Caps2.dwSize != sizeof(DDCAPS_DX7)))
	{
		LOG_LIMIT(100, __FUNCTION__ << " Error: Incorrect dwSize: " << Caps.dwSize << " " << Caps2.dwSize);
		return;
	}
	DWORD Size = Caps.dwSize;
	ZeroMemory(&Caps, Caps.dwSize);
	Caps.dwSize = Size;
	CopyMemory(&Caps, &Caps2, min(Caps.dwSize, Caps2.dwSize));
	m_IDirectDrawX::AdjustVidMemory(&Caps.dwVidMemTotal, &Caps.dwVidMemFree);
}

void ConvertCaps(DDCAPS &Caps7, D3DCAPS9 &Caps9)
{
	// Note: dwVidMemTotal and dwVidMemFree are not part of D3DCAPS9 and need to be set separately
	if (Caps7.dwSize != sizeof(DDCAPS))
	{
		LOG_LIMIT(100, __FUNCTION__ << " Error: Incorrect dwSize: " << Caps7.dwSize);
		return;
	}
	ZeroMemory(&Caps7, sizeof(DDCAPS));
	Caps7.dwSize = sizeof(DDCAPS);

	// Caps
	Caps7.dwCaps = (Caps9.Caps & (/*D3DCAPS_OVERLAY |*/ D3DCAPS_READ_SCANLINE)) |
		(DDCAPS_3D | DDCAPS_BLT | /*DDCAPS_BLTQUEUE | DDCAPS_BLTFOURCC |*/ DDCAPS_BLTSTRETCH | DDCAPS_GDI | /*DDCAPS_OVERLAYCANTCLIP | DDCAPS_OVERLAYFOURCC |
			DDCAPS_OVERLAYSTRETCH | DDCAPS_ZBLTS |*/ DDCAPS_COLORKEY | /*DDCAPS_ALPHA | DDCAPS_COLORKEYHWASSIST |*/ DDCAPS_BLTCOLORFILL | DDCAPS_CANBLTSYSMEM);
	Caps7.dwCaps2 = (Caps9.Caps2 & (D3DCAPS2_FULLSCREENGAMMA | D3DCAPS2_CANCALIBRATEGAMMA /*| D3DCAPS2_CANMANAGERESOURCE | D3DCAPS2_DYNAMICTEXTURES | D3DCAPS2_CANAUTOGENMIPMAP | D3DCAPS2_CANSHARERESOURCE*/)) |
		(DDCAPS2_CANBOBINTERLEAVED | DDCAPS2_CANBOBNONINTERLEAVED | /*DDCAPS2_NONLOCALVIDMEM |*/ DDCAPS2_WIDESURFACES | /*DDCAPS2_CANFLIPODDEVEN | DDCAPS2_COPYFOURCC |*/
			DDCAPS2_PRIMARYGAMMA | /*DDCAPS2_CANRENDERWINDOWED | DDCAPS2_FLIPINTERVAL |*/ DDCAPS2_FLIPNOVSYNC);
	Caps7.dwCKeyCaps = (DDCKEYCAPS_DESTBLT | DDCKEYCAPS_DESTBLTCLRSPACE | /*DDCKEYCAPS_DESTOVERLAY | DDCKEYCAPS_DESTOVERLAYCLRSPACE |*/ DDCKEYCAPS_SRCBLT | DDCKEYCAPS_SRCBLTCLRSPACE
		/*| DDCKEYCAPS_SRCOVERLAY | DDCKEYCAPS_SRCOVERLAYCLRSPACE*/);
	Caps7.dwFXCaps = (DDFXCAPS_BLTARITHSTRETCHY | DDFXCAPS_BLTMIRRORLEFTRIGHT | DDFXCAPS_BLTMIRRORUPDOWN | DDFXCAPS_BLTSHRINKX | DDFXCAPS_BLTSHRINKY | DDFXCAPS_BLTSTRETCHX |
		DDFXCAPS_BLTSTRETCHY /*| DDFXCAPS_OVERLAYARITHSTRETCHY | DDFXCAPS_OVERLAYSHRINKX | DDFXCAPS_OVERLAYSHRINKY | DDFXCAPS_OVERLAYSTRETCHX | DDFXCAPS_OVERLAYSTRETCHY |
		DDFXCAPS_OVERLAYMIRRORLEFTRIGHT | DDFXCAPS_OVERLAYMIRRORUPDOWN | DDFXCAPS_OVERLAYDEINTERLACE*/);

	// ddsCaps
	Caps7.ddsCaps.dwCaps = (DDSCAPS_3DDEVICE | DDSCAPS_BACKBUFFER | DDSCAPS_COMPLEX | DDSCAPS_FLIP | DDSCAPS_FRONTBUFFER | DDSCAPS_LOCALVIDMEM | /*DDSCAPS_MIPMAP | DDSCAPS_NONLOCALVIDMEM |*/
		DDSCAPS_OFFSCREENPLAIN | /*DDSCAPS_OVERLAY | DDSCAPS_OWNDC |*/ DDSCAPS_PRIMARYSURFACE | /*DDSCAPS_TEXTURE |*/ DDSCAPS_VIDEOMEMORY /*| DDSCAPS_ZBUFFER*/);
	Caps7.ddsCaps.dwCaps2 = 0 /*| DDSCAPS2_CUBEMAP*/;		// Additional surface capabilities
	Caps7.ddsCaps.dwCaps3 = 0;								// Not used
	Caps7.ddsCaps.dwCaps4 = 0;								// Not used
	Caps7.ddsCaps.dwVolumeDepth = 0;						// Not used
	Caps7.ddsOldCaps.dwCaps = Caps7.ddsCaps.dwCaps;

	// FourCCs
	if (Caps7.dwCaps & DDCAPS_BLTFOURCC)
	{
		Caps7.dwNumFourCCCodes = NumFourCCs;
	}

	// Overlay
	if (Caps7.dwCaps & DDCAPS_OVERLAY)
	{
		Caps7.dwMaxVisibleOverlays = 0x1;
		Caps7.dwMinOverlayStretch = 0x1;
		Caps7.dwMaxOverlayStretch = 0x4e20;
	}
	// Raster Operations
	Caps7.dwRops[DD_ROP_SPACE] = 4096;
	Caps7.dwSSBRops[DD_ROP_SPACE] = Caps7.dwRops[DD_ROP_SPACE];
	Caps7.dwVSBRops[DD_ROP_SPACE] = Caps7.dwRops[DD_ROP_SPACE];
	Caps7.dwSVBRops[DD_ROP_SPACE] = Caps7.dwRops[DD_ROP_SPACE];
	if (Caps7.dwCaps2 & DDCAPS2_NONLOCALVIDMEM)
	{
		Caps7.dwNLVBRops[DD_ROP_SPACE] = Caps7.dwRops[DD_ROP_SPACE];
	}

	// Bit Blt Caps
	DWORD BitBltCaps = DDCAPS_BLT | DDCAPS_BLTQUEUE | DDCAPS_BLTFOURCC | DDCAPS_BLTSTRETCH | DDCAPS_ZBLTS | DDCAPS_BLTCOLORFILL | DDCAPS_BLTDEPTHFILL | DDCAPS_CANBLTSYSMEM;
	DWORD BitBltCaps2 = DDCAPS2_COPYFOURCC;
	Caps7.dwSSBCaps = Caps7.dwCaps & BitBltCaps;
	Caps7.dwVSBCaps = Caps7.dwCaps & BitBltCaps;
	Caps7.dwSVBCaps = Caps7.dwCaps & BitBltCaps;
	Caps7.dwSVBCaps2 = Caps7.dwCaps2 & BitBltCaps2;
	if (Caps7.dwCaps2 & DDCAPS2_NONLOCALVIDMEM)
	{
		Caps7.dwNLVBCaps = Caps7.dwCaps & BitBltCaps;
		Caps7.dwNLVBCaps2 = Caps7.dwCaps2 & BitBltCaps2;
	}

	// Color Key Caps
	DWORD BitBltCK = DDCKEYCAPS_DESTBLT | DDCKEYCAPS_DESTBLTCLRSPACE | DDCKEYCAPS_DESTBLTCLRSPACEYUV | DDCKEYCAPS_DESTBLTYUV | DDCKEYCAPS_SRCBLT | DDCKEYCAPS_SRCBLTCLRSPACE
		| DDCKEYCAPS_SRCBLTCLRSPACEYUV | DDCKEYCAPS_SRCBLTYUV;
	Caps7.dwSSBCKeyCaps = Caps7.dwCKeyCaps & BitBltCK;
	Caps7.dwVSBCKeyCaps = Caps7.dwCKeyCaps & BitBltCK;
	Caps7.dwSVBCKeyCaps = Caps7.dwCKeyCaps & BitBltCK;
	if (Caps7.dwCaps2 & DDCAPS2_NONLOCALVIDMEM)
	{
		Caps7.dwNLVBCKeyCaps = Caps7.dwCKeyCaps & BitBltCK;
	}

	// FX Caps
	DWORD BitBltFX = DDFXCAPS_BLTARITHSTRETCHY | DDFXCAPS_BLTARITHSTRETCHYN | DDFXCAPS_BLTMIRRORLEFTRIGHT | DDFXCAPS_BLTMIRRORUPDOWN | DDFXCAPS_BLTROTATION | DDFXCAPS_BLTROTATION90 |
		DDFXCAPS_BLTSHRINKX | DDFXCAPS_BLTSHRINKXN | DDFXCAPS_BLTSHRINKY | DDFXCAPS_BLTSHRINKYN | DDFXCAPS_BLTSTRETCHX | DDFXCAPS_BLTSTRETCHXN | DDFXCAPS_BLTSTRETCHY |
		DDFXCAPS_BLTSTRETCHYN | DDFXCAPS_BLTALPHA;
	Caps7.dwSSBFXCaps = Caps7.dwFXCaps & BitBltFX;
	Caps7.dwVSBFXCaps = Caps7.dwFXCaps & BitBltFX;
	Caps7.dwSVBFXCaps = Caps7.dwFXCaps & BitBltFX;
	if (Caps7.dwCaps2 & DDCAPS2_NONLOCALVIDMEM)
	{
		Caps7.dwNLVBFXCaps = Caps7.dwFXCaps & BitBltFX;
	}

	// Live video ports
	Caps7.dwMaxVideoPorts = 0;
	Caps7.dwCurrVideoPorts = 0;
}

DWORD GetBitCount(DDPIXELFORMAT ddpfPixelFormat)
{
	if (ddpfPixelFormat.dwSize != sizeof(DDPIXELFORMAT))
	{
		LOG_LIMIT(100, __FUNCTION__ << " Error: Incorrect dwSize: " << ddpfPixelFormat.dwSize);
		return 0;
	}
	if (ddpfPixelFormat.dwRGBBitCount && (ddpfPixelFormat.dwFlags &
		(DDPF_RGB | DDPF_YUV | DDPF_ALPHA | DDPF_ZBUFFER | DDPF_LUMINANCE | DDPF_BUMPDUDV | DDPF_STENCILBUFFER | DDPF_PALETTEINDEXEDTO8)))
	{
		return ddpfPixelFormat.dwRGBBitCount;
	}
	if (ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED8)
	{
		return 8;
	}
	if (ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED4)
	{
		return 4;
	}
	if (ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED2)
	{
		return 2;
	}
	if (ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED1)
	{
		return 1;
	}
	if (ddpfPixelFormat.dwFlags & DDPF_FOURCC)
	{
		switch (ddpfPixelFormat.dwFourCC)
		{
		case D3DFMT_UYVY:
		case D3DFMT_YUY2:
			return 2;
		}
	}

	LOG_LIMIT(100, __FUNCTION__ << " Error: failed to get BitCount from PixelFormat! " << ddpfPixelFormat);
	return 0;
}

// https://github.com/microsoft/Windows-driver-samples/blob/master/video/pixlib/pixel.cpp
DWORD GetBitCount(D3DFORMAT Format)
{
	switch (DWORD(Format))
	{
	case D3DFMT_DXT1:
		// Size is negative to indicate DXT; and indicates
		// the size of the block
		return (UINT)(-8 * 8);

	case D3DFMT_DXT2:
	case D3DFMT_DXT3:
	case D3DFMT_DXT4:
	case D3DFMT_DXT5:
		// Size is negative to indicate DXT; and indicates
		// the size of the block
		return (UINT)(-16 * 8);

	case D3DFMT_A32B32G32R32F:
		return 16 * 8;

	case D3DFMT_A16B16G16R16:
	case D3DFMT_Q16W16V16U16:
	case D3DFMT_A16B16G16R16F:
	case D3DFMT_G32R32F:
	case D3DFMT_MULTI2_ARGB8:
		return 8 * 8;

	case D3DFMT_A8R8G8B8:
	case D3DFMT_X8R8G8B8:
	case D3DFMT_D32:
	case D3DFMT_D24S8:
	case D3DFMT_S8D24:
	case D3DFMT_X8L8V8U8:
	case D3DFMT_X4S4D24:
	case D3DFMT_D24X4S4:
	case D3DFMT_Q8W8V8U8:
	case D3DFMT_V16U16:
	case D3DFMT_A2W10V10U10:
	case D3DFMT_A2B10G10R10:
	case D3DFMT_A8B8G8R8:
	case D3DFMT_X8B8G8R8:
	case D3DFMT_G16R16:
	case D3DFMT_D24X8:
	case D3DFMT_X8D24:
	case D3DFMT_W11V11U10:
	case D3DFMT_A2R10G10B10:
	case D3DFMT_G16R16F:
	case D3DFMT_R32F:
	case D3DFMT_D32F_LOCKABLE:
	case D3DFMT_D24FS8:
	case D3DFMT_D32_LOCKABLE:
		return 4 * 8;

	case D3DFMT_R8G8B8:
		return 3 * 8;

	case D3DFMT_R5G6B5:
	case D3DFMT_X1R5G5B5:
	case D3DFMT_A1R5G5B5:
	case D3DFMT_A4R4G4B4:
	case D3DFMT_A8L8:
	case D3DFMT_V8U8:
	case D3DFMT_L6V5U5:
	case D3DFMT_D16:
	case D3DFMT_D16_LOCKABLE:
	case D3DFMT_D15S1:
	case D3DFMT_S1D15:
	case D3DFMT_A8P8:
	case D3DFMT_A8R3G3B2:
	case D3DFMT_UYVY:
	case D3DFMT_YUY2:
	case D3DFMT_X4R4G4B4:
	case D3DFMT_CxV8U8:
	case D3DFMT_L16:
	case D3DFMT_R16F:
	case D3DFMT_R8G8_B8G8:
	case D3DFMT_G8R8_G8B8:
		return 2 * 8;

	case D3DFMT_P8:
	case D3DFMT_L8:
	case D3DFMT_R3G3B2:
	case D3DFMT_A4L4:
	case D3DFMT_A8:
	case D3DFMT_A1:
	case D3DFMT_S8_LOCKABLE:
		return 1 * 8;

	default:
		LOG_LIMIT(100, __FUNCTION__ << " Display format not Implemented: " << Format);
		return 0;
	};
}

D3DFORMAT GetDisplayFormat(DDPIXELFORMAT ddpfPixelFormat)
{
	if (ddpfPixelFormat.dwSize != sizeof(DDPIXELFORMAT))
	{
		LOG_LIMIT(100, __FUNCTION__ << " Error: Incorrect dwSize: " << ddpfPixelFormat.dwSize);
		return D3DFMT_UNKNOWN;
	}
	if (ddpfPixelFormat.dwFlags & (DDPF_PALETTEINDEXED1 | DDPF_PALETTEINDEXED2 | DDPF_PALETTEINDEXED4))
	{
		LOG_LIMIT(100, __FUNCTION__ << " Error: 1-bit, 2-bit and 4-bit palette formats not Implemented");
		return D3DFMT_UNKNOWN;
	}
	if (ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXEDTO8)
	{
		LOG_LIMIT(100, __FUNCTION__ << " Error: 8-bit indexed to palette format not Implemented");
		return D3DFMT_UNKNOWN;
	}
	if (ddpfPixelFormat.dwFlags & DDPF_FOURCC)
	{
		switch (ddpfPixelFormat.dwFourCC)
		{
		case D3DFMT_DXT1:
		case D3DFMT_DXT2:
		case D3DFMT_DXT3:
		case D3DFMT_DXT4:
		case D3DFMT_DXT5:
		case D3DFMT_UYVY:
		case D3DFMT_YUY2:
			LOG_LIMIT(100, __FUNCTION__ << " Using format: " << (D3DFORMAT)ddpfPixelFormat.dwFourCC);
			return (D3DFORMAT)ddpfPixelFormat.dwFourCC;
		}

		LOG_LIMIT(100, __FUNCTION__ << " Error: FourCC format not Implemented. Code = " << (DDFOURCC)ddpfPixelFormat.dwFourCC);
		return D3DFMT_UNKNOWN;
	}
	if (ddpfPixelFormat.dwFlags & DDPF_YUV)
	{
		LOG_LIMIT(100, __FUNCTION__ << " Error: YUV format not Implemented");
	}
	if (ddpfPixelFormat.dwFlags & DDPF_RGBTOYUV)
	{
		LOG_LIMIT(100, __FUNCTION__ << " Warning: RGB to YUV format not Implemented");
	}
	if (ddpfPixelFormat.dwFlags & DDPF_ALPHAPREMULT)
	{
		LOG_LIMIT(100, __FUNCTION__ << " Warning: premultiplied alpha format not Implemented");
	}
	if (ddpfPixelFormat.dwFlags & DDPF_ZPIXELS)
	{
		LOG_LIMIT(100, __FUNCTION__ << " Warning: z-pixels not Implemented");
	}

	if (ddpfPixelFormat.dwFlags & (DDPF_RGB | DDPF_PALETTEINDEXED8 | DDPF_LUMINANCE | DDPF_ALPHA))
	{
		DWORD BitCount = GetBitCount(ddpfPixelFormat);
		switch (BitCount)
		{
		case 8:
			if ((ddpfPixelFormat.dwFlags & DDPF_ALPHAPIXELS) && (ddpfPixelFormat.dwLuminanceAlphaBitMask == 0xF0) &&
				(ddpfPixelFormat.dwFlags & DDPF_LUMINANCE) && (ddpfPixelFormat.dwLuminanceBitMask == 0x0F))
			{
				return D3DFMT_A4L4;
			}
			if ((ddpfPixelFormat.dwFlags & DDPF_ALPHA) && (ddpfPixelFormat.dwRGBAlphaBitMask == 0xFF))
			{
				return D3DFMT_A8;
			}
			if ((ddpfPixelFormat.dwFlags & DDPF_LUMINANCE) && (ddpfPixelFormat.dwLuminanceBitMask == 0xFF))
			{
				return D3DFMT_L8;
			}
			if (ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED8)
			{
				return D3DFMT_P8;
			}
			break;
		case 16:
			if ((ddpfPixelFormat.dwFlags & DDPF_ALPHAPIXELS) && (ddpfPixelFormat.dwLuminanceAlphaBitMask == 0xFF00) &&
				(ddpfPixelFormat.dwFlags & DDPF_LUMINANCE) && (ddpfPixelFormat.dwLuminanceBitMask == 0xFF))
			{
				return D3DFMT_A8L8;
			}
			if ((ddpfPixelFormat.dwRBitMask == 0x7C00) && (ddpfPixelFormat.dwGBitMask == 0x3E0) && (ddpfPixelFormat.dwBBitMask == 0x1F))
			{
				if ((ddpfPixelFormat.dwFlags & DDPF_ALPHAPIXELS) && (ddpfPixelFormat.dwRGBAlphaBitMask == 0x8000))
				{
					return D3DFMT_A1R5G5B5;
				}
				else if (ddpfPixelFormat.dwRGBAlphaBitMask == 0x00)
				{
					return D3DFMT_X1R5G5B5;
				}
			}
			if ((ddpfPixelFormat.dwRBitMask == 0xF800) && (ddpfPixelFormat.dwGBitMask == 0x7E0) && (ddpfPixelFormat.dwBBitMask == 0x1F))
			{
				return D3DFMT_R5G6B5;
			}
			if ((ddpfPixelFormat.dwRBitMask == 0xF00) && (ddpfPixelFormat.dwGBitMask == 0xF0) && (ddpfPixelFormat.dwBBitMask == 0xF) &&
				(ddpfPixelFormat.dwFlags & DDPF_ALPHAPIXELS) && (ddpfPixelFormat.dwRGBAlphaBitMask == 0xF000))
			{
				return D3DFMT_A4R4G4B4;
			}
			break;
		case 24:
			if ((ddpfPixelFormat.dwRBitMask == 0xFF0000) && (ddpfPixelFormat.dwGBitMask == 0xFF00) && (ddpfPixelFormat.dwBBitMask == 0xFF))
			{
				return D3DFMT_R8G8B8;
			}
			break;
		case 32:
			if ((ddpfPixelFormat.dwRBitMask == 0xFF0000) && (ddpfPixelFormat.dwGBitMask == 0xFF00) && (ddpfPixelFormat.dwBBitMask == 0xFF))
			{
				if ((ddpfPixelFormat.dwFlags & DDPF_ALPHAPIXELS) && (ddpfPixelFormat.dwRGBAlphaBitMask == 0xFF000000))
				{
					return D3DFMT_A8R8G8B8;
				}
				else if (ddpfPixelFormat.dwRGBAlphaBitMask == 0x00)
				{
					return D3DFMT_X8R8G8B8;
				}
			}
			if ((ddpfPixelFormat.dwRBitMask == 0x3FF00000) && (ddpfPixelFormat.dwGBitMask == 0xFFC00) && (ddpfPixelFormat.dwBBitMask == 0x3FF) &&
				(ddpfPixelFormat.dwFlags & DDPF_ALPHAPIXELS) && (ddpfPixelFormat.dwRGBAlphaBitMask == 0xC0000000))
			{
				return D3DFMT_A2R10G10B10;
			}
			break;
		}

		LOG_LIMIT(100, __FUNCTION__ << " Error: could not find RGB format for PixelFormat: " << ddpfPixelFormat);
		return D3DFMT_UNKNOWN;
	}

	// zBuffer formats
	if (ddpfPixelFormat.dwFlags & (DDPF_ZBUFFER | DDPF_STENCILBUFFER))
	{
		if (ddpfPixelFormat.dwFlags == DDPF_ZBUFFER && ddpfPixelFormat.dwZBufferBitDepth == 16 && ddpfPixelFormat.dwZBitMask == 0xFFFF)
		{
			return D3DFMT_D16;
		}
		if (ddpfPixelFormat.dwFlags == DDPF_ZBUFFER && ddpfPixelFormat.dwZBufferBitDepth == 32 && ddpfPixelFormat.dwZBitMask == 0xFFFFFF00)
		{
			return D3DFMT_D24X8;
		}
		if (ddpfPixelFormat.dwFlags == (DDPF_ZBUFFER | DDPF_STENCILBUFFER) && ddpfPixelFormat.dwZBufferBitDepth == 32 && ddpfPixelFormat.dwStencilBitDepth == 8 &&
			ddpfPixelFormat.dwZBitMask == 0xFFFFFF00 && ddpfPixelFormat.dwStencilBitMask == 0xFF)
		{
			return D3DFMT_D24S8;
		}
		if (ddpfPixelFormat.dwFlags == (DDPF_ZBUFFER | DDPF_STENCILBUFFER) && ddpfPixelFormat.dwZBufferBitDepth == 32 && ddpfPixelFormat.dwStencilBitDepth == 4 &&
			ddpfPixelFormat.dwZBitMask == 0xFFFFFF00 && ddpfPixelFormat.dwStencilBitMask == 0xF)
		{
			return D3DFMT_D24X4S4;
		}

		LOG_LIMIT(100, __FUNCTION__ << " Error: could not find z-buffer format for PixelFormat: " << ddpfPixelFormat);
		return D3DFMT_UNKNOWN;
	}

	LOG_LIMIT(100, __FUNCTION__ << " Error: PixelFormat not implemented: " << ddpfPixelFormat);
	return D3DFMT_UNKNOWN;
}

void SetPixelDisplayFormat(D3DFORMAT Format, DDPIXELFORMAT &ddpfPixelFormat)
{
	if (ddpfPixelFormat.dwSize != sizeof(DDPIXELFORMAT))
	{
		LOG_LIMIT(100, __FUNCTION__ << " Error: Incorrect dwSize: " << ddpfPixelFormat.dwSize);
		return;
	}

	// Initialize pixel format
	ddpfPixelFormat.dwFlags = DDPF_RGB;
	ddpfPixelFormat.dwFourCC = 0;
	ddpfPixelFormat.dwRGBBitCount = (Format & 0xFF000000) ? 0 : GetBitCount(Format);
	ddpfPixelFormat.dwRBitMask = 0x0;
	ddpfPixelFormat.dwGBitMask = 0x0;
	ddpfPixelFormat.dwBBitMask = 0x0;
	ddpfPixelFormat.dwRGBAlphaBitMask = 0x0;

	// Set BitCount and BitMask
	switch (Format)
	{
	case D3DFMT_A4R4G4B4:
		ddpfPixelFormat.dwFlags |= DDPF_ALPHAPIXELS;
		ddpfPixelFormat.dwRGBAlphaBitMask = 0xF000;
		ddpfPixelFormat.dwRBitMask = 0xF00;
		ddpfPixelFormat.dwGBitMask = 0xF0;
		ddpfPixelFormat.dwBBitMask = 0xF;
		break;
	case D3DFMT_R5G6B5:
		ddpfPixelFormat.dwRBitMask = 0xF800;
		ddpfPixelFormat.dwGBitMask = 0x7E0;
		ddpfPixelFormat.dwBBitMask = 0x1F;
		break;
	case D3DFMT_A1R5G5B5:
		ddpfPixelFormat.dwFlags |= DDPF_ALPHAPIXELS;
		ddpfPixelFormat.dwRGBAlphaBitMask = 0x8000;
	case D3DFMT_X1R5G5B5:
		ddpfPixelFormat.dwRBitMask = 0x7C00;
		ddpfPixelFormat.dwGBitMask = 0x3E0;
		ddpfPixelFormat.dwBBitMask = 0x1F;
		break;
	case D3DFMT_A8R8G8B8:
		ddpfPixelFormat.dwFlags |= DDPF_ALPHAPIXELS;
		ddpfPixelFormat.dwRGBAlphaBitMask = 0xFF000000;
	case D3DFMT_R8G8B8:
	case D3DFMT_X8R8G8B8:
		ddpfPixelFormat.dwRBitMask = 0xFF0000;
		ddpfPixelFormat.dwGBitMask = 0xFF00;
		ddpfPixelFormat.dwBBitMask = 0xFF;
		break;
	case D3DFMT_A2R10G10B10:
		ddpfPixelFormat.dwFlags |= DDPF_ALPHAPIXELS;
		ddpfPixelFormat.dwRGBAlphaBitMask = 0xC0000000;
		ddpfPixelFormat.dwRBitMask = 0x3FF00000;
		ddpfPixelFormat.dwGBitMask = 0xFFC00;
		ddpfPixelFormat.dwBBitMask = 0x3FF;
		break;
	case D3DFMT_V8U8:
		ddpfPixelFormat.dwFlags = DDPF_BUMPDUDV;
		ddpfPixelFormat.dwBumpDuBitMask = 0xFF;
		ddpfPixelFormat.dwBumpDvBitMask = 0xFF00;
		break;
	case D3DFMT_X8L8V8U8:
		ddpfPixelFormat.dwFlags = DDPF_BUMPLUMINANCE | DDPF_BUMPDUDV;
		ddpfPixelFormat.dwBumpDuBitMask = 0xFF;
		ddpfPixelFormat.dwBumpDvBitMask = 0xFF00;
		ddpfPixelFormat.dwBumpLuminanceBitMask = 0xFF0000;
		break;
	case D3DFMT_P8:
		ddpfPixelFormat.dwFlags |= DDPF_PALETTEINDEXED8;
		break;
	case D3DFMT_A8:
		ddpfPixelFormat.dwFlags = DDPF_ALPHA;
		ddpfPixelFormat.dwRGBAlphaBitMask = 0xFF;
		break;
	case D3DFMT_L8:
		ddpfPixelFormat.dwFlags = DDPF_LUMINANCE;
		ddpfPixelFormat.dwLuminanceBitMask = 0xFF;
		break;
	case D3DFMT_A4L4:
		ddpfPixelFormat.dwFlags = DDPF_ALPHAPIXELS | DDPF_LUMINANCE;
		ddpfPixelFormat.dwLuminanceAlphaBitMask = 0xF0;
		ddpfPixelFormat.dwLuminanceBitMask = 0x0F;
		break;
	case D3DFMT_A8L8:
		ddpfPixelFormat.dwFlags = DDPF_ALPHAPIXELS | DDPF_LUMINANCE;
		ddpfPixelFormat.dwLuminanceAlphaBitMask = 0xFF00;
		ddpfPixelFormat.dwLuminanceBitMask = 0xFF;
		break;

	// zBuffer formats
	case D3DFMT_D16:
		ddpfPixelFormat.dwFlags = DDPF_ZBUFFER;
		ddpfPixelFormat.dwZBitMask = 0xFFFF;
		break;
	case D3DFMT_D24X8:
		ddpfPixelFormat.dwFlags = DDPF_ZBUFFER;
		ddpfPixelFormat.dwZBitMask = 0xFFFFFF00;
		break;
	case D3DFMT_D24S8:
		ddpfPixelFormat.dwFlags = DDPF_ZBUFFER | DDPF_STENCILBUFFER;
		ddpfPixelFormat.dwStencilBitDepth = 8;
		ddpfPixelFormat.dwZBitMask = 0xFFFFFF00;
		ddpfPixelFormat.dwStencilBitMask = 0xFF;
		break;
	case D3DFMT_D24X4S4:
		ddpfPixelFormat.dwFlags = DDPF_ZBUFFER | DDPF_STENCILBUFFER;
		ddpfPixelFormat.dwStencilBitDepth = 4;
		ddpfPixelFormat.dwZBitMask = 0xFFFFFF00;
		ddpfPixelFormat.dwStencilBitMask = 0x0F;
		break;
	default:
		// FourCC
		if (Format & 0xFF000000)
		{
			ddpfPixelFormat.dwFlags = DDPF_FOURCC;
			ddpfPixelFormat.dwFourCC = Format;
			break;
		}
		// Not supported
		else
		{
			LOG_LIMIT(100, __FUNCTION__ << " Display format not Implemented: " << Format);
			ddpfPixelFormat.dwFlags = 0;
			ddpfPixelFormat.dwRGBBitCount = 0;
			return;
		}
	}
}

HRESULT SetDisplayFormat(DWORD BPP, DDPIXELFORMAT &ddpfPixelFormat)
{
	switch (BPP)
	{
	case 8:
		SetPixelDisplayFormat(D3DFMT_P8, ddpfPixelFormat);
		break;
	case 16:
		SetPixelDisplayFormat(D3DFMT_R5G6B5, ddpfPixelFormat);
		break;
	case 24:
		SetPixelDisplayFormat(D3DFMT_R8G8B8, ddpfPixelFormat);
		break;
	case 32:
		SetPixelDisplayFormat(D3DFMT_X8R8G8B8, ddpfPixelFormat);
		break;
	default:
		LOG_LIMIT(100, __FUNCTION__ << " Error: Bit mode not supported: " << BPP);
		ddpfPixelFormat.dwFlags = 0;
		ddpfPixelFormat.dwFourCC = 0;
		ddpfPixelFormat.dwRGBBitCount = 0;
		ddpfPixelFormat.dwRBitMask = 0x0;
		ddpfPixelFormat.dwGBitMask = 0x0;
		ddpfPixelFormat.dwBBitMask = 0x0;
		ddpfPixelFormat.dwRGBAlphaBitMask = 0x0;
		return DDERR_UNSUPPORTED;
	}
	return DD_OK;
}

DWORD ComputePitch(DWORD Width, DWORD BitCount)
{
	return ((((Width * BitCount) + 31) & ~31) >> 3);	// Use Surface Stride for pitch
}
