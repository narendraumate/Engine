//
//  Color.h
//  Camaleao
//
//  Created by Narendra Umate on 10/5/12.
//  Copyright (c) 2012 Narendra Umate. All rights reserved.
//

#ifndef __Camaleao__Color__
#define __Camaleao__Color__

#include <iostream>
#include "../Mathematics/Vector.h"

#if defined(__linux__) || defined(_WIN32)
#include <stdint.h>
#endif //defined(__linux__) || defined(_WIN32)

//----------------------------------------------------------------------------//
//  Endian  First Byte Low Address  Last Byte High Address  1000	Decimal   //
//  Big		Most Significant		Least Significant		03E8	Straight  //
//  Little  Least Significant		Most Significant		E803	Reverse   //
//----------------------------------------------------------------------------//

#if defined __LITTLE_ENDIAN__
#define RGBA(r, g, b, a) (a << 24 | b << 16 | g << 8 | r)   //  A8B8G8R8
#else
#define RGBA(r, g, b, a) (r << 24 | g << 16 | b << 8 | a)   //  R8G8B8A8
#endif

//  Reference
//  http://en.wikipedia.org/wiki/Webcolors


namespace Engine
{

	//  Color

	enum Color
	{
		//  Red colors
		IndianRed               = RGBA(0xCD, 0x5C, 0x5C, 0xFF), //  205  92  92 255
		LightCoral              = RGBA(0xF0, 0x80, 0x80, 0xFF), //  240 128 128 255
		Salmon                  = RGBA(0xFA, 0x80, 0x72, 0xFF), //  250 128 114 255
		DarkSalmon              = RGBA(0xE9, 0x96, 0x7A, 0xFF), //  233 150 122 255
		LightSalmon             = RGBA(0xFF, 0xA0, 0x7A, 0xFF), //  255 160 122 255
		Red                     = RGBA(0xFF, 0x00, 0x00, 0xFF), //  255   0   0 255
		Crimson                 = RGBA(0xDC, 0x14, 0x3C, 0xFF), //  220  20  60 255
		FireBrick               = RGBA(0xB2, 0x22, 0x22, 0xFF), //  178  34  34 255
		DarkRed                 = RGBA(0x8B, 0x00, 0x00, 0xFF), //  139   0   0 255

		//  Pink colors
		Pink                    = RGBA(0xFF, 0xC0, 0xCB, 0xFF), //  255 192 203 255
		LightPink               = RGBA(0xFF, 0xB6, 0xC1, 0xFF), //  255 182 193 255
		HotPink                 = RGBA(0xFF, 0x69, 0xB4, 0xFF), //  255 105 180 255
		DeepPink                = RGBA(0xFF, 0x14, 0x93, 0xFF), //  255  20 147 255
		MediumVioletRed         = RGBA(0xC7, 0x15, 0x85, 0xFF), //  199  21 133 255
		PaleVioletRed           = RGBA(0xDB, 0x70, 0x93, 0xFF), //  219 112 147 255

		//  Orange colors
		Coral                   = RGBA(0xFF, 0x7F, 0x50, 0xFF), //  255 127  80 255
		Tomato                  = RGBA(0xFF, 0x63, 0x47, 0xFF), //  255  99  71 255
		OrangeRed               = RGBA(0xFF, 0x45, 0x00, 0xFF), //  255  69   0 255
		DarkOrange              = RGBA(0xFF, 0x8C, 0x00, 0xFF), //  255 140   0 255
		Orange                  = RGBA(0xFF, 0xA5, 0x00, 0xFF), //  255 165   0 255

		//  Yellow colors
		Gold                    = RGBA(0xFF, 0xD7, 0x00, 0xFF), //  255 215   0 255
		Yellow                  = RGBA(0xFF, 0xFF, 0x00, 0xFF), //  255 255   0 255
		LightYellow             = RGBA(0xFF, 0xFF, 0xE0, 0xFF), //  255 255 224 255
		LemonChiffon            = RGBA(0xFF, 0xFA, 0xCD, 0xFF), //  255 250 205 255
		LightGoldenrodYellow    = RGBA(0xFA, 0xFA, 0xD2, 0xFF), //  250 250 210 255
		PapayaWhip              = RGBA(0xFF, 0xEF, 0xD5, 0xFF), //  255 239 213 255
		Moccasin                = RGBA(0xFF, 0xE4, 0xB5, 0xFF), //  255 228 181 255
		PeachPuff               = RGBA(0xFF, 0xDA, 0xB9, 0xFF), //  255 218 185 255
		PaleGoldenrod           = RGBA(0xEE, 0xE8, 0xAA, 0xFF), //  238 232 170 255
		Khaki                   = RGBA(0xF0, 0xE6, 0x8C, 0xFF), //  240 230 140 255
		DarkKhaki               = RGBA(0xBD, 0xB7, 0x6B, 0xFF), //  189 183 107 255

