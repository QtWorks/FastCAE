#ifndef _ANIGLOBALVAR_H_
#define _ANIGLOBALVAR_H_

//生成动画结构体
typedef struct aviSetting
{
	int frameRate;		//帧率
	QString aviFilePath;//动画保存路径
	bool saveFlag;		//是否保存动画
	
	aviSetting()
	{
		frameRate = 15;
		aviFilePath = "";
		saveFlag = false;
	}
}AviSetting;

#endif
