#ifndef _FUNC_CALLBACK_H_
#define _FUNC_CALLBACK_H_

#include <vtkCommand.h>
#include <QObject>

class vtkPlane;

class FuncCallback :public QObject , public vtkCommand
{
	Q_OBJECT

public:
	static FuncCallback* New();

	virtual void Execute(vtkObject* caller, unsigned long eventId, void* callData);

	vtkPlane* getPlane();
	void setPlane(vtkPlane* plane);

signals:
	void updatePlaneWidgetSig(double* nor, double* org);

private:
	FuncCallback();
	~FuncCallback();

private:
	vtkPlane* _plane{ nullptr };
};

#endif