		//  Purple colors
		Lavender                = RGBA(0xE6, 0xE6, 0xFA, 0xFF), //  230 230 250 255
		Thistle                 = RGBA(0xD8, 0xBF, 0xD8, 0xFF), //  216 191 216 255
		Plum                    = RGBA(0xDD, 0xA0, 0xDD, 0xFF), //  221 160 221 255
		Violet                  = RGBA(0xEE, 0x82, 0xEE, 0xFF), //  238 130 238 255
		Orchid                  = RGBA(0xDA, 0x70, 0xD6, 0xFF), //  218 112 214 255
		Fuchsia                 = RGBA(0xFF, 0x00, 0xFF, 0xFF), //  255   0 255 255
		Magenta                 = RGBA(0xFF, 0x00, 0xFF, 0xFF), //  255   0 255 255
		MediumOrchid            = RGBA(0xBA, 0x55, 0xD3, 0xFF), //  186  85 211 255
		MediumPurple            = RGBA(0x93, 0x70, 0xDB, 0xFF), //  147 112 219 255
		BlueViolet              = RGBA(0x8A, 0x2B, 0xE2, 0xFF), //  138  43 226 255
		DarkViolet              = RGBA(0x94, 0x00, 0xD3, 0xFF), //  148   0 211 255
		DarkOrchid              = RGBA(0x99, 0x32, 0xCC, 0xFF), //  153  50 204 255
		DarkMagenta             = RGBA(0x8B, 0x00, 0x8B, 0xFF), //  139   0 139 255
		Purple                  = RGBA(0x80, 0x00, 0x80, 0xFF), //  128   0 128 255
		Indigo                  = RGBA(0x4B, 0x00, 0x82, 0xFF), //   75   0 130 255
		DarkSlateBlue           = RGBA(0x48, 0x3D, 0x8B, 0xFF), //   72  61 139 255
		SlateBlue               = RGBA(0x6A, 0x5A, 0xCD, 0xFF), //  106  90 205 255
		MediumSlateBlue         = RGBA(0x7B, 0x68, 0xEE, 0xFF), //  123 104 238 255

		//  Green colors
		GreenYellow             = RGBA(0xAD, 0xFF, 0x2F, 0xFF), //  173 255  47 255
		Chartreuse              = RGBA(0x7F, 0xFF, 0x00, 0xFF), //  127 255   0 255
		LawnGreen               = RGBA(0x7C, 0xFC, 0x00, 0xFF), //  124 252   0 255
		Lime                    = RGBA(0x00, 0xFF, 0x00, 0xFF), //    0 255   0 255
		LimeGreen               = RGBA(0x32, 0xCD, 0x32, 0xFF), //   50 205  50 255
		PaleGreen               = RGBA(0x98, 0xFB, 0x98, 0xFF), //  152 251 152 255
		LightGreen              = RGBA(0x90, 0xEE, 0x90, 0xFF), //  144 238 144 255
		MediumSpringGreen       = RGBA(0x00, 0xFA, 0x9A, 0xFF), //    0 250 154 255
		SpringGreen             = RGBA(0x00, 0xFF, 0x7F, 0xFF), //    0 255 127 255
		MediumSeaGreen          = RGBA(0x3C, 0xB3, 0x71, 0xFF), //   60 179 113 255
		SeaGreen                = RGBA(0x2E, 0x8B, 0x57, 0xFF), //   46 139  87 255
		ForestGreen             = RGBA(0x22, 0x8B, 0x22, 0xFF), //   34 139  34 255
		Green                   = RGBA(0x00, 0x80, 0x00, 0xFF), //    0 128   0 255
		DarkGreen               = RGBA(0x00, 0x64, 0x00, 0xFF), //    0 100   0 255
		YellowGreen             = RGBA(0x9A, 0xCD, 0x32, 0xFF), //  154 205  50 255
		OliveDrab               = RGBA(0x6B, 0x8E, 0x23, 0xFF), //  107 142  35 255
		Olive                   = RGBA(0x80, 0x80, 0x00, 0xFF), //  128 128   0 255
		DarkOliveGreen          = RGBA(0x55, 0x6B, 0x2F, 0xFF), //   85 107  47 255
		MediumAquamarine        = RGBA(0x66, 0xCD, 0xAA, 0xFF), //  102 205 170 255
		DarkSeaGreen            = RGBA(0x8F, 0xBC, 0x8F, 0xFF), //  143 188 143 255
		LightSeaGreen           = RGBA(0x20, 0xB2, 0xAA, 0xFF), //   32 178 170 255
		DarkCyan                = RGBA(0x00, 0x8B, 0x8B, 0xFF), //    0 139 139 255
		Teal                    = RGBA(0x00, 0x80, 0x80, 0xFF), //    0 128 128 255

