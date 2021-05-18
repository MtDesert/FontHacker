#include"Widget_BitmapFont.h"
#include"DataBlock.h"

#include<QFile>
#include<QMessageBox>
#include<QApplication>
#include<QDebug>

Widget_BitmapFont::Widget_BitmapFont(QWidget *parent):QWidget(parent),xOffset(0),yOffset(28){
	setBitmapSize(32,32);
}

char Widget_BitmapFont::character[3];

void Widget_BitmapFont::charEng(int id){
	character[0]=0x20+id;
	character[1]=0x00;
}
void Widget_BitmapFont::charSymbol(int id){
	character[0]=0xA1+id/94;
	character[1]=0xA1+id%94;
	character[2]=0x00;
}
void Widget_BitmapFont::charLv1Chinese(int id){
	character[0]=0xB0+id/94;
	character[1]=0xA1+id%94;
	character[2]=0x00;
}
void Widget_BitmapFont::charLv2Chinese(int id){
	character[0]=0xD8+id/94;
	character[1]=0xA1+id%94;
	character[2]=0x00;
}

void Widget_BitmapFont::setBitmapSize(int width,int height){
	image=QImage(width,height,QImage::Format_RGBA8888);
	resetFont(font);
}
void Widget_BitmapFont::resetFont(const QFont &f){
	qDebug()<<f;
	font=f;
	font.setPixelSize(font.pointSize());
	font.setStyleStrategy(QFont::NoAntialias);
	drawBitmapFont("A");
}
void Widget_BitmapFont::drawBitmapFont(const char *charCode){
	image.fill(Qt::white);
	//绘图
	QPainter painter(&image);
	painter.setFont(font);
	painter.drawText(xOffset,yOffset,QString::fromLocal8Bit(charCode));
	//显示到控件上
	update();
}

void Widget_BitmapFont::makeBitmapFont(int amount,bool full,function<void(int)> charFunc,const string &filename){
	//计算空间,并申请
	DataBlock fontData;
	auto w=image.width(),h=image.height();
	if(!full)w/=2;//英文的话要减半
	auto totalBit=w*h*amount;//总位数
	auto totalByte = totalBit/8 + (totalBit%8?1:0);//总字节数
	fontData.memoryAllocate(totalByte);
	fontData.memset(0);
	//开始生成
	auto bytePos=0,bitPos=0;
	QColor black(Qt::black),color;
	for(auto a=0;a<amount;++a){
		charFunc(a);
		drawBitmapFont(character);
		for(auto y=h-1;y>=0;--y){
			for(auto x=0;x<w;++x){
				//写数据
				color=image.pixelColor(x,y);
				if(color==black){
					fontData.dataPointer[bytePos]|=(1<<bitPos);
				}
				//下一个位置
				++bitPos;
				if(bitPos>=8){
					++bytePos;
					bitPos=0;
				}
			}
		}
		QApplication::processEvents();//防止界面卡顿
	}
	//保存
	fontData.saveFile(filename);
	fontData.memoryFree();
}
void Widget_BitmapFont::makeAll(){
	makeBitmapFont(0x7F-0x20,false,charEng,"ascii");
	makeBitmapFont(846,true,charSymbol,"lv0");
	makeBitmapFont(3755,true,charLv1Chinese,"lv1");
	makeBitmapFont(3008,true,charLv2Chinese,"lv2");
}

void Widget_BitmapFont::paintEvent(QPaintEvent *ev){
	QPainter pntr(this);
	pntr.drawImage(0,0,image);
	pntr.setPen(QColor(Qt::green));
	pntr.drawRect(image.rect());
}