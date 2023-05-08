#ifndef _ANITHREAD_H_
#define _ANITHREAD_H_

#include <QThread>
#include <QQueue>
#include <QMutex>
#include <QStringList>
#include "PostRenderData/Macros.hxx"

ForwardDeclarNS(Post,RenderDataImportUnSteady)

extern QMutex g_mutex;
extern QQueue<Post::RenderDataImportUnSteady*> g_qUnSteady;

namespace Post {

	class AniThread : public QThread
	{
	public:
		Q_OBJECT
	public:
		AniThread();
		~AniThread();

		void initThread(int frame_xh, int max_frames, RenderDataImportUnSteady* unSteady);
		void stop(bool flag);

		void run() override;

	private:
		// 停止标志
		volatile bool stopped{ false };

		// 最大帧序号 序号从0开始
		int _maxFrameNum{ 0 };

		// 当前帧序号
		int _currFrameNum{ 0 };

		// 当前数据对象
		RenderDataImportUnSteady* _unSteadyObj{};

		// 文件列表
		QStringList _fileList{};
	};
}
#endif
