#ifndef WIDGET_BITMAPFONT_H
#define WIDGET_BITMAPFONT_H

#include<QWidget>
#include<QFont>
#include<QImage>
#include<QPainter>

#include<functional>
using namespace std;

class Widget_BitmapFont:public QWidget{
	static char character[3];//字符代码,用于给QPainter进行文字绘制
	static void charEng(int id);
	static void charSymbol(int id);
	static void charLv1Chinese(int id);
	static void charLv2Chinese(int id);
public:
	explicit Widget_BitmapFont(QWidget *parent=NULL);

	QFont font;//字体
	QImage image;//图像
	int xOffset,yOffset;//y偏移,针对上下空白的字体进行调整

	void setBitmapSize(int width,int height);
	void resetFont(const QFont &f);
	void drawBitmapFont(const char *charCode);

	void makeBitmapFont(int amount,bool full,function<void(int)> charFunc,const string &filename);//制造英文字模
	void makeAll();
protected:
	void paintEvent(QPaintEvent*);
};
#endif