		//  Blue/Cyan colors
		Aqua                    = RGBA(0x00, 0xFF, 0xFF, 0xFF), //    0 255 255 255
		Cyan                    = RGBA(0x00, 0xFF, 0xFF, 0xFF), //    0 255 255 255
		LightCyan               = RGBA(0xE0, 0xFF, 0xFF, 0xFF), //  224 255 255 255
		PaleTurquoise           = RGBA(0xAF, 0xEE, 0xEE, 0xFF), //  175 238 238 255
		Aquamarine              = RGBA(0x7F, 0xFF, 0xD4, 0xFF), //  127 255 212 255
		Turquoise               = RGBA(0x40, 0xE0, 0xD0, 0xFF), //   64 224 208 255
		MediumTurquoise         = RGBA(0x48, 0xD1, 0xCC, 0xFF), //   72 209 204 255
		DarkTurquoise           = RGBA(0x00, 0xCE, 0xD1, 0xFF), //	  0 206 209 255
		CadetBlue               = RGBA(0x5F, 0x9E, 0xA0, 0xFF), //   95 158 160 255
		SteelBlue               = RGBA(0x46, 0x82, 0xB4, 0xFF), //   70 130 180 255
		LightSteelBlue          = RGBA(0xB0, 0xC4, 0xDE, 0xFF), //  176 196 222 255
		PowderBlue              = RGBA(0xB0, 0xE0, 0xE6, 0xFF), //  176 224 230 255
		LightBlue               = RGBA(0xAD, 0xD8, 0xE6, 0xFF), //  173 216 230 255
		SkyBlue                 = RGBA(0x87, 0xCE, 0xEB, 0xFF), //  135 206 235 255
		LightSkyBlue            = RGBA(0x87, 0xCE, 0xFA, 0xFF), //  135 206 250 255
		DeepSkyBlue             = RGBA(0x00, 0xBF, 0xFF, 0xFF), //    0 191 255 255
		DodgerBlue              = RGBA(0x1E, 0x90, 0xFF, 0xFF), //   30 144 255 255
		CornflowerBlue          = RGBA(0x64, 0x95, 0xED, 0xFF), //  100 149 237 255
		RoyalBlue               = RGBA(0x41, 0x69, 0xE1, 0xFF), //   65 105 225 255
		Blue                    = RGBA(0x00, 0x00, 0xFF, 0xFF), //    0   0 255 255
		MediumBlue              = RGBA(0x00, 0x00, 0xCD, 0xFF), //    0   0 205 255
		DarkBlue                = RGBA(0x00, 0x00, 0x8B, 0xFF), //    0   0 139 255
		Navy                    = RGBA(0x00, 0x00, 0x80, 0xFF), //    0   0 128 255
		MidnightBlue            = RGBA(0x19, 0x19, 0x70, 0xFF), //   25  25 112 255

		//  Brown colors
		Cornsilk                = RGBA(0xFF, 0xF8, 0xDC, 0xFF), //  255 248 220 255
		BlanchedAlmond          = RGBA(0xFF, 0xEB, 0xCD, 0xFF), //  255 235 205 255
		Bisque                  = RGBA(0xFF, 0xE4, 0xC4, 0xFF), //  255 228 196 255
		NavajoWhite             = RGBA(0xFF, 0xDE, 0xAD, 0xFF), //  255 222 173 255
		Wheat                   = RGBA(0xF5, 0xDE, 0xB3, 0xFF), //  245 222 179 255
		BurlyWood               = RGBA(0xDE, 0xB8, 0x87, 0xFF), //  222 184 135 255
		Tan                     = RGBA(0xD2, 0xB4, 0x8C, 0xFF), //  210 180 140 255
		RosyBrown               = RGBA(0xBC, 0x8F, 0x8F, 0xFF), //  188 143 143 255
		SandyBrown              = RGBA(0xF4, 0xA4, 0x60, 0xFF), //  244 164  96 255
		Goldenrod               = RGBA(0xDA, 0xA5, 0x20, 0xFF), //  218 165  32 255
		DarkGoldenrod           = RGBA(0xB8, 0x86, 0x0B, 0xFF), //  184 134  11 255
		Peru                    = RGBA(0xCD, 0x85, 0x3F, 0xFF), //  205 133  63 255
		Chocolate               = RGBA(0xD2, 0x69, 0x1E, 0xFF), //  210 105  30 255
		SaddleBrown             = RGBA(0x8B, 0x45, 0x13, 0xFF), //  139  69  19 255
		Sienna                  = RGBA(0xA0, 0x52, 0x2D, 0xFF), //  160  82  45 255
		Brown                   = RGBA(0xA5, 0x2A, 0x2A, 0xFF), //  165  42  42 255
		Maroon                  = RGBA(0x80, 0x00, 0x00, 0xFF), //  128   0   0 255

