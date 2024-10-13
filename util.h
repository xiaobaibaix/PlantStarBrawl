#pragma once
#include <graphics.h>
#include <time.h>

#include "Camera.h"
#include "Vector2D.h"

#pragma comment(lib,"MSIMG32.LIB")

inline void flip_image(IMAGE* src,IMAGE* dst){//·­×ªÍ¼Æ¬s
	const int w = src->getwidth();
	const int h = src->getheight();

	Resize(dst, w, h);
	DWORD* src_buffer = GetImageBuffer(src);
	DWORD* dst_buffer = GetImageBuffer(dst);

	for (int y = 0;y < h;y++) {
		for (int x = 0;x < w;x++) {
			int idx_src = y * w + x;
			int idx_dst = y * w + (w-x-1);
			dst_buffer[idx_dst] = src_buffer[idx_src];
		}
	}
}

inline void putImage_alpha(int dst_x, int dst_y, IMAGE* img) {
	const int w = img->getwidth();
	const int h = img->getheight();
	AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

inline void putImage_alpha(const Camera& camera, int dst_x, int dst_y, IMAGE* img) {
	const int w = img->getwidth();
	const int h = img->getheight();
	const Vector2D& pos = camera.get_position();
	AlphaBlend(GetImageHDC(GetWorkingImage()), (int)(dst_x- pos.x), (int)(dst_y-pos.y), w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

inline void putImage_alpha(int dst_x, int dst_y, int wi, int hi, int src_x, int src_y, IMAGE* img) {
	const int w = wi>0 ? wi:img->getwidth();
	const int h = hi>0 ? hi:img->getheight();
	AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x,dst_y, w, h,
		GetImageHDC(img), src_x, src_y, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

inline void line(const Camera& camera,int x1,int y1,int x2,int y2) {
	const Vector2D& pos = camera.get_position();
	line((int)(x1-pos.x),(int)(y1-pos.y), (int)(x2 - pos.x), (int)(y2 - pos.y));
}

inline void drawRect(const Camera& camera, Point p1, Point p2)
{
	line(camera, p1.x, p1.y, p2.x, p1.y);
	line(camera, p1.x, p1.y, p1.x, p2.y);
	line(camera, p2.x, p1.y, p2.x, p2.y);
	line(camera, p1.x, p2.y, p2.x, p2.y);
}
