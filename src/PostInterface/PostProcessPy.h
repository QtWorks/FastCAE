#ifndef _POSTPROCESS_PY_H_
#define _POSTPROCESS_PY_H_

#include "PostInterfaceAPI.h"
#include <QMultiHash>

namespace GUI
{
	class MainWindow;
}

namespace Post {
	class PostTreeWidget;
	class RenderDirector;

	class POSTINTERFACEAPI PostProcessPy
	{
	public:
		PostProcessPy() = default;
		~PostProcessPy() = default;

		static void getBlockData(QMultiHash<int, int>& blockHash, char* blocks);
		static void init(GUI::MainWindow* mw, PostTreeWidget* tree);
		static void setDirector(RenderDirector* dire);
		static void openPostFile(int wID, QString file);
		static void setDisplayMode(int wID, int type);
		static void savePostImage(int wID, QString file);
		static void savePostAnimation(int pID, QString file, int fps);
		static void setBlockColor(QMultiHash<int, int> blocks, QString name, int type, int component, double red, double green, double blue, bool isVariable);
		static void createClip(int parentID, QMultiHash<int,int> blocks, QString name, double* ori, double* nor, bool out);
		static void editClip(int id, QMultiHash<int,int> blocks, QString name, double* ori, double* nor, bool out);
		static void createSlice(int parentID, QMultiHash<int, int> blocks, QString name, double* ori, double* nor);
		static void createISOSurface(int pID, QMultiHash<int, int> blocks, QString name, QString variable, QStringList values);
		static void createISOCurve(int pID, QMultiHash<int, int> blocks, QString name, QString variable, QStringList values);
		static void createVector(int pID, QMultiHash<int, int> blocks, QString name, QString vector, int maxNumber,
			int scaleMode, double scaleFactor, bool isPointData);
		static void createStreamLine(int pID, QMultiHash<int, int> blocks, QString name, QString vector, double* start, double* end, int seeds,
			double maxLength, double initStep, double minStep, double maxStep, int stepNumber, int direction, bool isPointData);
		static void createCalaulate(int pID, QMultiHash<int, int> blocks, QString name, QString func,
			QStringList scalars, QStringList vectors, bool isPointData);
		static void createReflection(int pID, QMultiHash<int, int> blocks, QString name, int plane, double center);
	
		static void runAnimation(int pID, int index);
		static void stopAnimation(int pID, int index);
		static void firstFrame(int pID);
		static void proviousFrame(int pID);
		static void nextFrame(int pID);
		static void lastFrame(int pID);

	private:
		static GUI::MainWindow* _mainWindow;
		static PostTreeWidget* _tree;
		static RenderDirector* _director;
	};
}

extern "C"{
	void POSTINTERFACEAPI openPostFile(int id, char* type, char* file);
	void POSTINTERFACEAPI setDisplayMode(int id, int type);
	void POSTINTERFACEAPI savePostImage(int id, char* file);
	void POSTINTERFACEAPI savePostAnimation(int id, char* file, int fps);
	void POSTINTERFACEAPI setBlockColor(char* blocks, char* name, int type,	int component, 
		double red, double green, double blue, bool isVariable);
	//Function
	void POSTINTERFACEAPI createClip(int pID, char* blocks, char* name, double xOri, double yOri, double zOri,
		double xNor, double yNor, double zNor, bool out);
	void POSTINTERFACEAPI editClip(int id, char* blocks, char* name, double xOri, double yOri, double zOri,
		double xNor, double yNor, double zNor, bool out);
	void POSTINTERFACEAPI createSlice(int pID, char* blocks, char* name, double xOri, double yOri, double zOri,
		double xNor, double yNor, double zNor);
	void POSTINTERFACEAPI createISOSurface(int pID, char* blocks, char* name, char* variable, char* values);
	void POSTINTERFACEAPI createISOCurve(int pID, char* blocks, char* name, char* variable, char* values);
	void POSTINTERFACEAPI createVector(int pID, char* blocks, char* name, char* vector, int maxNumber,
		int scaleMode, double scaleFactor, bool isPointData);
	void POSTINTERFACEAPI createStreamLine(int pID, char* blocks, char* name, char* vector, double xStart,
		double yStart, double zStart, double xEnd, double yEnd, double zEnd, int seeds, double maxLength,
		double initStep, double minStep, double maxStep, int stepNumber, int direction, bool isPointData);
	void POSTINTERFACEAPI createCalaulate(int pID, char* blocks, char* name, char* func,
		char* scalars, char*vectors, bool isPointData);
	void POSTINTERFACEAPI createReflection(int pID, char* blocks, char* name, int plane, double center);
	//animation
	void POSTINTERFACEAPI runAnimation(int pID, int index);
	void POSTINTERFACEAPI stopAnimation(int pID, int index);
	void POSTINTERFACEAPI firstFrame(int pID);
	void POSTINTERFACEAPI proviousFrame(int pID);
	void POSTINTERFACEAPI nextFrame(int pID);
	void POSTINTERFACEAPI lastFrame(int pID);
}

#endif