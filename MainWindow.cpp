#include "MainWindow.h"

#include<QImage>
#include<QPainter>
#include<QTextCodec>
#include<QKeyEvent>

#include<QInputDialog>
#include<QFontDialog>

#include<QDebug>

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent){
	fontDialog.setObjectName(QString::fromUtf8("fontDialog"));//为了自动连接信号槽
	fontDialog.setParent(this);
	fontDialog.hide();
	setupUi(this);
	//初始化工作
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("gb2312"));
	centerWidget->addTab(&widgetBitmapFont,tr("效果图"));
	widgetBitmapFont.resetFont(fontDialog.currentFont());
}
MainWindow::~MainWindow(){}

//信号槽
void MainWindow::on_action_BitmapFontSize_triggered(){
	auto size=widgetBitmapFont.image.size();
	bool ok;
	int w=QInputDialog::getInt(this,tr("Width"),tr("字模宽度"),size.width(),8,256,1,&ok);
	if(!ok)return;
	int h=QInputDialog::getInt(this,tr("Height"),tr("字模高度"),size.height(),8,256,1,&ok);
	if(!ok)return;
	//调整
	widgetBitmapFont.setBitmapSize(w,h);
}
void MainWindow::on_action_FontSelect_triggered(){
	fontDialog.show();
}

void MainWindow::on_fontDialog_currentFontChanged(QFont f){
	widgetBitmapFont.resetFont(f);
	update();
}
void MainWindow::on_fontDialog_fontSelected(QFont f){
	widgetBitmapFont.makeAll();
}

void MainWindow::keyReleaseEvent(QKeyEvent *ev){
	auto &xOffset(widgetBitmapFont.xOffset),&yOffset(widgetBitmapFont.yOffset);
	switch(ev->key()){
		case Qt::Key_Left:--xOffset;break;
		case Qt::Key_Right:++xOffset;break;
		case Qt::Key_Up:--yOffset;break;
		case Qt::Key_Down:++yOffset;break;
		case Qt::Key_Backspace:xOffset=yOffset=0;break;
		default:;
	}
	qDebug()<<yOffset;
	//重新绘图
	widgetBitmapFont.font=fontDialog.currentFont();
	on_fontDialog_currentFontChanged(widgetBitmapFont.font);
}
void MainWindow::closeEvent(QCloseEvent *ev){fontDialog.close();}