		//  White colors
		White                   = RGBA(0xFF, 0xFF, 0xFF, 0xFF), //  255 255 255 255
		Snow                    = RGBA(0xFF, 0xFA, 0xFA, 0xFF), //  255 250 250 255
		Honeydew                = RGBA(0xF0, 0xFF, 0xF0, 0xFF), //  240 255 240 255
		MintCream               = RGBA(0xF5, 0xFF, 0xFA, 0xFF), //  245 255 250 255
		Azure                   = RGBA(0xF0, 0xFF, 0xFF, 0xFF), //  240 255 255 255
		AliceBlue               = RGBA(0xF0, 0xF8, 0xFF, 0xFF), //  240 248 255 255
		GhostWhite              = RGBA(0xF8, 0xF8, 0xFF, 0xFF), //  248 248 255 255
		WhiteSmoke              = RGBA(0xF5, 0xF5, 0xF5, 0xFF), //  245 245 245 255
		Seashell                = RGBA(0xFF, 0xF5, 0xEE, 0xFF), //  255 245 238 255
		Beige                   = RGBA(0xF5, 0xF5, 0xDC, 0xFF), //  245 245 220 255
		OldLace                 = RGBA(0xFD, 0xF5, 0xE6, 0xFF), //  253 245 230 255
		FloralWhite             = RGBA(0xFF, 0xFA, 0xF0, 0xFF), //  255 250 240 255
		Ivory                   = RGBA(0xFF, 0xFF, 0xF0, 0xFF), //  255 255 240 255
		AntiqueWhite            = RGBA(0xFA, 0xEB, 0xD7, 0xFF), //  250 235 215 255
		Linen                   = RGBA(0xFA, 0xF0, 0xE6, 0xFF), //  250 240 230 255
		LavenderBlush           = RGBA(0xFF, 0xF0, 0xF5, 0xFF), //  255 240 245 255
		MistyRose               = RGBA(0xFF, 0xE4, 0xE1, 0xFF), //  255 228 225 255

		//  Gray colors
		Gainsboro               = RGBA(0xDC, 0xDC, 0xDC, 0xFF), //  220 220 220 255
		LightGray               = RGBA(0xD3, 0xD3, 0xD3, 0xFF), //  211 211 211 255
		Silver                  = RGBA(0xC0, 0xC0, 0xC0, 0xFF), //  192 192 192 255
		DarkGray                = RGBA(0xA9, 0xA9, 0xA9, 0xFF), //  169 169 169 255
		Gray                    = RGBA(0x80, 0x80, 0x80, 0xFF), //  128 128 128 255
		DimGray                 = RGBA(0x69, 0x69, 0x69, 0xFF), //  105 105 105 255
		LightSlateGray          = RGBA(0x77, 0x88, 0x99, 0xFF), //  119 136 153 255
		SlateGray               = RGBA(0x70, 0x80, 0x90, 0xFF), //  112 128 144 255
		DarkSlateGray           = RGBA(0x2F, 0x4F, 0x4F, 0xFF), //   47  79  79 255
		Black                   = RGBA(0x00, 0x00, 0x00, 0xFF), //	  0   0   0 255
	};

	//  Color4f

	class Color4f
	{

	public:

		Color4f(const Color &color = Black);
		Color4f(const float &r,const float &g,const float &b,const float &a = 1.0f);
		Color4f(const Vec3 &v, const float &a = 1.0f);
		Color4f(const Vec4 &v);

		Color4f&	operator=(const Color4f &u);
		Color4f		operator+(const Color4f &u) const;
		Color4f		operator-(const Color4f &u) const;
		Color4f		operator*(const Color4f &u) const;
		Color4f		operator/(const Color4f &u) const;

		Color4f operator*(const float &u) const;
		Color4f operator/(const float &u) const;
		Color4f operator+()const;
		Color4f operator-()const;

		Color4f&	operator+=(const Color4f &u);
		Color4f&	operator-=(const Color4f &u);
		Color4f&	operator/=(const Color4f &u);
		Color4f&	operator*=(const Color4f &u);
		Color4f&	operator/=(const float u);
		Color4f&	operator*=(const float u);

		bool		operator==(const Color4f &u) const;
		bool		operator!=(const Color4f &u) const;

		Color4f clamp();
		Vec3	vec3() const;
		Vec4	vec4() const;
		Color	color() const;

		friend std::ostream& operator<<(std::ostream& out, const Color4f &u);

		float r, g, b, a;

	};

	//  Functions

	Color   color(const Vec3 &v, const float &a = 1.0f);
	Color   color(const Vec4 &v);
	
	Color4f lerp(const Color4f &u, const Color4f &v, const float &t);
	
}

#endif
