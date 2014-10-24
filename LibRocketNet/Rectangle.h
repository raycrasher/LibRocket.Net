#pragma once

#include "Vector2.h"

using namespace System;

namespace LibRocketNet {

	public value class RectangleF {
	public:

		RectangleF(float l, float t, float w, float h) {
			Left = l;
			Top = t;
			Width = w;
			Height = h;
		}

		property float Right { 
			float get() {
				return Left + Width;
			}

			void set(float v){
				Width = v - Left;
			}
		}

		property float Bottom {
			float get() {
				return Top + Height;
			}

			void set(float v){
				Height = v - Top;
			}
		}

		float Left, Top, Width, Height;

		static RectangleF FromLTRB(float l, float t, float r, float b) {
			return RectangleF(l, t, r - l, b - t);
		}
	};

	public value class RectangleI {
	public:

		RectangleI(int l, int t, int w, int h) {
			Left = l;
			Top = t;
			Width = w;
			Height = h;
		}

		property int Right {
			int get() {
				return Left + Width;
			}

			void set(int v){
				Width = v - Left;
			}
		}

		property int Bottom {
			int get() {
				return Top + Height;
			}

			void set(int v){
				Height = v - Top;
			}
		}

		int Left, Top, Width, Height;

		static RectangleI FromLTRB(int l, int t, int r, int b) {
			return RectangleI(l, t, r - l, b - t);
		}
	};

}